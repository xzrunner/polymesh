#include "polymesh/Skin2Triangles.h"
#include "polymesh/MeshTransform.h"
#include "polymesh/define.h"

#include <memmgr/Allocator.h>

#include <assert.h>
#include <stddef.h>

namespace pm
{

Skin2Triangles::Skin2Triangles()
	: joint_num(0)
	, vert_num(0)
	, tri_num(0)
	, vertices(nullptr)
	, triangles(nullptr)
{
}

Skin2TrianglesPtr
Skin2Triangles::Create(const CU_VEC<Skin2Joint>& joints, const CU_VEC<int>& vertices,
	                   const CU_VEC<sm::vec2>& texcoords, const CU_VEC<int>& triangles)
{
	assert(vertices.size() == texcoords.size());

	int head_sz = sizeof(Skin2Triangles) + PTR_SIZE_DIFF * 3 - sizeof(Skin2Joint);
	int sz = head_sz;
	// joints
	sz += sizeof(Skin2Joint) * joints.size();
	// vertices
	sz += sizeof(Skin2Vertex) * vertices.size();
	sz += sizeof(uint16_t) * vertices.size();
	// triangles
	sz += sizeof(uint16_t) * triangles.size();
	
#ifdef USE_MM_ALLOCATOR
	void* buf = mm::AllocHelper::Allocate(sz);
#else
	void* buf = new uint8_t[sz];
#endif // USE_MM_ALLOCATOR
	uint8_t* ptr = static_cast<uint8_t*>(buf);
	Skin2Triangles* ret = new (buf) Skin2Triangles();
	ret->joint_num = static_cast<uint16_t>(joints.size());
	ret->vert_num  = static_cast<uint16_t>(vertices.size());
	ret->tri_num   = static_cast<uint16_t>(triangles.size());
	// joints
	for (int i = 0, n = joints.size(); i < n; ++i) {
		ret->joints[i] = joints[i];
	}
	// vertices
	ptr += head_sz + sizeof(Skin2Joint) * joints.size();
	ret->vertices = reinterpret_cast<Skin2Vertex*>(ptr);
	for (int i = 0, n = vertices.size(); i < n; ++i) {
		Skin2Vertex* v = reinterpret_cast<Skin2Vertex*>(ptr);
		v->xy.Set(0, 0);
		v->uv = texcoords[i];
		ptr += sizeof(Skin2Vertex);
	}
	ret->vertices_joint = reinterpret_cast<uint16_t*>(ptr);
	for (int i = 0, n = vertices.size(); i < n; ++i) {
		ret->vertices_joint[i] = vertices[i];
		ptr += sizeof(uint16_t);
	}
	// triangles
	ret->triangles = reinterpret_cast<uint16_t*>(ptr);
	for (int i = 0, n = triangles.size(); i < n; ++i) {
		ret->triangles[i] = triangles[i];
		ptr += sizeof(uint16_t);
	}

	return Skin2TrianglesPtr(ret, deleter);
}

size_t Skin2Triangles::GetSize() const
{
	size_t head_sz = sizeof(Skin2Triangles) + PTR_SIZE_DIFF * 3 - sizeof(Skin2Joint);
	size_t sz = head_sz;
	// joints
	sz += sizeof(Skin2Joint) * joint_num;
	// vertices
	sz += sizeof(Skin2Vertex) * vert_num;
	sz += sizeof(uint16_t) * vert_num;
	// triangles
	sz += sizeof(uint16_t) * tri_num;
	return sz;
}

}