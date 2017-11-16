#include "polymesh/Triangles.h"
#include "polymesh/define.h"

#include <assert.h>
#include <stddef.h>

namespace pm
{

Triangles::Triangles() 
	: vert_num(0)
	, tri_num(0)
	, triangles(nullptr)
{
}

TrianglesPtr 
Triangles::Create(const CU_VEC<sm::vec2>& vertices, 
	              const CU_VEC<sm::vec2>& texcoords, 
	              const CU_VEC<int>& triangles)
{
	assert(vertices.size() == texcoords.size());
	int head_sz = sizeof(Triangles) + PTR_SIZE_DIFF - sizeof(Vertex);
	int sz = head_sz;
	sz += sizeof(Vertex) * vertices.size();			// vertices
	sz += sizeof(uint16_t) * triangles.size();		// triangles

#ifdef USE_MM_ALLOCATOR	
	void* buf = mm::AllocHelper::Allocate(sz);
#else
	void* buf = new uint8_t[sz];
#endif // USE_MM_ALLOCATOR
	uint8_t* ptr = static_cast<uint8_t*>(buf);
	Triangles* ret = new (ptr) Triangles();
	ret->vert_num = static_cast<uint16_t>(vertices.size());
	ret->tri_num = static_cast<uint16_t>(triangles.size());
	for (int i = 0, n = vertices.size(); i < n; ++i) {
		ret->vertices[i].xy = ret->vertices[i].ori_xy = vertices[i];
		ret->vertices[i].uv = texcoords[i];
	}
	ret->triangles = (uint16_t*)(ptr + (head_sz + sizeof(Vertex) * vertices.size()));
	for (int i = 0, n = triangles.size(); i < n; ++i) {
		ret->triangles[i] = triangles[i];
	}

	return TrianglesPtr(ret, deleter);
}

size_t Triangles::GetSize() const
{
	size_t head_sz = sizeof(Triangles) + PTR_SIZE_DIFF - sizeof(Vertex);
	size_t sz = head_sz;
	sz += sizeof(Vertex) * vert_num;			// vertices
	sz += sizeof(uint16_t) * tri_num;			// triangles
	return sz;
}

}