

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sat May 28 17:06:51 2011
 */
/* Compiler settings for MultiVMR9.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IMultiVMR9Wizard,0x3A54122C,0x1180,0x4468,0xB9,0x97,0x3A,0x42,0x78,0x41,0xD6,0xDE);


MIDL_DEFINE_GUID(IID, IID_IMultiVMR9RenderEngine,0x476B9DBC,0xD303,0x4E71,0xA5,0x68,0x27,0x38,0xF8,0x1E,0x58,0xAE);


MIDL_DEFINE_GUID(IID, IID_IMultiVMR9UILayer,0x102A1639,0x48DA,0x4C93,0x8B,0x2E,0xEF,0xF5,0x97,0xB0,0x1E,0x01);


MIDL_DEFINE_GUID(IID, IID_IMultiVMR9MixerControl,0x35CE8FF4,0x3673,0x42F8,0xA2,0xFF,0x54,0x4F,0x3A,0xFA,0x2D,0xE2);


MIDL_DEFINE_GUID(IID, IID_INullInPlace,0x3A878B6A,0x1590,0x4cb9,0x80,0x9A,0x8C,0x75,0x42,0xED,0xFB,0x56);


MIDL_DEFINE_GUID(IID, LIBID_MultiVMR9Lib,0x52CCE217,0x77CF,0x4108,0x9D,0x55,0xCC,0xBA,0xAF,0x28,0x96,0xD7);


MIDL_DEFINE_GUID(CLSID, CLSID_MultiVMR9Wizard,0xCE8ED243,0x0078,0x41A2,0xB5,0x6C,0xEC,0x9C,0xF0,0xE8,0x87,0xC2);


MIDL_DEFINE_GUID(CLSID, CLSID_MultiVMR9RenderEngine,0x8BBB5505,0x250D,0x486D,0xBB,0x49,0xF7,0x41,0x41,0x88,0x04,0x90);


MIDL_DEFINE_GUID(CLSID, CLSID_MultiVMR9UILayer,0x70A2E5FE,0x981E,0x4518,0x83,0xC7,0x93,0x24,0xDC,0x95,0x7D,0xA4);


MIDL_DEFINE_GUID(CLSID, CLSID_MultiVMR9MixerControl,0xBB22E7B6,0x54E1,0x4C4D,0xAB,0xF7,0x99,0x19,0x35,0x50,0xA3,0xF4);


MIDL_DEFINE_GUID(CLSID, CLSID_NullInPlace,0xE89555FF,0x9F9B,0x417e,0xAC,0xEC,0xE8,0xA2,0xDB,0xF7,0x0B,0xA6);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



