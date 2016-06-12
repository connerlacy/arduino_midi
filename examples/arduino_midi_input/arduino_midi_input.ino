///////////////////////////////////////////////////////////
///
///   @file     arduino_midi_input.ino
///   @author   emergent.io
///   @license  BSD
///   @contact  conner@emergent.io
///
///  This example demonstrates the basic functionality of
///  the arduino_midi library by http://www.emergent.io
///  
///////////////////////////////////////////////////////////

#include <arduino_midi.h>

// Create MIDI
Midi midi;

void setup()
{
    // Start sendning and receiving messages
    midi.start(9600);    
}

void loop()
{    
    // ---------------------------------------------
    // ----- Get MIDI Input from Software/USB ------
    // ---------------------------------------------
    MidiMessage m = midi.receiveInput(midi.SOFTWARE);
    
    
    // ---------------------------------------------
    // ----- Echo MidiMessage to the hardware ------
    // ---------------------------------------------
    if(m.isValid())
    {
        // Echo the incoming message out to hardware
        midi.sendMidiMessage(m, midi.HARDWARE);
    }
}

