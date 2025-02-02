#include "Camera.h"
#include <cmath>

namespace rt {

Camera::Camera(math::vec3d i_lookFrom, math::vec3d i_lookAt, math::vec3d i_vUp, double i_vFov, double i_aspectRatio)
    : m_origin(i_lookFrom)
    , m_lookAt(i_lookAt)
    , m_vUp(i_vUp)
    , m_vFov(i_vFov)
    , m_aspectRatio(i_aspectRatio)
{
    UpdateCamera();
    std::cout << "LowerLeftCorner: (" << m_loweLeftCorner.x() << ", " << m_loweLeftCorner.y() << ", " << m_loweLeftCorner.z() << ")\n";
    std::cout << "Horizontal: (" << m_horizontal.x() << ", " << m_horizontal.y() << ", " << m_horizontal.z() << ")\n";
    std::cout << "Vertical: (" << m_vertical.x() << ", " << m_vertical.y() << ", " << m_vertical.z() << ")\n";
    std::cout << "Camera Origin: " << m_origin.x() << ", " << m_origin.y() << ", " << m_origin.z() << std::endl;
}

void Camera::UpdateCamera() {
    m_w = (m_origin - m_lookAt).normalize();
    m_u = (m_vUp.cross(m_w)).normalize();
    m_v = m_w.cross(m_u);

    double focalDistance = (m_origin - m_lookAt).magnitude();
    double theta = m_vFov * M_PI / 180.0;
    double h = tan(theta / 2) * focalDistance;
    double viewportHeight = 2.0 * h;
    double viewportWidth = m_aspectRatio * viewportHeight;


    m_horizontal = m_u * viewportWidth;
    m_vertical = m_v * viewportHeight;
    m_loweLeftCorner = m_origin - m_horizontal / 2 - m_vertical / 2 - m_w * focalDistance;
}

//  camera.move(camera.getU(), 1.0) moves one unit to the right
void Camera::Move(const math::vec3d i_dir, double i_distance) {
    math::vec3d moveVector = i_dir.normalize() * i_distance;
    m_origin = m_origin + moveVector;
    m_lookAt = m_lookAt + moveVector;
    UpdateCamera();
}

//TODO: Figure out rotations but since it is not the scope of the project I won't bother too much.
void Camera::Rotate(double i_yaw, double i_pitch) {
}
math::Ray3d Camera::GenerateRay(double i_s, double i_t) const {
    return math::Ray3d(m_origin , (m_loweLeftCorner + m_horizontal * i_s + m_vertical * i_t - m_origin));
}


} //namespace rt
