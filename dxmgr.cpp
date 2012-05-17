#include "DXMgr.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9")
#pragma comment(lib, "d3dx9")

static DXMgr* s_pInst = NULL;

DXMgr& DXMgr::GetInstance()
{
	if (!s_pInst)
	{
		s_pInst = new DXMgr();
	}
	return *s_pInst;
}

bool DXMgr::Init(HWND a_hWnd)
{
	// Initialise Direct3D

	//Call Direct3DCreate9(D3D_SDK_VERSION), store return value in m_pD3D, error check
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	// Initialise presentation parameters for our new device
	D3DPRESENT_PARAMETERS presentParams; 
	ZeroMemory(&presentParams, sizeof(presentParams));
	presentParams.Windowed = TRUE;
	presentParams.SwapEffect = D3DSWAPEFFECT_FLIP;
	presentParams.hDeviceWindow = a_hWnd;
	presentParams.EnableAutoDepthStencil = TRUE;
	presentParams.AutoDepthStencilFormat = D3DFMT_D24S8;

	// Create a device
	HRESULT result = m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, a_hWnd,
	D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &presentParams, &m_pDevice);
	if (FAILED(result))
	{
		// Failed to create device, undo initialisation of D3D
		m_pD3D->Release();
		m_pD3D = NULL;
		return false;
	}
	return true;
}

void DXMgr::Shutdown()
{
	// Destroy device
	if (m_pDevice)
	{
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	// Destroy Direct3D
	if (m_pD3D)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}

IDirect3D9* DXMgr::GetD3D() const
{
	return m_pD3D;
}

IDirect3DDevice9* DXMgr::GetDevice() const
{
	return m_pDevice;
}
