//
//  arduino_midi.cpp
//  
//
//  Created by connerlacy on 4/17/16.
//
//

#include "arduino_midi.h"


// ============================================================ //
// ============================ Midi ========================== //
// ============================================================ //

Midi::Midi()
{

}

void Midi::start()
{
    Serial.begin(31250);	
}

// ------------------------------------------------------------ //
// --------------------------- Output ------------------------- //
// ------------------------------------------------------------ //
void Midi::sendController(int channel, int cc, int value)
{
    Serial.write(clampChannel(channel) + 175); // Note On - Status bytes: [144 - 159] ==> Channel: [1 - 16]
    Serial.write(clampValue(cc));
    Serial.write(clampValue(value));
}

void Midi::sendNoteOn(int channel, int note, int velocity)
{
   Serial.write(clampChannel(channel) + 143); // Note On - Status bytes: [144 - 159] ==> Channel: [1 - 16]
   Serial.write(clampValue(note));
   Serial.write(clampValue(velocity)); 
}

void Midi::sendNoteOff(int channel, int note, int velocity)
{
   Serial.write(clampChannel(channel) + 127); // Note On - Status bytes: [144 - 159] ==> Channel: [1 - 16]
   Serial.write(clampValue(note));
   Serial.write(clampValue(velocity)); 
}

int Midi::clampChannel(int channel)
{
	if(channel > 16)
	{
		channel = 16;
	}
	else if(channel < 1)
	{
		channel = 1;
	}

	return channel;
}

int Midi::clampValue(int value)
{
	if(value > 127)
	{
		value = 127;
	}
	else if(value < 0)
	{
		value = 0;
	}

	return value;
}

// ------------------------------------------------------------ //
// --------------------------- Input -------------------------- //
// ------------------------------------------------------------ //
MidiMessageBuffer Midi::getInputMidiMessages()
{
    
}

void Midi::readSerial()
{
    // Read incoming bytes
    if (Serial.available())
    {
        serialByte = Serial.read();
    }
}

void Midi::processByte()
{
    
}

// ============================================================ //
// ======================= MidiMessage ======================== //
// ============================================================ //



