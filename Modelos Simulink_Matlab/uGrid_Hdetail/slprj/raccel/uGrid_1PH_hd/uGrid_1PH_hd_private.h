#include "__cf_uGrid_1PH_hd.h"
#ifndef RTW_HEADER_uGrid_1PH_hd_private_h_
#define RTW_HEADER_uGrid_1PH_hd_private_h_
#include "rtwtypes.h"
#include "builtin_typeid_types.h"
#include "multiword_types.h"
#include "uGrid_1PH_hd.h"
#if !defined(rt_VALIDATE_MEMORY)
#define rt_VALIDATE_MEMORY(S, ptr)   if(!(ptr)) {\
  ssSetErrorStatus(rtS, RT_MEMORY_ALLOCATION_ERROR);\
  }
#endif
#if !defined(rt_FREE)
#if !defined(_WIN32)
#define rt_FREE(ptr)   if((ptr) != (NULL)) {\
  free((ptr));\
  (ptr) = (NULL);\
  }
#else
#define rt_FREE(ptr)   if((ptr) != (NULL)) {\
  free((void *)(ptr));\
  (ptr) = (NULL);\
  }
#endif
#endif
extern void sfun_spid_contc ( SimStruct * rts ) ; extern void ttkernelMATLAB
( SimStruct * rts ) ; extern void qpOASES_SQProblem ( SimStruct * rts ) ;
extern void mkzpxgiktu ( real_T hpsurd5zwm , nz3ncpxmv0 * localB ) ; extern
void eg5dvdublc ( real_T flpwnmlheq , real_T e2w4vfsbda , const real_T
lbcjf2i2oa [ 2 ] , const real_T d3cqcv4bxl [ 200 ] , const real_T agnsujhbqb
[ 2 ] , const real_T hgbkf0tsgf [ 40000 ] , const real_T nmdszdoqpe [ 40000 ]
, jawacxuwmc * localB ) ; extern void mhb1lzv4x2 ( e325ebrcqg * localDW ) ;
extern void bnlvgadow4 ( const real_T kdmml43azh [ 200 ] , nzd2crx5th *
localB , e325ebrcqg * localDW ) ;
#if defined(MULTITASKING)
#error Models using the variable step solvers cannot define MULTITASKING
#endif
#endif
