#include "relay.h"
#include "segment.h"

using namespace std;

#define SEGMENT_ID  0

float time = 1000;
float weight;
int round_count;

int segment_0_pins[] = {8,4,3,5,6,7,8,9,10};
int segment_1_pins[] = {4,3,6,4,5};
int segment_2_pins[] = {8,3,4,5,6,7,8,9,10};
int segment_0_size = 8;
int segment_1_size = 4;
int segment_2_size = 8;

//connect color pins to pin 11, 12, 13.

const int color_array_size = 3;
const int segment_array_size = 3;

segment segment_array[segment_array_size] = {segment_0_pins,segment_1_pins,segment_2_pins};

unsigned long startTime;
unsigned long endTime;
unsigned long duration;;

bool Adjust = false;

void setup()
{
  Serial.begin(9600); 
  for(int i = 0; i < segment_array_size; i++)
  {
    if(i > 0)
      segment_array[i-1].set_next_segment(&segment_array[i]);
  }
  segment_array[segment_array_size-1].set_next_segment(&segment_array[0]);

  
}


void loop()
{
  if((SEGMENT_ID == 0||SEGMENT_ID == 1) && !Adjust)
  {
    delay(500);
    Adjust = true;
  }
  pattern_1();
  pattern_2();
  pattern_3();
}


void pattern_1()
{
  weight = 0.8;
  //Serial.println("full blackout");
  full_blackOut();
  //Serial.println("child blackout");
  child_blackOut();
  //Serial.println("loop begins");

  for (int i = 0; i < color_array_size; i++)
  {
    Serial.println(i);

    if(SEGMENT_ID == 0)
    {  
      if(i > 0)
        segment_array[SEGMENT_ID].color_array_RBY[i-1].off();  
      segment_array[SEGMENT_ID].color_array_RBY[i].on();
      if(i == 1)
        child_pattern_0();
      delay(time*weight*3);

    }
    else if(SEGMENT_ID == 1)
    {
      if(i == 1)
        child_blackOut();
      if(i > 0)
        segment_array[SEGMENT_ID].color_array_RBY[i-1].off();
      delay(time*weight);
      segment_array[SEGMENT_ID].color_array_RBY[i].on();  
      if (i == 0 || i == 2)
        child_pattern_0();
      delay(time*weight*2);
      if (i == 2)
        child_blackOut();
    }  
    else if(SEGMENT_ID == 2)
    {
      delay(time*weight*2);
      if(i > 0)
        segment_array[SEGMENT_ID].color_array_RBY[i-1].off();
      segment_array[SEGMENT_ID].color_array_RBY[i].on();
      if(i == 1)
        child_pattern_0();
      if(i == 2)
        child_blackOut();
      delay(time*weight);
    }
  }
  full_blackOut();
}

void pattern_2()
{
  for(int i = 0; i < color_array_size; i++)
  {
    if(SEGMENT_ID==0)
    {
      segment_array[SEGMENT_ID].color_array_RBY[i].on();
      segment_array[SEGMENT_ID].color_array_RBY[i].next_relay()->on();
      child_pattern_1();
    }
    else if(SEGMENT_ID == 1)
    {
      segment_array[SEGMENT_ID].color_array_RBY[i].on();
      segment_array[SEGMENT_ID].color_array_RBY[i].next_relay()->on();
      child_pattern_1();
    }
    else if(SEGMENT_ID == 2)
    {
      segment_array[SEGMENT_ID].color_array_RBY[i].on();
      segment_array[SEGMENT_ID].color_array_RBY[i].next_relay()->on();
      child_pattern_1();
    }
    segment_array[SEGMENT_ID].color_array_RBY[i].off();
  }
  full_blackOut();
}

void pattern_3()
{
  weight = 0.4;
  //full_color();
  for (int i = 0; i < 6; i++)
  {
    if(SEGMENT_ID == 0 || SEGMENT_ID == 2)
    { 
      segment_array[SEGMENT_ID].color_array_RBY[i%3].on();
      delay(time*weight);
      segment_array[SEGMENT_ID].color_array_RBY[i%3].next_relay()->on();
      delay(time*weight);
      segment_array[SEGMENT_ID].color_array_RBY[i%3].next_relay()->next_relay()->on();
      delay(time*weight);
    }
    else if (SEGMENT_ID == 1)
    {
      segment_array[SEGMENT_ID].color_array_RBY[i%3].on();
      delay(time*weight);
      delay(time*weight);
      delay(time*weight);
    }
    full_blackOut();
  }
}

void full_color()
{
  segment_array[SEGMENT_ID].color_array_RBY[0].on();
  segment_array[SEGMENT_ID].color_array_RBY[1].on();
  segment_array[SEGMENT_ID].color_array_RBY[2].on();  
}

void full_blackOut()
{
  for(int i = 0; i < color_array_size; i++)
  {
    segment_array[SEGMENT_ID].color_array_RBY[i].off();
  }
}

void child_blackOut()
{
  if(SEGMENT_ID == 1)
  {
    for(int i = 0; i < segment_1_size;i++)
    {
      segment_array[SEGMENT_ID].relay_array[i].off();
    }
  }
  else{
    for(int i = 0; i < segment_0_size;i++)
    {
      segment_array[SEGMENT_ID].relay_array[i].off();
    }
  }
}

void child_blackOut(int seg_)
{
  if(seg_ == 1)
  {
    for(int i = 0; i < segment_1_size;i++)
    {
      segment_array[seg_].relay_array[i].off();
    }
  }
  else{
    for(int i = 0; i < segment_0_size;i++)
    {
      segment_array[seg_].relay_array[i].off();
    }
  }
}

void child_pattern_0()
{
  if(SEGMENT_ID == 1)
  {
    for(int i = 0; i < segment_1_size;i++)
    {
      segment_array[SEGMENT_ID].relay_array[i].on();
    }
  }
  else{
    for(int i = 0; i < segment_0_size;i++)
    {
      segment_array[SEGMENT_ID].relay_array[i].on();
    }
  }
}

void child_pattern_1()
{
  weight = 0.5;
  if(SEGMENT_ID == 1)
  {
    for(int i = 0; i < segment_1_size;i++)
    {
      delay(time*weight);
    }
  }
  else{
    for(int i = 0; i < segment_0_size;i++)
    {
      segment_array[SEGMENT_ID].relay_array[i].on();
      segment_array[SEGMENT_ID].relay_array[i].next_relay()->next_relay()->on();
      segment_array[SEGMENT_ID].relay_array[i].next_relay()->next_relay()->next_relay()->next_relay()->on();
      segment_array[SEGMENT_ID].relay_array[i].next_relay()->next_relay()->next_relay()->next_relay()->next_relay()->next_relay()->on();
      delay(time*weight);
      segment_array[SEGMENT_ID].relay_array[i].off();
      segment_array[SEGMENT_ID].relay_array[i].next_relay()->next_relay()->off();
      segment_array[SEGMENT_ID].relay_array[i].next_relay()->next_relay()->next_relay()->next_relay()->off();
      segment_array[SEGMENT_ID].relay_array[i].next_relay()->next_relay()->next_relay()->next_relay()->next_relay()->next_relay()->off();
    }
  }
}