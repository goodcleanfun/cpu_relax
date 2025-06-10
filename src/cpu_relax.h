#ifndef CPU_RELAX_H
#define CPU_RELAX_H

#if defined(__SSE2__)
#include <emmintrin.h>
#endif

static inline void cpu_relax(void) {
#if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) || defined(_M_X64) || defined(_M_AMD64) || \
    defined(_M_IX86) || defined(__I86__) || defined(i686) || defined(__i686) || defined(__i686__) || \
    defined(i586) || defined(__i586) || defined(__i586__) || \
    defined(i486) || defined(__i486) || defined(__i486__) || \
    defined(i386) || defined(__i386) || defined(__i386__) || \
    defined(_X86_) || defined(__X86__) || defined(__THW_INTEL__)
  #if defined(__SSE2__)
    _mm_pause();
  #elif defined(_MSC_VER)
    __asm pause;
  #else
    __asm__ __volatile__("pause");
  #endif
#elif defined(__aarch64__) || defined(_M_ARM64)
  #if defined(_MSC_VER)
    __isb(_ARM64_BARRIER_SY);
  #else
    __asm__ __volatile__("isb\n");
  #endif
#elif defined(__ARM_ARCH) || defined(_M_ARM) || defined(__arm__) || defined(__thumb__) || defined(__TARGET_ARCH_ARM) || defined(_ARM)
  #if defined(_MSC_VER)
    __yield();
  #else
    __asm__ __volatile__("yield");
  #endif
#elif defined(__powerpc) || defined(__powerpc__) || defined(__POWERPC__) || defined(__ppc__) || defined(__PPC__) || defined(_ARCH_PPC) || defined(__ppc)
  __asm__ __volatile__("or 27,27,27" ::: "memory");
#elif defined(__riscv) || defined(__riscv__)
  #if defined(__riscv_pause)
    __builtin_riscv_pause();
  #else
    __asm__ __volatile__("nop");
  #endif
#elif defined(__loongarch32) || defined(__loongarch64)
  __asm__ __volatile__("nop");
#elif defined(__wasm__)
  __asm__ __volatile__("nop");
#endif
}

#endif