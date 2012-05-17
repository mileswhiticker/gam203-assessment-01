#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#define WIN32_LEAN_AND_MEAN
#include "windows.h"

#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>
#include "dxmgr.h"

#include "utils.h"

// include the Direct3D Library file
#pragma comment (lib, "d3d9.lib")

class WndwMgr
{
public:
	static WndwMgr& GetInstance(HINSTANCE a_hInst)
	{
		static WndwMgr* instance = NULL;
		if(!instance)
			instance = new WndwMgr(a_hInst);
		return *instance;
	}
	DXMgr& GetDxMgr();
	//
	WNDCLASSW m_WindowClass;
	LPDIRECT3D9 d3d;				// the pointer to our Direct3D interface
	LPDIRECT3DDEVICE9 d3ddev;		// the pointer to the device class
	//
	void cleanUp();
private:
	WndwMgr(HINSTANCE a_hInst);
	//
	void initD3D(HWND hWnd);
	DXMgr& dx_manager;
};

#endif