#ifndef __Molphene__sphere_data__
#define __Molphene__sphere_data__

#include <cstddef>
#include "logger.h"
#include "m3d.hpp"
#include "primitive_data.h"

namespace molphene {
    
    class sphere_data : public primitive_data<vec3f, float, colour> {
    public:
        sphere_data();
        
        void clear() override;
        
        void reserve(size_t n) override;
        
        void insert(size_t idx, vec3f pos, float rad, colour col) override;
        
        unsigned int unitlen() const override;
        
        float* radiuses();
        
    private:
        
        unsigned int londiv_;
        
        unsigned int latdiv_;
        
        float* radiuses_;
    };
}

#endif /* defined(__Molphene__sphere_data__) */
