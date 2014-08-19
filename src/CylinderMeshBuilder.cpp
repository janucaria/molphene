#include "CylinderMeshBuilder.h"

namespace molphene {
    
    CylinderMeshBuilder::CylinderMeshBuilder(unsigned int totalModels) :
    positions(nullptr),
    colors(nullptr),
    bands_(15)
    {
        unsigned int verticesPerModel = getVerticesSize();
        totalVertices = verticesPerModel * totalModels;
        
        positions = new vec3f[totalVertices];
        colors = new colour[totalVertices];
        normals = new vec3f[totalVertices];
        
    }
    
    CylinderMeshBuilder::~CylinderMeshBuilder() {
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
    
    unsigned int CylinderMeshBuilder::getVerticesSize() {
        return ((bands_ + 1) * 2 + 2) * 3;
    }
    
    unsigned int CylinderMeshBuilder::getTotalVertices() {
        return totalVertices;
    }
    
    const vec3f * CylinderMeshBuilder::getPositions() {
        return positions;
    }
    
    const colour * CylinderMeshBuilder::getColors() {
        return colors;
    }
    
    const vec3f * CylinderMeshBuilder::getNormals() {
        return normals;
    }
    
    void CylinderMeshBuilder::buildMesh(unsigned int idx, vec3f pos1, vec3f pos2, float rad, colour col) {
        
        idx *= getVerticesSize();
        
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
            
            positions[idx] = pos1;
            normals[idx] = -dir;
            colors[idx] = col;
            
            idx++;
            
            if(i == 0) {
                positions[idx] = pos1;
                normals[idx] = dir;
                colors[idx] = col;
                idx++;
            }
            
            positions[idx] = pos1 + n * rad;
            normals[idx] = -dir;
            colors[idx] = col;
            idx++;
            
            if(i == bands_) {
                positions[idx] = pos1 + n * rad;
                normals[idx] = -dir;
                colors[idx] = col;
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
            
            positions[idx] = pos1 + n * rad;
            normals[idx] = n;
            colors[idx] = col;
            
            idx++;
            
            if(i == 0) {
                positions[idx] = pos1 + n * rad;
                normals[idx] = n;
                colors[idx] = col;
                idx++;
            }
            
            positions[idx] = pos2 + n * rad;
            normals[idx] = n;
            colors[idx] = col;
            idx++;
            
            if(i == bands_) {
                positions[idx] = pos2 + n * rad;
                normals[idx] = n;
                colors[idx] = col;
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
            
            positions[idx] = pos2 + n * rad;
            normals[idx] = dir;
            colors[idx] = col;
            
            idx++;
            
            if(i == 0) {
                positions[idx] = pos2 + n * rad;
                normals[idx] = dir;
                colors[idx] = col;
                idx++;
            }
            
            positions[idx] = pos2;
            normals[idx] = dir;
            colors[idx] = col;
            idx++;
            
            if(i == bands_) {
                positions[idx] = pos2;
                normals[idx] = dir;
                colors[idx] = col;
                idx++;
            }
        }
    }
    
}