#ifndef relay_h
#define relay_h

class relay
{
    private:
        int pin;
        relay* next = nullptr; 
        char buff[6];
        
    public:
        relay();
        void set_pin(int p);
        int _pin_();
        void set_next_relay(relay * _next);
        relay * next_relay();
        void on();
        void off();
};

#endif
