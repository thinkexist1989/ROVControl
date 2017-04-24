// DIJoystick.cpp: implementation of the CDIJoystick class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DIJoystick.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// DIJoystick.cpp: implementation of the CDIJoystick class.
//
// Written and Developed by Jason Brooks
// (C) 2000 Jason Brooks
//
// You may use this code freely, however a mention in your credits
// would be nice.
//
// For more information, Bug Reports and so on I can be contacted :-
//
// E-Mail:   DirectInput@muckypaws.com
//
// Web:      www.muckypaws.com
// ICQ:      9609400
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DIJoystick.h"

#define BUFFERSIZE 16

// Set the maxmimum range to which we'll gauge the swing
#define JOYMAX 10000
#define JOYMIN -10000

/*				Y
				
				^
				|
				|
X	-10,000 <---*---> +10,000
				|
				|
				\/
*/
// Dead zone is the amount of sway the joystick can have before we start registering movement
// In this case 20%

#define JOYDEAD 1000

// The Saturation Point Is Where the Joystick is deemed to be at Full Swing, in this case 95%
#define JOYSAT  9500

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDIJoystick::CDIJoystick()
{
	// Initialise Member Variables
	m_EnumerationStarted=false;
	m_Initialised=false;
	m_hInstance=GetModuleHandle(NULL);  //返回当前应用程序的实例句柄

	m_lpDIDevice = NULL;
	m_lpDI =NULL;


}

//////////////////////////////////////////////////////////////////////
//
// Destroy The Direct Input Joystick Control and tidy up.
//
//////////////////////////////////////////////////////////////////////
CDIJoystick::~CDIJoystick()
{
	Shutdown();
}

//////////////////////////////////////////////////////////////////////
//
// Initialise Direct Input
//
//////////////////////////////////////////////////////////////////////
bool CDIJoystick::Initialise()
{
	HRESULT         hr; 

	hr = DirectInput8Create(m_hInstance,DIRECTINPUT_VERSION,IID_IDirectInput8,(void **)&m_lpDI,NULL);

	//hr = DirectInputCreateEx(m_hInstance, DIRECTINPUT_VERSION, 
		//	IID_IDirectInput8, (void**)&m_lpDI, NULL); 
	if FAILED(hr) 
	{ 
	    // DirectInput not available; 
	    // take appropriate action
		OutputDebugString("Failed To Initialise Direct Input 7 in CDIJoystick::Initialise\n");
		OutputDebugString(GetDIError(hr));
		return false;
	}

	m_hwnd=NULL;

	if FAILED(hr)
	{ 
		OutputDebugString(GetDIError(hr));
		Shutdown(); 
		return false; 
	}

	m_Initialised=true;
	return true;	// Successfully Created Direct Input 7 Object
}

//////////////////////////////////////////////////////////////////////
//
// Shutdown the Direct input object and release it.
//
// Basically clean up any memory allocated to this object
//
//////////////////////////////////////////////////////////////////////
void CDIJoystick::Shutdown()
{
	ClearFriendlyButtonNames();

	// Remove Joystick Information
	if(!m_DIJoystickList.IsEmpty())
	{
		POSITION pos=m_DIJoystickList.GetHeadPosition();
		LPVOID del=NULL;

		while(pos)
		{
			del=static_cast<LPVOID>(m_DIJoystickList.GetNext(pos));
			if(del)
			{
				delete del;
			}
		}
		m_DIJoystickList.RemoveAll();
	}

	// Shutdown Direct Input!
	if (m_lpDI) 
	{ 
		if (m_lpDIDevice) 
		{ 
				// Always unacquire device before calling Release().
			try
			{
				Acquire(false);
				m_lpDIDevice->Release();
				m_lpDIDevice = NULL; 
			}
			catch(...)
			{
				OutputDebugString("Failed to Release Pointer in CDIJoystick::Shutdown\n");
			}
		} 
		try
		{
			m_lpDI->Release();
			m_lpDI = NULL; 
		}
		catch(...)
		{
			OutputDebugString("Failed to Release DI7 Pointer in CDIJoystick::Shutdown\n");
		}
	} 
	m_Initialised=false;
}

