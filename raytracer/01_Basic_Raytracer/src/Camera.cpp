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
    UpdateCamera(m_origin, m_vUp);
}

void Camera::UpdateCamera(math::vec3d i_lookAt, math::vec3d i_vUp) {
    m_w = (m_origin - m_lookAt).normalize();
    m_u = (m_vUp.cross(m_w)).normalize();
    m_v = m_w.cross(m_u);

    double theta = m_vFov * M_PI / 180.0;
    double h = tan(theta / 2);
    double viewportHeight = 2.0 * h;
    double viewportWidth = m_aspectRatio * viewportHeight;


    m_horizontal = m_u * viewportWidth;
    m_vertical = m_v * viewportHeight;
    m_loweLeftCorner = m_origin - m_horizontal / 2 - m_vertical / 2 - m_w;
}

//  camera.move(camera.getU(), 1.0) moves one unit to the right
void Camera::Move(const math::vec3d i_dir, double i_distance) {
    m_origin = m_origin + i_dir.normalize() * i_distance;
    UpdateCamera(m_origin - m_w, m_v);
}

// camera.Rotate(15, 0) rotates 15 degrees to the right
void Camera::Rotate(double i_yaw, double i_pitch) {
    double radYaw = i_yaw * M_PI / 180.0;
    double radPitch = i_pitch * M_PI / 180.0;

    // Rotación alrededor del eje Y (yaw - izquierda/derecha)
    math::vec3d new_w = {
        m_w.x() * cos(radYaw) - m_w.z() * sin(radYaw),
        m_w.y(),
        m_w.x() * sin(radYaw) + m_w.z() * cos(radYaw)
    };

    // Rotación alrededor del eje X (pitch - arriba/abajo)
    math::vec3d new_v = {
        m_v.x(),
        m_v.y() * cos(radPitch) - m_v.z() * sin(radPitch),
        m_v.y() * sin(radPitch) + m_v.z() * cos(radPitch)
    };

    m_w = new_w.normalize();
    m_v = new_v.normalize();
    m_u = m_v.cross(m_w);

    UpdateCamera(m_origin - m_w, m_v);
}

math::Ray3d Camera::GenerateRay(double i_s, double i_t) const {
    return math::Ray3d(m_origin , m_loweLeftCorner + m_horizontal * i_s + m_vertical * i_t - m_origin);
}


} //namespace rt
