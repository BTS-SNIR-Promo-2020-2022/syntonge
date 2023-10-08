#include <MozziGuts.h>
#include <Oscil.h> // oscillator template
#include <tables/sin8192_int8.h> // sine table for oscillator
#include <EventDelay.h>
#define CONTROL_RATE 64
// use: Oscil <table_size, update_rate> oscilName (wavetable), look in .h file of table #included above
Oscil <SIN8192_NUM_CELLS, AUDIO_RATE> aSin(SIN8192_DATA);
// for scheduling audio gain changes
EventDelay Delay;
EventDelay Delay2;
char gain = 1;
int freq[] = {261, 329, 440};
int count=0;
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

void setup(){
  startMozzi(CONTROL_RATE);
  aSin.setFreq(330); // set the frequency
  Delay.set(1000); // 1 second countdown, within resolution of CONTROL_RATE
  pinMode(11,INPUT_PULLUP);
  pinMode(10,INPUT_PULLUP);
  pinMode(9,INPUT_PULLUP);
  Serial.begin(9600);
}
bool invert(int input){
  if(input==1){
    return false;
  }
  else if(input==0){
    return true;
  }
  return false;
}
void updateControl(){
      if(Delay.ready()){
        gain = 1-gain; // flip 0/1
        if(count<2){
          count++;
        }else{
          count = 0;
      }
    aSin.setFreq(freq[count]); // set the frequency
    Delay.start();
  }
  buttonState = invert(digitalRead(7));
  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
    } else {
    }
    delay(50);
  }
  lastButtonState = buttonState;
}
int updateAudio(){
  return aSin.next()*gain;
}
void loop(){
  audioHook();
}
