//
//  colour.cpp
//  molphene
//
//  Created by Januar Andaria on 4/27/14.
//  Copyright (c) 2014 Janucaria. All rights reserved.
//

#include "colour.h"

namespace molphene {
    colour::colour() : r(255), g(0), b(0), a(UCHAR_MAX) {}
    
    colour::colour(unsigned char r, unsigned char g, unsigned char b, unsigned char a) :
        r(r), g(g), b(b), a(a) {}
    
    colour::colour(unsigned int col) :
        r((col & 0x00FF0000) >> 16),
        g((col & 0x0000FF00) >> 8),
        b(col & 0x000000FF),
        a((col >> 24) ^ 0xFF)
    {
    }
    
    struct colour & colour::operator () (unsigned char r, unsigned char g, unsigned char b, unsigned char a)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
        
        return *this;
    }
    
    struct colour & colour::operator () (unsigned int col) {
        return (*this)((col & 0x00FF0000) >> 16, (col & 0x0000FF00) >> 8, col & 0x000000FF, (col >> 24) ^ 0xFF);
    }

}