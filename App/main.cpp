#include "Window.h"
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

int main(int argc, char** argv[])
{
	Window::init(GetModuleHandle(0));
	Window::createWindow();
	Window::run();

	return 0;
}