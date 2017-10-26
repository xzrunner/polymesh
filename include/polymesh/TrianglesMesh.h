#ifndef _POLYMESH_TRIANGLES_MESH_H_
#define _POLYMESH_TRIANGLES_MESH_H_

#include "polymesh/Mesh.h"
#include "polymesh/Triangles.h"

#include <SM_Vector.h>
#include <cu/cu_stl.h>

namespace pm
{

class TrianglesMesh : public Mesh
{
public:
	TrianglesMesh(const CU_VEC<sm::vec2>& vertices, const CU_VEC<sm::vec2>& texcoords,
		const CU_VEC<int>& triangles);

	virtual MeshType Type() const { return MESH_TRIANGLES; }

	virtual void Dump(CU_VEC<sm::vec2>& vertices, CU_VEC<sm::vec2>& texcoords,
		CU_VEC<int>& triangles) const;

	virtual void LoadFromTransform(const MeshTransform& transform);
	virtual void StoreToTransform(MeshTransform& transform) const;

	virtual const sm::vec2* GetVertexPos(int idx) const;
	virtual void SetVertexPos(int idx, const sm::vec2& pos);

	void Update(int offset0, int count0, int offset1, int count1, const float* vertices);

	const TrianglesPtr& GetMeshData() const { return m_mesh_data; }

private:
	TrianglesPtr m_mesh_data;

}; // TrianglesMesh

}

#endif // _POLYMESH_TRIANGLES_MESH_H_