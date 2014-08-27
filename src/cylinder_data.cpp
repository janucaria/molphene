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
    
    void cylinder_data::insert(size_t idx, vec3f pos1, vec3f pos2, float rad, colour col) {
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
            
            positions_[idx] = pos1;
            normals_[idx] = -dir;
            colors_[idx] = col;
            
            idx++;
            
            if(i == 0) {
                positions_[idx] = pos1;
                normals_[idx] = dir;
                colors_[idx] = col;
                idx++;
            }
            
            positions_[idx] = pos1 + n * rad;
            normals_[idx] = -dir;
            colors_[idx] = col;
            idx++;
            
            if(i == bands_) {
                positions_[idx] = pos1 + n * rad;
                normals_[idx] = -dir;
                colors_[idx] = col;
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
            
            positions_[idx] = pos1 + n * rad;
            normals_[idx] = n;
            colors_[idx] = col;
            
            idx++;
            
            if(i == 0) {
                positions_[idx] = pos1 + n * rad;
                normals_[idx] = n;
                colors_[idx] = col;
                idx++;
            }
            
            positions_[idx] = pos2 + n * rad;
            normals_[idx] = n;
            colors_[idx] = col;
            idx++;
            
            if(i == bands_) {
                positions_[idx] = pos2 + n * rad;
                normals_[idx] = n;
                colors_[idx] = col;
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
            
            positions_[idx] = pos2 + n * rad;
            normals_[idx] = dir;
            colors_[idx] = col;
            
            idx++;
            
            if(i == 0) {
                positions_[idx] = pos2 + n * rad;
                normals_[idx] = dir;
                colors_[idx] = col;
                idx++;
            }
            
            positions_[idx] = pos2;
            normals_[idx] = dir;
            colors_[idx] = col;
            idx++;
            
            if(i == bands_) {
                positions_[idx] = pos2;
                normals_[idx] = dir;
                colors_[idx] = col;
                idx++;
            }
        }
    }
    
}