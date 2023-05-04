#include "ColliderBase.h"

namespace Tmpl8
{
	ColliderBase::ColliderBase()
	{}
	ColliderBase::~ColliderBase()
	{
		if (colliderPoints != nullptr)
		{
			delete[]colliderPoints;
		}
	}
}