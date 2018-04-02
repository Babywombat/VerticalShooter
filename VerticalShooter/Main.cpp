#include <Windows.h>
#include "Graphics.h"

graphics* g_graphics;

/// <summary>
/// Window callback function. Processes messages sent to a window.
/// </summary>
/// <param name="hwnd">A handle to the window.</param>
/// <param name="uMsg">The message.</param>
/// <param name="wParam">Additional message information. The contents of this parameter depend on the value of the uMsg parameter.</param>
/// <param name="lParam">Additional message information. The contents of this parameter depend on the value of the uMsg parameter.</param>
/// <returns></returns>
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		case WM_DESTROY: {
			//Destroy the window
			PostQuitMessage(0);
			return 0;
		}
		case WM_PAINT: {
			//Paint event
			g_graphics->begin_draw();
			//Clear to dark blue
			g_graphics->clear_screen(0.0f, 0.0f, 0.0f);
			
			//Draw random circles
			for (size_t i = 0; i < 100; i++) {
				g_graphics->draw_circle(rand() % 1024, rand() % 768, rand() % 100, 1.0f, 0.0f, 0.0f, 1.0f);
			}
			g_graphics->end_draw();
		}
		default: {
			//Default processing of the message
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}
}

/// <summary>
/// Main entry point of the program.
/// </summary>
/// <param name="hInstance">A handle to the current instance of the application.</param>
/// <param name="hPrevInstance">A handle to the previous instance of the application. </param>
/// <param name="lpCmdLine ">The command line for the application, excluding the program name. </param>
/// <param name="nCmdShow">Controls how the window is to be shown.</param>
/// <returns></returns>
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
	const int WIN_WIDTH = 1024;
	const int WIN_HEIGHT = 768;

	//Create the window class and zero the memory
	WNDCLASSEX windowClassEx;
	ZeroMemory(&windowClassEx, sizeof(WNDCLASSEX));

	//Set window properties
	windowClassEx.cbSize = sizeof(WNDCLASSEX); //Size
	windowClassEx.hbrBackground = (HBRUSH)COLOR_WINDOW; //Background color
	windowClassEx.hInstance = hInstance; //Instance of application
	windowClassEx.lpfnWndProc = WindowProc; //Callback for messages
	windowClassEx.lpszClassName = "MainWindow"; //Name of the class
	windowClassEx.style = CS_HREDRAW | CS_VREDRAW; //Redraw the window when resized

	//Register the window class
	RegisterClassEx(&windowClassEx);

	//Calculate the real size of the window for the overlapped style
	RECT rect = { 0, 0, WIN_WIDTH, WIN_HEIGHT };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	//Create the window and get the handle
	HWND hwnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "MainWindow", "Vertical Shooter",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, 0);

	if (!hwnd) {
		//No window was created
		return -1;
	}

	//Create the graphics
	g_graphics = new graphics();
	if(!g_graphics->init(hwnd)) {
		delete g_graphics;
		return -1;
	}

	//Show the window
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	MSG message;
	//Get all the messages from this thread's windows
	while (GetMessage(&message, NULL, 0, 0)) {
		//Dispatch the message to the callback
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	delete g_graphics;
	return 0;
}