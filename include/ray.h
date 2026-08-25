#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
    private:
        point3 orig;
        vec3 dir; // Fully makes a ray - Origin position and the direction it goes in.
    
    public:
        ray() {}
        ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}

        const point3& origin() const {
            return orig;
        }

        const vec3& direction() const {
            return dir;
        }

        point3 at(double t) const {
            return orig + t*dir;
        }
}

#endif