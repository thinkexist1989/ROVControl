#pragma once

// 计算机生成了由 Microsoft Visual C++ 创建的 IDispatch 包装类

// 注意: 不要修改此文件的内容。如果此类由
//  Microsoft Visual C++ 重新生成，您的修改将被覆盖。

/////////////////////////////////////////////////////////////////////////////
// CIcompassx1 包装类

class CIcompassx1 : public CWnd
{
protected:
	DECLARE_DYNCREATE(CIcompassx1)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x60B74EE4, 0xDFD, 0x11D4, { 0x85, 0xC4, 0x0, 0xA0, 0xCC, 0x3A, 0x58, 0xC9 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
				UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
				BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// 特性
public:
enum
{
    ilmisRound = 0,
    ilmisRectangle = 1
}TxiLedMatrixIndiatorStyle;
enum
{
    ibsNone = 0,
    ibsRaised = 1,
    ibsLowered = 2
}TxiBevelStyle;
enum
{
    mbLeft = 0,
    mbRight = 1,
    mbMiddle = 2
}TxMouseButton;
enum
{
    ilasRight = 0,
    ilasLeft = 1,
    ilasUp = 2,
    ilasDown = 3,
    ilasLeftRight = 4,
    ilasUpDown = 5
}TxiLedArrowStyle;
enum
{
    ichs24 = 0,
    ichs12 = 1
}TxiClockHourStyle;
enum
{
    ifsDropFrame = 0,
    ifsNonDropFrame = 1
}TxiFrameStyle;
enum
{
    bsSolid = 0,
    bsClear = 1,
    bsHorizontal = 2,
    bsVertical = 3,
    bsFDiagonal = 4,
    bsBDiagonal = 5,
    bsCross = 6,
    bsDiagCross = 7
}TxBrushStyle;
enum
{
    psSolid = 0,
    psDash = 1,
    psDot = 2,
    psDashDot = 3,
    psDashDotDot = 4,
    psClear = 5,
    psInsideFrame = 6
}TxPenStyle;
enum
{
    tidoEllipse = 0,
    tidoRectangle = 1,
    tidoLine = 2,
    tidoText = 3,
    tidoImage = 4,
    tidoArc = 5,
    tidoPolygon = 6
}TxiDrawObjectType;
enum
{
    imcsClickAnyWhere = 0,
    imcsClickIndicator = 1
}TxiMouseControlStyle;
enum
{
    issDown = 0,
    issCenter = 1,
    issUp = 2
}TxiSwitchState;
enum
{
    ioVertical = 0,
    ioHorizontal = 1
}TxiOrientation;
enum
{
    iosBottomRight = 0,
    iosTopLeft = 1
}TxiOrientationSide;
enum
{
    ilgpsPointer = 0,
    ilgpsTriangle = 1,
    ilgpsTLine = 2,
    ilgpsColorBar = 3,
    ilgpsTube = 4
}TxiLinearGaugePointerStyle;
enum
{
    illsValue = 0,
    illsScientific = 1
}TxiLogLabelStyle;
enum
{
    itmnaInside = 0,
    itmnaCenter = 1,
    itmnaOutside = 2
}TxiTickMinorAlignment;
enum
{
    iavCenter = 0,
    iavTop = 1,
    iavBottom = 2
}TxiAlignmentVertical;
enum
{
    iahCenter = 0,
    iahLeft = 1,
    iahRight = 2
}TxiAlignmentHorizontal;
enum
{
    iagpsArrowLine = 0,
    iagpsArrow = 1,
    iagpsLine = 2,
    iagpsTriangle = 3
}TxiAngularGaugePointerStyle;
enum
{
    ithaCenterDisplay = 0,
    ithaCenterControl = 1
}TxiTitleHorizontalAlignment;
enum
{
    icpsTriangle = 0,
    icpsCircle = 1,
    icpsLine = 2
}TxiCompassPointerStyle;
enum
{
    tpIdle = 0,
    tpLowest = 1,
    tpLower = 2,
    tpNormal = 3,
    tpHigher = 4,
    tpHighest = 5,
    tpTimeCritical = 6
}TxThreadPriority;
enum
{
    itasCenter = 0,
    itasSide = 1
}TxiScaleAlignStyle;
enum
{
    isspsDualArrow = 0,
    isspsArrow = 1,
    isspsPointer = 2,
    isspsLine = 3
}TxiSlidingScalePointerStyle;
enum
{
    iasvTop = 0,
    iasvBottom = 1
}TxiAlignmentSideVertical;
enum
{
    ikbs104 = 0,
    ikbs87 = 1,
    ikbs74 = 2,
    ikbs61 = 3,
    ikbsNumericKeyPad = 4,
    ikbsCustom1 = 5,
    ikbsCustom2 = 6
}TxiKeyBoardStyle;
enum
{
    htKeyword = 0,
    htContext = 1
}TxHelpType;
enum
{
    itpsBar = 0,
    itpsCutOut1 = 1,
    itpsCutOut2 = 2,
    itpsLargeWindow = 3,
    itpsCustom = 4
}TxiTankPointerStyle;
enum
{
    ipfisCircle = 0,
    ipfisBox = 1,
    ipfisTriangle = 2
}TxiPipeFlowIndicatorStyle;
enum
{
    imbsTrapezoid = 0,
    imbsFeet = 1
}TxiMotorBaseStyle;
enum
{
    idesSunken = 0,
    idesRaised = 1,
    idesFlat = 2
}TxiDrawEdgeStyle;


// 操作
public:

// IiCompassX

// Functions
//

	long get_PointerMargin()
	{
		long result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_PointerMargin(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	unsigned long get_PointerColor()
	{
		unsigned long result;
		InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, NULL);
		return result;
	}
	void put_PointerColor(unsigned long newValue)
	{
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_PointerSize()
	{
		long result;
		InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_PointerSize(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_PointerStyle()
	{
		long result;
		InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_PointerStyle(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_OuterMargin()
	{
		long result;
		InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_OuterMargin(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_OuterBevelWidth()
	{
		long result;
		InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_OuterBevelWidth(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	unsigned long get_ScaleBackGroundColor()
	{
		unsigned long result;
		InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, NULL);
		return result;
	}
	void put_ScaleBackGroundColor(unsigned long newValue)
	{
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	unsigned long get_TickColor()
	{
		unsigned long result;
		InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, NULL);
		return result;
	}
	void put_TickColor(unsigned long newValue)
	{
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_TickLength()
	{
		long result;
		InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_TickLength(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_TickWidth()
	{
		long result;
		InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_TickWidth(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_TickMargin()
	{
		long result;
		InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_TickMargin(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_TickLabelInnerMargin()
	{
		long result;
		InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_TickLabelInnerMargin(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_TickLabelOuterMargin()
	{
		long result;
		InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_TickLabelOuterMargin(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_TickLabelFont()
	{
		LPDISPATCH result;
		InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void put_TickLabelFont(LPDISPATCH newValue)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	double get_Direction()
	{
		double result;
		InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
		return result;
	}
	void put_Direction(double newValue)
	{
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0x10, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_DirectionDisplayFont()
	{
		LPDISPATCH result;
		InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void put_DirectionDisplayFont(LPDISPATCH newValue)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x11, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_DirectionDisplayPrecision()
	{
		long result;
		InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_DirectionDisplayPrecision(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x12, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_ShowDirectionDisplay()
	{
		BOOL result;
		InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_ShowDirectionDisplay(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x13, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	unsigned long get_BackGroundColor()
	{
		unsigned long result;
		InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, NULL);
		return result;
	}
	void put_BackGroundColor(unsigned long newValue)
	{
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x14, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_BorderStyle()
	{
		long result;
		InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_BorderStyle(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x15, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_Enabled()
	{
		BOOL result;
		InvokeHelper(DISPID_ENABLED, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_Enabled(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(DISPID_ENABLED, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void AboutBox()
	{
		InvokeHelper(DISPID_ABOUTBOX, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ShowPropertyEditor()
	{
		InvokeHelper(0x2a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	unsigned long get_TickLabelFontColor()
	{
		unsigned long result;
		InvokeHelper(0x2b, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, NULL);
		return result;
	}
	void put_TickLabelFontColor(unsigned long newValue)
	{
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x2b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	unsigned long get_DirectionDisplayFontColor()
	{
		unsigned long result;
		InvokeHelper(0x2c, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, NULL);
		return result;
	}
	void put_DirectionDisplayFontColor(unsigned long newValue)
	{
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x2c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_Transparent()
	{
		BOOL result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_Transparent(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void RepaintAll()
	{
		InvokeHelper(0x16, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void BeginUpdate()
	{
		InvokeHelper(0x17, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void EndUpdate()
	{
		InvokeHelper(0x18, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Lock()
	{
		InvokeHelper(0x19, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Unlock()
	{
		InvokeHelper(0x1a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	long get_UpdateFrameRate()
	{
		long result;
		InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_UpdateFrameRate(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_ComponentHandle()
	{
		long result;
		InvokeHelper(0x1c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SaveImageToBitmap(LPCTSTR FileName)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileName);
	}
	void SaveImageToMetaFile(LPCTSTR FileName)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileName);
	}
	void SaveImageToJPEG(LPCTSTR FileName, long Compression, BOOL Progressive)
	{
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_BOOL ;
		InvokeHelper(0x1f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileName, Compression, Progressive);
	}
	long OPCAddItem()
	{
		long result;
		InvokeHelper(0x1001, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long OPCItemCount()
	{
		long result;
		InvokeHelper(0x1002, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void OPCRemoveAllItems()
	{
		InvokeHelper(0x1003, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void OPCItemActivate(long Index)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1004, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index);
	}
	void OPCItemDeactivate(long Index)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1005, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index);
	}
	CString GetOPCItemComputerName(long Index)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1006, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Index);
		return result;
	}
	CString GetOPCItemServerName(long Index)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1007, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Index);
		return result;
	}
	CString GetOPCItemItemName(long Index)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1008, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Index);
		return result;
	}
	CString GetOPCItemPropertyName(long Index)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1009, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Index);
		return result;
	}
	BOOL GetOPCItemAutoConnect(long Index)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x100a, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Index);
		return result;
	}
	long GetOPCItemUpdateRate(long Index)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x100b, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Index);
		return result;
	}
	void SetOPCItemComputerName(long Index, LPCTSTR Value)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR ;
		InvokeHelper(0x100c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index, Value);
	}
	void SetOPCItemServerName(long Index, LPCTSTR Value)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR ;
		InvokeHelper(0x100d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index, Value);
	}
	void SetOPCItemItemName(long Index, LPCTSTR Value)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR ;
		InvokeHelper(0x100e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index, Value);
	}
	void SetOPCItemPropertyName(long Index, LPCTSTR Value)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR ;
		InvokeHelper(0x100f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index, Value);
	}
	void SetOPCItemAutoConnect(long Index, BOOL Value)
	{
		static BYTE parms[] = VTS_I4 VTS_BOOL ;
		InvokeHelper(0x1010, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index, Value);
	}
	void SetOPCItemUpdateRate(long Index, long Value)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x1011, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index, Value);
	}
	void OPCItemLoaded(long Index)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1012, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index);
	}
	BOOL get_CachedDrawing()
	{
		BOOL result;
		InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_CachedDrawing(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x20, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long GetObjectPointer()
	{
		long result;
		InvokeHelper(0x1068, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	VARIANT GetBytesJPEG(long Compression, BOOL Progressive)
	{
		VARIANT result;
		static BYTE parms[] = VTS_I4 VTS_BOOL ;
		InvokeHelper(0x1069, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, Compression, Progressive);
		return result;
	}
	void SavePropertiesToFile(LPCTSTR FileName)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x106a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileName);
	}
	void LoadPropertiesFromFile(LPCTSTR FileName)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x106b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileName);
	}
	BOOL get_OptionSaveAllProperties()
	{
		BOOL result;
		InvokeHelper(0x106d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_OptionSaveAllProperties(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x106d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_AutoFrameRate()
	{
		BOOL result;
		InvokeHelper(0x106e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_AutoFrameRate(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x106e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void iPaintToDC(long X, long Y, BOOL Transparent, long DC)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BOOL VTS_I4 ;
		InvokeHelper(0x10cc, DISPATCH_METHOD, VT_EMPTY, NULL, parms, X, Y, Transparent, DC);
	}
	BOOL get_Visible()
	{
		BOOL result;
		InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_Visible(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x21, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_Width()
	{
		long result;
		InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Width(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x22, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_Height()
	{
		long result;
		InvokeHelper(0x23, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Height(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x23, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void OPCItemUpdateResume(long Index)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1013, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index);
	}
	void OPCItemUpdateSuspend(long Index)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1014, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index);
	}
	VARIANT GetOPCItemData(long Index)
	{
		VARIANT result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1015, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, Index);
		return result;
	}
	short GetOPCItemQuality(long Index)
	{
		short result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1016, DISPATCH_METHOD, VT_I2, (void*)&result, parms, Index);
		return result;
	}
	double GetOPCItemTimeStamp(long Index)
	{
		double result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1017, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Index);
		return result;
	}
	void SetOPCItemData(long Index, VARIANT Value)
	{
		static BYTE parms[] = VTS_I4 VTS_VARIANT ;
		InvokeHelper(0x1018, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index, &Value);
	}
	BOOL GetOPCItemActive(long Index)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1019, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Index);
		return result;
	}
	CString get_NCaption()
	{
		CString result;
		InvokeHelper(0x24, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_NCaption(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x24, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_NWCaption()
	{
		CString result;
		InvokeHelper(0x25, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_NWCaption(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x25, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_WCaption()
	{
		CString result;
		InvokeHelper(0x26, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_WCaption(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x26, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_SWCaption()
	{
		CString result;
		InvokeHelper(0x27, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_SWCaption(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x27, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_SCaption()
	{
		CString result;
		InvokeHelper(0x28, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_SCaption(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x28, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_SECaption()
	{
		CString result;
		InvokeHelper(0x29, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_SECaption(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x29, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_ECaption()
	{
		CString result;
		InvokeHelper(0x2d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_ECaption(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x2d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_NECaption()
	{
		CString result;
		InvokeHelper(0x2e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_NECaption(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x2e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString GetOPCItemGroupName(long Index)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x101c, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Index);
		return result;
	}
	void SetOPCItemGroupName(long Index, LPCTSTR Value)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR ;
		InvokeHelper(0x101d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index, Value);
	}
	void OPCDeleteItem(long Index)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x101e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index);
	}
	void OPCItemActivateSuspend(long Index)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x101f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index);
	}
	VARIANT GetBytesPNG(long Compression)
	{
		VARIANT result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1020, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, Compression);
		return result;
	}
	void SaveImageToPNG(LPCTSTR FileName, long Compression)
	{
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x1021, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileName, Compression);
	}
	VARIANT GetOPCItemDataNow(long Index, short * Quality)
	{
		VARIANT result;
		static BYTE parms[] = VTS_I4 VTS_PI2 ;
		InvokeHelper(0x1022, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, Index, Quality);
		return result;
	}
	BOOL GetOPCItemUpdateSuspended(long Index)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1023, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Index);
		return result;
	}
	double GetOPCItemScalar(long Index)
	{
		double result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1024, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Index);
		return result;
	}
	double GetOPCItemOffset(long Index)
	{
		double result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1025, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Index);
		return result;
	}
	void SetOPCItemScalar(long Index, double Value)
	{
		static BYTE parms[] = VTS_I4 VTS_R8 ;
		InvokeHelper(0x1026, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index, Value);
	}
	void SetOPCItemOffset(long Index, double Value)
	{
		static BYTE parms[] = VTS_I4 VTS_R8 ;
		InvokeHelper(0x1027, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index, Value);
	}

// Properties
//



};
