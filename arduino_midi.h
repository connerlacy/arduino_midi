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

    int statusByte = -1;
    int dataByte1 = -1;
    int dataByte2 = -1;

    int     numBytes = 0;
    bool    m_IsSysEx = false;

    bool    isValid()
    {
        // This condition needs more
        // work to be readable, but is
        // fairly robust given the
        // validation scheme
        if(statusByte <=  0)
        {
            return false;
        }

        if(dataByte2 < 0)
        {
            return false;
        }

        if(dataByte1 < 0)
        {
            return false;
        }

        return true;
    }

    void clear()
    {

    }
    
    bool    isController();
    bool    isNoteOn();
    bool    inNoteOff();
    bool    isNoteOnOrOff();+
    bool    isSysEx();
    
    //int     getNumBytes();
    
};

class Midi
{
public:
    
    Midi();
    
    // ============= Init
    void start(int softwareBaudRate);


    
    // ============= Output
    void sendController(int channel, int cc, int value, int port);
    void sendNoteOn(int channel, int note, int velocity, int port);
    void sendNoteOff(int channel, int note, int velocity, int port);
    void sendMidiMessage(const MidiMessage &message, int port);
    
    
    // ============= Input
    MidiMessage receiveInput(int port);
    //void appendInputMidiMessagesToBuffer(MidiMessageBuffer& buffer);
    //void fillBufferWithInputMidiMessages(MidiMessageBuffer& bufferToFill);


     static const int HARDWARE = 0;
     static const int SOFTWARE = 1;

    
private:
    int clampChannel(int channel);
    int clampValue(int value);
    void readSerial(int &byte, int port);
    void packByte(int &byte, MidiMessage &message);
    bool validatePacket(MidiMessage &message);
    bool processingSysEx = false;
    int packetSize = 0;

    MidiMessage m_Message;
    SoftwareSerial *m_HardwareSerial;
};

#endif /* arduino_midi_h */
