/*
 * Copyright (c) 2010-2015 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief Kernel swapper code for IA-32
 *
 * This module implements the __swap() routine for the IA-32 architecture.
 */

#include <kernel_structs.h>
#include <arch/x86/ia32/asm.h>
#include <offsets_short.h>

	/* exports (internal APIs) */

	GTEXT(__swap)
	GTEXT(z_x86_thread_entry_wrapper)
	GTEXT(_x86_user_thread_entry_wrapper)

	/* externs */
#if !defined(CONFIG_X86_KPTI) && defined(CONFIG_X86_USERSPACE)
	GTEXT(z_x86_swap_update_page_tables)
#endif
	GDATA(_k_neg_eagain)

/**
 *
 * @brief Initiate a cooperative context switch
 *
 * The __swap() routine is invoked by various kernel services to effect
 * a cooperative context switch.  Prior to invoking __swap(), the
 * caller disables interrupts (via irq_lock) and the return 'key'
 * is passed as a parameter to __swap().  The 'key' actually represents
 * the EFLAGS register prior to disabling interrupts via a 'cli' instruction.
 *
 * Given that __swap() is called to effect a cooperative context switch, only
 * the non-volatile integer registers need to be saved in the TCS of the
 * outgoing thread.  The restoration of the integer registers of the incoming
 * thread depends on whether that thread was preemptively context switched out.
 * The _INT_ACTIVE and _EXC_ACTIVE bits in the k_thread->thread_state field
 * will signify that the thread was preemptively context switched out, and thus
 * both the volatile and non-volatile integer registers need to be restored.
 *
 * The non-volatile registers need to be scrubbed to ensure they contain no
 * sensitive information that could compromise system security.  This is to
 * make sure that information will not be leaked from one application to
 * another via these volatile registers.
 *
 * Here, the integer registers (EAX, ECX, EDX) have been scrubbed.  Any changes
 * to this routine that alter the values of these registers MUST be reviewed
 * for potential security impacts.
 *
 * Floating point registers are handled using a lazy save/restore
 * mechanism since it's expected relatively few threads will be created
 * with the K_FP_REGS or K_SSE_REGS option bits.  The kernel data structure
 * maintains a 'current_fp' field to keep track of the thread that "owns"
 * the floating point registers.  Floating point registers consist of
 * ST0->ST7 (x87 FPU and MMX registers) and XMM0 -> XMM7.
 *
 * All floating point registers are considered 'volatile' thus they will
 * only be saved/restored when a preemptive context switch occurs.
 *
 * Floating point registers are currently NOT scrubbed, and are subject to
 * potential security leaks.
 *
 * @return -EAGAIN, or a return value set by a call to
 * z_set_thread_return_value()
 *
 * C function prototype:
 *
 * unsigned int __swap (unsigned int eflags);
 *
 */

.macro read_tsc var_name
	push %eax
	push %edx
	rdtsc
	mov %eax,\var_name
	mov %edx,\var_name+4
	pop %edx
	pop %eax
.endm
SECTION_FUNC(TEXT, __swap)
#ifdef CONFIG_EXECUTION_BENCHMARKING
	/* Save the eax and edx registers before reading the time stamp
	* once done pop the values.
	*/
	push %eax
	push %edx
	rdtsc
	mov %eax,__start_swap_time
	mov %edx,__start_swap_time+4
	pop %edx
	pop %eax
#endif
#ifdef CONFIG_X86_IAMCU
	/* save EFLAGS on stack right before return address, just as SYSV would
	 * have done
	 */
	pushl	0(%esp)
	movl	%eax, 4(%esp)
