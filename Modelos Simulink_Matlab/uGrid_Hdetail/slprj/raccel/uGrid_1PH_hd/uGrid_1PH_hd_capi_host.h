#include "__cf_uGrid_1PH_hd.h"
#ifndef RTW_HEADER_uGrid_1PH_hd_cap_host_h_
#define RTW_HEADER_uGrid_1PH_hd_cap_host_h_
#ifdef HOST_CAPI_BUILD
#include "rtw_capi.h"
#include "rtw_modelmap.h"
typedef struct { rtwCAPI_ModelMappingInfo mmi ; }
uGrid_1PH_hd_host_DataMapInfo_T ;
#ifdef __cplusplus
extern "C" {
#endif
void uGrid_1PH_hd_host_InitializeDataMapInfo (
uGrid_1PH_hd_host_DataMapInfo_T * dataMap , const char * path ) ;
#ifdef __cplusplus
}
#endif
#endif
#endif
