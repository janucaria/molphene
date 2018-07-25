#include "Scene.h"
#include "sphere_data.h"
#include "m3d.hpp"

namespace molphene {
    
    Scene::Scene()
    : colorMode_(0)
    , molecule_(new molecule())
    {
    }
    
    Scene::~Scene() {
        delete molecule_;
        molecule_ = nullptr;
    }
    
    bool Scene::setupGraphics() {
        glClearColor(0.5, 0.5, 0.5, 1.0);
        glEnable(GL_DEPTH_TEST);
        std::cout << "Hello World" << std::endl;

        renderer.setupGL();
      
        renderer.useGLProgram();
      
        renderer.setLightSourceAmbient(0.5, 0.5, 0.5, 1.0);
        renderer.setLightSourceDiffuse(1.0, 1.0, 1.0, 1.0);
        renderer.setLightSourceSpecular(0.5, 0.5, 0.5, 1.0);
        renderer.setLightSourcePosition(0.0, 0.0, 0.0);
      
        renderer.setMaterialAmbient(0.3, 0.3, 0.3, 1.0);
        renderer.setMaterialDiffuse(1.0, 1.0, 1.0, 1.0);
        renderer.setMaterialSpecular(0.5, 0.5, 0.5, 1.0);
        renderer.setMaterialShininess(10);
      
        sphere_buff_atoms.setup();
      
        return true;
    }
    
    void Scene::changeDimension(GLsizei width, GLsizei height) {
       camera.setAspect(1.0f * width / height);
       camera.updateProjectionMatrix();
        
        glViewport(0, 0, width, height);
    }
    
    void Scene::resetMesh() {
        std::vector<atom*> atoms;
        std::vector<bond*> bonds;
        
        molecule::model_iterator modelIt = molecule_->mdlbegin();
        molecule::model_iterator modelEndIt = molecule_->mdlend();
        
        for( ; modelIt != modelEndIt; ++modelIt) {
            model::chain_iterator chainIt = modelIt->chainbegin();
            model::chain_iterator chainEndIt = modelIt->chainend();
            
            for( ; chainIt != chainEndIt; ++chainIt) {
                chain::compound_iterator compoundIt = chainIt->compbegin();
                chain::compound_iterator compoundEndIt = chainIt->resend();
                
                for( ; compoundIt != compoundEndIt; ++compoundIt) {
                    compound::atom_iterator atomIt = compoundIt->atmbegin();
                    compound::atom_iterator atomEndIt = compoundIt->atmend();
                    
                    for( ; atomIt != atomEndIt; ++atomIt) {
                        atom * atm = &(*atomIt);
                        atoms.push_back(atm);
                    }
                }
                
                compoundEndIt = chainIt->compend();
                for( ; compoundIt != compoundEndIt; ++compoundIt) {
                    compound::atom_iterator atomIt = compoundIt->atmbegin();
                    compound::atom_iterator atomEndIt = compoundIt->atmend();
                    
                    for( ; atomIt != atomEndIt; ++atomIt) {
                        atom * atm = &(*atomIt);
                        atoms.push_back(atm);
                    }
                }
            }
            
            model::bond_iterator bondIt = modelIt->beginBond();
            model::bond_iterator bondEndIt = modelIt->endBond();
            for( ; bondIt != bondEndIt; ++bondIt) {
                bond * bnd = &(*bondIt);
                bonds.push_back(bnd);
            }
        }
        
        sphere_data spheredat;
        
        LOG_D("Size of atoms : %u", static_cast<GLuint>(atoms.size()));
        
        GLuint totalAtoms = static_cast<GLuint>(atoms.size());
        spheredat.reserve(totalAtoms);
        GLuint totalVertices = totalAtoms * spheredat.unitlen();
        sphere_buff_atoms.reserve(totalVertices);
        
        LOG_D("vertices size : %u", totalVertices);
        
        for(unsigned int i = 0; i < totalAtoms; ++i) {
            atom & atm = *atoms.at(i);
            const atom::element & element = atm.getElement();
            const vec3f & apos = atm.getPosition();
            const colour & acol = getAtomColor_(atm);
            float arad = element.radiiVdW;
            
            spheredat.push(apos, arad, acol);
            
            if(spheredat.is_full()) {
                sphere_buff_atoms.push(spheredat.length(), spheredat.positions(), spheredat.normals(), spheredat.colors(), spheredat.radiuses());
                spheredat.resize();
            }
        }
        
        sphere_buff_atoms.push(spheredat.length(), spheredat.positions(), spheredat.normals(), spheredat.colors(), spheredat.radiuses());
    }
    