#endif
	/*
	 * Push all non-volatile registers onto the stack; do not copy
	 * any of these registers into the k_thread.  Only the 'esp' register
	 * after all the pushes have been performed) will be stored in the
	 * k_thread.
	 */

	pushl	%edi

	movl	$_kernel, %edi

	pushl	%esi
	pushl	%ebx
	pushl	%ebp

	/*
	 * Carve space for the return value. Setting it to a default of
	 * -EAGAIN eliminates the need for the timeout code to set it.
	 * If another value is ever needed, it can be modified with
	 * z_set_thread_return_value().
	 */

	pushl   _k_neg_eagain


	/* save esp into k_thread structure */

	movl	_kernel_offset_to_current(%edi), %edx
	movl	%esp, _thread_offset_to_esp(%edx)

#ifdef CONFIG_TRACING
	/* Register the context switch */
	push %edx
	call	z_sys_trace_thread_switched_in
	pop %edx
#endif
	movl	_kernel_offset_to_ready_q_cache(%edi), %eax

	/*
	 * At this point, the %eax register contains the 'k_thread *' of the
	 * thread to be swapped in, and %edi still contains &_kernel. %edx
	 * has the pointer to the outgoing thread.
	 */
#if defined(CONFIG_X86_USERSPACE) && !defined(CONFIG_X86_KPTI)

#ifdef CONFIG_X86_IAMCU
	push	%eax
#else
	push	%eax
#endif
	call	z_x86_swap_update_page_tables
#ifdef CONFIG_X86_IAMCU
	pop	%eax
#else
	pop	%eax
#endif
	/* Page tables updated. All memory access after this point needs to be
	 * to memory that has the same mappings and access attributes wrt
	 * supervisor mode!
	 */
#endif

#ifdef CONFIG_EAGER_FP_SHARING
	/* Eager floating point state restore logic
	 *
	 * Addresses CVE-2018-3665
	 * Used as an alternate to CONFIG_LAZY_FP_SHARING if there is any
	 * sensitive data in the floating point/SIMD registers in a system
	 * with untrusted threads.
	 *
	 * Unconditionally save/restore floating point registers on context
	 * switch.
	 */
	/* Save outgpoing thread context */
#ifdef CONFIG_SSE
	fxsave	_thread_offset_to_preempFloatReg(%edx)
	fninit
#else
	fnsave	 _thread_offset_to_preempFloatReg(%edx)
#endif
	/* Restore incoming thread context */
#ifdef CONFIG_SSE
	fxrstor _thread_offset_to_preempFloatReg(%eax)
#else
	frstor _thread_offset_to_preempFloatReg(%eax)
#endif /* CONFIG_SSE */
#elif defined(CONFIG_LAZY_FP_SHARING)
	/*
	 * Clear the CR0[TS] bit (in the event the current thread
	 * doesn't have floating point enabled) to prevent the "device not
	 * available" exception when executing the subsequent fxsave/fnsave
	 * and/or fxrstor/frstor instructions.
	 *
	 * Indeed, it's possible that none of the aforementioned instructions
	 * need to be executed, for example, the incoming thread doesn't
	 * utilize floating point operations.  However, the code responsible
	 * for setting the CR0[TS] bit appropriately for the incoming thread
	 * (just after the 'restoreContext_NoFloatSwap' label) will leverage
	 * the fact that the following 'clts' was performed already.
	 */

	clts


	/*
	 * Determine whether the incoming thread utilizes floating point registers
	 * _and_ whether the thread was context switched out preemptively.
	 */

	testb	$_FP_USER_MASK, _thread_offset_to_user_options(%eax)
	je 	restoreContext_NoFloatSwap


	/*
	 * The incoming thread uses floating point registers:
	 * Was it the last thread to use floating point registers?
	 * If so, there there is no need to restore the floating point context.
	 */

	movl	_kernel_offset_to_current_fp(%edi), %ebx
	cmpl	%ebx, %eax
	je	restoreContext_NoFloatSwap


	/*
	 * The incoming thread uses floating point registers and it was _not_
	 * the last thread to use those registers:
	 * Check whether the current FP context actually needs to be saved
	 * before swapping in the context of the incoming thread.
	 */

	testl	%ebx, %ebx
	jz	restoreContext_NoFloatSave


	/*
	 * The incoming thread uses floating point registers and it was _not_
	 * the last thread to use those registers _and_ the current FP context
	 * needs to be saved.
	 *
	 * Given that the ST[0] -> ST[7] and XMM0 -> XMM7 registers are all
	 * 'volatile', only save the registers if the "current FP context"
	 * was preemptively context switched.
	 */

	testb	$_INT_OR_EXC_MASK, _thread_offset_to_thread_state(%ebx)
	je	restoreContext_NoFloatSave


