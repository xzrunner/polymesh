#include "polymesh2/SkinVertex.h"

#include <string.h>

namespace pm2
{

SkinVertex::SkinVertex()
{
	memset(joint_id, 0xff, sizeof(joint_id));
	memset(joint_weight, 0, sizeof(joint_weight));
}

}