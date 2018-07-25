#ifndef __molphene__Scene__
#define __molphene__Scene__

#include <istream>
#include <fstream>
#include "opengl.h"
#include "m3d.hpp"
#include "Renderer.h"
#include "ColorLightRenderer.h"
#include "Camera.h"
#include "atom.h"
#include "bond.h"
#include "model.h"
#include "molecule.h"
#include "ColourManager.h"
#include "BoundingSphere.h"
#include "PDBParser.h"
#include "color_light_buffer.h"
#include "sphere_buffer.h"

namespace molphene {
    typedef unsigned char colormode_t;
    
    class Scene {
    public:
    
        Scene();
        
        virtual ~Scene();
        
        bool setupGraphics();
        
        void resetMesh();
        
        void changeDimension(GLsizei width, GLsizei height);
        
        void clearRect();
        
        void renderFrame();
        
        void rotate(float x, float y, float z);
        
        void openStream(std::istream & is);
        
        void reset_molecules();
        
        void zoom(float z);
        
    private:
        
        sphere_buffer sphere_buff_atoms;
        
        Renderer renderer;
        
        mat4f modelMatrix;
        
        Camera camera;
        
        molecule * molecule_;
        
        ColourManager colorManager;
    };
    
    
}

#endif /* defined(__molphene__Scene__) */
