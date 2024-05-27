#include "relay.h"
#include "segment.h"

segment::segment(int p[])
{
    this->relay_array_size = p[0];
    this->pin = new int[p[0]];
    this->color_pins = new int[3];

    for (int i = 0; i < relay_array_size; i++)
        pin[i] = p[i+1];
    for(int i = 0; i < color_array_size; i++)
        color_pins[i] = i+11;
    set_relay();
}

void segment::set_relay()
{
    this->relay_array = new relay[relay_array_size];
    this->color_array_RBY = new relay[color_array_size];

    for (int i = 0; i < relay_array_size ; i++)
    {
        relay_array[i].set_pin(pin[i]);
        if(i > 0)
        {
            relay_array[i-1].set_next_relay(&relay_array[i]);
        }
    } 
    relay_array[relay_array_size-1].set_next_relay(&relay_array[0]);

    for (int i = 0; i < color_array_size; i++)
    {
        color_array_RBY[i].set_pin(color_pins[i]);
        if(i > 0)
        {
            color_array_RBY[i-1].set_next_relay(&color_array_RBY[i]);
        }
    } 
    color_array_RBY[color_array_size-1].set_next_relay(&color_array_RBY[0]);
}

void segment::set_next_segment(segment *_next)
{
    this->next = _next;
}

segment *segment::next_segment()
{
    return next;
}

