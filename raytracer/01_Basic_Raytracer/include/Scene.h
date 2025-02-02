#pragma once
#include "Image.h"
#include <Camera.h>
#include <memory>
#include <thread>

namespace rt {

class IObject;
class Scene {
public:
	Scene();
	void Render(Image& image);
	rt::Camera& GetSceneCamera() { return m_camera; }
private:
	static void RenderSection(Image& image, Camera& camera, const std::vector<std::shared_ptr<IObject>>& objects, 
                   int startX, int endX);
	std::vector<std::thread> m_threads;
	std::vector<std::shared_ptr<IObject>> m_objects;
	rt::Camera m_camera;

};

} // namespace rt
