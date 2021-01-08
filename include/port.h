#ifndef NASHBE_PORT_H
#define NASHBE_PORT_H

#ifdef __cplusplus__
extern "C"{
#endif

#undef PORT_SYS_ARCH
#undef PORT_SYS_COMP
#undef PORT_SYS_OS

// supported general architectures
#define SYS_ARCH_X86    0
#define SYS_ARCH_X86_64 1
#define SYS_ARCH_ARM    2
#define SYS_ARCH_ARM64  3
#define SYS_ARCH_MIPS   4
#define SYS_ARCH_PPC    5
// supported general compilers
#define SYS_COMP_GCC    0
#define SYS_COMP_MSVC   1
#define SYS_COMP_ICC    2
#define SYS_COMP_CLANG  3
#define SYS_COMP_LLVM   4
#define SYS_COMP_MINGW  5
// supported general operating systems
#define SYS_OS_WIN32    0
#define SYS_OS_WIN64    1
#define SYS_OS_MACOS    2
#define SYS_OS_MACOSX   3
#define SYS_OS_LINUX    4
#define SYS_OS_POSIX    5

// GNUC architecture macro checks
#if defined(__i386) || defined(i386) || defined(__i386__)
    #define PORT_SYS_ARCH SYS_ARCH_X86
#elif defined(__x86_64) || defined(__x86_64__) || defined(__amd64) || \
    defined(__amd64__)
    #define PORT_SYS_ARCH SYS_ARCH_X86_64
#elif defined(__arm__)
    #define PORT_SYS_ARCH SYS_ARCH_ARM
#elif defined(__aarch64__)
    #define PORT_SYS_ARCH SYS_ARCH_ARM64
#elif defined(__mips__) || defined(mips)
    #define PORT_SYS_ARCH SYS_ARCH_MIPS
#elif defined(_powerpc) || defined(__powerpc__) || defined(__ppc__) || \
    defined(__powerpc64__) || defined(__POWERPC__) || defined(__ppc64) || \
    defined(__PPC__) || defined(__PPC64__) || defined(_ARCH_PPC) || defined(_ARCH_PPC64)
    #define PORT_SYS_ARCH SYS_ARCH_PPC
#endif

// MSC_VER architecture macro checks
#if defined(_M_IX86)
    #define PORT_SYS_ARCH SYS_ARCH_X86
#elif defined(_M_X64) || defined(_M_AMD64)
    #define PORT_SYS_ARCH SYS_ARCH_X86_64
#elif defined(_M_PPC)
    #define PORT_SYS_ARCH SYS_ARCH_PPC
#elif defined(_M_ARM64)
    #define PORT_SYS_ARCH SYS_ARCH_ARM64
#elif defined(_M_ARM)
    #define PORT_SYS_ARCH SYS_ARCH_ARM
#endif
// NOTE: Windows build for MIPS and PowerPC (PPC) were dropped in 2000.

// Compiler macro checks
#if defined(__GNUC__) && !defined(__clang__)
    #define PORT_SYS_COMP SYS_COMP_GCC
#elif defined(__clang__)
    #define PORT_SYS_COMP SYS_COMP_CLANG
#elif defined(__MINGW32__) || defined(__MINGW64)
    #define PORT_SYS_COMP SYS_COMP_MINGW
#elif defined(_MSC_VER)
    #define PORT_SYS_COMP SYS_COMP_MSVC
#elif defined(__INTEL_COMPILER) || defined(ICL)
    #define PORT_SYS_COMP SYS_COMP_ICC
#endif

// Operating system macro checks
#if defined(_WIN64) || defined(__WIN64__)
    #define PORT_SYS_OS SYS_OS_WIN64
#elif defined(_WIN32) || defined(__WIN32__)
    #define PORT_SYS_OS SYS_OS_WIN32
#elif defined(__APPLE__) && defined(__MACH__)
    #define PORT_SYS_OS SYS_OS_MACOSX
#elif defined(macintosh) || defined(Macintosh)
    #define PORT_SYS_OS SYS_OS_MACOS
#elif defined(__linux__)
    #define PORT_SYS_OS SYS_OS_LINUX
#endif

#ifdef __cplusplus__
}
#endif

#endif
