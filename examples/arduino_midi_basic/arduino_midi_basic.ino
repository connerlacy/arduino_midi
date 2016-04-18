#include <arduino_midi.h>

Midi midi;

void setup()
{
    midi.start();
}

void loop()
{
    midi.sendNoteOn(1,60,127);
    delay(1000);
    
    for(int i = 0; i < 127; i++)
    {
       midi.sendController(1,7,i);
    }
    
    midi.sendNoteOff(1,60,127);
}
