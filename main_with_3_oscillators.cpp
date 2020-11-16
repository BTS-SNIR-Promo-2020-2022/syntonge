#include <Arduino.h>
#include <MozziGuts.h>   // at the top of your sketch
#include <Oscil.h> // oscillator template
#include <tables/sin8192_int8.h> // sine table for oscillator
#include <AudioDelay.h>
#include <EventDelay.h>

Oscil<SIN8192_NUM_CELLS, AUDIO_RATE> aCos2(SIN8192_DATA);
Oscil<SIN8192_NUM_CELLS, AUDIO_RATE> aCos1(SIN8192_DATA);
Oscil<SIN8192_NUM_CELLS, AUDIO_RATE> aCos3(SIN8192_DATA);

#define CONTROL_RATE 128 // Hz, powers of 2 are most reliable


void setup(){
  startMozzi(CONTROL_RATE);
  aCos1.setFreq(440); //la
  aCos2.setFreq(659); //mi
  aCos3.setFreq(523); //do
}


void updateControl(){
}

int updateAudio(){
  int asig = aCos1.next() + aCos2.next() + aCos3.next();
  return asig>>3; // return an int signal centred around 0
}
int check_pause(){
    // if(paused==true){
    //   stopMozzi();
    // }
    // if(paused==false){
    //   startMozzi();
    // }
}

void loop(){
    // EventDelay(5000);
    audioHook();
    // EventDelay(5000);
    // stopMozzi();
    // EventDelay(5000);
    // startMozzi(CONTROL_RATE);
}
