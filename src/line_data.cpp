#include "line_data.h"

namespace molphene {
    
    line_data::line_data()
    : primitive_data()
    {
    }
    
    unsigned int line_data::unitlen() const {
        return 2;
    }
    
    void line_data::insert(size_t idx, vec3f pos1, vec3f pos2, colour col) {
        
        positions_[idx] = pos1;
        normals_[idx] = vec3f(0,0,0);
        colors_[idx] = col;
        
        idx++;
        
        positions_[idx] = pos2;
        normals_[idx] = vec3f(0,0,0);
        colors_[idx] = col;
        
        idx++;
    }
    
}