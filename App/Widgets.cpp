#include "Widgets.h"
#pragma comment(lib, "Comctl32.lib")
#include <CommCtrl.h>
#include <fstream>
#include <iostream>
#include <string>

namespace Widgets
{
	void init(HWND windowHandle, HINSTANCE programInstance)
	{
		winHandle = windowHandle;
		hInstance = programInstance;
	}

	void initCommControls()
	{
		INITCOMMONCONTROLSEX icex;
		icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
		icex.dwICC = ICC_STANDARD_CLASSES;
		InitCommonControlsEx(&icex);
	}

	void createMenus()
	{
		baseMenu = CreateMenu();
		fileMenu = CreateMenu();

		AppendMenuW(fileMenu, MF_STRING, FILE_OPEN, L"&Open");
		AppendMenuW(fileMenu, MF_STRING, FILE_SAVE, L"&Save");

		AppendMenuW(baseMenu, MF_POPUP, (UINT_PTR)fileMenu, L"&File");
		SetMenu(winHandle, baseMenu);
	}

	void createInputControls()
	{
		// Create a font
		HFONT font = CreateFont(23, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Consolas"));

		// The main editing area
		editArea = CreateWindow(L"EDIT", L"", WS_CHILD | WS_VISIBLE | ES_LEFT | ES_MULTILINE | WS_VSCROLL,
			5, 0, 1060, 700, winHandle, nullptr, hInstance, nullptr);

		SendMessage(editArea, WM_SETFONT, (WPARAM)font, (LPARAM)MAKELONG(TRUE, 0));
		
	}

	HWND getEditHandle() { return editArea; }

	void createChildWidgets()
	{
		initCommControls();
		createMenus();
		createInputControls();
	}
}

namespace EventHandler
{
	void init(HWND hwnd)
	{
		handle = hwnd;
	}

	void openFileDialog(HWND editControl)
	{
		OPENFILENAME ofn = { 0 };
		TCHAR szFile[260] = { 0 };
		// Initialize remaining fields of OPENFILENAME structure
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = handle;
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (GetOpenFileName(&ofn) == TRUE)
		{
			std::ifstream file(ofn.lpstrFile);

			std::string line{};
			std::string source{};
			int index = 0;
			if (file.is_open())
			{
				std::cout << "file is open\n";
				while (file)
				{
					if (!file.good())
					{
						break;
					}

					std::getline(file, line);
					source += line;
				}
			}

			SetWindowText(editControl, std::wstring(source.begin(), source.end()).c_str());
		}
	}
}