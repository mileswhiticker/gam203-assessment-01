#include "WindowManager.h"

#include <iostream>

typedef void(*fncptr_keydown_space);

//int (*pt2Function)(float, char, char) = NULL;   
namespace utils
{
	#ifndef KEYPRESS_HANDLER
	#define KEYPRESS_HANDLER
	//fncptr_keydown_space space_fncptr = NULL;
	//default window procedure, can be overwritten later
	void (*space_fncptr)() = NULL;
	LRESULT CALLBACK WndProc(HWND a_hWnd, UINT a_msg, WPARAM a_wParam, LPARAM a_lParam)
	{
		switch (a_msg)
		{
			case(WM_CHAR):
				{
					//WM_CHAR chCharCode = (TCHAR) wParam;
					//lKeyData = lParam;
					//setup letter keypress callback funcs
					switch(a_wParam)
					{
					case('q'):
						{
							utils::keypress_q();
							break;
						}
					case('a'):
						{
							utils::keypress_a();
							break;
						}
					case('w'):
						{
							utils::keypress_w();
							break;
						}
					case('s'):
						{
							utils::keypress_s();
							break;
						}
					case('e'):
						{
							utils::keypress_e();
							break;
						}
					case('d'):
						{
							utils::keypress_d();
							break;
						}
					case('r'):
						{
							utils::keypress_r();
							break;
						}
					case('t'):
						{
							utils::keypress_t();
							break;
						}
					case('1'):
						{
							utils::keypress_1();
							break;
						}
					case('2'):
						{
							utils::keypress_2();
							break;
						}
					}
					break;
				}
			case WM_KEYDOWN:
				{
					//setup special keypress callback funcs
					if(a_wParam == VK_SPACE)
					{
						utils::keypress_space();
						break;
					}
					if(a_wParam == VK_CONTROL)
					{
						utils::keypress_ctrl();
						break;
					}
					if(a_wParam == VK_SHIFT)
					{
						utils::keypress_shift();
						break;
					}
					if(a_wParam == VK_UP)
					{
						utils::keypress_up();
						break;
					}
					if(a_wParam == VK_DOWN)
					{
						utils::keypress_down();
						break;
					}
					if(a_wParam == VK_LEFT)
					{
						utils::keypress_left();
						break;
					}
					if(a_wParam == VK_RIGHT)
					{
						utils::keypress_right();
						break;
					}
					if(a_wParam == VK_TAB)
					{
						utils::keypress_tab();
						break;
					}

					//
					if(a_wParam != VK_ESCAPE)
						break;
				}
			case WM_CLOSE:
			case WM_DESTROY:
				PostQuitMessage(0);  // Posts a WM_QUIT message to our application
				return 0;
			default:
				break;
		}

		// We didn't handle this msg; pass it to the default window procedure
		return DefWindowProc(a_hWnd, a_msg, a_wParam, a_lParam);
	}
	#endif
}

WndwMgr::WndwMgr(HINSTANCE a_hInst)
:	dx_manager(DXMgr::GetInstance())
{
	m_WindowClass.cbClsExtra = NULL;
	m_WindowClass.cbWndExtra = NULL;
	m_WindowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	m_WindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	m_WindowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	m_WindowClass.hInstance = a_hInst;
	m_WindowClass.lpfnWndProc = utils::WndProc;
	m_WindowClass.lpszClassName = L"window";	//WINDOW_CLASS_NAME;
	m_WindowClass.lpszMenuName = NULL;
	m_WindowClass.style = CS_CLASSDC;			// Try putting CS_DROPSHADOW here!

	//register window class
	RegisterClass(&m_WindowClass);

	//create window
	HWND handle = CreateWindowW(L"window",L"Gam203 / Gam204 Miles Whiticker",WS_BORDER|WS_MINIMIZEBOX|WS_SYSMENU,CW_USEDEFAULT,CW_USEDEFAULT,800,800,NULL,NULL,a_hInst,NULL);

	// Draw the window
	UpdateWindow(handle);

	// Set window as visible
	ShowWindow(handle, SW_SHOW);

	//init DXMgr
	dx_manager.Init(handle);

	//set up d3d
	initD3D(handle);
}

// this function initializes and prepares Direct3D for use
void WndwMgr::initD3D(HWND hWnd)
{
    d3d = Direct3DCreate9(D3D_SDK_VERSION);		// create the Direct3D interface

    D3DPRESENT_PARAMETERS d3dpp;				// create a struct to hold various device information

    ZeroMemory(&d3dpp, sizeof(d3dpp));			// clear out the struct for use
    d3dpp.Windowed = TRUE;						// program windowed, not fullscreen
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	// discard old frames
    d3dpp.hDeviceWindow = hWnd;					// set the window to be used by Direct3D

    // create a device class using this information and information from the d3dpp stuct
    d3d->CreateDevice(D3DADAPTER_DEFAULT,
                      D3DDEVTYPE_HAL,
                      hWnd,
                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                      &d3dpp,
                      &d3ddev);
}

// this is the function that cleans up Direct3D and COM
void WndwMgr::cleanUp()
{
    d3ddev->Release();			// close and release the 3D device
    d3d->Release();				// close and release Direct3D
	dx_manager.Shutdown();		// shutdown DXMgr
}

DXMgr& WndwMgr::GetDxMgr()
{
	return dx_manager;
}
