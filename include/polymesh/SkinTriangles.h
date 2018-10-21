#ifndef _POLYMESH_SKIN_TRIANGLES_H_
#define _POLYMESH_SKIN_TRIANGLES_H_

#include "polymesh/SkinVertex.h"

#include <cu/cu_stl.h>

#include <memory>

namespace pm
{

class SkinTriangles
{
public:
	uint16_t   vert_num;
	uint16_t   tri_num;
	uint16_t*  triangles;
	SkinVertex vertices[1];

public:
	SkinTriangles();

#ifdef USE_MM_ALLOCATOR
	static void deleter(SkinTriangles* tris) {
		mm::AllocHelper::Free(static_cast<void*>(tris), tris->GetSize());
	};
#else
	static void deleter(SkinTriangles* tris) {
		delete[] reinterpret_cast<uint8_t*>(tris);
	};
#endif // USE_MM_ALLOCATOR
	static std::unique_ptr<SkinTriangles, decltype(&deleter)> Create(
		const CU_VEC<SkinVertex>& vertices,
		const CU_VEC<int>& triangles);

private:
	size_t GetSize() const;

}; // SkinTriangles

using SkinTrianglesPtr = std::unique_ptr<SkinTriangles, decltype(&SkinTriangles::deleter)>;

}

#endif // _POLYMESH_SKIN_TRIANGLES_H_