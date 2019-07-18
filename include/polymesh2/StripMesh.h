#ifndef _POLYMESH_STRIP_MESH_H_
#define _POLYMESH_STRIP_MESH_H_

#include "polymesh2/Mesh.h"

namespace pm2
{

class StripMesh : public Mesh
{
public:
	StripMesh() {}

	virtual MeshType Type() const override { return MESH_STRIP; }

private:

}; // StripMesh

}

#endif // _POLYMESH_STRIP_MESH_H_