#include "Window.h"

/**
* Generalized Internal WndProc
* Handles Window Messages that the DefWindowProc doesn't usually handle.
* @param hWnd : Handle to the Window
* @param msg : Message to process
* @param wParam : WPARAM
* @param lParam : LPARAM
* @result LRESULT : Result of the Proc
*/
LRESULT InternalWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(EXIT_SUCCESS);

		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

// @name 

Window::Window(int* code_rs, HINSTANCE hInstance, LPCWSTR lpszClassName, int ClsExtra, int WndExtra, HBRUSH BackgroundBrush, LPWSTR hIconRes, LPWSTR hCursorRes, UINT ClassStyle, UINT WndStyle, LPCWSTR Title, int X, int Y, int SizeX, int SizeY) : lpszClassName(lpszClassName), hInstance(hInstance) {
	//* preliminari

	this->__WindowClass.cbSize = sizeof(WNDCLASSEX);
	this->__WindowClass.hInstance = this->hInstance;
	this->__WindowClass.lpszClassName = this->lpszClassName;
	//* bo
	this->__WindowClass.cbClsExtra = ClsExtra;
	this->__WindowClass.cbWndExtra = WndExtra;
	//* stili
	this->__WindowClass.style = ClassStyle;
	this->__WindowClass.hbrBackground = BackgroundBrush;

	this->__WindowClass.hCursor = LoadCursor(hInstance, hCursorRes);

	this->__WindowClass.hIcon = LoadIcon(this->hInstance, hIconRes);
	this->__WindowClass.hIconSm = LoadIcon(this->hInstance, hIconRes);
	//* ultimatum
	this->__WindowClass.lpszMenuName = NULL;
	this->__WindowClass.lpfnWndProc = InternalWndProc;

	if (!RegisterClassEx(&this->__WindowClass)) {
		MessageBox(NULL, L"Window Construction cannot proceed due to an unexpected Class-Registering error. Code 0x260a", L"Window Construction Error", MB_ICONERROR | MB_OK);

		*(code_rs) = WNDCLASSEX_CONSTRUCTION_ERROR; // restituisce l'error code per controllare se la costruzione della classe e' andata a buon fine.

		return;
	}

	this->CurrentHWND = CreateWindow(this->lpszClassName, Title, WndStyle, X, Y, SizeX, SizeY, NULL, NULL, this->hInstance, NULL);

	if (!this->CurrentHWND) {
		MessageBox(NULL, L"Window Construction cannot proceed due to an unexpected Window Creation error. Code 0x271e", L"Window Construction Error", MB_ICONERROR | MB_OK);

		*(code_rs) = CREATEWINDOW_CONSTRUCTION_ERROR;

		return;
	}

	this->UpdateWindowDisplayMode(SW_SHOWNORMAL);
	UpdateWindow(this->CurrentHWND);
}
Window::~Window() { // ye whatever
	DestroyWindow(this->CurrentHWND);
}

int Window::MessagePump() {
	while (GetMessage(&this->CurrentMSG, this->CurrentHWND, 0, 0)) {
		TranslateMessage(&this->CurrentMSG);
		DispatchMessage(&this->CurrentMSG);
	}

	return (int)this->CurrentMSG.message;
}

HWND* Window::CreateSubwindow(LPCWSTR SwtClassname, LPCWSTR WndText, UINT OverlappedStyle, int X, int Y, int SizeX, int SizeY) {
	HWND g = CreateWindowEx(WS_EX_CLIENTEDGE, SwtClassname, WndText, WS_CHILD | WS_VISIBLE | OverlappedStyle, X, Y, SizeX, SizeY, this->CurrentHWND, NULL, this->hInstance, NULL);

	this->subwindows.push_back(g);

	return &g;
}

void Window::SetTitle(LPCWSTR Title) {
	SetWindowText(this->CurrentHWND, Title);
}

void Window::UpdateWindowDisplayMode(int nShowCmd) {
	ShowWindow(this->CurrentHWND, nShowCmd);
}

HWND Window::GetHWND() {
	return this->CurrentHWND;
}

LPCWSTR Window::GetClassname() {
	return this->lpszClassName;
}

HINSTANCE Window::GetRegisteredHINSTANCE() {
	return this->hInstance;
}
