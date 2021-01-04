#ifndef NASHBE_PORT_H
#define NASHBE_PORT_H

#ifdef __cplusplus__
extern "C"{
#endif

// supported general architectures
#undef SYS_ARCH_X86
#undef SYS_ARCH_X86_64
#undef SYS_ARCH_ARM
#undef SYS_ARCH_ARM64
#undef SYS_ARCH_MIPS
#undef SYS_ARCH_PPC
// supported general compilers
#undef SYS_COMP_GCC
#undef SYS_COMP_MSVC
#undef SYS_COMP_ICC
#undef SYS_COMP_CLANG
#undef SYS_COMP_LLVM
#undef SYS_COMP_MINGW
// supported general operating systems
#undef SYS_OS_WIN32
#undef SYS_OS_WIN64
#undef SYS_OS_MACOS
#undef SYS_OS_MACOSX
#undef SYS_OS_LINUX
#undef SYS_OS_POSIX

// GNUC macro checks
#if defined(__i386) || defined(i386) || defined(__i386__)
    #define SYS_ARCH_X86
#elif defined(__x86_64) || defined(__x86_64__) || defined(__amd64) || \
    defined(__amd64__)
    #define SYS_ARCH_X86_64
#elif defined(__arm__)
    #define SYS_ARCH_ARM
#elif defined(__aarch64__)
    #define SYS_ARCH_ARM64
#elif defined(__mips__) || defined(mips)
    #define SYS_ARCH_MIPS
#elif defined(_powerpc) || defined(__powerpc__) || defined(__ppc__) || \
    defined(__powerpc64__) || defined(__POWERPC__) || defined(__ppc64) || \
    defined(__PPC__) || defined(__PPC64__) || defined(_ARCH_PPC) || defined(_ARCH_PPC64)
    #define SYS_ARCH_PPC
#endif

// MSC_VER macro checks
#if defined(_M_IX86)
    #define SYS_ARCH_X86
#elif defined(_M_X64) || defined(_M_AMD64)
    #define SYS_ARCH_X86_64
#elif defined(_M_PPC)
    #define SYS_ARCH_PPC
#elif defined(_M_ARM64)
    #define SYS_ARCH_ARM64
#elif defined(_M_ARM)
    #define SYS_ARCH_ARM
#endif
// NOTE: Windows build for MIPS and PowerPC (PPC) were dropped in 2000.

#if defined(__GNUC__) && !defined(__clang__)
    #define SYS_COMP_GCC
#elif defined(__clang__)
    #define SYS_COMP_CLANG
#elif defined(__MINGW32__) || defined(__MINGW64)
    #define SYS_COMP_MINGW
#elif defined(_MSC_VER)
    #define SYS_COMP_MSVC
#elif defined(__INTEL_COMPILER) || defined(ICL)
    #define SYS_COMP_ICC
#endif

#if defined(_WIN64) || defined(__WIN64__)
    #define SYS_OS_WIN64
#elif defined(_WIN32) || defined(__WIN32__)
    #define SYS_OS_WIN32
#elif defined(__APPLE__) && defined(__MACH__)
    #define SYS_OS_MACOSX
#elif defined(macintosh) || defined(Macintosh)
    #define SYS_OS_MACOS
#elif defined(__linux__)
    #define SYS_OS_LINUX
#endif

#ifdef __cplusplus__
}
#endif

#endif
