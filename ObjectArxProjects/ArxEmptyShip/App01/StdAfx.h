#ifndef STDA_FX_H
#define STDA_FX_H 

#define CUSTDBX_MODULE

#pragma pack (push, 8)
#pragma warning(disable: 4786 4996)
//#pragma warning(disable: 4098)

#include <tchar.h> // _T() macros

#include <windows.h>

//- ObjectARX and OMF headers needs this
#include <map>
//-----------------------------------------------------------------------------
//- Include ObjectDBX/ObjectARX headers
//- Uncomment one of the following lines to bring a given library in your project.
//#define _BREP_SUPPORT_					//- Support for the BRep API
//#define _HLR_SUPPORT_						//- Support for the Hidden Line Removal API
//#define _AMODELER_SUPPORT_				//- Support for the AModeler API
#include "dbxHeaders.h"

#include "dbjig.h"

#pragma pack (pop)

#endif