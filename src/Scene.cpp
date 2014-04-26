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
        
        struct vec3f * positions = new struct vec3f[verticesPerModel] {
            vec3f(-0.0f, +1.0f, +0.0f),
            vec3f(+1.0f, +1.0f, +0.0f),
            vec3f(+0.0f, -1.0f, +0.0f)
        };
        
        renderer.setVericesSize(verticesPerModel);
        renderer.setBufferPosition(positions);
        
        delete[] positions;
    }
    
    void Scene::clearRect() {
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    }
    
    void Scene::renderFrame() {
        clearRect();
        renderer.render();
    }
    
    
}