//////////////////////////////////////////////////////////////////////////
//
// GAM203
// Basic D3DX mesh
// MeshBasic.h
// 
// Scott Taylor
// Qantm College
//
//////////////////////////////////////////////////////////////////////////

#if !defined(MESHBASIC_H)
#define MESHBASIC_H

#include "Drawable.h"

#include <d3d9.h>
#include <d3d9types.h>

// Forward declarations of pointer types used below; saves us a #include here
struct IDirect3DDevice9;
struct ID3DXMesh;

class MeshBasic : public Drawable
{
public:
  MeshBasic();
  virtual ~MeshBasic();

  virtual bool CreateObject(IDirect3DDevice9* a_pDevice);
  virtual void Render(float a_dt, IDirect3DDevice9* a_pDevice);

private:
  ID3DXMesh* m_pMesh;
  D3DMATERIAL9 m_mat;
};

#endif  // MESHBASIC_H
