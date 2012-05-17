#include "Teapot.h"

#include <d3dx9.h>

Teapot::Teapot()
:	m_pMesh(NULL)
{
	m_Pos.x = 0;
	m_Pos.y = 0;
	m_Pos.z = 0;
}

Teapot::~Teapot()
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
bool Teapot::CreateObject(IDirect3DDevice9* a_pDevice)
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
	m_mat.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	m_mat.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_mat.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	return true;
}

//
// Draw this object
//
void Teapot::Render(float a_dt, IDirect3DDevice9* a_pDevice)
{
  if (a_pDevice && m_pMesh)
  {
    a_pDevice->SetMaterial(&m_mat);
    a_pDevice->SetTexture(0, NULL);  // D3DX shapes don't have UVs, can't be textured

    //@HACK: Dodgy static, doesn't work for multiple Teapot objects!
    static float hackAngle = 0.0f;
    hackAngle += (float)a_dt*0.1f;

	D3DXMATRIX worldMatrix;
	D3DXMatrixIdentity(&worldMatrix);

    // Create an X rotation matrix
    D3DXMATRIX rotMatX;
    D3DXMatrixRotationX(&rotMatX, hackAngle);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &rotMatX);

    // Create a Y rotation matrix
    D3DXMATRIX rotMatY;
    D3DXMatrixRotationY(&rotMatY, hackAngle);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &rotMatX);

    // Create an Z rotation matrix
    D3DXMATRIX rotMatZ;
    D3DXMatrixRotationZ(&rotMatZ, hackAngle);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &rotMatZ);

	// Translation matrix
	D3DXMATRIX transMat;
	D3DXMatrixIdentity(&transMat);
	D3DXMatrixTranslation(&transMat,m_Pos.x,m_Pos.y,m_Pos.z);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &transMat);

    a_pDevice->SetTransform(D3DTS_WORLD, &worldMatrix);

    // Draw our mesh
    m_pMesh->DrawSubset(0);  // So easy with ID3DXMesh!!
  }
}
