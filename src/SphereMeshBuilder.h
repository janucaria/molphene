#ifndef __Molphene__SphereMeshBuilder__
#define __Molphene__SphereMeshBuilder__

#include <cmath>
#include "logger.h"
#include "vec3f.h"
#include "colour.h"

namespace molphene {
    class SphereMeshBuilder {
    public:
        SphereMeshBuilder(unsigned int totalModels);
        ~SphereMeshBuilder();
        
        unsigned int getTotalVertices();
        
        void buildSphere(unsigned int idx, vec3f pos, float rad, colour col);
        
        const vec3f * getPositions();
        const colour * getColors();
        const vec3f * getNormals();
        
    private:
        unsigned int getVerticesSize();
        
        unsigned int lonDiv;
        unsigned int latDiv;
        
        unsigned int totalVertices;
        
        vec3f * positions;
        vec3f * normals;
        colour * colors;
    };
}

#endif /* defined(__Molphene__SphereMeshBuilder__) */
