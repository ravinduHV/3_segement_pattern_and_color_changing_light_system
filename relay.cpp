#include "relay.h"
#include <Arduino.h>

//#include <iostream>
using namespace std;

relay::relay()
{
  Serial.println("Relay Created");
}

int relay::_pin_()
{
  return pin;
}

void relay::set_pin(int p)
{
  //Serial.begin(9600); 
  this->pin = p;
  Serial.print("Relay Created ::Reference Pin: ");
  Serial.println(p);
  pinMode(p, OUTPUT);
}

void relay::set_next_relay(relay * _next)
{
  this->next = _next;
  sprintf(buff,"%p",next);
  Serial.print("Set Next Relay at :: ");
  Serial.println(buff);
}

relay * relay::next_relay()
{
  return next;
}

void relay::on()
{
  digitalWrite(pin, HIGH);
  Serial.print("Relay up:on pin:");
  Serial.println(pin);
}

void relay::off()
{
  digitalWrite(pin, LOW);
  Serial.print("Relay down:on pin:");
  Serial.println(pin);
}

