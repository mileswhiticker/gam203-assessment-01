#ifndef DXMGR_H
#define DXMGR_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

struct IDirect3D9;
struct IDirect3DDevice9;

class DXMgr
{
public:
	static DXMgr& GetInstance();  // Gets the singleton instance
	bool Init(HWND a_hWnd);
	void Shutdown();
	IDirect3D9* GetD3D() const;
	IDirect3DDevice9* GetDevice() const;

private:
	// Private constructor (inaccessible outside class)
	DXMgr::DXMgr() : m_pD3D(NULL), m_pDevice(NULL) {}
	DXMgr::~DXMgr() {}
	// Direct3D stuff
	IDirect3D9* m_pD3D;
	IDirect3DDevice9* m_pDevice;
};

#endif