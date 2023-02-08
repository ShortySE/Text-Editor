#include "Window.h"

namespace Window
{
	// Window callback
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
			case WM_CREATE:
				createWidgets(hwnd);
				break;

			case WM_COMMAND:
				switch (wParam)
				{
					case FILE_OPEN:
						EventHandler::openFileDialog(Widgets::getEditHandle());
						MessageBox(NULL, L"Open clicked", L"Windows", MB_OK);
						break;
				}
				break;

			case WM_CLOSE:
				PostQuitMessage(0);
				break;

			default:
				return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}

	// Initializing program critical variables
	void init(HINSTANCE hInstance)
	{
		programInstance = hInstance;
		className = L"WindowClass";
	}

	// Creating the actual window
	void createWindow()
	{
		WNDCLASSEX wndcx = { 0 };
		wndcx.cbSize = sizeof(WNDCLASSEX);
		wndcx.hInstance = programInstance;
		wndcx.lpszClassName = className;
		wndcx.hbrBackground = (HBRUSH)COLOR_WINDOW;
		wndcx.lpfnWndProc = &WindowProc;

		RegisterClassEx(&wndcx);

		windowHandle = CreateWindowEx(0, className, L"Win32 Window", WS_VISIBLE | WS_BORDER | WS_SYSMENU | WS_MINIMIZEBOX,
			CW_USEDEFAULT, CW_USEDEFAULT, 1080, 720, nullptr, nullptr, programInstance, nullptr);

		ShowWindow(windowHandle, SW_SHOW);
	}

	// Main loop
	void run()
	{
		MSG msg = { 0 };
		while (GetMessage(&msg, NULL, 0u, 0u))
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
	}

	// Function to create the widgets
	void createWidgets(HWND hwnd)
	{
		Widgets::init(hwnd, programInstance);
		Widgets::createChildWidgets();
	}
}