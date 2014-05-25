#include "SphereMeshBuilder.h"

namespace molphene {
    
    SphereMeshBuilder::SphereMeshBuilder(unsigned int totalModels) :
        positions(nullptr),
        colors(nullptr),
        latDiv(10),
        lonDiv(10)
    {
        unsigned int verticesPerModel = getVerticesSize();
        totalVertices = verticesPerModel * totalModels;
        
        positions = new vec3f[totalVertices];
        colors = new colour[totalVertices];
        normals = new vec3f[totalVertices];
        
    }
    
    SphereMeshBuilder::~SphereMeshBuilder() {
        if(positions) {
            delete[] positions;
            positions = nullptr;
        }
        
        if(colors) {
            delete[] colors;
            colors = nullptr;
        }
        
        if(normals) {
            delete[] normals;
            normals = nullptr;
        }
    }
    
    unsigned int SphereMeshBuilder::getVerticesSize() {
        return (latDiv + 1) * (lonDiv + 1);
    }
    
    unsigned int SphereMeshBuilder::getTotalVertices() {
        return totalVertices;
    }
    
    const vec3f * SphereMeshBuilder::getPositions() {
        return positions;
    }
    
    const colour * SphereMeshBuilder::getColors() {
        return colors;
    }
    
    const vec3f * SphereMeshBuilder::getNormals() {
        return normals;
    }
    
    void SphereMeshBuilder::buildSphere(unsigned int idx, vec3f pos, float rad, colour col) {
        
        idx *= getVerticesSize();
        
        for(unsigned int i = 0; i <= lonDiv; ++i) {
            float theta = 1.0f * i * M_PI / lonDiv;
            float sinTheta = sin(theta);
            float cosTheta = cos(theta);
            
            for (unsigned int j = 0; j <= latDiv; ++j) {
                float phi = 2.0f * M_PI * j / latDiv;
                float sinPhi = sin(phi);
                float cosPhi = cos(phi);
                
                float x = cosPhi * sinTheta;
                float y = sinPhi * sinTheta;
                float z = cosTheta;
                
                positions[idx] = pos;
                normals[idx] = vec3f(x, y, z) * rad;
                colors[idx] = col;
                
                idx++;
            }
        }
    }
    
}