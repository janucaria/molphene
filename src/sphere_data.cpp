#include "sphere_data.h"

namespace molphene {
    
    sphere_data::sphere_data()
    : primitive_data()
    , latdiv_(20)
    , londiv_(10)
    , radiuses_(nullptr)
    {
    }
    
    unsigned int sphere_data::unitlen() const {
        return londiv_ * (latdiv_ + 1) * 2 + londiv_ * 2;
    }
    
    void sphere_data::clear() {
        primitive_data::clear();
        delete[] radiuses_;
        radiuses_ = nullptr;
    }
    
    void sphere_data::reserve(size_t n) {
        primitive_data::reserve(n);
        
        size_t totalvers = capacity() * unitlen();
        
        radiuses_ = new float[totalvers];
    }
    
    float* sphere_data::radiuses() {
        return radiuses_;
    }
    
    void sphere_data::insert(size_t idx, vec3f pos, float rad, colour col) {
        for(unsigned int i = 0; i < londiv_; ++i) {
            float theta = 1.0f * i * M_PI / londiv_;
            float sinTheta = sin(theta);
            float cosTheta = cos(theta);
            
            float nextTheta = 1.0f * (i + 1) * M_PI / londiv_;
            float nextSinTheta = sin(nextTheta);
            float nextCosTheta = cos(nextTheta);
            
            for (unsigned int j = 0; j <= latdiv_; ++j) {
                float phi = 2.0f * M_PI * j / latdiv_;
                float sinPhi = sin(phi);
                float cosPhi = cos(phi);
                
                vec3f norm(cosPhi * sinTheta, sinPhi * sinTheta, cosTheta);
                
                positions_[idx] = pos;
                normals_[idx] = norm;
                colors_[idx] = col;
                radiuses_[idx] = rad;
                idx++;
                
                if(j == 0) {
                    positions_[idx] = positions_[idx - 1];
                    normals_[idx] = normals_[idx - 1];
                    colors_[idx] = colors_[idx - 1];
                    radiuses_[idx] = radiuses_[idx - 1];
                    idx++;
                }
                
                norm = {cosPhi * nextSinTheta, sinPhi * nextSinTheta, nextCosTheta};
                
                positions_[idx] = pos;
                normals_[idx] = norm;
                colors_[idx] = col;
                radiuses_[idx] = rad;
                idx++;
                
                if(j == latdiv_) {
                    positions_[idx] = positions_[idx - 1];
                    normals_[idx] = normals_[idx - 1];
                    colors_[idx] = colors_[idx - 1];
                    radiuses_[idx] = radiuses_[idx - 1];
                    idx++;
                }
            }
        }
    }
    
}