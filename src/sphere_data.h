#ifndef __Molphene__sphere_data__
#define __Molphene__sphere_data__

#include "logger.h"
#include "vec3f.h"
#include "colour.h"
#include "primitive_data.h"

namespace molphene {
    
    class sphere_data : public primitive_data<vec3f, float, colour> {
    public:
        sphere_data();
        
        void insert(size_t idx, vec3f pos, float rad, colour col) override;
        
        unsigned int unitlen() const override;
        
    private:
        
        unsigned int londiv_;
        
        unsigned int latdiv_;
    };
}

#endif /* defined(__Molphene__sphere_data__) */