//////////////////////////////////////////////////////////////////////
//
// Start the Enumeration Of Attached Joystick Devices.
//
//////////////////////////////////////////////////////////////////////
bool CDIJoystick::Enumerate_Joysticks()
{
	HRESULT hr=NULL;

	if(!m_Initialised) Initialise();

	if(!m_lpDI) // Has a Direct Input Interface Already Been Initialised?
	{
		//hr = DirectInputCreateEx(m_hInstance, DIRECTINPUT_VERSION, 
			//				   IID_IDirectInput7, (void**)&m_lpDI, NULL);

		hr = DirectInput8Create(m_hInstance,DIRECTINPUT_VERSION,IID_IDirectInput8,(void **)&m_lpDI,NULL);

		if FAILED(hr) 
		{
			OutputDebugString("Error in CDIJoystick::Enumerate_Joysticks()\n");
			OutputDebugString(GetDIError(hr));
			return false; 
		}
	}
	
	if(m_lpDI) hr=m_lpDI->EnumDevices(DI8DEVCLASS_GAMECTRL,EnumDevicesProc,this,DIEDFL_ATTACHEDONLY);
    if FAILED(hr) 
	{
		OutputDebugString("Error in CDIJoystick::Enumerate_Joysticks()\n");
		OutputDebugString(GetDIError(hr));
		return false; 
	}

	OutputDebugString("Enumerating Joystick Devices\n");
	return true;
}

//////////////////////////////////////////////////////////////////////
//
// Add Enumerated Devices To A Link List Object
// Continue Enumeration Of The Device
//
//////////////////////////////////////////////////////////////////////
BOOL CDIJoystick::EnumDevicesProc(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef)
{
	CDIJoystick *obj=(CDIJoystick*)(pvRef);
	obj->AddDeviceInfo(lpddi);

	return DIENUM_CONTINUE;   
}

//////////////////////////////////////////////////////////////////////
//
// Add Device Info To The List Of Pointers Held in m_DIJoystickList
//
// return  true = Successfully Added 
//        false = Failed To Add
//
//////////////////////////////////////////////////////////////////////
bool CDIJoystick::AddDeviceInfo(LPCDIDEVICEINSTANCE lpddi)
{
	m_EnumerationStarted=true;

	LPCDIDEVICEINSTANCE lpdi2=new DIDEVICEINSTANCE;
	if(lpdi2)
	{
		memcpy((void*)lpdi2,lpddi,sizeof(DIDEVICEINSTANCE));

		if(m_DIJoystickList.AddHead((void*)lpdi2))return true;
		OutputDebugString("Failed To Add Device Info in CDIJoystick::AddDeviceInfo(LPCDIDEVICEINSTANCE lpddi)\n");
	}
	return false;
}

//////////////////////////////////////////////////////////////////////
//
// Return First Joystick Device Data If Possible
//
// return  NULL if Failed or No Joysticks Available
//
//////////////////////////////////////////////////////////////////////
LPCDIDEVICEINSTANCE CDIJoystick::GetFirstJoystickID()
{
	if(!m_EnumerationStarted) {
		OutputDebugString("Joystick Have Not Yet Been Enumerated Returning NULL from CDIJoystick::GetFirstJoystickID()\n");
		return NULL;
	}

	if(m_DIJoystickList.IsEmpty()) {
		OutputDebugString("Joysticks Have Been Enumerated However None Were Found Attached To This System\n"
						  "Therefore I am Returning NULL from CDIJoystick::GetFirstJoystickID()\n");
		return NULL;
	}

	m_DevicePOS = m_DIJoystickList.GetHeadPosition();

	return GetNextJoystickID();

	LPCDIDEVICEINSTANCE info=static_cast<LPCDIDEVICEINSTANCE>(m_DIJoystickList.GetNext(m_DevicePOS));

	return info;
}

//////////////////////////////////////////////////////////////////////
//
// Return Next Joystick Device Data If Possible
//
// return  NULL if Failed or No Joysticks Available
//
//////////////////////////////////////////////////////////////////////
LPCDIDEVICEINSTANCE CDIJoystick::GetNextJoystickID()
{
	if(!m_DevicePOS) return NULL;

	return static_cast<LPCDIDEVICEINSTANCE>(m_DIJoystickList.GetNext(m_DevicePOS));
}

