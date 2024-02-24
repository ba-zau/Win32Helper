# Win32Helper
A Simple Win32 Window Wrapper to ease development of GUI applications. I probably will update it in the future...

<img src="https://www.zau.lol/window.png">

## Usage:

- Step 1:
Include Window.h
- Step 2:
Implement the WinMain Function:

```cpp
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nShowCmd) {}
```
- Step 3:
Similarly to HRESULTS, Win32Helper will give back an error code in case construction fails, along with displaying a Message Box to the user with the details needed about the Error.

```
...
  int rs = 0; // error code
```
- Step 4:
Create the Root Window
```cpp
Window* wnd = new Window(&rs, hInstance, L"TestApp", 0, 0, (HBRUSH) COLOR_WINDOW, IDI_APPLICATION, IDC_ARROW, CS_VREDRAW | CS_HREDRAW, WS_OVERLAPPEDWINDOW, L"Sample Window", 0, 0, 640, 480);
```
- Step 5:
Check the error code int
```cpp
if (rs != 0) return rs; // ye
```
- Step 6:
Run the Message Pump synchronously and return its value when the pump breaks out of the loop.

```cpp
return wnd->MessagePump();
```

### Et voila

You now have a simple app up and running.