#ifdef CONFIG_SSE
	testb	$K_SSE_REGS, _thread_offset_to_user_options(%ebx)
	je	x87FloatSave

	/*
	 * 'fxsave' does NOT perform an implicit 'fninit', therefore issue an
	 * 'fninit' to ensure a "clean" FPU state for the incoming thread
	 * (for the case when the fxrstor is not executed).
	 */

	fxsave	_thread_offset_to_preempFloatReg(%ebx)
	fninit
	jmp	floatSaveDone

x87FloatSave:
#endif /* CONFIG_SSE */

	/* 'fnsave' performs an implicit 'fninit' after saving state! */

	fnsave	 _thread_offset_to_preempFloatReg(%ebx)

	/* fall through to 'floatSaveDone' */

floatSaveDone:
restoreContext_NoFloatSave:

	/*********************************************************
	 * Restore floating point context of the incoming thread.
	 *********************************************************/

	/*
	 * Again, given that the ST[0] -> ST[7] and XMM0 -> XMM7 registers are
	 * all 'volatile', only restore the registers if the incoming thread
	 * was previously preemptively context switched out.
	 */

	testb   $_INT_OR_EXC_MASK, _thread_offset_to_thread_state(%eax)
	je 	restoreContext_NoFloatRestore

#ifdef CONFIG_SSE
	testb	$K_SSE_REGS, _thread_offset_to_user_options(%eax)
	je	x87FloatRestore

	fxrstor	_thread_offset_to_preempFloatReg(%eax)
	jmp	floatRestoreDone

x87FloatRestore:

#endif /* CONFIG_SSE */

	frstor	_thread_offset_to_preempFloatReg(%eax)

	/* fall through to 'floatRestoreDone' */

floatRestoreDone:
restoreContext_NoFloatRestore:

	/* record that the incoming thread "owns" the floating point registers */

	movl	%eax, _kernel_offset_to_current_fp(%edi)


	/*
	 * Branch point when none of the floating point registers need to be
	 * swapped because: a) the incoming thread does not use them OR
	 * b) the incoming thread is the last thread that used those registers.
	 */

restoreContext_NoFloatSwap:

	/*
	 * Leave CR0[TS] clear if incoming thread utilizes the floating point
	 * registers
	 */

	testb	$_FP_USER_MASK, _thread_offset_to_user_options(%eax)
	jne	CROHandlingDone

	/*
	 * The incoming thread does NOT currently utilize the floating point
	 * registers, so set CR0[TS] to ensure the "device not available"
	 * exception occurs on the first attempt to access a x87 FPU, MMX,
	 * or XMM register.
	 */

	movl %cr0, %edx
	orl $0x8, %edx
	movl %edx, %cr0

CROHandlingDone:

#endif /* CONFIG_LAZY_FP_SHARING */

	/* update _kernel.current to reflect incoming thread */

	movl    %eax, _kernel_offset_to_current(%edi)

	/* recover thread stack pointer from k_thread */

	movl	_thread_offset_to_esp(%eax), %esp


	/* load return value from a possible z_set_thread_return_value() */

	popl	%eax

	/* pop the non-volatile registers from the stack */

	popl	%ebp
	popl	%ebx
	popl	%esi
	popl	%edi

	/*
	 * %eax may contain one of these values:
	 *
	 * - the return value for __swap() that was set up by a call to
	 * z_set_thread_return_value()
	 * - -EINVAL
	 */

	/* Utilize the 'eflags' parameter to __swap() */

	pushl	4(%esp)
	popfl
