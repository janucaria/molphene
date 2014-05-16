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
        
        mat4f modelMatrix;
        
        modelMatrix.scale(0.5f);
        modelMatrix.rotate(0.0f, 0.0f, 1.0f, 3.14f);
        
        renderer.setProjectionMatrix(camera.getProjectionMatrix());
        renderer.setModelViewMatrix(modelMatrix * camera.getViewMatrix());
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
        
        GLuint totalAtoms = atoms.size();
        
        GLuint verticesPerModel = 3 * totalAtoms;
        renderer.setVericesSize(verticesPerModel);
        
        LOG_D("vertices size : %u", verticesPerModel);
        
        vec3f * positions = new vec3f[verticesPerModel];
        
        for(unsigned int i = 0; i < totalAtoms; ++i) {
            
            vec3f apos = atoms.at(i).getPosition();
            
            LOG_D("positio : [%f, %f, %f]", apos.x, apos.y, apos.z);
            
            positions[i * 3 + 0] = vec3f(apos.x - 1.0f, apos.y + 1.0f, apos.z + 0.0f) * 0.25;
            positions[i * 3 + 1] = vec3f(apos.x + 1.0f, apos.y + 1.0f, apos.z + 0.0f) * 0.25;
            positions[i * 3 + 2] = vec3f(apos.x + 0.0f, apos.y - 1.0f, apos.z + 0.0f) * 0.25;

        }
        
        renderer.setBufferPosition(positions);
        
        delete[] positions;
        
        colour * colours = new colour[verticesPerModel] {
            colour(255, 0, 0),
            colour(255, 0, 0),
            colour(255, 0, 0),
            
            colour(0, 255, 0),
            colour(0, 255, 0),
            colour(0, 255, 0),
            
            colour(0, 0, 255),
            colour(0, 0, 255),
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