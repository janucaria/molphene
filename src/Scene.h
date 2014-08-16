#ifndef __molphene__Scene__
#define __molphene__Scene__

#include <istream>
#include <fstream>
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
#include "SphereMeshBuilder.h"
#include "ColourManager.h"
#include "BoundingSphere.h"
#include "PDBParser.h"

namespace molphene {
    
    class Scene {
    public:
        
        Scene();
        
        bool setupGraphics(GLsizei width, GLsizei height);
        
        void resetMesh();
        
        void changeDimension(GLsizei width, GLsizei height);
        
        void clearRect();
        
        void renderFrame();
        
        void rotate(float x, float y, float z);
        
        void openStream(std::istream & is);
        
    private:
        Renderer renderer;
        
        mat4f modelMatrix;
        
        Camera camera;
        
        Molecule molecule;
        
        ColourManager colorManager;
        
    };
    
    
}

#endif /* defined(__molphene__Scene__) */
