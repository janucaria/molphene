#ifndef __Molphene__cylinder_data__
#define __Molphene__cylinder_data__

#include <tuple>
#include "logger.h"
#include "vec3f.h"
#include "colour.h"
#include "primitive_data.h"

namespace molphene {
    class cylinder_data : public primitive_data<std::tuple<vec3f, vec3f, float, colour>> {
    public:
        
        cylinder_data();
        
        void insert(size_t idx, input_type param) override;
        
        unsigned int unitlen() const override;
        
    private:
        
        unsigned int bands_;
    
    };
}

#endif /* defined(__Molphene__cylinder_data__) */
