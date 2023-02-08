#pragma once
#include <Windows.h>
#include "Widgets.h"

namespace Window
{
	void init(HINSTANCE hInstance);
	void createWindow();
	void run();

	void createWidgets(HWND hwnd);

	namespace
	{
		HINSTANCE programInstance;
		LPCWSTR className;
		HWND windowHandle;
	}
}