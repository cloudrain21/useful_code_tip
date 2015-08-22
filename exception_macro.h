/*
 * This is gatherings of various exception macros.
 */
#ifndef __EXCEPTION_MACRO_H__
#define __EXCEPTION_MACRO_H__


////////////////////////////////////////////////////////////////////////////////
// common for compilers
////////////////////////////////////////////////////////////////////////////////
#ifndef __cplusplus
#define true    1
#define false   0
typedef int     bool;
#endif

#ifndef TRUE
#define TRUE    1
#define FALSE   0
#endif

////////////////////////////////////////////////////////////////////////////////
// Exception Handling
////////////////////////////////////////////////////////////////////////////////
#ifndef __TRY_MACRO__
#define __TRY_MACRO__

#define _TRY                int _rc=0, _line=0;
#define _CATCH              if ( likely ( _rc == 0 || _line == 0 ) ) goto _finally; _catch: NULL;
#define _FINALLY            if ( unlikely ( _rc != 0 ) ) _finally: NULL;

#define _END                { return _rc; }
#define _ENDVOID            { return; }
#define _ENDNULL            { return NULL; }
#define _ENDBOOL            { return TRUE; }

// For using _EXCEPTION and _CATCH at the same time
#define _BEGIN_SUB_CATCH    goto _end_sub_catch;
#define _SUB_CATCH(x)       goto _end_sub_catch; x:
#define _END_SUB_CATCH      _end_sub_catch:
#define _IF_RAISE2(exp,x)   if ( unlikely(exp) ) { _line=__LINE__; goto x; }
#define _RAISE2(x)          { _line=__LINE__; goto x; }

#define _VOID               int   /* 0:succ, n:fail */
#define _BOOL               int   /* 1:succ, 0:fail */
#define _CALL(x)            if ( unlikely( (_rc=(x)) != 0 ) )  _THROW(_rc)
#define _RETURN             { _rc = 0; goto _finally; }

#define _THROW(x)           { _rc = x; _line=__LINE__; goto _catch; }
#if 0 //def _DEBUG
#undef  _THROW
#define _THROW(x)           { if (!x)  { _PRT( "%s:%d _THROW(0) detected\n", __FILE__, __LINE__ ); _DASSERT(0); } _rc = x; _line=__LINE__; goto _catch; }
#endif

#define _TEST_THROW(exp,x)  if ( unlikely( !(exp) ) ) _THROW(x)
#define _IF_THROW(exp,x)    if ( unlikely(exp) ) _THROW(x)

#define _EXIT(x)            { log_flush(); exit(x); }
#define _ASSERT(x)          if ( unlikely( !(x) ) ) { _PRT("assert occur(%s) on %s:%d (err=%d,tid=%d)\n", #x, __FILE__, __LINE__, errno, gettid_s() ); log_flush(); abort(); }
#ifdef _DEBUG
#define _DASSERT(x)         _ASSERT(x)
#else
#define _DASSERT(x)         NULL
#endif

////////////////////////////////////////////////////////////////////////////////
// Exception Handling (Etc)
////////////////////////////////////////////////////////////////////////////////
#define _RAISE(aLabel)                          \
    { goto aLabel; }

#define _LABEL(aLabel)                          aLabel:

#define _EXCEPTION_END                          EXCEPTION_END_LABEL:

#define _EXCEPTION(aLabel)                      \
    goto EXCEPTION_END_LABEL;                   \
    aLabel:

#define _TEST_RAISE(aExpr, aLabel)              \
    do {                                        \
        if ( !(aExpr) )                         \
        {                                       \
            goto aLabel;                        \
        }                                       \
        else                                    \
        {                                       \
        }                                       \
    } while(0)


// _TEST_xx is conditionally opposite to _IF_xx
#define _IF_RAISE(aExpr, aLabel)                \
    do {                                        \
        if (aExpr)                              \
        {                                       \
            goto aLabel;                        \
        }                                       \
        else                                    \
        {                                       \
        }                                       \
    } while(0)


#endif /* __TRY_MACRO__ */


#define _PRT_LN(k,v,w)      { _PRT( "  %-*s <int>     =  \"%d\"\n", w, k, v ); }
#define _PRT_LS(k,v,w)      { _PRT( "  %-*s <string>  =  \"%s\"\n", w, k, v ); }
#define _PRT_N(k,v)         _PRT_LN(k,v,30)
#define _PRT_S(k,v)         _PRT_LS(k,v,30)
#define _PRT_S2(v)          _PRT_LS((#v),v,30)

#endif /* __EXCEPTION_MACRO_H__ */
