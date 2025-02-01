#pragma once

#include "Ray.h"

namespace rt {

class Camera {
public:
	Camera(math::vec3d i_lookFrom, math::vec3d i_lookAt, math::vec3d i_vUp, double i_vFov, double i_aspectRatio);

	inline math::vec3d GetLookAt() { return m_lookAt; };
	inline math::vec3d getLowerLeftCorner() const { return m_loweLeftCorner; }
	inline math::vec3d getScreenCenter() const { return m_loweLeftCorner + (m_horizontal * 0.5) + (m_vertical * 0.5); }
	inline math::vec3d getHorizontal() const { return m_horizontal; }
	inline math::vec3d getVertical() const { return m_vertical; }
	inline math::vec3d getU() const { return m_u; }
	inline math::vec3d getV() const { return m_v; }
	inline math::vec3d getW() const { return m_w; }

	math::Ray3d GenerateRay(double i_s, double i_t) const;

	void Move(const math::vec3d i_dir, double i_distance);
	void Rotate(double i_yaw, double i_pitch);

private:
	void UpdateCamera(math::vec3d i_lookAt, math::vec3d i_vUp);
private:
	math::vec3d m_origin;
	math::vec3d m_lookAt;
	math::vec3d m_vUp;
	double m_vFov;
	double m_aspectRatio;
	math::vec3d m_loweLeftCorner;
	math::vec3d m_horizontal;
	math::vec3d m_vertical;
	math::vec3d m_w;
	math::vec3d m_u;
	math::vec3d m_v;
};

} // namespace rt
