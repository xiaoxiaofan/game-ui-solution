

/* this ALWAYS GENERATED file contains the proxy stub code */


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

#if !defined(_M_IA64) && !defined(_M_AMD64)


#pragma warning( disable: 4049 )  /* more than 64k source lines */
#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning( disable: 4211 )  /* redefine extern to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma warning( disable: 4024 )  /* array to pointer mapping*/
#pragma warning( disable: 4152 )  /* function/data pointer conversion in expression */
#pragma warning( disable: 4100 ) /* unreferenced arguments in x86 call */

#pragma optimize("", off ) 

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 475
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif /* __RPCPROXY_H_VERSION__ */


#include "MultiVMR9.h"

#define TYPE_FORMAT_STRING_SIZE   3                                 
#define PROC_FORMAT_STRING_SIZE   1                                 
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   0            

typedef struct _MultiVMR9_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } MultiVMR9_MIDL_TYPE_FORMAT_STRING;

typedef struct _MultiVMR9_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } MultiVMR9_MIDL_PROC_FORMAT_STRING;

typedef struct _MultiVMR9_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } MultiVMR9_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const MultiVMR9_MIDL_TYPE_FORMAT_STRING MultiVMR9__MIDL_TypeFormatString;
extern const MultiVMR9_MIDL_PROC_FORMAT_STRING MultiVMR9__MIDL_ProcFormatString;
extern const MultiVMR9_MIDL_EXPR_FORMAT_STRING MultiVMR9__MIDL_ExprFormatString;



#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT50_OR_LATER)
#error You need Windows 2000 or later to run this stub because it uses these features:
#error   /robust command line switch.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will fail with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const MultiVMR9_MIDL_PROC_FORMAT_STRING MultiVMR9__MIDL_ProcFormatString =
    {
        0,
        {

			0x0
        }
    };

static const MultiVMR9_MIDL_TYPE_FORMAT_STRING MultiVMR9__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */

			0x0
        }
    };


/* Standard interface: __MIDL_itf_MultiVMR9_0000_0000, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IMultiVMR9Wizard, ver. 0.0,
   GUID={0x3A54122C,0x1180,0x4468,{0xB9,0x97,0x3A,0x42,0x78,0x41,0xD6,0xDE}} */


/* Object interface: IMultiVMR9RenderEngine, ver. 0.0,
   GUID={0x476B9DBC,0xD303,0x4E71,{0xA5,0x68,0x27,0x38,0xF8,0x1E,0x58,0xAE}} */


/* Object interface: IMultiVMR9UILayer, ver. 0.0,
   GUID={0x102A1639,0x48DA,0x4C93,{0x8B,0x2E,0xEF,0xF5,0x97,0xB0,0x1E,0x01}} */


/* Standard interface: __MIDL_itf_MultiVMR9_0000_0003, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: IMultiVMR9MixerControl, ver. 0.0,
   GUID={0x35CE8FF4,0x3673,0x42F8,{0xA2,0xFF,0x54,0x4F,0x3A,0xFA,0x2D,0xE2}} */


/* Object interface: INullInPlace, ver. 0.0,
   GUID={0x3A878B6A,0x1590,0x4cb9,{0x80,0x9A,0x8C,0x75,0x42,0xED,0xFB,0x56}} */

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    MultiVMR9__MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x50002, /* Ndr library version */
    0,
    0x700022b, /* MIDL Version 7.0.555 */
    0,
    0,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0
    };

const CInterfaceProxyVtbl * const _MultiVMR9_ProxyVtblList[] = 
{
    0
};

const CInterfaceStubVtbl * const _MultiVMR9_StubVtblList[] = 
{
    0
};

PCInterfaceName const _MultiVMR9_InterfaceNamesList[] = 
{
    0
};


#define _MultiVMR9_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _MultiVMR9, pIID, n)

int __stdcall _MultiVMR9_IID_Lookup( const IID * pIID, int * pIndex )
{
    return 0;
}

const ExtendedProxyFileInfo MultiVMR9_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _MultiVMR9_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _MultiVMR9_StubVtblList,
    (const PCInterfaceName * ) & _MultiVMR9_InterfaceNamesList,
    0, /* no delegation */
    & _MultiVMR9_IID_Lookup, 
    0,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
#pragma optimize("", on )
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/

