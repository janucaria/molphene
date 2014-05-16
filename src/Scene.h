#ifndef __molphene__Scene__
#define __molphene__Scene__

#include <cmath>
#include "opengl.h"
#include "vec3f.h"
#include "colour.h"
#include "Renderer.h"
#include "mat4f.h"
#include "Camera.h"
#include "Atom.h"
#include "Model.h"
#include "Molecule.h"

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
        
        Camera camera;
        
        Molecule molecule;
        
    };
    
    
}

#endif /* defined(__molphene__Scene__) */
