#ifndef _POLYMESH_POINTS_MESH_H_
#define _POLYMESH_POINTS_MESH_H_

#include "polymesh/Mesh.h"
#include "polymesh/Triangles.h"

#include <SM_Vector.h>
#include <cu/cu_stl.h>

namespace pm
{

class Triangles;

class PointsMesh : public Mesh
{
public:
	PointsMesh(const CU_VEC<sm::vec2>& outline, const CU_VEC<sm::vec2>& points,
		float width, float height);

	virtual MeshType Type() const override { return MESH_POINTS; }

	virtual void Dump(CU_VEC<sm::vec2>& vertices, CU_VEC<sm::vec2>& texcoords,
		CU_VEC<int>& triangles) const override;

	virtual void LoadFromTransform(const MeshTransform& transform) override;
	virtual void StoreToTransform(MeshTransform& transform) const override;

	virtual const sm::vec2* GetVertexPos(int idx) const override;
	virtual void SetVertexPos(int idx, const sm::vec2& pos) override;

	void Build(const CU_VEC<sm::vec2>& outline, const CU_VEC<sm::vec2>& points);
	void Clear();

	const CU_VEC<sm::vec2>& GetOutline() const { return m_outline; }
	const CU_VEC<sm::vec2>& GetPoints() const { return m_points; }
	void SetOuterLine(const CU_VEC<sm::vec2>& outline);
	void SetInnerPoints(const CU_VEC<sm::vec2>& points);

	const TrianglesPtr& GetMeshData() const { return m_mesh_data; }

private:
	float m_width, m_height;

	CU_VEC<sm::vec2> m_outline;
	CU_VEC<sm::vec2> m_points;

	TrianglesPtr m_mesh_data;

}; // PointsMesh

}

#endif // _POLYMESH_POINTS_MESH_H_