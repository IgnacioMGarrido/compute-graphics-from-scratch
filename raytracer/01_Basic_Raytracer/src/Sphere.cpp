#include "Sphere.h"
#include "Ray.h"

namespace rt {

Sphere::Sphere(math::vec3d i_center, double i_radius, math::vec3d i_color) 
    : m_center(i_center)
    , m_radius(i_radius)
    , m_color(i_color)
{
}

bool Sphere::Intersect(const math::Ray3d& i_ray, math::vec3d& o_intersectionPoint, double& o_t) const {
    const math::vec3d oc = i_ray.From() - m_center;
    const double a = i_ray.Dir().dot(i_ray.Dir());
    const double b = oc.dot(i_ray.Dir()) * 2;
    const double c = oc.dot(oc) - m_radius * m_radius;

    const double discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return false;
    }

    const double sqDiscriminant = std::sqrt(discriminant);
    const double t1 = (-b + sqDiscriminant) / (2 * a);
    if (t1 > 0) {
        o_t = t1;
        o_intersectionPoint = i_ray.From() + i_ray.Dir() * o_t;
        return true;
    }

    const double t2 = (-b - sqDiscriminant) / (2 * a);
    if (t2 > 0) {
        o_t = t2;
        o_intersectionPoint = i_ray.From() + i_ray.Dir() * o_t;
        return true;
    }

    return false;
}

math::vec3d Sphere::GetNormal(math::vec3d i_point) const
{
    return (i_point - m_center).normalize();
}


math::vec3d Sphere::GetMaterial() const {
    return m_color;
}
} //namespace rt
