#ifndef _POLYMESH_SKIN_TRIANGLES_H_
#define _POLYMESH_SKIN_TRIANGLES_H_

#include "polymesh/SkinVertex.h"

#include <cu/cu_stl.h>

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

	static void deleter(SkinTriangles* tris) {
		mm::AllocHelper::Free(static_cast<void*>(tris), tris->GetSize());
	};
	static std::unique_ptr<SkinTriangles, decltype(&deleter)> Create(
		const CU_VEC<SkinVertex>& vertices,
		const CU_VEC<int>& triangles);

private:
	size_t GetSize() const;

}; // SkinTriangles

using SkinTrianglesPtr = std::unique_ptr<SkinTriangles, decltype(&SkinTriangles::deleter)>;

}

#endif // _POLYMESH_SKIN_TRIANGLES_H_