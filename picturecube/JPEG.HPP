// Borland C++ Builder
// Copyright (c) 1995, 1998 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'jpeg.pas' rev: 3.00

#ifndef jpegHPP
#define jpegHPP
#include <Graphics.hpp>
#include <Classes.hpp>
#include <SysUtils.hpp>
#include <Windows.hpp>
#include <SysInit.hpp>
#include <System.hpp>

//-- user supplied -----------------------------------------------------------

namespace Jpeg
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TJPEGData;
class PASCALIMPLEMENTATION TJPEGData : public Graphics::TSharedImage 
{
	typedef Graphics::TSharedImage inherited;
	
private:
	Classes::TCustomMemoryStream* FData;
	int FHeight;
	int FWidth;
	bool FGrayscale;
	
protected:
	virtual void __fastcall FreeHandle(void);
	
public:
	__fastcall virtual ~TJPEGData(void);
public:
	/* TObject.Create */ __fastcall TJPEGData(void) : Graphics::TSharedImage() { }
	
};

typedef Shortint TJPEGQualityRange;

enum TJPEGPerformance { jpBestQuality, jpBestSpeed };

enum TJPEGScale { jsFullSize, jsHalf, jsQuarter, jsEighth };

enum TJPEGPixelFormat { jf24Bit, jf8Bit };

class DELPHICLASS TJPEGImage;
class PASCALIMPLEMENTATION TJPEGImage : public Graphics::TGraphic 
{
	typedef Graphics::TGraphic inherited;
	
private:
	TJPEGData* FImage;
	Graphics::TBitmap* FBitmap;
	int FScaledWidth;
	int FScaledHeight;
	HPALETTE FTempPal;
	bool FSmoothing;
	bool FGrayScale;
	TJPEGPixelFormat FPixelFormat;
	TJPEGQualityRange FQuality;
	bool FProgressiveDisplay;
	bool FProgressiveEncoding;
	TJPEGPerformance FPerformance;
	TJPEGScale FScale;
	bool FNeedRecalc;
	void __fastcall CalcOutputDimensions(void);
	Graphics::TBitmap* __fastcall GetBitmap(void);
	bool __fastcall GetGrayscale(void);
	void __fastcall SetGrayscale(bool Value);
	void __fastcall SetPerformance(TJPEGPerformance Value);
	void __fastcall SetPixelFormat(TJPEGPixelFormat Value);
	void __fastcall SetScale(TJPEGScale Value);
	void __fastcall SetSmoothing(bool Value);
	
protected:
	virtual void __fastcall AssignTo(Classes::TPersistent* Dest);
	virtual void __fastcall Changed(System::TObject* Sender);
	virtual void __fastcall Draw(Graphics::TCanvas* ACanvas, const Windows::TRect &Rect);
	virtual bool __fastcall Equals(Graphics::TGraphic* Graphic);
	void __fastcall FreeBitmap(void);
	virtual bool __fastcall GetEmpty(void);
	virtual int __fastcall GetHeight(void);
	virtual HPALETTE __fastcall GetPalette(void);
	virtual int __fastcall GetWidth(void);
	void __fastcall NewBitmap(void);
	void __fastcall NewImage(void);
	virtual void __fastcall ReadData(Classes::TStream* Stream);
	void __fastcall ReadStream(int Size, Classes::TStream* Stream);
	virtual void __fastcall SetHeight(int Value);
	virtual void __fastcall SetPalette(HPALETTE Value);
	virtual void __fastcall SetWidth(int Value);
	virtual void __fastcall WriteData(Classes::TStream* Stream);
	__property Graphics::TBitmap* Bitmap = {read=GetBitmap};
	
public:
	__fastcall virtual TJPEGImage(void);
	__fastcall virtual ~TJPEGImage(void);
	void __fastcall Compress(void);
	void __fastcall DIBNeeded(void);
	void __fastcall JPEGNeeded(void);
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	virtual void __fastcall LoadFromStream(Classes::TStream* Stream);
	virtual void __fastcall SaveToStream(Classes::TStream* Stream);
	virtual void __fastcall LoadFromClipboardFormat(Word AFormat, int AData, HPALETTE APalette);
	virtual void __fastcall SaveToClipboardFormat(Word &AFormat, int &AData, HPALETTE &APalette);
	__property bool Grayscale = {read=GetGrayscale, write=SetGrayscale, nodefault};
	__property bool ProgressiveEncoding = {read=FProgressiveEncoding, write=FProgressiveEncoding, nodefault
		};
	__property TJPEGQualityRange CompressionQuality = {read=FQuality, write=FQuality, nodefault};
	__property TJPEGPixelFormat PixelFormat = {read=FPixelFormat, write=SetPixelFormat, nodefault};
	__property bool ProgressiveDisplay = {read=FProgressiveDisplay, write=FProgressiveDisplay, nodefault
		};
	__property TJPEGPerformance Performance = {read=FPerformance, write=SetPerformance, nodefault};
	__property TJPEGScale Scale = {read=FScale, write=SetScale, nodefault};
	__property bool Smoothing = {read=FSmoothing, write=SetSmoothing, nodefault};
};

#pragma pack(push, 1)
struct TJPEGDefaults
{
	TJPEGQualityRange CompressionQuality;
	bool Grayscale;
	TJPEGPerformance Performance;
	TJPEGPixelFormat PixelFormat;
	bool ProgressiveDisplay;
	bool ProgressiveEncoding;
	TJPEGScale Scale;
	bool Smoothing;
} ;
#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE TJPEGDefaults JPEGDefaults;
extern PACKAGE int JPegLibInit;
extern PACKAGE void __fastcall FakeInitJPEGLib(void);

}	/* namespace Jpeg */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Jpeg;
#endif
//-- end unit ----------------------------------------------------------------
#endif	// jpeg
