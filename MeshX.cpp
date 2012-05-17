/////////////////////////////////////////////////////////////////////////
//
// GAM203
// D3DX mesh from an .x file
// MeshX.cpp
// 
// Scott Taylor
// Qantm College
//
//////////////////////////////////////////////////////////////////////////

#include "MeshX.h"

#include <d3dx9.h>

MeshX::MeshX()
: m_pMesh(NULL)
, m_segmentCount(0)
{
	//
}

MeshX::~MeshX()
{
	// Release any textures we created
	//@TODO: Clean up after yourself, buddy! Release those textures!

	// Release mesh if it was loaded
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
bool MeshX::CreateObject(IDirect3DDevice9* a_pDevice)
{
	if (!a_pDevice)
	{
		return false;
	}

	const char* HACK_FILENAME = "media/Dwarf.x";

	// Load the .x file
	// D3DXLoadMeshFromX returns data via these ID3DXBuffer objects
	// These allow D3DXLoadMeshFromX to return data of arbitrary length (which is what we need for an unknown number of materials etc)
	ID3DXBuffer* pMaterialBuf = NULL;
	ID3DXBuffer* pEffectBuf = NULL;

	//@TODO: Call D3DXLoadMeshFromX(filename, D3DXMESH_DYNAMIC, ...)
	//       Note that the number of materials (pNumMaterials) IS the segment count (our m_segmentCount)
	//HRESULT result = D3DERR_INVALIDCALL;
	HRESULT result = D3DXLoadMeshFromX(L"media/Dwarf.x",D3DXMESH_DYNAMIC,a_pDevice,NULL,&pMaterialBuf,&pEffectBuf,&m_segmentCount,&m_pMesh);
	//result = ???

	if (result != D3D_OK)
	{
		return false;
	}

	// We have to cast the buffer's data into the type we need (since the buffer is just arbitrary data)
	// In this case it is an array of D3DXMATERIAL structs, which are just a {D3DMATERIAL9, char*}
	D3DXMATERIAL* pMaterials;
	pMaterials = (D3DXMATERIAL*)pMaterialBuf->GetBufferPointer();
	// So pMaterials is now an array of D3DXMATERIALs (of size m_segmentCount)

	// For each segmentIndex in the mesh, read its material data
	for (DWORD i = 0; i < m_segmentCount; ++i)
	{
		D3DXMATERIAL& segmentMaterialData = pMaterials[i];

		//we'll handle textures next week
		IDirect3DTexture9* pNewTex = NULL;

		// Store this segmentIndex's material data; we copy-by-value this D3DMATERIAL9 into a new pair
		// (If we only stored a ptr to segmentMaterialData.MatD3D, that would be dangerous because the buffer is about to be released below!)
		MaterialTexturePair newMtlTexPair(segmentMaterialData.MatD3D, pNewTex);
		m_materials.push_back(newMtlTexPair);
	}

	// Release these since we don't need them anymore
	if (pMaterialBuf) pMaterialBuf->Release();
	{
		if (pEffectBuf) pEffectBuf->Release();
		{
			//@TODO: Hack position the dwarf here if you like (use m_worldMatrix in base class)
			D3DXMatrixTranslation(&m_worldMatrix, 0, 0, 0);
			return true;
		}
	}
}

//
// Draw this object
//
void MeshX::Render(float a_dt, IDirect3DDevice9* a_pDevice)
{
	if (a_pDevice && m_pMesh)
	{
		// Set up our world transform
		//@TODO: Use our new m_worldMatrix after you've added it!
		a_pDevice->SetTransform(D3DTS_WORLD, &m_worldMatrix);

		// Draw each segmentIndex of our mesh
		for (DWORD segmentIndex = 0; segmentIndex < m_segmentCount; ++segmentIndex)
		{
			// The "first" part of the pair is our D3DMATERIAL9 struct
			a_pDevice->SetMaterial(&m_materials[segmentIndex].first);
			// The "second" part of the pair is the texture pointer (which is ok if it's NULL)
			a_pDevice->SetTexture(segmentIndex, m_materials[segmentIndex].second);

			// Draw the mesh segment
			m_pMesh->DrawSubset(segmentIndex);
		}
	}
}

