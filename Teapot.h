#ifndef TEAPOT_H
#define TEAPOT_H

#include "Drawable.h"

#include <d3d9.h>
#include <d3d9types.h>

struct IDirect3DDevice9;
struct ID3DXMesh;

class Teapot : public Drawable
{
public:
  Teapot();
  virtual ~Teapot();

  virtual bool CreateObject(IDirect3DDevice9* a_pDevice);
  virtual void Render(float a_dt, IDirect3DDevice9* a_pDevice);
  //
  D3DXVECTOR3 m_Pos;
private:
  ID3DXMesh* m_pMesh;
  D3DMATERIAL9 m_mat;
};

#endif