#include "Scene.h"
#include "Sphere.h"
#include "Vector.h"
#include <mutex>
#include <memory>
namespace rt {

std::mutex renderMutex;

Scene::Scene() 
    : m_camera({0.0, -10.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, 80, 16.0 / 9.0)
{

    m_objects = { 
        std::make_shared<Sphere>(math::vec3d{ 0.0, 5.0, 0.0}, 1.0,  math::ColorVec{255, 0, 0}),
        std::make_shared<Sphere>(math::vec3d{ 2.25, 0.0, 0.0}, 1.0, math::ColorVec{0, 255, 0}),
        std::make_shared<Sphere>(math::vec3d{-2.25, 0.0, 0.0}, 1.0, math::ColorVec{0, 0, 255}),
    };

}

void Scene::RenderSection(Image& image, Camera& camera, const std::vector<std::shared_ptr<IObject>>& objects, 
                   int startX, int endX) {

    for (int x = startX; x < endX; x++) {
        for (int y = 0; y < image.GetHeight(); y++) {
            double u = static_cast<double>(x) / image.GetWidth();
            double v = static_cast<double>(y) / image.GetHeight();

            math::Ray3d ray = camera.GenerateRay(u, v);

            double closest = std::numeric_limits<double>::max();
            bool hit = false;
            math::ColorVec closestColor;
            math::vec3d intersectionPoint;
            for (const auto& object : objects) {
                double t = 1000;
                math::vec3d tempIntersection;
                if (object->Intersect(ray, tempIntersection, t)) {
                    math::ColorVec color = object->GetMaterial();
                    double dist = (tempIntersection - ray.From()).magnitude();

                    if (dist < closest) {
                        closest = dist;
                        closestColor = object->GetMaterial();
                        intersectionPoint = tempIntersection;
                        hit = true;
                    }
                }
            }
            if (hit) {
                double shadingFactor = 0;
                image.SetPixel(x, y, closestColor.x() - shadingFactor, closestColor.y() - shadingFactor, closestColor.z() - shadingFactor);
            } else {
                image.SetPixel(x, y, 0, 0, 0);
            }
        }
    }
}

void Scene::Render(Image& image) {

    static int numThreads = std::thread::hardware_concurrency();
    if (numThreads == 0) numThreads = 4;
    std::vector<std::thread> threads;
    int width = image.GetWidth();
    int chunkSize = width / numThreads;

    static double minDistance = 1e6;
    static double maxDistance = 0.0;
    for (int i = 0; i < numThreads; i++) {
        int startX = i * chunkSize;
        int endX = (i == numThreads - 1) ? width : startX + chunkSize;

        threads.emplace_back(RenderSection, std::ref(image), std::ref(m_camera), std::ref(m_objects), 
                             startX, endX);
        }

    for (auto& thread : threads) {
        thread.join();
    }

    image.Display();
}
} //namespace rt
