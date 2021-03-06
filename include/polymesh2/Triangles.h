#ifndef _POLYMESH_TRIANGLES_H_
#define _POLYMESH_TRIANGLES_H_

#include "polymesh2/Vertex.h"

#include <cu/cu_stl.h>

#include <memory>

#include <stdint.h>

namespace pm2
{

class MeshTransform;

class Triangles
{
public:
	uint16_t  vert_num;
	uint16_t  tri_num;
	uint16_t* triangles;
	Vertex    vertices[1];

public:
	Triangles();

#ifdef USE_MM_ALLOCATOR
	static void deleter(Triangles* tris) {
		mm::AllocHelper::Free(static_cast<void*>(tris), tris->GetSize());
	};
#else
	static void deleter(Triangles* tris) {
		delete[] reinterpret_cast<uint8_t*>(tris);
	};
#endif // USE_MM_ALLOCATOR
	static std::unique_ptr<Triangles, decltype(&deleter)> Create(const CU_VEC<sm::vec2>& vertices,
		const CU_VEC<sm::vec2>& texcoords,
		const CU_VEC<int>& triangles);

private:
	size_t GetSize() const;

}; // Triangles

using TrianglesPtr = std::unique_ptr<Triangles, decltype(&Triangles::deleter)>;

}

#endif // _POLYMESH_TRIANGLES_H_