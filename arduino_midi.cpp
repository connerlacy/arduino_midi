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
MidiMessage Midi::getInputMidiMessage()
{
    MidiMessage message;

    readSerial(serialByte);

    if(serialByte > -1)
    {
        packByte(serialByte, message);
    }

    if(packetSize == 3)
    {
        validatePacket(message);
    }
}

void Midi::readSerial(int &byte)
{
    // Read incoming bytes
    if (Serial.available())
    {
        byte = Serial.read();
    }
}

void Midi::packByte(int &byte, MidiMessage &message)
{
    if(!processingSysEx)
    {
        // Expecting status byte...
        if(packetSize == 0)
        {
            // Get message type.
            int status = 0x08 ^ ((byte) >> 4);

            // Check to make sure it's in the appropriate range
            if(status >= 0 && status <= 7)
            {
                // If it is, increment packet size
                packetSize++;
                message.type = status;

                // Set Channel (if not SysEx)
                if(status != 7)
                {
                    message.channel = (byte) & 0x0F;
                }
                else
                {
                    // Handle sysetem exclusive here
                }
            }
            else
            {
                // ERROR
            }
        }

        // Expecting first Data Byte...
        else if(packetSize == 1)
        {
            if(!(byte >> 7))
            {
                packetSize++;
                message.dataByte1 = byte;
            }
            else
            {
                // ERROR INVALID DATA BYTE 1
            }
        }

        // Expecting second Data Byte...
        else if(packetSize == 2)
        {
            if(!(byte >> 7))
            {
                packetSize++;
                message.dataByte1 = byte;
                completMessage();
            }
            else
            {
                // ERROR INVALID DATA BYTE 2
            }
        }

        // Packet size is greater than 2, must be processing sysex
        else
        {

        }
        
        /*
        switch (status)
        {
            case MidiMessage::NOTE_OFF:
            break;

            case MidiMessage::NOTE_ON:
            break;

            case MidiMessage::POLYPHONIC:
            break;

            case MidiMessage::CC:
            break;

            case MidiMessage::PROGRAM_CHANGE:
            break;

            case MidiMessage::CHANNEL_PRESSURE:
            break;

            case MidiMessage::PITCH_BEND:
            break;

            case MidiMessage::SYSTEM_EXCLUSIVE:
            processingSysEx = true;
            break;    			

            default:
            break;
        }
            */
    }

}

bool Midi::validatePacket(MidiMessage &message)
{
    if(message.channel > 15  || message.channel < 0)
    {
        return false;
    }

    if(type < 0 || type > 6) // Not supporting sysex for now
    {
        return false;
    }

    if(dataByte1 < 0 || dataByte1 > 127)
    {
        return false;
    }

    if(dataByte2 < 0 || dataByte2 > 127)
    {
        return false;
    }

    return true;
}

// ============================================================ //
// ======================= MidiMessage ======================== //
// ============================================================ //



