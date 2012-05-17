#include <iostream>

#include "guicon.h"
#include "app.h"
#include "utils.h"

//application entry point
int WINAPI WinMain(HINSTANCE a_hInst, HINSTANCE a_hPrevInst, LPSTR a_pCmdLine, int a_nCmdShow)
{
	//setup console window
	RedirectIOToConsole();

	//output usage instructions
	std::cout << " Welcome to RenderDemo! \n~Miles Whiticker" << std::endl << std::endl;
	std::cout << "Press ctrl to cycle through demos" << std::endl;
	std::cout << "Press space to cycle through subdemos" << std::endl;

	//instantiate application class
	cApp app(a_hInst);
	
	//message pump
	bool hasQuit = false;
	while (!hasQuit)
	{
		// Process all messages queued up for our window
		MSG msg;
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);		// Let Windows perform some processing on our msg
			DispatchMessage(&msg);		// Send the message to our window procedure
			if (msg.message == WM_QUIT)
			{
				hasQuit = true;
			}
		}
		if(!app.update(0.3f))
			return 0;
	}
	// clean up DirectX, COM and DXMgr
	app.cleanUp();
	return 0;
}
