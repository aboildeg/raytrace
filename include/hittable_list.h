#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "common.h"
#include "hittable.h"
#include <vector>


class Hittable_list : public Hittable {
    public:
        std::vector<shared_ptr<Hittable>> objects;

        Hittable_list() {}
        Hittable_list(shared_ptr<Hittable> object) {add(object);}

        void clear() {objects.clear();}

        void add(shared_ptr<Hittable> object) {
            objects.push_back(object);
        }

        bool hit(const ray& r, double tmin, double tmax, hit_record& rec) const override {
            hit_record temp_rec;
            bool hit_anything = false;
            double closest = tmax;

            for (const shared_ptr<Hittable>& object : objects) {
                if (object->hit(r, tmin, closest, temp_rec)) {
                    hit_anything = true;
                    closest = temp_rec.t;
                    rec = temp_rec;
                }
            }

            return hit_anything;
        }
};

#endif

