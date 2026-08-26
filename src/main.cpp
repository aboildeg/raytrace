#include <iostream>
#include "color.h"
#include "vec3.h"
#include "ray.h"

// Whole buncha complicated maths about finding where a ray intersects a sphere
double hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = center - r.origin(); // This is the (C - Q) in the vector form of the sphere equation
    // This sets up a quadratic equation
    double a = dot(r.direction(), r.direction());
    double h = dot(r.direction(), oc);
    double c = dot(oc, oc) - radius*radius;
    double discriminant = h*h - a*c; 
    if (discriminant < 0) {
        return -1.0;
    } else {
        return (h - std::sqrt(discriminant)) / h; // Entire quadratic equation - Then returns either positive or negative t values
    }
}

color ray_color(const ray& r) {
    double t = hit_sphere(point3(0, 0, -1), 0.5, r);
    if (t > 0.0) { // Make sure the sphere ain't behind the camera
        vec3 n = unit_vector(r.at(t) - vec3(0, 0, -1)); // Creates a normal vector at that point and normalizes it
        return 0.5*color(n.x() + 1, n.y() + 1, n.z() + 1); // Maps xyz to rgb
    }
    vec3 unit_direction = unit_vector(r.direction());
    double a = 0.5*(unit_direction.y() + 1.0); // viewport y goes up to 1 and down to -1 so add 1 to offset the -1 to 0
    return (1.0 - a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

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

    // Camera
    point3 camera_origin = point3(0, 0, 0); // Origin
    double focal_length = 1.0;
    
    // Calculate viewport vectors
    vec3 viewport_u = vec3(viewport_width, 0, 0);
    vec3 viewport_v = vec3(0, -viewport_height, 0);

    // Calculate u and v delta vectors from each pixel
    vec3 pixel_delta_u = viewport_u / image_width;
    vec3 pixel_delta_v = viewport_v / image_height;

    // Location of uppoer left pixel
    point3 viewport_origin = camera_origin - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    point3 pixel00 = viewport_origin + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush; // Progress Reporting
        for (int i = 0; i < image_width; i++) {
            point3 pixel = pixel00 + (i * pixel_delta_u) + (j * pixel_delta_v);
            vec3 ray_direction = pixel - camera_origin;

            ray r = ray(camera_origin, ray_direction);
            color pixel_color = ray_color(r);

            write_color(std::cout, pixel_color);
        }
    }
    
    std::clog << "\rDone.                 \n";
}