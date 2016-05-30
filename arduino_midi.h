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
#include <SoftwareSerial.h>

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

    int channel = -1;
    int type = -1;
    int dataByte1 = -1;
    int dataByte2 = -1;

    int     numBytes = 0;
    bool    m_IsSysEx = false;
    
        
    /*
    
    bool    isController();
    bool    isNoteOn();
    bool    inNoteOff();
    bool    isNoteOnOrOff();+
    bool    isSysEx();
    
    int     getNumBytes();
    
    */
};

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
    MidiMessage receiveInput();
    //void appendInputMidiMessagesToBuffer(MidiMessageBuffer& buffer);
    //void fillBufferWithInputMidiMessages(MidiMessageBuffer& bufferToFill);

    
private:
    int clampChannel(int channel);
    int clampValue(int value);
    void readSerial(int &byte);
    void packByte(int &byte, MidiMessage &message);
    bool validatePacket(MidiMessage &message);
    bool processingSysEx = false;
    int packetSize = 0;

    MidiMessage m_Message;
    SoftwareSerial *m_SoftSerial;

};



#endif /* arduino_midi_h */
