#include "SOC_Modelling_capi_host.h"
static SOC_Modelling_host_DataMapInfo_T root;
static int initialized = 0;
__declspec( dllexport ) rtwCAPI_ModelMappingInfo *getRootMappingInfo()
{
    if (initialized == 0) {
        initialized = 1;
        SOC_Modelling_host_InitializeDataMapInfo(&(root), "SOC_Modelling");
    }
    return &root.mmi;
}

rtwCAPI_ModelMappingInfo *mexFunction() {return(getRootMappingInfo());}
