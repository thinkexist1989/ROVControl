// DIJoystick.h: interface for the CDIJoystick class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIJOYSTICK_H__D1950720_938F_4491_A3E3_583B1FB98E2C__INCLUDED_)
#define AFX_DIJOYSTICK_H__D1950720_938F_4491_A3E3_583B1FB98E2C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAXJOYBUTTONS 256

class CDIJoystick  
{
public:
	CDIJoystick();
	virtual ~CDIJoystick();

	void StartToDo();

	bool PollDevice();				// Update the device state.
	void SetPreferredDevice(GUID* pguid);  // Set the current GUID for joystick device.
	void SetHWND(HWND hwnd);		// The the HWND to which the joystick will be attached.
	bool InitDevice(void);			// Initialise the Device Pointer
	bool InitJoystick(void);		// Initialise the Joystick
	int HowManyButtons(void);		// Find out how many buttons the attached device has
	bool CreateDevice(GUID *guid);	// Create A Device Pointer for a GUID

	LPCDIDEVICEINSTANCE GetFirstJoystickID(void);	// Get First Joystick Device Data For Enumerated Devices (Must be called before GetNextJoystickID()
	LPCDIDEVICEINSTANCE GetNextJoystickID();		// Get Next Joystick Device Data For Enumerated Devices
	TCHAR* GetFirstButtonName(void);// Get First Joystick Button Friendly Name For Enumerated Device (Must be called before GetNextJoystickID()
	TCHAR* GetNextButtonName();		// Get First Joystick Button Friendly Name For Enumerated Device

	bool IsJoystickLeft(void) {return m_JoyLeft;};	// Is Joystick Being Moved Left?
	bool IsJoystickRight(void) {return m_JoyRight;};// Is Joystick Being Moved Right?
	bool IsJoystickUp(void) {return m_JoyUp;};		// Is Joystick Being Moved Up?
	bool IsJoystickDown(void) { return m_JoyDown;};	// Is Joystick Being Moved Down?
	bool IsJoystickFire(void) { return m_JoyFire1;};// Has Any Fire Button Been Pressed?
	bool IsJoystickFire(int button) { return m_JoyFire[button%MAXJOYBUTTONS];};// Has a specific button been pressed?

	DIJOYSTATE* GetJoystickStateInfo(void) {return &m_dijs;};
	void RunControlPanel(void);		// Run the Control Panel

protected:
	bool Initialise(void);			// Initialise Direct Input 7
	void Shutdown(void);			// Close down and de-allocate any memory assigned to this object.
	bool Enumerate_Joysticks(void);	// Start Enumeration of Attached Joystick Devices

	TCHAR* GetDIError(HRESULT error);// Return Friendly Text to DI7 Error HR
	bool ReInitialise(void);		// ReInitialise DI7 (Not Implemented)

	void ClearFriendlyButtonNames(void);	// Clear Down Allocated Memory for Friendly Button Names
	bool AddDeviceInfo(LPCDIDEVICEINSTANCE lpddi); // Add DI7 Device Info for Enumerated Device
	static BOOL CALLBACK EnumDevicesProc( LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef); // Callback procedure for Enumerating Attached Joystick Devices
	bool Acquire(bool state);		// Acquire/UnAcquire the Joystick

private:
	POSITION m_DevicePOS;			// Used in CPtrList to keep track of next item.
	POSITION m_ButtonPOS;			// Used in CPtrList to keep track of next item.

	bool m_EnumerationStarted;		// Has enumeration started and joystick been found?

	DIJOYSTATE   m_dijs;				// Holds Joystick State Information   所有DIJOYSTATE必须统一，包括SetDataFormat( &c_dfDIJoystick）   可以全部换成DIJOYSTATE2
	
	GUID m_JoystickGUID;			// Current Joystick GUID
	
	CPtrList	m_DIJoystickList;	// Contains a pointer list to Attached Joystick Devices
	CPtrList	m_DIButtonNames;	// Contains a pointer list to Button Names for selected Joystick

	bool m_JoyLeft;					// Generic Direction, Is Joystick Moving Left
	bool m_JoyUp;					// Generic Direction, Is Joystick Moving Up
	bool m_JoyDown;					// Generic Direction, Is Joystick Moving Down
	bool m_JoyRight;				// Generic Direction, Is Joystick Moving Right
	bool m_JoyFire[MAXJOYBUTTONS];	// Which Fire Button Has Been Pressed?
	bool m_JoyFire1;				// Has any fire button been pressed?
	
	
	HCURSOR m_hCursorWait;			// Wait Cursor Handle when Enumerating Feedback Effects
	HWND m_hwnd;					// HWND to which Direct Input will be attached to.
	
	bool m_Initialised;				// Has Direct Input Been Initialised?
	char m_buffer[256];				// A Generic buffer

	HINSTANCE m_hInstance;				// This modules Instance
	LPDIRECTINPUT8  m_lpDI;				// Pointer to Direct Input 7
	LPDIRECTINPUTDEVICE8  m_lpDIDevice;	// Pointer to Direct Input 7 Device

	//////////////////////////////////////////////////////////////////////
	// Used for Force Feed Back, Not Yet Implemented
	//////////////////////////////////////////////////////////////////////
	LPDIRECTINPUTEFFECT  m_lpTriggerEffect;	// For Force Feedback Effects
	LPDIRECTINPUTEFFECT  m_lpStickyEffect;	// For Force Feedback Effects
	LPDIRECTINPUTEFFECT  m_lpResistEffect;	// For Force Feedback Effects
	bool m_TriggerOK;
	BOOL m_FFAvailable;				// Is device Force Feedback Compatible?
	GUID m_TriggerGuid;				// GUID For Force Feed Back Device?
};
#endif // !defined(AFX_DIJOYSTICK_H__D1950720_938F_4491_A3E3_583B1FB98E2C__INCLUDED_)
