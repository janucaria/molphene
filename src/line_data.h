#ifndef __molphene__line_data__
#define __molphene__line_data__

#include <cstddef>
#include "logger.h"
#include "vec3f.h"
#include "colour.h"
#include "primitive_data.h"

namespace molphene {
    
    class line_data : public primitive_data<vec3f, vec3f, colour> {
    public:
        
        line_data();
        
        void insert(size_t idx, vec3f pos1, vec3f pos2, colour col) override;
        
        unsigned int unitlen() const override;
        
    private:
        
    };
}



#endif /* defined(__molphene__line_data__) */
