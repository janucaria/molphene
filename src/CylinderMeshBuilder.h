#ifndef __Molphene__CylinderMeshBuilder__
#define __Molphene__CylinderMeshBuilder__

#include <cmath>
#include "logger.h"
#include "vec3f.h"
#include "colour.h"

namespace molphene {
    class CylinderMeshBuilder {
    public:
        CylinderMeshBuilder(unsigned int totalModels);
        ~CylinderMeshBuilder();
        
        unsigned int getTotalVertices();
        
        void buildMesh(unsigned int idx, vec3f pos1, vec3f pos2, float rad, colour col);
        
        const vec3f * getPositions();
        const colour * getColors();
        const vec3f * getNormals();
        
    private:
        unsigned int getVerticesSize();
        
        unsigned int bands_;
        
        unsigned int totalVertices;
        
        vec3f * positions;
        vec3f * normals;
        colour * colors;
    };
}

#endif /* defined(__Molphene__CylinderMeshBuilder__) */
