#ifndef __molphene__Scene__
#define __molphene__Scene__

#include "opengl.h"
#include "vec3f.h"
#include "colour.h"
#include "Renderer.h"

namespace molphene {
    
    class Scene {
    public:
        
        Scene();
        
        bool setupGraphics();
        
        void resetMesh();
        
        void changeDimension(GLsizei width, GLsizei height);
        
        void clearRect();
        
        void renderFrame();
        
    private:
        Renderer renderer;
        
    };
    
    
}

#endif /* defined(__molphene__Scene__) */
