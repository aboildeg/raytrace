#include "color.h"

void write_color(std::ostream& out, const color& pixel_color) {
    double r = pixel_color.x();
    double g = pixel_color.y();
    double b = pixel_color.z();

    int rbyte = static_cast<int>(r * 255.999); // Map from [0, 1] to [0, 255] - We use 255.999 because we want 0.999 to map to 255 and 1 also maps to that
    int gbyte = static_cast<int>(g * 255.999);
    int bbyte = static_cast<int>(b * 255.999);

    out << rbyte << " " << gbyte << " " << bbyte << "\n";
}