#include "Scene.h"


namespace rt {

void Scene::Render(Image& image) {
    for (int x = 0; x < image.GetWidth(); x++) {
        for (int y = 0; y < image.GetHeight(); y++) {
            double red = (static_cast<double>(x) / image.GetWidth()) * 255.0;
            double green = (static_cast<double>(y) / image.GetHeight()) * 255.0;
            image.SetPixel(x, y, red, green, 0);
        }
    }

    image.Display();
}
} //namespace rt
