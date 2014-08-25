#include "cylinder_data.h"

namespace molphene {
    
    cylinder_data::cylinder_data()
    : primitive_data()
    , bands_(15)
    {
    }
    
    unsigned int cylinder_data::unitlen() const {
        return ((bands_ + 1) * 2 + 2) * 3;
    }
    
    void cylinder_data::insert(size_t idx, cylinder_data::input_type param) {
        vec3f pos1, pos2;
        float rad;
        colour col;
        vec3f * posdat;
        vec3f * normdat;
        colour * coldat;
        
        std::tie(pos1, pos2, rad, col) = param;
        std::tie(posdat, normdat, coldat) = data_;
        
        vec3f dir = pos2 - pos1;
        dir.normalize();
        
        vec3f top = cross(vec3f(0, 0, 1), dir);
        if(!top.length()) {
            top = vec3f(0, 1, 0);
        }
        
        top.normalize();
        
        vec3f right = cross(dir, top);
        
        right.normalize();
        
        for(unsigned int i = 0; i <= bands_; ++i) {
            float theta = 2.0f * M_PI * (i % bands_) / bands_;
            float sinTheta = sin(theta);
            float cosTheta = cos(theta);
            
            vec3f vx = right * cosTheta;
            vec3f vy = top * sinTheta;
            vec3f n = vx + vy;
            
            posdat[idx] = pos1;
            normdat[idx] = -dir;
            coldat[idx] = col;
            
            idx++;
            
            if(i == 0) {
                posdat[idx] = pos1;
                normdat[idx] = dir;
                coldat[idx] = col;
                idx++;
            }
            
            posdat[idx] = pos1 + n * rad;
            normdat[idx] = -dir;
            coldat[idx] = col;
            idx++;
            
            if(i == bands_) {
                posdat[idx] = pos1 + n * rad;
                normdat[idx] = -dir;
                coldat[idx] = col;
                idx++;
            }
        }
        
        for(unsigned int i = 0; i <= bands_; ++i) {
            float theta = 2.0f * M_PI * (i % bands_) / bands_;
            float sinTheta = sin(theta);
            float cosTheta = cos(theta);
            
            vec3f vx = right * cosTheta;
            vec3f vy = top * sinTheta;
            vec3f n = vx + vy;
            
            posdat[idx] = pos1 + n * rad;
            normdat[idx] = n;
            coldat[idx] = col;
            
            idx++;
            
            if(i == 0) {
                posdat[idx] = pos1 + n * rad;
                normdat[idx] = n;
                coldat[idx] = col;
                idx++;
            }
            
            posdat[idx] = pos2 + n * rad;
            normdat[idx] = n;
            coldat[idx] = col;
            idx++;
            
            if(i == bands_) {
                posdat[idx] = pos2 + n * rad;
                normdat[idx] = n;
                coldat[idx] = col;
                idx++;
            }
        }
        
        for(unsigned int i = 0; i <= bands_; ++i) {
            float theta = 2.0f * M_PI * (i % bands_) / bands_;
            float sinTheta = sin(theta);
            float cosTheta = cos(theta);
            
            vec3f vx = right * cosTheta;
            vec3f vy = top * sinTheta;
            vec3f n = vx + vy;
            
            posdat[idx] = pos2 + n * rad;
            normdat[idx] = dir;
            coldat[idx] = col;
            
            idx++;
            
            if(i == 0) {
                posdat[idx] = pos2 + n * rad;
                normdat[idx] = dir;
                coldat[idx] = col;
                idx++;
            }
            
            posdat[idx] = pos2;
            normdat[idx] = dir;
            coldat[idx] = col;
            idx++;
            
            if(i == bands_) {
                posdat[idx] = pos2;
                normdat[idx] = dir;
                coldat[idx] = col;
                idx++;
            }
        }
    }
    
}