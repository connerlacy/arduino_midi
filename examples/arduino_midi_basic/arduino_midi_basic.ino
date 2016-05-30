///////////////////////////////////////////////////////////
///
///   @file     arduino_midi_basic.ino
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
    midi.start();    
}

void loop()
{    
    // ---------------------------------------------
    // -------- Play all notes in an octave --------
    // ---------------------------------------------
    for(int note = 60; note < 73; note++)
    {
        // Send 'note' on channel 1, with a velocity of 127
        midi.sendNoteOn(1, note, 127);
        
        // Wait 125ms
        delay(125);
        
        // Turn off 'note' on channel 1 with velocity of 0
        midi.sendNoteOff(1, note, 0);
    }
    
    delay(1000);
    
    
    
    // ---------------------------------------------
    // ------------ Play Triad Chord ---------------
    // ---------------------------------------------
    midi.sendNoteOn(1,40,64);
    midi.sendNoteOn(1,44,64);
    midi.sendNoteOn(1,47,64);
    
    // Wait
    delay(1000);
    
    // Turn off all notes on all channels
    //midi.allNotesOff();
    
    
    
    // ---------------------------------------------
    // ------------- Send CC Message ---------------
    // ---------------------------------------------
    midi.sendNoteOn(1,40,64);
    
    for(int val = 0; val < 128; val++)
    {
        // Send val on channel 1, CC 7
        midi.sendController(1, 7, val);
        delay(20);
    }
    
    midi.sendNoteOff(1,40,0);
    
    // Wait
    delay(1000);
}

