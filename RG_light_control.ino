#include "Timer.h"  //https://github.com/JChristensen/Timer

Timer tmr;  

const int green_led = 2;
const int yellow_led = 3;
const int red_led = 4;

#define STATE_GREEN 1
#define STATE_YELLOW 2
#define STATE_RED 3

int state;
int next_tick;
int now;

void led_switch() {

    if(now == next_tick)
    {
        switch(state)
        {      
            case STATE_GREEN:
            digitalWrite(green_led, HIGH);
            digitalWrite(yellow_led, LOW);
            digitalWrite(red_led, LOW);
            next_tick+=250;         // 25s ÷ 100ms = 250 counts
            state = STATE_YELLOW;
            break;
            
            case STATE_YELLOW:
            digitalWrite(green_led, LOW);
            digitalWrite(yellow_led, HIGH);
            digitalWrite(red_led, LOW);
            next_tick+=25;          // 2.5s ÷ 100ms = 25 counts
            state = STATE_RED;
            break;
            
            case STATE_RED:
            digitalWrite(green_led, LOW);
            digitalWrite(yellow_led, LOW);
            digitalWrite(red_led, HIGH);
            next_tick+=50;         // 5s ÷ 100ms = 50 counts
            state = STATE_GREEN;
            break;
        }
    }
}

void myTick() {
    now++;
}

void setup() {
    state = STATE_GREEN;
    next_tick = 0;
    now = 0;

    Serial.begin(9600);
    
    pinMode(green_led, OUTPUT);
    pinMode(yellow_led, OUTPUT);
    pinMode(red_led, OUTPUT);
    
    tmr.every(100, myTick);

    parking_init();
}

void loop() {
    tmr.update();
    led_switch();

    parking_poll(now);
    alarm_poll(now);
}
