#ifndef _POLYMESH_SKELETON2_MESH_H_
#define _POLYMESH_SKELETON2_MESH_H_

#include "polymesh2/Mesh.h"
#include "polymesh2/Skin2Joint.h"
#include "polymesh2/Skin2Vertex.h"
#include "polymesh2/Skin2Triangles.h"

#include <cu/cu_stl.h>

namespace pm2
{

class Skin2Triangles;

class Skin2Mesh : public Mesh
{
public:
	Skin2Mesh(const CU_VEC<Skin2Joint>& joints, const CU_VEC<int>& vertices,
		const CU_VEC<sm::vec2>& texcoords, const CU_VEC<int>& triangles);

	virtual MeshType Type() const override { return MESH_SKIN2; }

	virtual void Dump(CU_VEC<sm::vec2>& vertices, CU_VEC<sm::vec2>& texcoords,
		CU_VEC<int>& triangles) const override;

	virtual void LoadFromTransform(const MeshTransform& transform) override;
	virtual void StoreToTransform(MeshTransform& transform) const override;

	virtual const sm::vec2* GetVertexPos(int idx) const override;
	virtual void SetVertexPos(int idx, const sm::vec2& pos) override;

	void Update(const float* (*query_joint_world_mt)(int joint_id, const void* ud), const void* ud);
	void Update(int offset0, int count0, int offset1, int count1, const float* vertices);

	const Skin2TrianglesPtr& GetMeshData() const { return m_mesh_data; }

private:
	Skin2TrianglesPtr m_mesh_data;

}; // Skin2Mesh

}

#endif // _POLYMESH_SKELETON2_MESH_H_