//////////////////////////////////////////////////////////////////////
//
// Return First Joystick Button Name Data If Possible
//
// return  NULL if Failed or No Joysticks Available
//
//////////////////////////////////////////////////////////////////////
TCHAR* CDIJoystick::GetFirstButtonName()
{
	if(!m_EnumerationStarted) 
	{
		OutputDebugString("Joystick Have Not Yet Been Enumerated\nor None attached to this systemReturning NULL from CDIJoystick::GetFirstJoystickID()\n");
		return NULL;
	}

	if(m_DIButtonNames.IsEmpty()) 
	{
		OutputDebugString("Joysticks Have Been Enumerated However None Were Found Attached To This System\n"
						  "Therefore I am Returning NULL from CDIJoystick::GetFirstButtonName()\n");
		return NULL;
	}

	m_ButtonPOS=m_DIButtonNames.GetHeadPosition();

	TCHAR* info=static_cast<TCHAR*>(m_DIButtonNames.GetNext(m_ButtonPOS));
	return info;	
}

//////////////////////////////////////////////////////////////////////
//
// Return First Joystick Button Name Data If Possible
//
// return  NULL if Failed or No Joysticks Available
//
//////////////////////////////////////////////////////////////////////
TCHAR* CDIJoystick::GetNextButtonName()
{
	if(!m_ButtonPOS) return NULL;

	return static_cast<TCHAR*>(m_DIButtonNames.GetNext(m_ButtonPOS));
}


//////////////////////////////////////////////////////////////////////
//
//  Create the Joystick Device Using GUID Passed
//
//////////////////////////////////////////////////////////////////////
bool CDIJoystick::CreateDevice(GUID *guid)
{
	HRESULT hr=NULL;

	// If a device already exists and is created, Release it.
	if (m_lpDIDevice) 
    { 
		// Always unacquire device before calling Release().
		try
		{
			hr=m_lpDIDevice->Unacquire(); 
		}
		catch(...)
		{
		}
		try
		{
			hr=m_lpDIDevice->Release();
			if(FAILED(hr))
			{
				OutputDebugString(GetDIError(hr));
			}
			else m_lpDIDevice = NULL; 
		}
		catch(...)
		{
			OutputDebugString("Failed to Release Pointer in CDIJoystick::CreateDevice(GUID *guid)\n");
		}
    }
	
	// Check to see that Direct Input has been created and initialised.
	if(!m_lpDI) 
	{
		OutputDebugString("Failed to Create DI 7 interface to device in CDIJoystick::CreateDevice(GUID *guid) m_lpDI not initialised.\n");
		return false;
	}

	// Attempt to create the device based on the GUID passed to this routine
	//hr=m_lpDI->CreateDeviceEx(*guid,IID_IDirectInputDevice8,(void**)&m_lpDIDevice,NULL);

	hr = m_lpDI->CreateDevice(*guid,&m_lpDIDevice,NULL);
	if(FAILED(hr))
	{
		OutputDebugString("Failed to Create DI 7 interface to device in CDIJoystick::CreateDevice(GUID *guid)\n");
		return false;
	}

	// We must have been successful at this point.
	// Therefore copy the GUID to this members instance for future reference.
	//memcpy(&m_JoystickGUID,guid,sizeof(GUID));   原文件中使用，但个人认为没有必要，因为形参guid就是指向m_JoystickGUID的指针

	return true;
}

//////////////////////////////////////////////////////////////////////
//
// Return How Many Buttons The Attached Device Has Installed
// When giving the player an option of which joystick to use
// You may wish to evaluate the buttons available per attached device.
// Returns the number of buttons for the currently selected device.
//
//////////////////////////////////////////////////////////////////////
int CDIJoystick::HowManyButtons()
{
    DIDEVICEOBJECTINSTANCE didoi;
    DWORD x;
    DWORD dwOfs;
	int count=0;
	HRESULT hr=NULL;
	
	ClearFriendlyButtonNames();

	//if(m_lpDIDevice)
	if(InitDevice())
	{
		ZeroMemory(&didoi,sizeof(DIDEVICEOBJECTINSTANCE));
		didoi.dwSize = sizeof( didoi );

		for ( x = 0; x < 32; x++ )
		{
			dwOfs = DIJOFS_BUTTON( x ); 

			hr=m_lpDIDevice->GetObjectInfo( &didoi, dwOfs, DIPH_BYOFFSET );
            
			if ( SUCCEEDED( hr ) )
			{
				count++;
				TCHAR* name=new char[sizeof(didoi.tszName)];

				// Should include UNICODE support here.
				strcpy(name,didoi.tszName);

				// Add the button name to the Pointer List for future reference.
				m_DIButtonNames.AddTail(name);
			}
			else
			{
				OutputDebugString(GetDIError(hr));
			}
		}
	}
	return count;	// How many buttons did we find?
}

