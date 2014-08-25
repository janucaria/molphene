#ifndef Molphene_primitive_data_h
#define Molphene_primitive_data_h

#include <tuple>
#include "logger.h"
#include "vec3f.h"
#include "colour.h"
#include "shape_data.h"

namespace molphene {
    template<typename T>
    class primitive_data : public shape_data<T, typename std::tuple<vec3f*, vec3f*, colour*>> {
    public:
        typedef typename shape_data<T, typename std::tuple<vec3f*, vec3f*, colour*>>::output_type output_type;
        
        primitive_data();
        
        virtual ~primitive_data();
        
        void clear() override;
        
        void reserve(size_t n) override;
        
        const vec3f * positions();
        
        const vec3f * normals();
        
        const colour * colors();
        
        virtual unsigned int unitlen() const = 0;
        
        const output_type data() override;
        
    protected:
        output_type data_;
    };
    
    
    template<typename T>
    primitive_data<T>::primitive_data()
    : shape_data<T, typename primitive_data<T>::output_type>()
    , data_(std::make_tuple(nullptr, nullptr, nullptr))
    {
    }
    
    template<typename T>
    primitive_data<T>::~primitive_data() {
        clear();
    }
    
    template<typename T>
    void primitive_data<T>::clear() {
        shape_data<T, typename primitive_data<T>::output_type>::clear();
        
        delete[] std::get<0>(data_);
        delete[] std::get<1>(data_);
        delete[] std::get<2>(data_);
        
        data_ = std::make_tuple(nullptr, nullptr, nullptr);
    }
    
    template<typename T>
    void primitive_data<T>::reserve(size_t n) {
        shape_data<T, typename primitive_data<T>::output_type>::reserve(n);
        
        size_t totalVertices = shape_data<T, typename primitive_data<T>::output_type>::capacity() * unitlen();
        
        data_ = std::make_tuple(new vec3f[totalVertices], new vec3f[totalVertices], new colour[totalVertices]);
    }
    
    template<typename T>
    const vec3f * primitive_data<T>::positions() {
        return std::get<0>(data_);
    }
    
    template<typename T>
    const vec3f * primitive_data<T>::normals() {
        return std::get<1>(data_);
    }
    
    template<typename T>
    const colour * primitive_data<T>::colors() {
        return std::get<2>(data_);
    }
    
    template<typename T>
    const typename primitive_data<T>::output_type primitive_data<T>::data() {
        return data_;
    }
}

#endif
