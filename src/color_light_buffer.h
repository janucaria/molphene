#ifndef __Molphene__color_light_buffer__
#define __Molphene__color_light_buffer__

#include "opengl.h"
#include "logger.h"
#include "vec3f.h"
#include "colour.h"

namespace molphene {
    class color_light_buffer {
        
    public:
        
        color_light_buffer();
        
        ~color_light_buffer();
        
        void setup();
        
        void reserve(GLuint size);
        
        void set_position_data(GLintptr offset, GLsizeiptr size, const vec3f * data);
        
        void set_normal_data(GLintptr offset, GLsizeiptr size, const vec3f * data);
        
        void set_color_data(GLintptr offset, GLsizeiptr size, const colour * data);
        
        void push(GLsizeiptr size, const vec3f * posdat, const vec3f * normdat, const colour * caldat);
        
        void render(GLenum mode, GLuint posloc, GLuint normloc, GLuint colloc);
        
    protected:
        GLintptr size_;
        GLuint capacity_;
        
        GLuint position_buffer_;
        GLuint normal_buffer_;
        GLuint color_buffer_;
    };
}

#endif /* defined(__Molphene__color_light_buffer__) */
