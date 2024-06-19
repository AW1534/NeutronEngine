//
// Created by aw1lt on 14/06/24.
//

#include "Neutron/Image.h"

// required for stb libraries
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION

#include "stb_image.h"
#include "stb_image_resize2.h"

#include "Logger.h"

namespace Neutron {
    void Image::resize(int new_width, int new_height) {
        if (actualWidth == new_width && actualHeight == new_height) return;

        auto* resizedPixels = new unsigned char[new_width * new_height * channels];
        stbir_resize_uint8_linear(this->data, actualWidth, actualHeight, 0, resizedPixels, new_width, new_height, 0, static_cast<stbir_pixel_layout>(channels));
        stbi_image_free(this->data); // Free the original image data
        this->data = resizedPixels; // Update the image pointer
        width = new_width;
        height = new_height;
    }

    void Image::Constructor(std::string path) {
        int temp_channels{};

        data = stbi_load(path.c_str(), &actualWidth, &actualHeight, &temp_channels, 4);

        channels = static_cast<ImageChannels>(temp_channels);

        Logger::Assert(data != nullptr, "Failed to load '" + path + "'", 3);

        loaded = true;
    };

    Image::Image(std::string path) {
        Constructor(path);
        width = actualWidth;
        height = actualHeight;
    }

    Image::Image(std::string path, Math::Vector2 size) {
        Constructor(path);
        resize(size.x, size.y);
    }

    Image::Image(std::string path, int width, int height) {
        Constructor(path);
        resize(width, height);
    }

    Image::~Image() {
        stbi_image_free(data);
    }

    GLFWimage Image::asGlfwImage() {
        GLFWimage glfwImage;
        glfwImage.width = width;
        glfwImage.height = height;
        glfwImage.pixels = data;

        return glfwImage;
    }
}