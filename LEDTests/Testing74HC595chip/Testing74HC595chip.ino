//**************************************************************//
//  Name    : First 8 LEDs Test
//  Author  : Griffin Moede
//  Date    : 7 Sep 2025
//  Version : 1.0
//  Notes   : Prototyping LED circuit for shadowbox
//****************************************************************
// #define planeHit0 A0
// #define planeHit1 A1
// #define planeHit2 A2
// #define planeHit3 A3
// #define planeHit4 A4
// #define planeHit5 A5
// #define planeHit6 A6
// #define planeHit7 A7

static const int planeHits[] = {A0, A1, A2, A3, A4, A5, 11, 12};

static const int planeLightPatternsLength = 6;

static int maxBrightness = 255;
static int minBrightness = 0;

//PIN DEFINITIONS
static const int hangGliderPin = 3;
static const int mouseBodyPin = 5;
static const int planeLLPin = 4;
static const int planeLRPin = 7;
static const int planeRLPin = 8;
static const int planeRRPin = 10;
static const int heliEyesPin = 9;


int hangGliderBrightness = 51;
int hangGliderFadeAmount = 4;
int mouseBodyBrightness = maxBrightness;
int mouseBodyFadeAmount = 6;

int heliEyesBrightness = 90;
int heliEyesFadeAmount = 15;

int planeLightPhase = 1;

int gunSequenceDelayOne = 1500;
int gunSequenceDelayTwo = 500;
int gunClock = 0;

int planeLights[] = { planeLLPin, planeLRPin, planeRLPin, planeRRPin };
int planeLightPattern0[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
int planeLightStep = 0;
int planeLightPattern = 0;
int planeLightPattern1[] = { 0b00001001, 0b00000110, 0b00001001, 0b00000110,0b00001001, 0b00000110,0b00001001, 0b00000110};
int planeLightPattern2[] = { 0b00001000, 0b00000100, 0b00000010, 0b00000001, 0b00001000, 0b00000100, 0b00000010, 0b00000001};
int planeLightPattern3[] = { 0b00001001, 0b00000000, 0b00001001, 0b00000000, 0b00001001, 0b00000000, 0b00001001, 0b00000000};
int planeLightPattern4[] = { 0b00000110, 0b00000000, 0b00000110, 0b00000000, 0b00000110, 0b00000000, 0b00000110, 0b00000000};
int planeLightPattern5[] = { 0b00001000, 0b00000100, 0b00000010, 0b00000001, 0b00000001, 0b00000010, 0b00000100, 0b00001000};
int* planeLightPatterns[planeLightPatternsLength] = { planeLightPattern0, planeLightPattern1 , planeLightPattern2, planeLightPattern3, planeLightPattern4, planeLightPattern5};
bool shouldChooseNextPlaneLightPhase = true;



void setup() {
  Serial.begin(9600);
  pinMode(hangGliderPin, OUTPUT);
  pinMode(mouseBodyPin, OUTPUT);
  pinMode(planeLLPin, OUTPUT);
  pinMode(planeLRPin, OUTPUT);
  pinMode(planeRLPin, OUTPUT);
  pinMode(planeRRPin, OUTPUT);
  pinMode(heliEyesPin, OUTPUT);

  for(int i = 0; i < 8; i++){
    pinMode(planeHits[i], OUTPUT);
  }
}

void loop() {
  //digitalWrite(latchPin, );
  // pause before next value:
  analogWrite(hangGliderPin, hangGliderBrightness);
  analogWrite(mouseBodyPin, mouseBodyBrightness);
  analogWrite(heliEyesPin, heliEyesBrightness);
  fade(hangGliderPin, hangGliderFadeAmount, hangGliderBrightness);
  fade(mouseBodyPin, mouseBodyFadeAmount, mouseBodyBrightness);
  fade(heliEyesPin, heliEyesFadeAmount, heliEyesBrightness);
  shootPlaneGuns();

  delay(75);
}

void shootPlaneGuns() {
  if(planeLightStep >= 8){
    int randomNumber = random(0, planeLightPatternsLength);
    Serial.println(randomNumber);
    planeLightPattern =  randomNumber;
    planeLightStep = 0;
  }
  int planeLightPatternInteger = planeLightPatterns[planeLightPattern][planeLightStep];
  writePlaneLights(planeLightPatternInteger);
  planeLightStep++;

  // if(shouldChooseNextPlaneLightPhase){
  //   shouldChooseNextPlaneLightPhase = false;
  //   int randomNumber = random(0, planeLightPatternsLength);
  //   Serial.println(randomNumber);
  //   planeLightPattern =  randomNumber;
  //   planeLightStep = 0;
  // }
}

void writePlaneLights(int planeLightPatternInteger){
    digitalWrite(planeLLPin, planeLightPatternInteger & 0b1000);
    digitalWrite(planeLRPin, planeLightPatternInteger & 0b0100);
    digitalWrite(planeRLPin, planeLightPatternInteger & 0b0010);
    digitalWrite(planeRRPin, planeLightPatternInteger & 0b0001);
      for(int i = 0; i < 8; i++){
        if(planeLightPatternInteger!= 0 && i == planeLightStep){
          digitalWrite(planeHits[i], HIGH);
        } else {
          digitalWrite(planeHits[i], LOW);
        }
      }
    
}

// the loop routine runs over and over again forever:
void fade(int pin, int &fadeAmount, int &brightness) {
  // set the brightness of pin 9:
  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0) {
    brightness = 0;
    fadeAmount = -fadeAmount;
  } else if (brightness >= 255) {
    brightness = 255;
    fadeAmount = -fadeAmount;
  }
}
