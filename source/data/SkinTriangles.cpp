#include "SkinTriangles.h"
#include "pm_define.h"

#include <memmgr/Allocator.h>

#include <stddef.h>

namespace pm
{

SkinTriangles::SkinTriangles()
	: vert_num(0)
	, tri_num(0)
	, triangles(NULL)
{
}

SkinTrianglesPtr 
SkinTriangles::Create(const CU_VEC<SkinVertex>& vertices, const CU_VEC<int>& triangles)
{
	int head_sz = sizeof(SkinTriangles) + PTR_SIZE_DIFF - sizeof(SkinVertex);
	int sz = head_sz;
	sz += sizeof(SkinVertex) * vertices.size();		// vertices
	sz += sizeof(uint16_t) * triangles.size();		// triangles
	
	void* buf = mm::AllocHelper::Allocate(sz);
	uint8_t* ptr = static_cast<uint8_t*>(buf);
	SkinTriangles* ret = new (ptr) SkinTriangles();
	ret->vert_num = static_cast<uint16_t>(vertices.size());
	ret->tri_num = static_cast<uint16_t>(triangles.size());
	for (int i = 0, n = vertices.size(); i < n; ++i) {
		ret->vertices[i] = vertices[i];
	}
	ret->triangles = (uint16_t*)(ptr + (head_sz + sizeof(SkinVertex) * vertices.size()));
	for (int i = 0, n = triangles.size(); i < n; ++i) {
		ret->triangles[i] = triangles[i];
	}

	return SkinTrianglesPtr(ret, deleter);
}

size_t SkinTriangles::GetSize() const
{
	size_t head_sz = sizeof(SkinTriangles) + PTR_SIZE_DIFF - sizeof(SkinVertex);
	size_t sz = head_sz;
	sz += sizeof(SkinVertex) * vert_num;		// vertices
	sz += sizeof(uint16_t) * tri_num;			// triangles
	return sz;
}

}