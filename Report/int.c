    #define __NR_getpid 20
    asm volatile
    (
        "int \$0x80"
        : "=a" (pid)
        : "0"(__NR_getpid)
        : "cc", "edi", "esi", "memory"
    );
