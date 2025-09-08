int led = 9;         // the fade PWM pin the LED is attached to
int flash1 = 10;  
int flash2 = 9;
int brightness = 50;  // how bright the LED is
int fadeAmount = 5;  // how many points to fade the LED by
int BRIGHTNESS_MAX = 255;
bool flash1active = true;
bool flash2active = false;


// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  pinMode(led, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // set the brightness of pin 9:
  //flash();
  turnOn();
}

void turnOn(){
  analogWrite(flash1, BRIGHTNESS_MAX);
  analogWrite(flash2, BRIGHTNESS_MAX);
}

void flash(){
    // set the brightness of pin 9:
  analogWrite(flash1, flash1active ? BRIGHTNESS_MAX : 0);
  analogWrite(flash2, flash2active ? BRIGHTNESS_MAX : 0);

  if(flash1active || flash2active){
    flash1active = !flash1active;
    flash2active = !flash2active;
  }


  // analogWrite(flash1, BRIGHTNESS_MAX);

  // // change the brightness for next time through the loop:
  // brightness = brightness + fadeAmount;

  // // reverse the direction of the fading at the ends of the fade:
  // if (brightness <= 50 || brightness >= 255) {
  //   fadeAmount = -fadeAmount;
  // }
  // wait for 30 milliseconds to see the dimming effect
  delay(40);
}