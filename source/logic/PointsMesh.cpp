#include "polymesh/PointsMesh.h"
#include "polymesh/TrianglesHelper.h"

#include <SM_Triangulation.h>

namespace pm
{

PointsMesh::PointsMesh(const CU_VEC<sm::vec2>& outline, const CU_VEC<sm::vec2>& points, 
					   float width, float height)
	: m_width(width)
	, m_height(height)
	, m_mesh_data(nullptr, Triangles::deleter)
{
	Build(outline, points);
}

void PointsMesh::Dump(CU_VEC<sm::vec2>& vertices, 
					  CU_VEC<sm::vec2>& texcoords, 
					  CU_VEC<int>& triangles) const
{
	TrianglesHelper::Dump(*m_mesh_data, vertices, texcoords, triangles);
}

void PointsMesh::LoadFromTransform(const MeshTransform& transform)
{
	TrianglesHelper::LoadFromTransform(*m_mesh_data, transform);
}

void PointsMesh::StoreToTransform(MeshTransform& transform) const
{
	TrianglesHelper::StoreToTransform(transform, *m_mesh_data);
}

const sm::vec2* PointsMesh::GetVertexPos(int idx) const
{
	return TrianglesHelper::GetVertexPos(*m_mesh_data, idx);
}

void PointsMesh::SetVertexPos(int idx, const sm::vec2& pos)
{
	TrianglesHelper::SetVertexPos(*m_mesh_data, idx, pos);
}

void PointsMesh::Build(const CU_VEC<sm::vec2>& outline, const CU_VEC<sm::vec2>& points)
{
	m_outline = outline;
	m_points = points;

	CU_VEC<sm::vec2> vertices;
	CU_VEC<int> triangles;
	sm::triangulate_points(outline, points, vertices, triangles);

	CU_VEC<sm::vec2> texcoords;
	texcoords.reserve(vertices.size());
	for (int i = 0, n = vertices.size(); i < n; ++i) {
		float x = vertices[i].x / m_width + 0.5f,
			  y = vertices[i].y / m_height + 0.5f;
		texcoords.push_back(sm::vec2(x, y));
	}

	m_mesh_data = Triangles::Create(vertices, texcoords, triangles);
}

void PointsMesh::Clear()
{
	m_outline.clear();
	m_points.clear();
	m_mesh_data.reset();
}

}