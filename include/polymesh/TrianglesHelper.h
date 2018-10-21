#ifndef _POLYMESH_TRIANGLES_HELPER_H_
#define _POLYMESH_TRIANGLES_HELPER_H_

#include <SM_Vector.h>
#include <SM_Rect.h>
#include <cu/cu_stl.h>

namespace pm
{

class Vertex;
class Triangles;
class MeshTransform;

class TrianglesHelper
{
public:
	static void Dump(const Triangles& src, CU_VEC<sm::vec2>& vertices,
		CU_VEC<sm::vec2>& texcoords, CU_VEC<int>& triangles);

	static void LoadFromTransform(Triangles& dst, const MeshTransform& src);
	static void StoreToTransform(MeshTransform& dst, const Triangles& src);

	static const Vertex* PointQueryVertex(const Triangles& src, const sm::vec2& p, float radius);
	static void RectQueryVertices(const Triangles& src, const sm::rect& r, CU_VEC<const Vertex*>& vertices);

	static const sm::vec2* GetVertexPos(const Triangles& src, int idx);
	static void SetVertexPos(Triangles& src, int idx, const sm::vec2& pos);

}; // TrianglesHelper

}

#endif // _POLYMESH_TRIANGLES_HELPER_H_