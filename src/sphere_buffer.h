#ifndef __molphene__sphere_buffer__
#define __molphene__sphere_buffer__

#include "color_light_buffer.h"

namespace molphene {
    class sphere_buffer : public color_light_buffer {
    public:
        
        sphere_buffer();
        
        void setup() override;
        
        void teardown() override;
        
        void reserve(GLuint size) override;
        
        void set_radius_data(GLintptr offset, GLsizeiptr size, const float * data);
        
        void push(GLsizeiptr size, const vec3f * posdat, const vec3f * normdat, const colour * caldat, const float* raddat);

        void render(GLenum mode, GLuint posloc, GLuint normloc, GLuint colloc, GLuint radloc);
        
    protected:
        GLuint radius_buffer_;
        
        void enable_vertex_attribs(GLuint posloc, GLuint normloc, GLuint colloc, GLuint radloc);
        
        void disable_vertex_attribs(GLuint posloc, GLuint normloc, GLuint colloc, GLuint radloc);
    };
}

#endif /* defined(__molphene__sphere_buffer__) */
