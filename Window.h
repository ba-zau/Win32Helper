#include "stdafx.h"

#define WNDCLASSEX_CONSTRUCTION_ERROR 0x260a
#define CREATEWINDOW_CONSTRUCTION_ERROR 0x271e

#define SWT_TEXT L"static"
#define SWT_BUTTON L"button"
#define SWT_INPUT L"edit"

class Window {
private:
	WNDCLASSEX __WindowClass;
	HWND CurrentHWND = NULL;
	LPCWSTR lpszClassName;
	HINSTANCE hInstance;
	MSG CurrentMSG;

	std::vector<HWND> subwindows;
public:

	Window(int* rc, HINSTANCE hInstance, LPCWSTR lpszClassName, int ClsExtra, int WndExtra, HBRUSH BackgroundBrush, LPWSTR hIconRes, LPWSTR hCursorRes, UINT ClassStyle, UINT WndStyle, LPCWSTR Text, int X, int Y, int SizeX, int SizeY);
	virtual ~Window();
	/**
	* Simple Window-reserved Message Pump
	* A Synchronous Loop that Translates, Dispatches messages and returns the message casted to an integer in case the loop breaks.
	* @result message : Last Recorded Message
	*/
	int MessagePump();

	// subcreator


	/**
	* Subwindow Creator
	* Creates a sub-window such as a Button, Text, Input
	* @param SwtClassname : Classname of the Subwindow. Use SWT macros for easier use of the function
	* @param WndText : Text/Title of the Subwindow.
	* @param OverlappedStyle : Additional Styles to add onto the basic WS_CHILD and WS_VISIBLE styles in the creation of the window.
	* @param X : X Position of the Subwindow.
	* @param Y : Y Position of the Subwindow.
	* @param SizeX : Width of the Subwindow.
	* @param SizeY : Height of the Subwindow.
	*
	* @result HWND* (reference to the subwindow)
	*/
	HWND* CreateSubwindow(LPCWSTR SwtClassname, LPCWSTR WndText, UINT OverlappedStyle, int X, int Y, int SizeX, int SizeY);

	// setter

	/**
	* SetTitle
	* Sets the Title of the Root Window
	* @param 
	*/
	void SetTitle(LPCWSTR Title);

	/**
	* UpdateWindowDisplayMode
	* Sets the Display Mode of the Window
	* @param nShowCmd : New Display Mode of the Root Window
	*/
	void UpdateWindowDisplayMode(int nShowCmd);

	// getter

	/**
	* GetHWND
	* Gets the Root Window Handle
	* @result HWND : Handle to the Root Window
	*/
	HWND GetHWND();

	/**
	* GetClassname
	* Gets the Root Window's Classname
	* @result LPCWSTR : Classname of the Root Window
	*/
	LPCWSTR GetClassname();

	/**
	* GetHWND
	* Gets the Root Window Handle
	* @result HWND : Handle to the Root Window
	*/
	HINSTANCE GetRegisteredHINSTANCE();
};
