#include "nsIGenericFactory.h"
#include "DNdox.h"

NS_GENERIC_FACTORY_CONSTRUCTOR(DNdox)

static nsModuleComponentInfo components[] =
{
    {
       DNDOX_CLASSNAME, 
       DNDOX_CID,
       DNDOX_CONTRACTID,
       DNdoxConstructor,
    }
};

NS_IMPL_NSGETMODULE("DNdoxModule", components) 

