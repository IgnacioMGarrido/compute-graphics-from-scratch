#pragma once
#include "Ray.h"
namespace rt {

class IObject {
public:
	virtual ~IObject() = default;
	virtual bool Intersect(const math::Ray3d& i_ray, math::vec3d& o_intersectionPoint, double& i_t) const = 0;
	virtual math::vec3d GetNormal(math::vec3d i_point) const = 0;
	// TODO: Return an actual material struct, for now it is just the color
	virtual math::vec3d GetMaterial() const = 0;
};
} // namespace rt
