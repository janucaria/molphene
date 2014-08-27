#include "Scene.h"
#include "sphere_data.h"
#include "cylinder_data.h"
#include "mat3f.h"
#include <tuple>

namespace molphene {
    
    Scene::Scene()
    : displaySpacefill(true)
    , displayStick(false)
    , colorMode_(0)
    , molecule(new Molecule())
    {
    }
    
    Scene::~Scene() {
        delete molecule;
        molecule = nullptr;
    }
    
    bool Scene::setupGraphics(GLsizei width, GLsizei height) {
        glClearColor(0.5, 0.5, 0.5, 1.0);
        glEnable(GL_DEPTH_TEST);
        
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
        
        
        cylinderRenderer.setupGL();
        cylinderRenderer.useGLProgram();
        
        cylinderRenderer.setLightSourceAmbient(0.5, 0.5, 0.5, 1.0);
        cylinderRenderer.setLightSourceDiffuse(1.0, 1.0, 1.0, 1.0);
        cylinderRenderer.setLightSourceSpecular(0.5, 0.5, 0.5, 1.0);
        cylinderRenderer.setLightSourcePosition(0.0, 0.0, 0.0);
        
        cylinderRenderer.setMaterialAmbient(0.3, 0.3, 0.3, 1.0);
        cylinderRenderer.setMaterialDiffuse(1.0, 1.0, 1.0, 1.0);
        cylinderRenderer.setMaterialSpecular(0.5, 0.5, 0.5, 1.0);
        cylinderRenderer.setMaterialShininess(10);
        
        changeDimension(width, height);
        
        return true;
    }
    
    void Scene::changeDimension(GLsizei width, GLsizei height) {
        camera.setAspect(1.0f * width / height);
        camera.updateProjectionMatrix();
        
        glViewport(0, 0, width, height);
    }
    
    void Scene::resetMesh() {
        std::vector<Atom*> atoms;
        std::vector<Bond*> bonds;
        
        Molecule::model_iterator modelIt = molecule->beginModel();
        Molecule::model_iterator modelEndIt = molecule->endModel();
        
        for( ; modelIt != modelEndIt; ++modelIt) {
            Model::chain_iterator chainIt = modelIt->beginChain();
            Model::chain_iterator chainEndIt = modelIt->endChain();
            
            for( ; chainIt != chainEndIt; ++chainIt) {
                Chain::compound_iterator compoundIt = chainIt->beginCompound();
                Chain::compound_iterator compoundEndIt = chainIt->endResidue();
                
                for( ; compoundIt != compoundEndIt; ++compoundIt) {
                    Compound::atom_iterator atomIt = compoundIt->beginAtom();
                    Compound::atom_iterator atomEndIt = compoundIt->endAtom();
                    
                    for( ; atomIt != atomEndIt; ++atomIt) {
                        Atom * atom = &(*atomIt);
                        atoms.push_back(atom);
                    }
                }
                
                compoundEndIt = chainIt->endCompound();
                for( ; compoundIt != compoundEndIt; ++compoundIt) {
                    Compound::atom_iterator atomIt = compoundIt->beginAtom();
                    Compound::atom_iterator atomEndIt = compoundIt->endAtom();
                    
                    for( ; atomIt != atomEndIt; ++atomIt) {
                        Atom * atom = &(*atomIt);
                        atoms.push_back(atom);
                    }
                }
            }
            
            Model::BondList::iterator bondIt = modelIt->beginBond();
            Model::BondList::iterator bondEndIt = modelIt->endBond();
            for( ; bondIt != bondEndIt; ++bondIt) {
                Bond * bond = &(*bondIt);
                bonds.push_back(bond);
            }
        }
        
        sphere_data spheredat;
        cylinder_data cylinderdat;
        
        LOG_D("Size of atoms : %ld", atoms.size());
        
        GLuint totalAtoms = static_cast<GLuint>(atoms.size());
        spheredat.reserve(totalAtoms);
        GLuint totalVertices = totalAtoms * spheredat.unitlen();
        renderer.setVericesSize(totalVertices);
        
        LOG_D("vertices size : %u", totalVertices);
        
        for(unsigned int i = 0; i < totalAtoms; ++i) {
            Atom & atom = *atoms.at(i);
            const Element & element = atom.getElement();
            const vec3f & apos = atom.getPosition();
            const colour & acol = getAtomColor_(atom);
            float arad = element.radiiVdW;
            
            spheredat.push(apos, arad, acol);
            
            if(spheredat.is_full()) {
                renderer.push(spheredat.length(), spheredat.positions(), spheredat.normals(), spheredat.colors());
                spheredat.resize();
            }
        }
        
        renderer.push(spheredat.length(), spheredat.positions(), spheredat.normals(), spheredat.colors());
        
        
        LOG_D("Size of bonds : %ld", bonds.size());
        
        GLuint totalBonds = static_cast<GLuint>(bonds.size());
        cylinderdat.reserve(totalBonds);
        GLuint totalVertices2 = totalBonds * cylinderdat.unitlen() * 2;
        cylinderRenderer.setVericesSize(totalVertices2);

//        LOG_D("vertices size : %u", totalVertices);
        
        for(unsigned int i = 0; i < totalBonds; ++i) {
            Bond * bond = bonds.at(i);
            Atom & atom1 = bond->getAtom1();
            Atom & atom2 = bond->getAtom2();
            
            const vec3f & apos1 = atom1.getPosition();
            const colour & acol1 = getAtomColor_(atom1);
            
            const vec3f & apos2 = atom2.getPosition();
            const colour & acol2 = getAtomColor_(atom2);
            
            vec3f midpos((apos1 + apos2) / 2);
            float arad = 0.25f;
            
            cylinderdat.push(apos1, midpos, arad, acol1);
            if(cylinderdat.is_full()) {
                cylinderRenderer.push(cylinderdat.length(), cylinderdat.positions(), cylinderdat.normals(), cylinderdat.colors());
                cylinderdat.resize();
            }
            cylinderdat.push(midpos, apos2, arad, acol2);
            if(cylinderdat.is_full()) {
                cylinderRenderer.push(cylinderdat.length(), cylinderdat.positions(), cylinderdat.normals(), cylinderdat.colors());
                cylinderdat.resize();
            }
        }
        
        cylinderRenderer.push(cylinderdat.length(), cylinderdat.positions(), cylinderdat.normals(), cylinderdat.colors());
    }
    