////////////////////////////////////////////////////////////////////////
//
// Shutdown the the link list of Friendly Button Names
//
////////////////////////////////////////////////////////////////////////
void CDIJoystick::ClearFriendlyButtonNames()
{
	try
	{
		if(!m_DIButtonNames.IsEmpty())
		{
			POSITION pos=m_DIButtonNames.GetHeadPosition();
			LPVOID del=NULL;

			while(pos)
			{
				del=static_cast<LPVOID>(m_DIButtonNames.GetNext(pos));
				if(del)
				{
					delete del;
				}
			}
			m_DIButtonNames.RemoveAll();
		}
		//m_DIButtonNames.RemoveAll();
	}
	catch(...)
	{
		OutputDebugString("Some unforseen error occurred in CDIJoystick::ClearFriendlyButtonNames()\n");
	}
}

//////////////////////////////////////////////////////////////////////
//
// Initialise The Joystick!
//
//////////////////////////////////////////////////////////////////////
bool CDIJoystick::InitJoystick()
{
    // Set range. 
    // Note: range, deadzone, and saturation are being set for the
    // entire device. This could have unwanted effects on
    // sliders, dials, etc.

    DIPROPRANGE diprg; 
 
    diprg.diph.dwSize       = sizeof( diprg ); 
    diprg.diph.dwHeaderSize = sizeof( diprg.diph ); 
    diprg.diph.dwObj        = 0; 
    diprg.diph.dwHow        = DIPH_DEVICE; 
    diprg.lMin              = JOYMIN; 
    diprg.lMax              = JOYMAX; 
 
    if ( FAILED( m_lpDIDevice->SetProperty( DIPROP_RANGE, &diprg.diph ) ) )
        return FALSE; 

    // Set deadzone.
    DIPROPDWORD dipdw;

    dipdw.diph.dwSize       = sizeof( dipdw ); 
    dipdw.diph.dwHeaderSize = sizeof( dipdw.diph ); 
    dipdw.diph.dwObj        = 0;
    dipdw.diph.dwHow        = DIPH_DEVICE;
    dipdw.dwData            = JOYDEAD;

    if ( FAILED( m_lpDIDevice->SetProperty( DIPROP_DEADZONE, &dipdw.diph ) ) )
        return FALSE;

    // Set saturation.
    dipdw.dwData            = JOYSAT;
    if ( FAILED( m_lpDIDevice->SetProperty( DIPROP_SATURATION, &dipdw.diph ) ) )
        return FALSE;

    // Find out if force feedback available.
    DIDEVCAPS didc;
    didc.dwSize = sizeof( DIDEVCAPS );
    if ( FAILED( m_lpDIDevice->GetCapabilities( &didc ) ) ) 
        return FALSE;
    m_FFAvailable = ( didc.dwFlags & DIDC_FORCEFEEDBACK );

    // If it's a force feedback stick, turn off autocenter so it doesn't
    // get in the way of our effects.
    if ( m_FFAvailable )
    {
        DIPROPDWORD DIPropAutoCenter;
        DIPropAutoCenter.diph.dwSize = sizeof( DIPropAutoCenter );
        DIPropAutoCenter.diph.dwHeaderSize = sizeof( DIPROPHEADER );
        DIPropAutoCenter.diph.dwObj = 0;
        DIPropAutoCenter.diph.dwHow = DIPH_DEVICE;
        DIPropAutoCenter.dwData = 0;

        m_lpDIDevice->SetProperty( DIPROP_AUTOCENTER, 
                               &DIPropAutoCenter.diph );
    } 
    return TRUE;
}

