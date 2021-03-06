#ifndef _POLYMESH_SKIN2_TRIS_HELPER_H_
#define _POLYMESH_SKIN2_TRIS_HELPER_H_

#include <SM_Vector.h>
#include <SM_Rect.h>
#include <cu/cu_stl.h>

namespace pm2
{

class Skin2Vertex;
class Skin2Triangles;
class MeshTransform;

class Skin2TrisHelper
{
public:
	static void Dump(const Skin2Triangles& src, CU_VEC<sm::vec2>& vertices,
		CU_VEC<sm::vec2>& texcoords, CU_VEC<int>& triangles);

	static void LoadFromTransform(Skin2Triangles& dst, const MeshTransform& src);
	static void StoreToTransform(MeshTransform& dst, const Skin2Triangles& src);

	static const Skin2Vertex* PointQueryVertex(const Skin2Triangles& src, const sm::vec2& p, float radius);
	static void RectQueryVertices(const Skin2Triangles& src, const sm::rect& r, CU_VEC<const Skin2Vertex*>& vertices);

	static const sm::vec2* GetVertexPos(const Skin2Triangles& src, int idx);
	static void SetVertexPos(Skin2Triangles& src, int idx, const sm::vec2& pos);

}; // Skin2TrisHelper

}

#endif // _POLYMESH_SKIN2_TRIS_HELPER_H_