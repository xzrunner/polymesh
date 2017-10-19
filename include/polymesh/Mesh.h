#ifndef _POLYMESH_MESH_H_
#define _POLYMESH_MESH_H_

#include "MeshType.h"

#include <cu/cu_stl.h>
#include <SM_Vector.h>

namespace pm
{

class MeshTransform;

class Mesh
{
public:
	virtual ~Mesh() {}

	virtual MeshType Type() const = 0;

	virtual void Dump(CU_VEC<sm::vec2>& vertices, CU_VEC<sm::vec2>& texcoords,
		CU_VEC<int>& triangles) const = 0;

	virtual void LoadFromTransform(const MeshTransform& transform) = 0;
	virtual void StoreToTransform(MeshTransform& transform) const = 0;

	virtual const sm::vec2* GetVertexPos(int idx) const = 0;
	virtual void SetVertexPos(int idx, const sm::vec2& pos) = 0;

}; // Mesh

}

#endif // _POLYMESH_MESH_H_