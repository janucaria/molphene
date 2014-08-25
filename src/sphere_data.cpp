#include "sphere_data.h"

namespace molphene {
    
    sphere_data::sphere_data()
    : primitive_data()
    , latdiv_(20)
    , londiv_(10)
    {
    }
    
    unsigned int sphere_data::unitlen() const {
        return londiv_ * (latdiv_ + 1) * 2 + londiv_ * 2;
    }
    
    void sphere_data::insert(size_t idx, sphere_data::input_type param) {
        vec3f pos;
        float rad;
        colour col;
        vec3f * posdat;
        vec3f * normdat;
        colour * coldat;
        
        std::tie(pos, rad, col) = param;
        std::tie(posdat, normdat, coldat) = data_;
        
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
                
                posdat[idx] = pos;
                normdat[idx] = norm * rad;
                coldat[idx] = col;
                idx++;
                
                if(j == 0) {
                    posdat[idx] = posdat[idx - 1];
                    normdat[idx] = normdat[idx - 1];
                    coldat[idx] = coldat[idx - 1];
                    idx++;
                }
                
                norm(cosPhi * nextSinTheta, sinPhi * nextSinTheta, nextCosTheta);
                
                posdat[idx] = pos;
                normdat[idx] = norm * rad;
                coldat[idx] = col;
                idx++;
                
                if(j == latdiv_) {
                    posdat[idx] = posdat[idx - 1];
                    normdat[idx] = normdat[idx - 1];
                    coldat[idx] = coldat[idx - 1];
                    idx++;
                }
            }
        }
    }
    
}