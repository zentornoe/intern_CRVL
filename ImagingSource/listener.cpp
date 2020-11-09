//////////////////////////////////////////////////////////////////////
// Listener.cpp: implementation of the CListener class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Listener.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListener::CListener()
{
	m_pParent = NULL;
}

//////////////////////////////////////////////////////////////////////////

CListener::~CListener() 
{
}

//////////////////////////////////////////////////////////////////////////

void CListener::SetParent( CWnd *pParent)
{
	m_pParent = pParent;
}

//////////////////////////////////////////////////////////////////////////
// Notify parent, device is lost.
//////////////////////////////////////////////////////////////////////////

void CListener::deviceLost( Grabber& param) 
{
	if( m_pParent != NULL)
		m_pParent->PostMessage(MESSAGEDEVICELOST,0,0);
}

//////////////////////////////////////////////////////////////////////////
// Callback handler.
//////////////////////////////////////////////////////////////////////////

void CListener::frameReady( Grabber& param, smart_ptr<MemBuffer> pBuffer, DWORD FrameNumber)
{
	pBuffer->lock();
	DoImageProcessing( pBuffer );
	pBuffer->unlock();
}

//////////////////////////////////////////////////////////////////////////
// The image processing is done here. For the sake of simplicity, the
// image data is inverted by this sample code.
//////////////////////////////////////////////////////////////////////////

void CListener::DoImageProcessing( smart_ptr<MemBuffer> pBuffer)
{
	// Get the bitmap info header from the membuffer. It contains the bits per pixel,
	// width and height.
	smart_ptr<BITMAPINFOHEADER> pInf = pBuffer->getBitmapInfoHeader();

	// Now retrieve a pointer to the image. For organization of the image data, please
	// refer to:
	// http://www.imagingcontrol.com/ic/docs/html/class/Pixelformat.htm

	BYTE* pImageData = pBuffer->getPtr();

	// Calculate the size of the image.
	int iImageSize = pInf->biWidth * pInf->biHeight * pInf->biBitCount / 8 ;

	// Now loop through the data and change every byte. This small sample inverts every pixel.
}