//////////////////////////////////////////////////////////////////////
//
// Initialise The Joystick Device
//
//////////////////////////////////////////////////////////////////////
bool CDIJoystick::InitDevice()
{
    HRESULT hr;
    DIDEVICEINSTANCE    diDeviceInstance;

	// Just a precaution when Enumerating Devices and button Names if you create
	// An options Dialog before creating your main gaming window.
	// Then simply use the desktop window, temporarily!
	if(!m_hwnd)m_hwnd=::GetDesktopWindow();

    // Release device if it already exists.
    if ( m_lpDIDevice ) 
    {
        //if ( m_FFAvailable ) ReleaseEffects(); 
        
		Acquire( false);

        hr=m_lpDIDevice->Release();
		if(FAILED(hr))
		{
			OutputDebugString("Error Releasing Interface in CDIJoystick::InitDevice()\n");
			OutputDebugString(GetDIError(hr));
		} 
		else m_lpDIDevice=NULL;
    }

    // Create game device and set IDirectInputDevice7 interface in m_lpDIDevice.
    if(!CreateDevice( &m_JoystickGUID ))
	{
		OutputDebugString("Failed to create device in CDIJoystick::InitDevice()\n");
		return false;
	}

    // Find out what type it is and set data format accordingly.

    diDeviceInstance.dwSize = sizeof( DIDEVICEINSTANCE );

    hr=m_lpDIDevice->GetDeviceInfo( &diDeviceInstance );
	if ( FAILED( hr ) ) 
	{
		OutputDebugString("Failed to obtain device info in CDIJoystick::InitDevice()\n");
		OutputDebugString(GetDIError(hr));
		return false;
	}

	// Set the data format to be a Joystick
	hr = m_lpDIDevice->SetDataFormat( &c_dfDIJoystick );  //设置数据格式
	if ( FAILED( hr ) ) 
	{
		OutputDebugString("Failed to create device in CDIJoystick::InitDevice()\n");
		OutputDebugString(GetDIError(hr));
		return false;
	}

    // Set cooperative level. 
    DWORD cl, cl1;
	cl = DISCL_EXCLUSIVE;

	// Set foreground level for release version, but use background level
	// for debugging so we don't keep losing the device when switching to 
	// a debug window. 

    //cl1 = DISCL_FOREGROUND;
	cl1 = DISCL_BACKGROUND;
#ifdef _DEBUG
    cl1 = DISCL_BACKGROUND;
#endif

	// now set the co-operation level.
	//hr=m_lpDIDevice->SetCooperativeLevel( m_hwnd, cl | cl1 );
	hr = m_lpDIDevice->SetCooperativeLevel(m_hwnd,DISCL_BACKGROUND|DISCL_EXCLUSIVE);   //希望使用后台模式和独占模式，这样应用程序在前台和后台都能够使用DirectInput设备
    if ( FAILED( hr ))
    {
        OutputDebugString( "Failed to set game device cooperative level.\n" );
		OutputDebugString(GetDIError(hr));
        return false;
    }

    // Set up the data buffer.
    DIPROPDWORD dipdw =
    {
        // The header.
        {
            sizeof( DIPROPDWORD ),      // diph.dwSize
            sizeof( DIPROPHEADER ),     // diph.dwHeaderSize
            0,                          // diph.dwObj
            DIPH_DEVICE,                // diph.dwHow
        },
        // Number of elements in data buffer.
        BUFFERSIZE              // dwData
    };

    hr=m_lpDIDevice->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph );
	if(FAILED(hr))
    {
        OutputDebugString( "Failed to set up Data Buffer property.\n" );
		OutputDebugString(GetDIError(hr));
        return false;
    }

	// Resest the Force Feedback Flag
    m_FFAvailable = FALSE;

	// Try and initialise the Joystick!
    if ( !InitJoystick() ) return FALSE;  

    // In case you were wondering, this is not a good time to acquire the 
    // device. For one thing, we can't acquire in foreground mode here 
    // because the options dialog may be open. We'll acquire it when the
    // main window is activated.

    return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Either Acquire or Unacquire the Device!
//
////////////////////////////////////////////////////////////////////////////////
bool CDIJoystick::Acquire(bool state)
{
    HRESULT hr;

	if(!m_lpDIDevice)
	{
		OutputDebugString("Error in CDIJoystick::Acquire(bool state)\nDevice Has Not Been Created.\n");
		return false;
	}

    if ( !state )  // Unacquire.
    {
        hr = m_lpDIDevice->Unacquire();
    }
    else       // Acquire.
    {
        // This could take a while with FF.
        ::SetCursor( m_hCursorWait );

        hr = m_lpDIDevice->Acquire();
        if ( SUCCEEDED( hr ) ) 
        {
            // Initialize effects; ignore failure and just
            // pretend FF not there.
            if ( m_FFAvailable )      // First set when device initialized.
            {
                //m_FFAvailable = InitFFEffects();
            }
        }
    }

	if(FAILED(hr))
	{
		OutputDebugString("Failed in CDIJoystick::Acquire(bool state)\n");
		OutputDebugString(GetDIError(hr));
		return false;
	}
	return true;
}

