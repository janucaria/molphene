#include "Scene.h"

namespace molphene {
    
    Scene::Scene() {
        
        Atom atom1(1);
        atom1.setElement("C");
        atom1.setPosition(-1.0f, +1.0f, 0.0f);
        
        Atom atom2(2);
        atom2.setElement("C");
        atom2.setPosition(+1.0f, +1.0f, +0.0f);
        
        Atom atom3(3);
        atom3.setElement("C");
        atom3.setPosition(+0.0f, -1.0f, +0.0f);
        
        Model model;
        
        model.addAtom(atom1);
        model.addAtom(atom2);
        model.addAtom(atom3);
        
        molecule.addModel(model);
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
        
        camera.setFov(fov);
        camera.setNear(near);
        camera.setFar(far);
        camera.setAspect(aspect);
        camera.updateProjectionMatrix();
        camera.translate(0, 0, focalLength);
        
        modelMatrix();
        
        modelMatrix.scale(0.5f);
        modelMatrix.rotate(0.0f, 0.0f, 1.0f, 3.14f);
    }
    
    void Scene::resetMesh() {
        
        Molecule::ModelList & models = molecule.getModels();
        Molecule::ModelList::iterator modIt = models.begin();
        
        std::vector<Atom> atoms;
        
        for( ; modIt != models.end(); ++modIt) {
            Model model = *modIt;
            Model::AtomMap atomMap = model.getAtoms();
            Model::AtomMap::iterator atomIt= atomMap.begin();
            
            for( ; atomIt != atomMap.end(); ++atomIt) {
                Atom & atm = atomIt->second;
                atoms.push_back(atm);
            }
        }
        
        
        LOG_D("Size of atoms : %ld", atoms.size());
        
        GLuint totalAtoms = static_cast<GLuint>(atoms.size());
        SphereMeshBuilder meshBuilder(totalAtoms);
        GLuint totalVertices = meshBuilder.getTotalVertices();
        renderer.setVericesSize(totalVertices);
        
        LOG_D("vertices size : %u", totalVertices);
        
        for(unsigned int i = 0; i < totalAtoms; ++i) {
            
            Atom & atom = atoms.at(i);
            vec3f apos = atom.getPosition();
            colour acol = colour(255, 0, 0);
            float arad = 0.25f;
            
            meshBuilder.buildSphere(i, apos, arad, acol);

        }
        
        renderer.setBufferPosition(meshBuilder.getPositions());
        renderer.setBufferColor(meshBuilder.getColors());
    }
    
    void Scene::clearRect() {
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    }
    
    void Scene::renderFrame() {
        clearRect();
        
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
    
    
}