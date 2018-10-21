#include "polymesh/TrianglesMesh.h"
#include "polymesh/TrianglesHelper.h"

namespace pm
{

TrianglesMesh::TrianglesMesh(const CU_VEC<sm::vec2>& vertices,
							 const CU_VEC<sm::vec2>& texcoords,
							 const CU_VEC<int>& triangles)
	: m_mesh_data(Triangles::Create(vertices, texcoords, triangles))
{
}

void TrianglesMesh::Dump(CU_VEC<sm::vec2>& vertices,
						 CU_VEC<sm::vec2>& texcoords,
						 CU_VEC<int>& triangles) const
{
	TrianglesHelper::Dump(*m_mesh_data, vertices, texcoords, triangles);
}

void TrianglesMesh::LoadFromTransform(const MeshTransform& transform)
{
	TrianglesHelper::LoadFromTransform(*m_mesh_data, transform);
}

void TrianglesMesh::StoreToTransform(MeshTransform& transform) const
{
	TrianglesHelper::StoreToTransform(transform, *m_mesh_data);
}

const sm::vec2* TrianglesMesh::GetVertexPos(int idx) const
{
	return TrianglesHelper::GetVertexPos(*m_mesh_data, idx);
}

void TrianglesMesh::SetVertexPos(int idx, const sm::vec2& pos)
{
	TrianglesHelper::SetVertexPos(*m_mesh_data, idx, pos);
}

void TrianglesMesh::Update(int offset0, int count0,
						   int offset1, int count1,
						   const float* vertices)
{
	for (int i = 0; i < count0; ++i) {
		m_mesh_data->vertices[offset0 + i].xy = m_mesh_data->vertices[offset0 + i].ori_xy;
	}
	for (int i = 0; i < count1; ++i) {
		m_mesh_data->vertices[offset1 + i].xy = m_mesh_data->vertices[offset1 + i].ori_xy;
	}

	int ptr = 0;
	for (int i = 0; i < count0; ++i) {
		m_mesh_data->vertices[offset0 + i].xy.x += vertices[ptr++];
		m_mesh_data->vertices[offset0 + i].xy.y += vertices[ptr++];
	}
	for (int i = 0; i < count1; ++i) {
		m_mesh_data->vertices[offset1 + i].xy.x += vertices[ptr++];
		m_mesh_data->vertices[offset1 + i].xy.y += vertices[ptr++];
	}
}

}