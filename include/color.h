#ifndef COLOR_H
#define COLOR_H

#include "common.h"
#include "vec3.h"

using color = vec3;

void write_color(std::ostream& out, const color& pixel_color);
#endif