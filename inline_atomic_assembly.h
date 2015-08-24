// This code has been tested in Redhat Linux 6.
// About the atomic functions more, refer to the article below.
// http://stackoverflow.com/questions/2287451/how-to-perform-atomic-operations-on-linux-that-work-on-x86-arm-gcc-and-icc

__inline__
int atomic_cas32( volatile void*  aAddr,
                    volatile int    aWith,
                    volatile int    aCmp )
{
    int     sPrev;

    __asm__ __volatile__ ( "lock; cmpxchgl %1,%2"
                          : "=a"(sPrev)
                          : "r"(aWith),
                            "m"(*(volatile int*)aAddr),
                            "0"(aCmp)
                          : "memory" );
    return sPrev;
}


__inline__
int atomic_set32( volatile void* aAddr, volatile int aVal )
{
    __asm__ __volatile__ ( "xchgl %0,%1"
                          : "=r"(aVal)
                          : "m"(*(volatile int*)aAddr), "0"(aVal)
                          : "memory" );
    return aVal;
}


__inline__
int atomic_add32( volatile void* aAddr, volatile int aVal )
{
    int     sTemp = aVal;

    __asm__ __volatile__ ( "lock; xaddl %0,%1"
                          : "+r"(sTemp), "+m"(*(volatile int*)aAddr)
                          :
                          : "memory" );
    return sTemp + aVal;
}


__inline__
long long atomic_cas64( volatile void* aAddr, volatile long long  aWith, volatile long long  aCmp )
{
    long long sPrev;

    __asm__ __volatile__ ( "lock; cmpxchgq %1,%2"
                          : "=a"(sPrev)
                          : "r"(aWith),
                            "m"(*(volatile long long*)aAddr),
                            "0"(aCmp)
                          : "memory" );
    return sPrev;
}


__inline__
long long atomic_get64( volatile void* aAddr )
{
    return *(volatile long long*)aAddr;
}


__inline__
long long atomic_set64( volatile void* aAddr, volatile long long aVal )
{
    __asm__ __volatile__ ( "xchgq %0,%1"
                          : "=r"(aVal)
                          : "m"(*(volatile long long*)aAddr), "0"(aVal)
                          : "memory" );
    return aVal;
}


__inline__
long long atomic_add64( volatile void* aAddr, volatile long long aVal )
{
    long long sPrev = aVal;

    __asm__ __volatile__ ("lock; xaddq %0,%1"
                          : "+r"(sPrev), "+m"(*(volatile long long*)aAddr)
                          :
                          : "memory");
    return sPrev + aVal;
}

__inline__
int atomic_get32 ( volatile void* aAddr )
{
    return *(volatile int*) aAddr;
}

__inline__
int atomic_inc32 ( volatile void* aAddr )
{
    return atomicAdd32 ( aAddr, 1 );
}

__inline__
int atomic_dec32 ( volatile void* aAddr )
{
    return atomicAdd32 ( aAddr, -1 );
}

__inline__
long long atomic_inc64 ( volatile void* aAddr )
{
    return atomicAdd64 ( aAddr, 1 );
}

__inline__
long long atomic_dec64 ( volatile void* aAddr )
{
    return atomicAdd64 ( aAddr, -1 );
}