#if CONFIG_X86_IAMCU
	/* Remember that eflags we stuck into the stack before the return
	 * address? need to get it out of there since the calling convention
	 * will not do that for us.
	 */
	popl	%edx
	movl	%edx, (%esp)
#endif

#ifdef CONFIG_EXECUTION_BENCHMARKING
	/* Save the eax and edx registers before reading the time stamp
	* once done pop the values.
	*/
	cmp $0x1,__read_swap_end_time_value
	jne time_read_not_needed
	movw $0x2,__read_swap_end_time_value
	read_tsc __common_var_swap_end_time
	pushl __start_swap_time
	popl __temp_start_swap_time
time_read_not_needed:
#endif
	ret

#ifdef _THREAD_WRAPPER_REQUIRED
/**
 *
 * @brief Adjust stack/parameters before invoking thread entry function
 *
 * This function adjusts the initial stack frame created by z_new_thread() such
 * that the GDB stack frame unwinders recognize it as the outermost frame in
 * the thread's stack.  For targets that use the IAMCU calling convention, the
 * first three arguments are popped into eax, edx, and ecx. The function then
 * jumps to z_thread_entry().
 *
 * GDB normally stops unwinding a stack when it detects that it has
 * reached a function called main().  Kernel threads, however, do not have
 * a main() function, and there does not appear to be a simple way of stopping
 * the unwinding of the stack.
 *
 * SYS V Systems:
 *
 * Given the initial thread created by z_new_thread(), GDB expects to find a
 * return address on the stack immediately above the thread entry routine
 * z_thread_entry, in the location occupied by the initial EFLAGS.
 * GDB attempts to examine the memory at this return address, which typically
 * results in an invalid access to page 0 of memory.
 *
 * This function overwrites the initial EFLAGS with zero.  When GDB subsequently
 * attempts to examine memory at address zero, the PeekPoke driver detects
 * an invalid access to address zero and returns an error, which causes the
 * GDB stack unwinder to stop somewhat gracefully.
 *
 * The initial EFLAGS cannot be overwritten until after z_swap() has swapped in
 * the new thread for the first time.  This routine is called by z_swap() the
 * first time that the new thread is swapped in, and it jumps to
 * z_thread_entry after it has done its work.
 *
 * IAMCU Systems:
 *
 * There is no EFLAGS on the stack when we get here. z_thread_entry() takes
 * four arguments, and we need to pop off the first three into the
 * appropriate registers. Instead of using the 'call' instruction, we push
 * a NULL return address onto the stack and jump into z_thread_entry,
 * ensuring the stack won't be unwound further. Placing some kind of return
 * address on the stack is mandatory so this isn't conditionally compiled.
 *
 *       __________________
 *      |      param3      |   <------ Top of the stack
 *      |__________________|
 *      |      param2      |           Stack Grows Down
 *      |__________________|                  |
 *      |      param1      |                  V
 *      |__________________|
 *      |      pEntry      |  <----   ESP when invoked by z_swap() on IAMCU
 *      |__________________|
 *      | initial EFLAGS   |  <----   ESP when invoked by z_swap() on Sys V
 *      |__________________|             (Zeroed by this routine on Sys V)
 *
 * The address of the thread entry function needs to be in %edi when this is
 * invoked. It will either be z_thread_entry, or if userspace is enabled,
 * _arch_drop_to_user_mode if this is a user thread.
 *
 * @return this routine does NOT return.
 */

SECTION_FUNC(TEXT, z_x86_thread_entry_wrapper)
#ifdef CONFIG_X86_IAMCU
	/* IAMCU calling convention has first 3 arguments supplied in
	 * registers not the stack
	 */
	pop	%eax
	pop	%edx
	pop	%ecx
	push	$0	 /* Null return address */
#endif
	movl	$0, (%esp)
	INDIRECT_JMP(%edi)
#endif /* _THREAD_WRAPPER_REQUIRED */
