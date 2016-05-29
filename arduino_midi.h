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

class MidiMessage;
class MidiMessageBuffer;

class Midi
{
public:
    
    Midi();
    
    // ============= Init
    void start();

    
    // ============= Output
    void sendController(int channel, int cc, int value);
    void sendNoteOn(int channel, int note, int velocity);
    void sendNoteOff(int channel, int note, int velocity);
    
    
    // ============= Input
    MidiMessageBuffer getInputMidiMessages();
    //void appendInputMidiMessagesToBuffer(MidiMessageBuffer& buffer);
    //void fillBufferWithInputMidiMessages(MidiMessageBuffer& bufferToFill);

    
private:
    int clampChannel(int channel);
    int clampValue(int value);
    void readSerial();
    void processByte();
    bool processingSysEx = false;

    int serialByte = -1;
    int rawByteBuffer[256];
};

class MidiMessage
{
public:
    enum TYPE
    {
        NOTE_OFF,
        NOTE_ON,
        POLYPHONIC,
        CC,
        PROGRAM_CHANGE,
        CHANNEL_PRESSURE,
        PITCH_BEND,
        SYSTEM_EXCLUSIVE
    };
    
        
    /*
    
    bool    isController();
    bool    isNoteOn();
    bool    inNoteOff();
    bool    isNoteOnOrOff();
    bool    isSysEx();
    
    int     getNumBytes();
    
    */
};

class MidiMessageBuffer
{
public:
    /*
    void clear();
    void appendMidiMessage(MidiMessage message);
    void prependMidiMessage(MidiMessage message);
    int  getNumMessages();
    MidiMessage getMessageAtIndex(int index)
     */
    
};

#endif /* arduino_midi_h */
