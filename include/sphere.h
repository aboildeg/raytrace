#ifndef SPHERE_H
#define SPHERE_H

#include "common.h"
#include "hittable.h"

class Sphere : public Hittable {
    public:
        Sphere(const point3& center, double radius) : center(center), radius(std::fmax(0, radius)) {}
        
        bool hit(const ray& r, double tmin, double tmax, hit_record& rec) const override;
    
    private:
        double radius;
        point3 center;
};


#endif