//
//  arduino_midi.hpp
//  
//
//  Created by connerlacy on 4/17/16.
//
//

#ifndef arduino_midi_h
#define arduino_midi_h

#include <stdio.h>
#include "Arduino.h"

class Midi
{
public:
    
    Midi();
    
    void start();

    void sendController(int channel, int cc, int value);
    void sendNoteOn(int channel, int note, int velocity);
    void sendNoteOff(int channel, int note, int velocity);


private:
	int clampChannel(int channel);
	int clampValue(int value);
};

#endif /* arduino_midi_h */
