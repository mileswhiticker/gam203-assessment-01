//////////////////////////////////////////////////////////////////////////
//
// GAM203
// Triangle class
// Triangle.h
// 
// Scott Taylor
// Qantm College
//
//////////////////////////////////////////////////////////////////////////

#if !defined(TRIANGLE_H)
#define TRIANGLE_H

#include "Drawable.h"

#include <d3d9.h>
#include <d3d9types.h>

class Triangle : public Drawable
{
public:
  // Vertex format we will use to describe our vertices (must match FVF format below)
  struct VertexData
  {
    D3DVECTOR pos;  // XYZ position
    D3DCOLOR col;  // Diffuse colour (aka. 'vert colour')
  };

  // DirectX's way of identifying what's in our vertex structure (we bitwise OR these values)
  static const DWORD VERTEX_FORMAT_FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;

public:
  virtual bool CreateObject(IDirect3DDevice9* a_pDevice);
  virtual void Render(float a_dt, IDirect3DDevice9* a_pDevice);
};

#endif  // TRIANGLE_H
