//------------------------------------------------------------------------------
// File: NullIP.h
//
// Desc: DirectShow sample code - illustrates: 
//             An in-place transform filter
//             Media types and the connection process
//             Performance logging using Measure.dll
//             Use of CAutoLock class to automatically release critical sections             
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------


//
//     Summary
//
// A simple in-place transform with one input pin and one output pin.
// The filter operates in-place which means that it has no media type
// enumerators of its own.  It obtains enumerators from the filters either
// on either side and passes types so obtained across for approval by the
// one on the other side.  On the way through it sees if it likes the
// type and rejects any that it doesn't.  The property sheet displays the
// list of types obtained from the upstream filter and allows one or
// all to be selected.  Any type not selected will be rejected by the
// connection process.  Almost all the work is done by the base classes.
//
//
//     Demonstration instructions
//
// First build the sample and get it registered
// Start GraphEdit (available in the SDK DXUtils folder).
// Select Graph then InsertFilters and insert FileSource (async)
// Select Angry.AVI as the source file.
// Insert Null-In-Place.  (If it is not on the list then you
// failed to register it properly.  If it fails to load then you either
// didn't build it properly or the registration does not correctly point to
// the path where nullip.ax is now found.)
// Right click on the output pin of the source filter. Select Render.
// In the resulting graph you will see the Null-In-Place filter inserted between
// the AVI decompressor and the video renderer.
// Right click on the null-in-place filter to bring up its properties page.
// Select Major Type: MEDIATYPE_Video - Sub Type:MEDIASUBTYPE_RGB24 <etc>
// Click on Apply.  It wil tell you that it can't do it.
// Delete the output connection (Null-In-Place to Video Renderer)
// Try to Apply the media type again.  It succeeds.
// Connect the Mull-In-Place transform to the Video Renderer again.
// It will (probably) insert a Colour Space Transform to make the connection.
//
//
//     Implementation
//
// This filter has one input pin, one output pin and
// does its "transform" in-place (i.e. without copying the data)
// on the push thread (i.e. it is called with a buffer, which it
// "transforms" and gives to the next filter downstream.  It is
// then blocked until that filter returns.  It then returns
// to its own caller.)
//
// In this case the transform does nothing.  It just passes the data on.
//
// It has a properties page which allows control of what media types
// are allowed on connection.

// Note about Receive:
//
// NOTE: Please note that we shoud NOT override the Receive method to Deliver
// the input sample directly. We may have a case where we could not negotiate
// the same allocator for the input and output pins. (For example, if the
// upstream filter insists on its own allocator and provides a read-only
// allocator, that will be the case). In this case samples need to be
// copied from input to output allocator and then transformed. The base
// class Receive method does this. Transform () will get called on the copied
// over buffer and in our case, that function is a NOP and does nothing.
//
//
//      Files
//
// nullip.cpp    This file - main implementation
// nullprop.cpp  Implementation of the properties sheet
// nullprop.h    Class definition of properties class (used in nullip.cpp)
// nullprop.rc   Defines the property page dialog
// inull.h       Interface between nullip and nullprop
// nulluids.h    The public class ids (only referred to in nullip)
// resource.h    constants shared between nullip.rc and nullip.cpp
// texttype.cpp  implementation of class used to display media types as text
// texttype.h    definition of class used to display media types as text
// nullip.def    Imports and exports
// makefile      How to build it
//
//
//     Base classes used (refer to docs for diagram of what they inherit):
//
// CTransInPlaceFilter
// CBasePropertyPage
// CMediaType
// CTransInPlaceInputPin
// CTransInPlaceOutputPin


#include <streams.h>          // quartz, includes windows

// Eliminate two expected level 4 warnings from the Microsoft compiler.
// The class does not have an assignment or copy operator, and so cannot
// be passed by value.  This is normal.  This file compiles clean at the
// highest (most picky) warning level (-W4).
#pragma warning(disable: 4511 4512)

//#include <measure.h>          // performance measurement (MSR_)
#include "MultiVMR9.h"
//#include "MultiVMRguids.h"


//#include "nullUids.h"         // our own public guids

//#include "inull.h"            // interface between filter and property sheet
//#include "nullprop.h"         // property sheet implementatino class



// ----------------------------------------------------------------------------
// Class definitions of input pin, output pin and filter
// ----------------------------------------------------------------------------



// CNullInPlace
//
class CNullInPlace : public CTransInPlaceFilter
                   , public INullInPlace
{
	public:
       class CNullInPlaceInputPin : public CTransInPlaceInputPin
		{
			public:
				CNullInPlaceInputPin( TCHAR * pObjectName
									, CTransInPlaceFilter *pTransInPlaceFilter
									, HRESULT * phr
									, LPCWSTR pName
									)
									: CTransInPlaceInputPin(pObjectName
															, pTransInPlaceFilter
															, phr
															, pName
															)
				{
				}

				HRESULT CheckMediaType(const CMediaType* pmt);
		};


		class CNullInPlaceOutputPin : public CTransInPlaceOutputPin
		{
			public:
				CNullInPlaceOutputPin( TCHAR * pObjectName
									, CTransInPlaceFilter *pTransInPlaceFilter
									, HRESULT * phr
									, LPCWSTR pName
									)
									: CTransInPlaceOutputPin( pObjectName
															, pTransInPlaceFilter
															, phr
															, pName
															)
				{
				}

				HRESULT CheckMediaType(const CMediaType* pmt);
		};




    public:
		
        static CUnknown * WINAPI CreateInstance(LPUNKNOWN punk, HRESULT *phr);

        DECLARE_IUNKNOWN;

        //
        // --- CTransInPlaceFilter Overrides --
        //

        virtual CBasePin *GetPin( int n );
		
        HRESULT CheckInputType(const CMediaType* mtIn)
            { UNREFERENCED_PARAMETER(mtIn);  return S_OK; }

        // Basic COM - used here to reveal our property interface.
        STDMETHODIMP NonDelegatingQueryInterface(REFIID riid, void ** ppv);

        STDMETHODIMP get_IPin (IPin **ppPin) ;
        STDMETHODIMP put_MediaType(CMediaType *pmt);
        STDMETHODIMP get_MediaType(CMediaType **pmt);
        STDMETHODIMP get_State(FILTER_STATE *state);

		
			//
			// Needed for the CreateInstance mechanism
			//
			CFactoryTemplate m_Templates[2];

			/*********************************************************************************/
        //
        // --- ISpecifyPropertyPages ---
        //

        STDMETHODIMP GetPages(CAUUID *pPages);

    private:

        CNullInPlace(TCHAR *tszName, LPUNKNOWN punk, HRESULT *phr);

        //
        // Overrides the PURE virtual Transform of CTransInPlaceFilter base class
        // This is where the "real work" is done.
        //
        HRESULT Transform(IMediaSample *pSample)
            { UNREFERENCED_PARAMETER(pSample); return NOERROR; }
        //
        //
        // If there are multiple instances of this filter active, it's
        // useful for debug messages etc. to know which one this is.
        //
        static int m_nInstanceCount;   // total instances
        int m_nThisInstance;

        CMediaType m_mtPreferred;  // Media type chosen from property sheet

        CCritSec m_NullIPLock;     // To serialise access.
};


