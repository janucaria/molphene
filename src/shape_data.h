#ifndef __Molphene__shape_data__
#define __Molphene__shape_data__

namespace molphene {
    template<typename T, typename U>
    class shape_data {
    public:
        typedef T input_type;
        typedef U output_type;
        
        shape_data();
        
        virtual ~shape_data();
        
        void push(input_type param);
        
        virtual const output_type data() = 0;
        
        virtual void reserve(size_t n);
        
        size_t capacity() const;
        
        size_t size() const;
        
        void resize();
        
        virtual void clear();
        
        bool is_full();
        
        size_t length() const;
        
        virtual unsigned int unitlen() const = 0;
        
    protected:
        
        virtual void insert(size_t idx, input_type param) = 0;
        
    private:
        size_t size_;
        
        size_t capacity_;
    };
    
    
    template<typename T, typename U>
    shape_data<T, U>::shape_data()
    : size_(0)
    , capacity_(0)
    {
    }
    
    template<typename T, typename U>
    shape_data<T, U>::~shape_data() {
    }
    
    template<typename T, typename U>
    void shape_data<T, U>::clear() {
        size_ = 0;
    }
    
    template<typename T, typename U>
    void shape_data<T, U>::reserve(size_t n) {
        capacity_ = n;
    }
    
    template<typename T, typename U>
    bool shape_data<T, U>::is_full() {
        return size_ == capacity_;
    }
    
    template<typename T, typename U>
    size_t shape_data<T, U>::size() const {
        return size_;
    }
    
    template<typename T, typename U>
    void shape_data<T, U>::resize() {
        size_ = 0;
    }
    
    template<typename T, typename U>
    size_t shape_data<T, U>::capacity() const {
        return capacity_;
    }
    
    template<typename T, typename U>
    void shape_data<T, U>::push(shape_data<T, U>::input_type param) {
        insert(size_ * unitlen(), param);
        ++size_;
    }
    
    template<typename T, typename U>
    size_t shape_data<T, U>::length() const {
        return size_ * unitlen();
    }
}

#endif /* defined(__Molphene__shape_data__) */
