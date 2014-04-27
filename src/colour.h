//
//  colour.h
//  molphene
//
//  Created by Januar Andaria on 4/27/14.
//  Copyright (c) 2014 Janucaria. All rights reserved.
//

#ifndef __molphene__colour__
#define __molphene__colour__

#include <climits>

namespace molphene {
    struct colour {
        unsigned char r, g, b, a;
        
        colour();
        colour(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
        colour(unsigned int col);
        
        struct colour & operator () (unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
        struct colour & operator () (unsigned int col);
    };
}

#endif /* defined(__molphene__colour__) */
