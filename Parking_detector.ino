#include "pitches.h"

const int train_detect_pin=12;  // digital input
const int note_pin = 8;         // digital output
const int note_duration = 1000 / 4;

int alarm_state = 0;
int note_restart_tick = 0;

void note_restart()
{
    note_restart_tick = now + 3;
    tone(note_pin, NOTE_C5, note_duration);
}

void alarm_poll(int now)
{
    if(alarm_state)
    {
        if(now > note_restart_tick)
        {
            note_restart();
        }
    }
    else
    {
        noTone(note_pin);
    }
}

void parking_init()
{
    pinMode(train_detect_pin, INPUT);
}

void parking_poll(int now)
{
    if(digitalRead(train_detect_pin))
    { 
        alarm_state = 1;
    }
    else
    { 
        alarm_state = 0;
    }
}