//////////////////////////////////////////////////////////////////////
//
// Set the HWND that will be used when Acquiring Devices!
//
//////////////////////////////////////////////////////////////////////
void CDIJoystick::SetHWND(HWND hwnd)
{
	//Shutdown();
	m_hwnd=hwnd;
	//m_EnumerationStarted=false;
	m_hInstance=GetModuleHandle(NULL);

	// Initialise Direct Input
	//Initialise();

	// Start Enumeration of Attached Joysticks.
	//Enumerate_Joysticks();
}

//////////////////////////////////////////////////////////////////////
//
// Set the preferred GUID for the joystick device
//
//////////////////////////////////////////////////////////////////////
void CDIJoystick::SetPreferredDevice(GUID *pguid)
{
	memcpy(&m_JoystickGUID,pguid,sizeof(GUID));
}

//////////////////////////////////////////////////////////////////////
//
// Re-Initialise this object, used when changing HWND or Device
// Not yet implemented.
//
//////////////////////////////////////////////////////////////////////
bool CDIJoystick::ReInitialise()
{
//	m_EnumerationStarted=false;
//	m_hInstance=GetModuleHandle(NULL);
//	Enumerate_Joysticks();
	return true;
}

//////////////////////////////////////////////////////////////////////
//
// Return Error Text From HRESULT
//
//////////////////////////////////////////////////////////////////////
TCHAR* CDIJoystick::GetDIError(HRESULT error)
{
	switch(error)
	{
	case E_PENDING : return _T("E_PENDING : Data Not Available.\n");
		break;
	case E_HANDLE :  return _T("E_HANDLE : The HWND parameter is not a valid top-level window that belongs to the process.\n");
		break;
	case DIERR_UNSUPPORTED : return _T("DIERR_UNSUPPORTED : The function called is not supported at this time. This value is equal to the E_NOTIMPL standard COM return value.\n");
		break;
	case DIERR_UNPLUGGED : return _T("DIERR_UNPLUGGED : The operation could not be completed because the device is not plugged in.\n");
		break;
	case DIERR_REPORTFULL : return _T("DIERR_REPORTFULL : More information was requested to be sent than can be sent to the device.\n");
		break;
	case DIERR_READONLY : return _T("DIERR_READONLY : The specified property cannot be changed. This value is equal to the E_ACCESSDENIED standard COM return value.\n");
		break;
	case DIERR_OUTOFMEMORY : return _T("DIERR_OUTOFMEMORY : The DirectInput subsystem could not allocate sufficient memory to complete the call. This value is equal to the E_OUTOFMEMORY standard COM return value.\n");
		break;
//	case DIERR_OTHERAPPHASPRIO : return _T("DIERR_OTHERAPPHASPRIO : Another application has a higher priority level, preventing this call from succeeding. This value is equal to the E_ACCESSDENIED standard COM return value. This error can be returned when an application has only foreground access to a device but is attempting to acquire the device while in the background. ");
//		break;
	case DIERR_OLDDIRECTINPUTVERSION : return _T("DIERR_OLDDIRECTINPUTVERSION : The application requires a newer version of DirectInput.\n");
		break;
	case DIERR_OBJECTNOTFOUND : return _T("DIERR_OBJECTNOTFOUND : The requested object does not exist.\n");
		break;
	case DIERR_NOTINITIALIZED : return _T("DIERR_NOTINITIALIZED : This object has not been initialized.\n");
		break;
//	case DIERR_NOTFOUND : return _T("DIERR_NOTFOUND : The requested object does not exist.\n");
//		break;
	case DIERR_NOTEXCLUSIVEACQUIRED : return _T("DIERR_NOTEXCLUSIVEACQUIRED : The operation cannot be performed unless the device is acquired in DISCL_EXCLUSIVE mode.\n");
		break;
	case DIERR_NOTDOWNLOADED : return _T("DIERR_NOTDOWNLOADED : The effect is not downloaded.\n");
		break;
	case DIERR_NOTBUFFERED : return _T("DIERR_NOTBUFFERED : The device is not buffered. Set the DIPROP_BUFFERSIZE property to enable buffering.\n");
		break;
	case DIERR_NOTACQUIRED : return _T("DIERR_NOTACQUIRED : The operation cannot be performed unless the device is acquired.\n");
		break;
	case DIERR_NOINTERFACE : return _T("DIERR_NOINTERFACE : The specified interface is not supported by the object. This value is equal to the E_NOINTERFACE standard COM return value.\n");
		break;
	case DIERR_NOAGGREGATION : return _T("DIERR_NOAGGREGATION : This object does not support aggregation.\n");
		break;
	case DIERR_MOREDATA : return _T("DIERR_MOREDATA : Not all the requested information fit into the buffer.\n");
		break;
	case DIERR_INVALIDPARAM : return _T("DIERR_INVALIDPARAM : An invalid parameter was passed to the returning function, or the object was not in a state that permitted the function to be called. This value is equal to the E_INVALIDARG standard COM return value.\n");
		break;
	case DIERR_INPUTLOST : return _T("DIERR_INPUTLOST : Access to the input device has been lost. It must be reacquired.\n");
		break;
	case DIERR_INCOMPLETEEFFECT : return _T("DIERR_INCOMPLETEEFFECT : The effect could not be downloaded because essential information is missing. For example, no axes have been associated with the effect, or no type-specific information has been supplied.\n");
		break;
//	case DIERR_HANDLEEXISTS : return _T("DIERR_HANDLEEXISTS : The device already has an event notification associated with it. This value is equal to the E_ACCESSDENIED standard COM return value.\n");
//		break;
	case DIERR_GENERIC : return _T("DIERR_GENERIC : An undetermined error occurred inside the DirectInput subsystem. This value is equal to the E_FAIL standard COM return value.\n");
		break;
	case DIERR_HASEFFECTS : return _T("DIERR_HASEFFECTS : The device cannot be reinitialized because there are still effects attached to it.\n");
		break;
	case DIERR_EFFECTPLAYING : return _T("DIERR_EFFECTPLAYING : The parameters were updated in memory but were not downloaded to the device because the device does not support updating an effect while it is still playing.\n");
		break;
	case DIERR_DEVICENOTREG : return _T("DIERR_DEVICENOTREG : The device or device instance is not registered with DirectInput. This value is equal to the REGDB_E_CLASSNOTREG standard COM return value.\n");
		break;
	case DIERR_DEVICEFULL : return _T("DIERR_DEVICEFULL : The device is full.\n");
		break;
	case DIERR_BETADIRECTINPUTVERSION : return _T("DIERR_BETADIRECTINPUTVERSION : The application was written for an unsupported prerelease version of DirectInput.\n");
		break;
	case DIERR_BADDRIVERVER : return _T("DIERR_BADDRIVERVER : The object could not be created due to an incompatible driver version or mismatched or incomplete driver components.\n");
		break;
	case DIERR_ALREADYINITIALIZED : return _T("DIERR_ALREADYINITIALIZED : This object is already initialized\n");
		break;
	case DIERR_ACQUIRED : return _T("DIERR_ACQUIRED : The operation cannot be performed while the device is acquired.\n");
		break;
	case DI_TRUNCATEDANDRESTARTED : return _T("DI_TRUNCATEDANDRESTARTED : Equal to DI_EFFECTRESTARTED | DI_TRUNCATED\n");
		break;
	case DI_TRUNCATED : return _T("DI_TRUNCATED : The parameters of the effect were successfully updated, but some of them were beyond the capabilities of the device and were truncated to the nearest supported value.\n");
		break;
	case DI_PROPNOEFFECT : return _T("DI_PROPNOEFFECT : The change in device properties had no effect. This value is equal to the S_FALSE standard COM return value.\n");
		break;
	case DI_POLLEDDEVICE : return _T("DI_POLLEDDEVICE : The device is a polled device. As a result, device buffering does not collect any data and event notifications is not signaled until the IDirectInputDevice7::Poll method is called.\n");
		break;
	case DI_OK : return _T("DI_OK : The operation completed successfully. This value is equal to the S_OK standard COM return value.\n");
		break;
//	case DI_NOTATTACHED : return _T("DI_NOTATTACHED : The device exists but is not currently attached. This value is equal to the S_FALSE standard COM return value.\n");
//		break;
//	case DI_NOEFFECT : return _T("DI_NOEFFECT : The operation had no effect. This value is equal to the S_FALSE standard COM return value.\n");
//		break;
	case DI_EFFECTRESTARTED : return _T("DI_EFFECTRESTARTED : The effect was stopped, the parameters were updated, and the effect was restarted.\n");
		break;
	case DI_DOWNLOADSKIPPED : return _T("The parameters of the effect were successfully updated, but the effect could not be downloaded because the associated device was not acquired in exclusive mode.\n");
		break;
//	case DI_BUFFEROVERFLOW : return _T("DI_BUFFEROVERFLOW : The device buffer overflowed and some input was lost. This value is equal to the S_FALSE standard COM return value.\n");
//		break;
	default: return _T("Unknown Error Code.\n");
	}
}


