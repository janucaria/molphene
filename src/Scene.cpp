#include "Scene.h"

namespace molphene {
    
    Scene::Scene() {
        
    }
    
    bool Scene::setupGraphics() {
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
        
        return true;
    }
    
    void Scene::changeDimension(GLsizei width, GLsizei height) {
        // calculate bounding sphere
        BoundingSphere bs;
        
        Molecule::ModelList & models = molecule.getModels();
        Molecule::ModelList::iterator modIt = models.begin();
        
        std::vector<Atom> atoms;
        
        for( ; modIt != models.end(); ++modIt) {
            Model model = *modIt;
            Model::AtomMap atomMap = model.getAtoms();
            Model::AtomMap::iterator atomIt = atomMap.begin();
            
            for( ; atomIt != atomMap.end(); ++atomIt) {
                Atom & atm = *atomIt->second;
                bs.expand(atm.getPosition());
            }
        }
        
        glViewport(0, 0, width, height);
        
        mat4f projectionMatrix;
        
        float fov         = M_PI / 4.0f;
        float theta       = fov / 2.0f;
        float tanTheta    = tan(theta);
        float y           = bs.getRadius() + 2.0f;
        float focalLength = y / tanTheta;
        float near        = focalLength - y;
        float far         = focalLength + y;
        float aspect      = 1.0f * width / height;
        
        camera.setFov(fov);
        camera.setNear(near);
        camera.setFar(far);
        camera.setAspect(aspect);
        camera.translate(0, 0, focalLength);
        camera.updateProjectionMatrix();
        
        modelMatrix();
        modelMatrix.translate(-bs.getCenter());
    }
    
    void Scene::resetMesh() {
        
        std::vector<Atom*> atoms;
        
        Molecule::model_iterator modelIt = molecule.beginModel();
        Molecule::model_iterator modelEndIt = molecule.endModel();
        
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
                        Atom * atom = &(*atomIt);
                        atoms.push_back(atom);
                    }
                }
            }
        }
        
        
        LOG_D("Size of atoms : %ld", atoms.size());
        
        GLuint totalAtoms = static_cast<GLuint>(atoms.size());
        SphereMeshBuilder meshBuilder(totalAtoms);
        GLuint totalVertices = meshBuilder.getTotalVertices();
        renderer.setVericesSize(totalVertices);
        
        LOG_D("vertices size : %u", totalVertices);
        
        for(unsigned int i = 0; i < totalAtoms; ++i) {
            
            Atom & atom = *atoms.at(i);
            const Element & element = atom.getElement();
            const vec3f & apos = atom.getPosition();
            const colour & acol = colorManager.getElementColor(element.symbol);
            float arad = element.radiiVdW;
            
            meshBuilder.buildSphere(i, apos, arad, acol);
        }
        
        renderer.setBufferPosition(meshBuilder.getPositions());
        renderer.setBufferNormal(meshBuilder.getNormals());
        renderer.setBufferColor(meshBuilder.getColors());
    }
    
    void Scene::clearRect() {
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    }
    
    void Scene::renderFrame() {
        clearRect();
        
        renderer.useGLProgram();
        
        renderer.setProjectionMatrix(camera.getProjectionMatrix());
        renderer.setModelViewMatrix(modelMatrix * camera.getViewMatrix());
        
        renderer.render();
    }
    
    
    void Scene::rotate(float x, float y, float z) {
        modelMatrix.rotate(1.0f, 0.0f, 0.0f, x);
        modelMatrix.rotate(0.0f, 1.0f, 0.0f, y);
        modelMatrix.rotate(0.0f, 0.0f, 1.0f, z);
        renderFrame();
    }
    
    void Scene::openStream(std::istream & is) {
        PDBParser parser;
        parser.parse(molecule, is);
    }
    
    
}