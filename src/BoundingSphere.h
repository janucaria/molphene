#ifndef __Molphene__BoundingSphere__
#define __Molphene__BoundingSphere__

#include "vec3f.h"

namespace molphene {
    class BoundingSphere {
        float radius;
        vec3f center;
    public:
        BoundingSphere();
        void reset();
        void expand(const vec3f & position);
        float getRadius();
        vec3f getCenter();
    };
    
}


#endif /* defined(__Molphene__BoundingSphere__) */
