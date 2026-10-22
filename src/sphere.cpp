#include "sphere.h"

bool Sphere::hit(const ray& r, double tmin, double tmax, hit_record& rec) const {
    vec3 oc = center - r.origin();
    double a = r.direction().length_squared();
    double h = dot(r.direction(), oc);
    double c = oc.length_squared() - radius * radius;

    double discriminant = h*h - a*c;
    if (discriminant < 0) {
        return false;
    }

    double sqrtd = std::sqrt(discriminant);

    // Find nearest root that's valid
    double root = (h - sqrtd) / a;
    if (root <= tmin || tmax <= root) {
        root = (h + sqrtd) / a;
        if (root <= tmin || tmax <= root) {
            return false;
        }
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 outward_normal = (rec.p - center) / radius; // Outward sphere normal equation
    rec.set_face_normal(r, outward_normal);

    return true;
}
