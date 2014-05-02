#include "Scene.h"

namespace molphene {
    
    Scene::Scene() {
    }
    
    bool Scene::setupGraphics() {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        
        renderer.setupGL();
        
        return true;
    }
    
    void Scene::changeDimension(GLsizei width, GLsizei height) {
        glViewport(0, 0, width, height);
    }
    
    void Scene::resetMesh() {
        
        GLsizei verticesPerModel = 3;
        renderer.setVericesSize(verticesPerModel);
        
        struct vec3f * positions = new struct vec3f[verticesPerModel] {
            vec3f(-1.0f, +1.0f, +0.0f),
            vec3f(+1.0f, +1.0f, +0.0f),
            vec3f(+0.0f, -1.0f, +0.0f)
        };
        
        renderer.setBufferPosition(positions);
        
        delete[] positions;
        
        struct colour * colours = new struct colour[verticesPerModel] {
            colour(255, 0, 0),
            colour(0, 255, 0),
            colour(0, 0, 255)
            
        };
        
        renderer.setBufferColor(colours);
        
        delete[] colours;
        
        mat4f modelMatrix;
        mat4f viewMatrix;
        
        modelMatrix.scale(0.5f);
        modelMatrix.rotate(0.0f, 0.0f, 1.0f, 3.14f);
        viewMatrix.translate(0.25f, 0.0f, 0.0f);
        
        renderer.setModelViewMatrix(modelMatrix * viewMatrix);
    }
    
    void Scene::clearRect() {
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    }
    
    void Scene::renderFrame() {
        clearRect();
        renderer.render();
    }
    
    
}