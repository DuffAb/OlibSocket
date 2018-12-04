/************************************************************************************

PublicHeader:   n/a
Filename    :   OTypes.h
Content     :   Standard library defines and simple types
Created     :   December 4, 2018
Authors     :   defeng.liang
************************************************************************************/

#ifndef _O_TYPE_H_
#define _O_TYPE_H_

#if defined(_MSC_VER)
typedef signed char        int8_t;
typedef unsigned char     uint8_t;
typedef signed short      int16_t;
typedef unsigned short   uint16_t;
typedef signed int        int32_t;
typedef unsigned int     uint32_t;
typedef signed __int64    int64_t;
typedef unsigned __int64 uint64_t;
#else
#include <stdint.h>
#endif

#endif  /*_O_TYPE_H_*/