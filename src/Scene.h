#ifndef __molphene__Scene__
#define __molphene__Scene__

#include <istream>
#include <fstream>
#include "opengl.h"
#include "vec3f.h"
#include "colour.h"
#include "Renderer.h"
#include "ColorLightRenderer.h"
#include "mat4f.h"
#include "Camera.h"
#include "atom.h"
#include "bond.h"
#include "model.h"
#include "molecule.h"
#include "ColourManager.h"
#include "BoundingSphere.h"
#include "PDBParser.h"
#include "color_light_buffer.h"

namespace molphene {
    typedef unsigned char colormode_t;
    
    class Scene {
    public:
        
        bool displaySpacefill;
        bool displayStick;
        bool displayWireframe;
        
        Scene();
        
        virtual ~Scene();
        
        bool setupGraphics(GLsizei width, GLsizei height);
        
        void resetMesh();
        
        void changeDimension(GLsizei width, GLsizei height);
        
        void clearRect();
        
        void renderFrame();
        
        void rotate(float x, float y, float z);
        
        void openStream(std::istream & is);
        
        colormode_t setColorMode(colormode_t val);
        
        colormode_t getColorMode();
        
        void zoom(float z);
        
    private:
        colormode_t colorMode_;
        
        color_light_buffer sphere_buff_atoms;
        color_light_buffer cylinder_buff_atoms;
        color_light_buffer line_buff_bonds;
        
        Renderer renderer;
        
        ColorLightRenderer cylinderRenderer;
        
        mat4f modelMatrix;
        
        Camera camera;
        
        molecule * molecule_;
        
        ColourManager colorManager;
        
        const colour & getAtomColor_(const atom & atm);
        
    };
    
    
}

#endif /* defined(__molphene__Scene__) */
