#pragma once
#include <Windows.h>

#define FILE_OPEN 1
#define FILE_SAVE 2

namespace Widgets
{
	void init(HWND windowHandle, HINSTANCE programInstance);
	void createChildWidgets();

	HWND getEditHandle();

	namespace // Annonymous namespace
	{
		HWND winHandle;
		HMENU baseMenu;
		HMENU fileMenu;
		HWND editArea;
		HINSTANCE hInstance;
	}
}

namespace EventHandler
{
	void init(HWND hwnd);
	void openFileDialog(HWND editControl);

	namespace
	{
		HWND handle;
	}
}