    void Scene::clearRect() {
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    }
    
    void Scene::renderFrame() {
        clearRect();
        
        mat4f modelViewMatrix = modelMatrix * camera.getViewMatrix();
        mat3f normalMalrix = mat3f(mat4f(modelViewMatrix).inverse().transpose());
        
        renderer.useGLProgram();
        renderer.setProjectionMatrix(camera.getProjectionMatrix());
        renderer.setModelViewMatrix(modelViewMatrix);

        renderer.render(sphere_buff_atoms);
        
        glFlush();
    }
    
    void Scene::rotate(float x, float y, float z) {
        modelMatrix.rotate(1.0f, 0.0f, 0.0f, x);
        modelMatrix.rotate(0.0f, 1.0f, 0.0f, y);
        modelMatrix.rotate(0.0f, 0.0f, 1.0f, z);
        renderFrame();
    }
    
    void Scene::reset_molecules() {
        
        // calculate bounding sphere
        BoundingSphere bs;
        
        molecule::model_iterator modelIt = molecule_->mdlbegin();
        molecule::model_iterator modelEndIt = molecule_->mdlend();
        
        for( ; modelIt != modelEndIt; ++modelIt) {
            model::chain_iterator chainIt = modelIt->chainbegin();
            model::chain_iterator chainEndIt = modelIt->chainend();
            
            for( ; chainIt != chainEndIt; ++chainIt) {
                chain::compound_iterator compoundIt = chainIt->compbegin();
                chain::compound_iterator compoundEndIt = chainIt->compend();
                
                for( ; compoundIt != compoundEndIt; ++compoundIt) {
                    compound::atom_iterator atomIt = compoundIt->atmbegin();
                    compound::atom_iterator atomEndIt = compoundIt->atmend();
                    
                    for( ; atomIt != atomEndIt; ++atomIt) {
                        bs.expand(atomIt->getPosition());
                    }
                }
            }
        }
        
        float fov         = M_PI / 4.0f;
        float theta       = fov / 2.0f;
        float tanTheta    = tan(theta);
        float y           = bs.getRadius() + 2.0f;
        float focalLength = y / tanTheta;
        float near        = focalLength - y;
        float far         = focalLength + y;
        
        camera.setFov(fov);
        camera.setNear(near);
        camera.setFar(far);
        camera.translate(0, 0, focalLength);
        camera.updateProjectionMatrix();
        
        modelMatrix.identity();
        modelMatrix.translate(-bs.getCenter());
    }
    
    void Scene::openStream(std::istream & is) {
        delete molecule_;
        molecule_ = nullptr;
        
        sphere_buff_atoms.reserve(0);
        
        molecule_ = new molecule();
        
        PDBParser parser;
        parser.parse(*molecule_, is);
        
        reset_molecules();
    }
    
    colormode_t Scene::getColorMode() {
        return colorMode_;
    }
    
    colormode_t Scene::setColorMode(colormode_t val) {
        if(colorMode_ != val) {
            colorMode_ = val;
            // NOTE: resetMesh to expensive for just reset the veritces colors
            resetMesh();
        }
        return colorMode_ = val;
    }
    
    const colour & Scene::getAtomColor_(const atom & atm) {
        switch (colorMode_) {
            case 1:
                return colorManager.getAltlocColor(atm.getAltLoc());
                break;
        }
        
        return colorManager.getElementColor(atm.getElement().symbol);
    }
    
    void Scene::zoom(float z) {
        camera.zoom(z);
        camera.updateProjectionMatrix();
    }
    
}