    void Scene::clearRect() {
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    }
    
    void Scene::renderFrame() {
        clearRect();
        
        mat4f modelViewMatrix = modelMatrix * camera.getViewMatrix();
        mat3f normalMalrix = mat3f(mat4f(modelViewMatrix).inverse().transpose());
        
        if(displaySpacefill) {
            renderer.useGLProgram();
            
            renderer.setProjectionMatrix(camera.getProjectionMatrix());
            renderer.setModelViewMatrix(modelViewMatrix);
            
            renderer.render();
        }
        
        if(displayStick) {
            cylinderRenderer.useGLProgram();
            
            cylinderRenderer.setProjectionMatrix(camera.getProjectionMatrix());
            cylinderRenderer.setNormalMatrix(normalMalrix);
            cylinderRenderer.setModelViewMatrix(modelViewMatrix);
            
            cylinderRenderer.render();
        }
    }
    
    void Scene::rotate(float x, float y, float z) {
        modelMatrix.rotate(1.0f, 0.0f, 0.0f, x);
        modelMatrix.rotate(0.0f, 1.0f, 0.0f, y);
        modelMatrix.rotate(0.0f, 0.0f, 1.0f, z);
        renderFrame();
    }
    
    void Scene::openStream(std::istream & is) {
        PDBParser parser;
        delete molecule;
        molecule = nullptr;
        molecule = new Molecule();
        parser.parse(*molecule, is);
        
        // calculate bounding sphere
        BoundingSphere bs;
        
        Molecule::model_iterator modelIt = molecule->beginModel();
        Molecule::model_iterator modelEndIt = molecule->endModel();
        
        for( ; modelIt != modelEndIt; ++modelIt) {
            Model::chain_iterator chainIt = modelIt->beginChain();
            Model::chain_iterator chainEndIt = modelIt->endChain();
            
            for( ; chainIt != chainEndIt; ++chainIt) {
                Chain::compound_iterator compoundIt = chainIt->beginCompound();
                Chain::compound_iterator compoundEndIt = chainIt->endCompound();
                
                for( ; compoundIt != compoundEndIt; ++compoundIt) {
                    Compound::atom_iterator atomIt = compoundIt->beginAtom();
                    Compound::atom_iterator atomEndIt = compoundIt->endAtom();
                    
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

        modelMatrix();
        modelMatrix.translate(-bs.getCenter());
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
    
    const colour & Scene::getAtomColor_(const Atom & atm) {
        switch (colorMode_) {
            case 1:
                return colorManager.getAltlocColor(atm.getAltLoc());
                break;
        }
        
        return colorManager.getElementColor(atm.getElement().symbol);
    }
    
}