//////////////////////////////////////////////////////////////////////////////////////////
//
// Update member variables to reflect the state of the device
//
//////////////////////////////////////////////////////////////////////////////////////////
bool CDIJoystick::PollDevice()
{
	static	int	 loopcount=0;
     
    HRESULT            hr;
    //DIDEVICEOBJECTDATA rgdod[BUFFERSIZE];
    //DWORD              dwItems; 

	ZeroMemory(&m_dijs,sizeof(m_dijs));

	// Has device been initialised ?
	if (!m_lpDIDevice) 
	{
		// Try and initialise device
		if(!InitDevice())
		OutputDebugString("Failed To Initialise and Poll Joystick in CDIJoystick::PollDevice()\n");
		return false;
	}

	hr=m_lpDIDevice->Poll();  // May be unnecessary but never hurts.
	
	if(FAILED(hr))
	{
		OutputDebugString("Failed To Poll Joystick in CDIJoystick::PollDevice()\n");
		OutputDebugString(GetDIError(hr));
	}

getImmediateData:
	if(loopcount>20) return false;	// Infinite Loop Protection
    hr = m_lpDIDevice->GetDeviceState( sizeof( DIJOYSTATE ), &m_dijs ); 

    // The data stream was interrupted. Reacquire the device and try again.
	if ( hr == DIERR_INPUTLOST )
    {
		OutputDebugString("Failed To Obtain Immediate Device State in CDIJoystick::PollDevice()\n");
		OutputDebugString(GetDIError(hr));

		// Increment Infinite Loop Protection Counter and try again.
		loopcount++;

		// Try and acquire device and start again.
        if ( Acquire( true ) )
            goto getImmediateData;
    }

        // We can't get the device because it has not been acquired so try and acquire it.
    if ( hr == DIERR_NOTACQUIRED )
    {
		// Increment Infinite Loop Protection Counter.
		loopcount++;

		OutputDebugString("Device Not Acquired Trying Again immediate CDIJoystick::PollDevice()\n");
		if(!Acquire(true))
		{
			OutputDebugString("Unable to acquire Immediate Device in CDIJoystick::PollDevice() Quitting\n");
			return false;
		}
		// Try and get buffered data if device is buffered!
		goto getImmediateData;
    }

	if ( FAILED(hr))
    {
		OutputDebugString("Unable to obtain Immediate Data from Device in CDIJoystick::PollDevice() Quitting\n");
		return false;
    }

	// First set immediate direction if your only interested in basic movement
    if ( m_dijs.lX < 0 ) m_JoyLeft=true; else m_JoyLeft=false;
	if ( m_dijs.lX > 0 ) m_JoyRight=true; else m_JoyRight=false;
	if ( m_dijs.lY < 0 ) m_JoyUp=true; else m_JoyUp=false;
	if ( m_dijs.lY > 0 ) m_JoyDown=true; else m_JoyDown=false;

	m_JoyFire1=false;

#ifdef _DEBUG
	int firecount=0;
#endif
	for(int i=0;i<sizeof(m_dijs.rgbButtons);i++)
	{
		if(m_dijs.rgbButtons[i]&0x80)
		{
#ifdef _DEBUG
			firecount++;
#endif
			m_JoyFire[i]=true;
			m_JoyFire1=true;
		}
		else m_JoyFire[i]=false;
	}
#ifdef _DEBUG
	if(firecount>0) 
	{
		OutputDebugString("Many Buttons Pressed\n");
	}
#endif
	return true;
}

//////////////////////////////////////////////////////////////////////
//
// Run the joystick Control Panel!
//
//////////////////////////////////////////////////////////////////////
void CDIJoystick::RunControlPanel()
{
	if(!m_lpDI) return;
	m_lpDI->RunControlPanel(m_hwnd,NULL);
}

void CDIJoystick::StartToDo()
{
	// Initialise Direct Input
	Initialise();

	// Start Enumeration of Attached Joysticks.
	Enumerate_Joysticks();
}
