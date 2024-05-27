#ifndef segegment_h
#define segment_h
#include "relay.h"

class segment
{
    private:
        int * pin;
        int * color_pins;
        segment* next = nullptr; 
        int relay_array_size;
        int color_array_size = 3;
        
    public:
        relay * relay_array;
        relay * color_array_RBY;
        segment(int p[]);
        void set_relay();
        void set_next_segment(segment * _next);
        segment * next_segment();
};

#endif