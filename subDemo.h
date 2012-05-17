#ifndef SUBDEMO_H
#define SUBDEMO_H

enum SUBDEMOTYPE
{
	int SUBDEMO_INVALID = 0,
	SUBDEMO_VERTEXCOLOURING,
	SUBDEMO_FLAT,
	SUBDEMO_GOURARD,
	SUBDEMO_POINT,
	SUBDEMO_DIRECTIONAL,
	SUBDEMO_SPOT,
	SUBDEMO_AMBIENT,
	SUBDEMO_DIFFUSE,
	SUBDEMO_SPECULAR,
	SUBDEMO_AMBIENTMAT,
	SUBDEMO_DIFFUSEMAT,
	SUBDEMO_SPECULARMAT,
	SUBDEMO_EMISSIVEMAT
}

namespace SubDemo
{
	Apply(SUBDEMOTYPE a_Type);
	Undo(SUBDEMOTYPE a_Type);
}

#endif