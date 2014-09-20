#ifndef __Molphene__shape_data__
#define __Molphene__shape_data__

#include <cstddef>

namespace molphene {
    template<typename... T>
    class shape_data {
    public:
        
        shape_data();
        
        virtual ~shape_data();
        
        void push(T... param);
        
        virtual void reserve(size_t n);
        
        size_t capacity() const;
        
        size_t size() const;
        
        void resize();
        
        virtual void clear();
        
        bool is_full();
        
        size_t length() const;
        
        virtual unsigned int unitlen() const = 0;
        
    protected:
        
        virtual void insert(size_t idx, T... param) = 0;
        
    private:
        size_t size_;
        
        size_t capacity_;
    };
    
    
    template<typename ...T>
    shape_data<T...>::shape_data()
    : size_(0)
    , capacity_(0)
    {
    }
    
    template<typename ...T>
    shape_data<T...>::~shape_data() {
    }
    
    template<typename ...T>
    void shape_data<T...>::clear() {
        size_ = 0;
    }
    
    template<typename ...T>
    void shape_data<T...>::reserve(size_t n) {
        capacity_ = n;
    }
    
    template<typename ...T>
    bool shape_data<T...>::is_full() {
        return size_ == capacity_;
    }
    
    template<typename ...T>
    size_t shape_data<T...>::size() const {
        return size_;
    }
    
    template<typename ...T>
    void shape_data<T...>::resize() {
        size_ = 0;
    }
    
    template<typename ...T>
    size_t shape_data<T...>::capacity() const {
        return capacity_;
    }
    
    template<typename ...T>
    void shape_data<T...>::push(T... param) {
        insert(size_ * unitlen(), param...);
        ++size_;
    }
    
    template<typename ...T>
    size_t shape_data<T...>::length() const {
        return size_ * unitlen();
    }
}

#endif /* defined(__Molphene__shape_data__) */
