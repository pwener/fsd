/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _CALCULA_H_RPCGEN
#define _CALCULA_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct operandos {
	int x;
	int y;
};
typedef struct operandos operandos;

#define PROG 10
#define VERSAO 1

#if defined(__STDC__) || defined(__cplusplus)
#define add 1
extern  int * add_1(operandos *, CLIENT *);
extern  int * add_1_svc(operandos *, struct svc_req *);
#define sub 2
extern  int * sub_1(operandos *, CLIENT *);
extern  int * sub_1_svc(operandos *, struct svc_req *);
#define mul 3
extern  int * mul_1(operandos *, CLIENT *);
extern  int * mul_1_svc(operandos *, struct svc_req *);
#define div 4
extern  int * div_1(operandos *, CLIENT *);
extern  int * div_1_svc(operandos *, struct svc_req *);
extern int prog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define add 1
extern  int * add_1();
extern  int * add_1_svc();
#define sub 2
extern  int * sub_1();
extern  int * sub_1_svc();
#define mul 3
extern  int * mul_1();
extern  int * mul_1_svc();
#define div 4
extern  int * div_1();
extern  int * div_1_svc();
extern int prog_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_operandos (XDR *, operandos*);

#else /* K&R C */
extern bool_t xdr_operandos ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_CALCULA_H_RPCGEN */
