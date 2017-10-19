#ifndef _POLYMESH_SKIN2_TRIANGLES_H_
#define _POLYMESH_SKIN2_TRIANGLES_H_

#include "Skin2Vertex.h"
#include "Skin2Joint.h"

#include <cu/cu_stl.h>

#include <stdint.h>

namespace pm
{

class MeshTransform;

class Skin2Triangles
{
public:
	uint16_t joint_num;
	uint16_t vert_num;
	uint16_t tri_num;
	uint16_t padding;

	Skin2Vertex* vertices;
	uint16_t*    vertices_joint;

	uint16_t*    triangles;

	Skin2Joint   joints[1];	

public:
	Skin2Triangles();

	static void deleter(Skin2Triangles* tris) {
		mm::AllocHelper::Free(static_cast<void*>(tris), tris->GetSize());
	};
	static std::unique_ptr<Skin2Triangles, decltype(&deleter)> Create(const CU_VEC<Skin2Joint>& joints,
		const CU_VEC<int>& vertices,
		const CU_VEC<sm::vec2>& texcoords,
		const CU_VEC<int>& triangles);

private:
	size_t GetSize() const;

}; // Skin2Triangles

using Skin2TrianglesPtr = std::unique_ptr<Skin2Triangles, decltype(&Skin2Triangles::deleter)>;

}

#endif // _POLYMESH_SKIN2_TRIANGLES_H_