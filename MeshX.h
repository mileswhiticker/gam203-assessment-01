#include "drawable.h"

#include <D3DX9Mesh.h>
#include <vector>

class MeshX : public Drawable
{
public:
	MeshX();
	virtual ~MeshX();

	virtual bool CreateObject(IDirect3DDevice9* a_pDevice);
	virtual void Render(float a_dt, IDirect3DDevice9* a_pDevice);

private:
	ID3DXMesh* m_pMesh;  // Same as last week :)
	DWORD m_segmentCount;  // Number of segments in mesh

	// List of materials on mesh
	typedef std::pair<D3DMATERIAL9, IDirect3DTexture9*> MaterialTexturePair;
	typedef std::vector<MaterialTexturePair> MaterialList;
	MaterialList m_materials;
};
