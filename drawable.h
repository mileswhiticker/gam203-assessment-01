//////////////////////////////////////////////////////////////////////////
//
// GAM203
// Drawable base class
// Drawable.h
// 
// Scott Taylor
// Qantm College
//
//////////////////////////////////////////////////////////////////////////

#if !defined(DRAWABLE_H)
#define DRAWABLE_H

// Forward declarations of pointer types used below; saves us a #include here
struct IDirect3DDevice9;
struct IDirect3DVertexBuffer9;
struct IDirect3DIndexBuffer9;

#include <d3d9.h>
#include <d3dx9math.h>

class Drawable
{
public:
	Drawable();
	virtual ~Drawable();  // Virtual destructor is important if we have any virtual functions!

	// These are pure virtual functions...
	// This means we cannot instantiate (create) an object of type Drawable
	// We have to instantiate a derived class that defines these functions
	virtual bool CreateObject(IDirect3DDevice9* a_pDevice) = 0;
	virtual void Render(float a_dt, IDirect3DDevice9* a_pDevice) = 0;
	//
	virtual bool ReleaseObject();

protected:
	IDirect3DVertexBuffer9* m_pVertexBuf;
	IDirect3DIndexBuffer9* m_pIndexBuf;
	D3DXMATRIX m_worldMatrix;
};

#endif  // DRAWABLE_H
