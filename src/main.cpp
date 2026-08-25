#include <iostream>
#include "color.h"
#include "vec3.h"

int main() {

    // Image
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    
    int image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Viewport (pixel coordinates)
    // We want viewport pixels to have square spacing so they have same aspect ratio as the image
    double viewport_height = 2.0; // Arbitrary number
    double viewport_width = viewport_height * (static_cast<double>(image_width) / image_height); // We use image_width and height because they might be slightly off from actual aspect ratio due to rounding errors


    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush; // Progress Reporting
        for (int i = 0; i < image_width; i++) {
            double r = double(i) / (image_width-1);
            double g = double(j) / (image_height-1);
            double b = 0.0;

            color pixel_color = color(r, g, b);

            write_color(std::cout, pixel_color);
        }
    }
    
    std::clog << "\rDone.                 \n";
}