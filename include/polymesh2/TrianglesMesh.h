#ifndef _POLYMESH_TRIANGLES_MESH_H_
#define _POLYMESH_TRIANGLES_MESH_H_

#include "polymesh2/Mesh.h"
#include "polymesh2/Triangles.h"

#include <SM_Vector.h>
#include <cu/cu_stl.h>

namespace pm2
{

class TrianglesMesh : public Mesh
{
public:
	TrianglesMesh(const CU_VEC<sm::vec2>& vertices, const CU_VEC<sm::vec2>& texcoords,
		const CU_VEC<int>& triangles);

	virtual MeshType Type() const override { return MESH_TRIANGLES; }

	virtual void Dump(CU_VEC<sm::vec2>& vertices, CU_VEC<sm::vec2>& texcoords,
		CU_VEC<int>& triangles) const override;

	virtual void LoadFromTransform(const MeshTransform& transform) override;
	virtual void StoreToTransform(MeshTransform& transform) const override;

	virtual const sm::vec2* GetVertexPos(int idx) const override;
	virtual void SetVertexPos(int idx, const sm::vec2& pos) override;

	void Update(int offset0, int count0, int offset1, int count1, const float* vertices);

	const TrianglesPtr& GetMeshData() const { return m_mesh_data; }

private:
	TrianglesPtr m_mesh_data;

}; // TrianglesMesh

}

#endif // _POLYMESH_TRIANGLES_MESH_H_