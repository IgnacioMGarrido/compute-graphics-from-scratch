#pragma once
#include "IObject.h"

namespace rt {
class Sphere : public IObject {
public:
	Sphere(math::vec3d i_center, double i_radius, math::vec3d i_color);
	bool Intersect(const math::Ray3d& i_ray, math::vec3d& o_intersectionPoint, double& i_t) const override;
	math::vec3d GetNormal(math::vec3d i_point) const override;
	math::vec3d GetMaterial() const override;
private:
	math::vec3d m_center;
	double m_radius;
	math::vec3d m_color;
};
} //namespace rt
