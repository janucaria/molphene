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
        
        mat4f projectionMatrix;
        
        float fov         = M_PI / 4.0f;
        float theta       = fov / 2.0f;
        float tanTheta    = tan(theta);
        float y           = 1.0f;
        float focalLength = y / tanTheta;
        float near        = focalLength - y;
        float far         = focalLength + y;
        float aspect      = 1.0f * width / height;
        
        float top         = tan(fov / 2.0f) * near;
        float bottom      = -top;
        
        float left        = aspect * bottom;
        float right       = aspect * top;
        
        projectionMatrix.frustum(left, right, bottom, top, near, far);
        renderer.setProjectionMatrix(projectionMatrix);
        
        mat4f modelMatrix;
        mat4f viewMatrix;
        
        modelMatrix.scale(0.5f);
        modelMatrix.rotate(0.0f, 0.0f, 1.0f, 3.14f);
        viewMatrix.translate(0.0f, 0.0f, -focalLength);
        
        renderer.setModelViewMatrix(modelMatrix * viewMatrix);
    }
    
    void Scene::resetMesh() {
        
        GLsizei verticesPerModel = 3;
        renderer.setVericesSize(verticesPerModel);
        
        vec3f * positions = new vec3f[verticesPerModel] {
            vec3f(-1.0f, +1.0f, +0.0f),
            vec3f(+1.0f, +1.0f, +0.0f),
            vec3f(+0.0f, -1.0f, +0.0f)
        };
        
        renderer.setBufferPosition(positions);
        
        delete[] positions;
        
        colour * colours = new colour[verticesPerModel] {
            colour(255, 0, 0),
            colour(0, 255, 0),
            colour(0, 0, 255)
            
        };
        
        renderer.setBufferColor(colours);
        
        delete[] colours;
    }
    
    void Scene::clearRect() {
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    }
    
    void Scene::renderFrame() {
        clearRect();
        renderer.render();
    }
    
    
}