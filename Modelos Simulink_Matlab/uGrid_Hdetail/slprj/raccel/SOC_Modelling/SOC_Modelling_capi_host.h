#include "__cf_SOC_Modelling.h"
#ifndef RTW_HEADER_SOC_Modelling_cap_host_h_
#define RTW_HEADER_SOC_Modelling_cap_host_h_
#ifdef HOST_CAPI_BUILD
#include "rtw_capi.h"
#include "rtw_modelmap.h"
typedef struct { rtwCAPI_ModelMappingInfo mmi ; }
SOC_Modelling_host_DataMapInfo_T ;
#ifdef __cplusplus
extern "C" {
#endif
void SOC_Modelling_host_InitializeDataMapInfo (
SOC_Modelling_host_DataMapInfo_T * dataMap , const char * path ) ;
#ifdef __cplusplus
}
#endif
#endif
#endif
