/////////////////////////////////////////////////////////////////////////
//
// GAM203
// Basic D3DX mesh
// MeshBasic.cpp
// 
// Scott Taylor
// Qantm College
//
//////////////////////////////////////////////////////////////////////////

#include "MeshBasic.h"

#include <d3dx9.h>

MeshBasic::MeshBasic()
  : m_pMesh(NULL)
{
}

MeshBasic::~MeshBasic()
{
  if (m_pMesh)
  {
    m_pMesh->Release();
    m_pMesh = NULL;
  }
}

//
// Sets up this object with some data
// Returns true if successful
//
bool MeshBasic::CreateObject(IDirect3DDevice9* a_pDevice)
{
  if (!a_pDevice)
  {
    return false;
  }

  // Create a shape in our mesh helper
  HRESULT result = D3DXCreateTeapot(a_pDevice,&m_pMesh,NULL);

  //@TODO: Create a D3DX mesh! result = D3DXCreateTeapot() or D3DXCreateTorus() or some other D3DXCreate...

  if (result != D3D_OK)
  {
    return false;
  }

  // Set up our material
  ZeroMemory(&m_mat, sizeof(m_mat));  // Zero out the material (ie. all colours black, power set to zero)
  //m_mat.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
  //m_mat.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
  m_mat.Diffuse = D3DXCOLOR(3.0f, 3.0f, 3.0f, 3.0f);

  //Well look at more material stuff later

  return true;
}

//
// Draw this object
//
void MeshBasic::Render(float a_dt, IDirect3DDevice9* a_pDevice)
{
  if (a_pDevice && m_pMesh)
  {
    a_pDevice->SetMaterial(&m_mat);
    a_pDevice->SetTexture(0, NULL);  // D3DX shapes don't have UVs, can't be textured

    //@HACK: Dodgy static, doesn't work for multiple MeshBasic objects!
    static float hackAngle = 0.0f;
    hackAngle += (float)a_dt*0.1f;

    // Create a translation matrix
    D3DXMATRIX translationMat;
    D3DXMatrixTranslation(&translationMat, 3, 0, 0);

    // Create an X rotation matrix
    D3DXMATRIX rotMatX;
    D3DXMatrixRotationX(&rotMatX, hackAngle);

    // Create a Y rotation matrix
    D3DXMATRIX rotMatY;
    D3DXMatrixRotationY(&rotMatY, hackAngle / 5);

    // Calculate our world transform - a combination of a rotation and a translation
    // We can combine these into one matrix by multiplying them together (order is important!)
    // We apply the rotation THEN the translation
    D3DXMATRIX worldMatrix = rotMatX * rotMatY * translationMat;
    a_pDevice->SetTransform(D3DTS_WORLD, &worldMatrix);

    // Draw our mesh
    m_pMesh->DrawSubset(0);  // So easy with ID3DXMesh!!
  }
}
