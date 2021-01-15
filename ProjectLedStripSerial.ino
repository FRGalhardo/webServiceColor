#include <Adafruit_NeoPixel.h>
#include <string.h>
#include <stdlib.h>
#define PIN 7
#define NUM_LEDS 238
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
// ALL METHODS FINISH BY T4A are take by tweaking4all website in that link bellow:
//https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/#Basicframework
// THE METHODS showStrip, setPixel, setAll ALSO GOT CAUGHT ON THE SITE ABOVE.
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);
String rec = "";
String param[10];
String stat = "CLR";
byte red = 255;
byte green = 255;
byte blue = 255;
int pacPos[6] = {0};
int emSize = 4;
int speedDelay = 1;
int returnDelay = 1;
int flashDelay = 50;
int waveDelay = 1;
int endPause = 1000;
int count = 10;
int meteorTrailDecay = 64;
bool meteorRandomDecay = true;

byte colors[3][3] = { {0, 230, 0},
                      {255, 255,0},
                      {115, 0, 230} };
            
byte pacColors[5][3] = { {255, 255,0}, //PAC
             {0, 42, 255}, //SCARED PHANTON
             {0, 230, 0},  // PHANTON 1
             {255   , 0   , 63}, // PHANTON 2
             {255   , 255   , 255}}; // POWER

void setup() {
  Serial.begin(4800);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {

  if (Serial.available()) {
    //CapturaSerial
    rec = Serial.readString();
    Serial.println(rec);
    //ConversaoString>Char*
    int n = rec.length();
    char mid[n + 1];
    strcpy(mid, rec.c_str());
    n = 0;
    //SplitChar*
    char *token;
    token = strtok(mid, "|");
    while (token != NULL) {
      param[n] = token;
      token = strtok(NULL, "|");
      n++;
    }

    setAll(255, 255, 255);

    for (int h; h < 10; h++) {
      Serial.print("Param");
      Serial.print(h);
      Serial.print(":");
      Serial.println(param[h]);
    }

    //SelectEffect
    selectEffect();
  }else{
    runEffect();
  }
}

void selectEffect(){
  if (param[0] == "CLR") {
      stat = "CLR";
      red = atoi(param[1].c_str());
      green = atoi(param[2].c_str());
      blue = atoi(param[3].c_str());
    }
    if (param[0] == "OFF") {
      stat = "OFF";
    }
    if (param[0] == "FIO") {
      stat = "FIO";
      red = atoi(param[1].c_str());
      green = atoi(param[2].c_str());
      blue = atoi(param[3].c_str());
    }
    if (param[0] == "STR") {
      stat = "STR";
      red = atoi(param[1].c_str());
      green = atoi(param[2].c_str());
      blue = atoi(param[3].c_str());
      count = 10;
      flashDelay = 50;
      endPause = 1000;
    }
    if (param[0] == "CYL") {
      stat = "CYL";
      red = atoi(param[1].c_str());
      green = atoi(param[2].c_str());
      blue = atoi(param[3].c_str());
      emSize = atoi(param[4].c_str());
      speedDelay = 10;
      returnDelay = 50;
    }
    if (param[0] == "KTT") {
      stat = "KTT";
      red = atoi(param[1].c_str());
      green = atoi(param[2].c_str());
      blue = atoi(param[3].c_str());
      emSize = atoi(param[4].c_str());
      speedDelay = 10;
      returnDelay = 50;
    }
    if(param[0] == "COO"){
    stat = "COO";
      red = atoi(param[1].c_str());
      green = atoi(param[2].c_str());
      blue = atoi(param[3].c_str());
      emSize = atoi(param[4].c_str());
      speedDelay = 10;
      returnDelay = 50;
    }
    if(param[0] == "SPK"){
    stat = "SPK";
      red = atoi(param[1].c_str());
      green = atoi(param[2].c_str());
      blue = atoi(param[3].c_str());
      speedDelay = 0;
    }
    if(param[0] == "RLT"){
      stat = "RLT";
      red = atoi(param[1].c_str());
      green = atoi(param[2].c_str());
      blue = atoi(param[3].c_str());
      waveDelay = 0;
    }
    if(param[0] == "CWP"){
    stat = "CWP";
      red = atoi(param[1].c_str());
      green = atoi(param[2].c_str());
      blue = atoi(param[3].c_str());
      speedDelay = 50;
    }
    if(param[0] == "RBW"){
    stat = "RBW";
      speedDelay = 50;
    }
    if(param[0] == "THC"){
      stat = "THC";
      red = atoi(param[1].c_str());
      green = atoi(param[2].c_str());
      blue = atoi(param[3].c_str());
      speedDelay = 50;
    }
    if(param[0] == "BCB"){
    stat = "BCB";
    count = atoi(param[4].c_str());
    }
    if(param[0] == "MTR"){
      stat = "MTR";
      red = atoi(param[1].c_str());
      green = atoi(param[2].c_str());
      blue = atoi(param[3].c_str());
    emSize = atoi(param[4].c_str());
    meteorRandomDecay = atoi(param[5].c_str());
      speedDelay = 50; 
    }
    if(param[0] == "SNK"){
      stat = "SNK"; 
    speedDelay = atoi(param[4].c_str());
    }
    if(param[0] == "PAC"){
      stat = "PAC"; 
    speedDelay = atoi(param[4].c_str());
    }
}

void runEffect(){
    if(stat == "CLR") {
      setAll(red, green, blue);
    }
    if(stat == "OFF") {
      setAll(0, 0, 0);
    }
    if(stat == "FIO") {
      FadeInOutT4A(red, green, blue);
    }
    if(stat == "STR"){
      StrobeT4A(red, green, blue, count, flashDelay, endPause);
    }
    if(stat == "CYL"){
      CylonBounceT4A(red, green, blue, emSize, speedDelay, returnDelay);
    }
    if(stat == "KTT"){
      NewKITTT4A();
    }
    if(stat == "COO"){
      centerOrOutside();
    }
    if(stat == "SPK"){
      SparkleT4A(red, green, blue, speedDelay);
    }
    if(stat == "RLT"){
      RunningLightsT4A(red, green, blue, speedDelay);
    }
    if(stat == "CWP"){
      colorWipeOnOffT4A();
    }
    if(stat == "RBW"){
      rainbowCycleT4A(speedDelay);
    }
    if(stat == "THC"){
      theaterChaseT4A(red, green, blue, speedDelay);
    }
    if(stat == "BCB"){
      BouncingColoredBallsT4A(count, colors);
    }
    if(stat == "MTR"){
      meteorRainT4A(red, green, blue, emSize, 64, meteorRandomDecay, speedDelay);
    }
    if(stat == "SNK"){
     
    }
    if(stat == "PAC"){
     
    }
}

void showStrip() {
#ifdef ADAFRUIT_NEOPIXEL_H
  // NeoPixel
  strip.show();
#endif
#ifndef ADAFRUIT_NEOPIXEL_H
  // FastLED
  FastLED.show();
#endif
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
#ifdef ADAFRUIT_NEOPIXEL_H
  // NeoPixel
  strip.setPixelColor(Pixel, strip.Color(red, green, blue));
#endif
#ifndef ADAFRUIT_NEOPIXEL_H
  // FastLED
  leds[Pixel].r = red;
  leds[Pixel].g = green;
  leds[Pixel].b = blue;
#endif
}

void setAll(byte red, byte green, byte blue) {
  for (int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue);
  }
  showStrip();
}

void FadeInOutT4A(byte red, byte green, byte blue) {
  float r, g, b;

  for (int k = 0; k < 256; k = k + 1) {
    r = (k / 256.0) * red;
    g = (k / 256.0) * green;
    b = (k / 256.0) * blue;
    setAll(r, g, b);
    showStrip();
  }

  for (int k = 255; k >= 0; k = k - 2) {
    r = (k / 256.0) * red;
    g = (k / 256.0) * green;
    b = (k / 256.0) * blue;
    setAll(r, g, b);
    showStrip();
  }
}

void StrobeT4A(byte red, byte green, byte blue, int StrobeCount, int FlashDelay, int EndPause){
  for(int j = 0; j < StrobeCount; j++) {
    setAll(red,green,blue);
    showStrip();
    delay(FlashDelay);
    setAll(0,0,0);
    showStrip();
    delay(FlashDelay);
  }
 
 delay(EndPause);
}

void CylonBounceT4A(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {

  for (int i = 0; i < NUM_LEDS - EyeSize - 2; i++) {
    setAll(0, 0, 0);
    setPixel(i, red / 10, green / 10, blue / 10);
    for (int j = 1; j <= EyeSize; j++) {
      setPixel(i + j, red, green, blue);
    }
    setPixel(i + EyeSize + 1, red / 10, green / 10, blue / 10);
    showStrip();
    delay(SpeedDelay);
  }

  delay(ReturnDelay);

  for (int i = NUM_LEDS - EyeSize - 2; i > 0; i--) {
    setAll(0, 0, 0);
    setPixel(i, red / 10, green / 10, blue / 10);
    for (int j = 1; j <= EyeSize; j++) {
      setPixel(i + j, red, green, blue);
    }
    setPixel(i + EyeSize + 1, red / 10, green / 10, blue / 10);
    showStrip();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

void NewKITTT4A() {
  LeftToRightT4A(red, green, blue, emSize, speedDelay, returnDelay);
  RightToLeftT4A(red, green, blue, emSize, speedDelay, returnDelay);
  CenterToOutsideT4A(red, green, blue, emSize, speedDelay, returnDelay);
  OutsideToCenterT4A(red, green, blue, emSize, speedDelay, returnDelay);
  setAll(red, green, blue);
  setAll(0,0,0);
  LeftToRightT4A(red, green, blue, emSize, speedDelay, returnDelay);
  RightToLeftT4A(red, green, blue, emSize, speedDelay, returnDelay);
  OutsideToCenterT4A(red, green, blue, emSize, speedDelay, returnDelay);
  CenterToOutsideT4A(red, green, blue, emSize, speedDelay, returnDelay);
}

void centerOrOutside() {
  CenterToOutsideT4A(red, green, blue, emSize, speedDelay, returnDelay);
  OutsideToCenterT4A(red, green, blue, emSize, speedDelay, returnDelay);
  CenterToOutsideT4A(red, green, blue, emSize, speedDelay, returnDelay);
  OutsideToCenterT4A(red, green, blue, emSize, speedDelay, returnDelay);
}

void CenterToOutsideT4A(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for (int i = ((NUM_LEDS - EyeSize) / 2); i >= 0; i--) {
    setAll(0, 0, 0);

    setPixel(i, red / 10, green / 10, blue / 10);
    for (int j = 1; j <= EyeSize; j++) {
      setPixel(i + j, red, green, blue);
    }
    setPixel(i + EyeSize + 1, red / 10, green / 10, blue / 10);

    setPixel(NUM_LEDS - i, red / 10, green / 10, blue / 10);
    for (int j = 1; j <= EyeSize; j++) {
      setPixel(NUM_LEDS - i - j, red, green, blue);
    }
    setPixel(NUM_LEDS - i - EyeSize - 1, red / 10, green / 10, blue / 10);

    showStrip();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

void OutsideToCenterT4A(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for (int i = 0; i <= ((NUM_LEDS - EyeSize) / 2); i++) {
    setAll(0, 0, 0);

    setPixel(i, red / 10, green / 10, blue / 10);
    for (int j = 1; j <= EyeSize; j++) {
      setPixel(i + j, red, green, blue);
    }
    setPixel(i + EyeSize + 1, red / 10, green / 10, blue / 10);

    setPixel(NUM_LEDS - i, red / 10, green / 10, blue / 10);
    for (int j = 1; j <= EyeSize; j++) {
      setPixel(NUM_LEDS - i - j, red, green, blue);
    }
    setPixel(NUM_LEDS - i - EyeSize - 1, red / 10, green / 10, blue / 10);

    showStrip();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

void LeftToRightT4A(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for (int i = 0; i < NUM_LEDS - EyeSize - 2; i++) {
    setAll(0, 0, 0);
    setPixel(i, red / 10, green / 10, blue / 10);
    for (int j = 1; j <= EyeSize; j++) {
      setPixel(i + j, red, green, blue);
    }
    setPixel(i + EyeSize + 1, red / 10, green / 10, blue / 10);
    showStrip();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

void RightToLeftT4A(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for (int i = NUM_LEDS - EyeSize - 2; i > 0; i--) {
    setAll(0, 0, 0);
    setPixel(i, red / 10, green / 10, blue / 10);
    for (int j = 1; j <= EyeSize; j++) {
      setPixel(i + j, red, green, blue);
    }
    setPixel(i + EyeSize + 1, red / 10, green / 10, blue / 10);
    showStrip();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

void SparkleT4A(byte red, byte green, byte blue, int SpeedDelay) {
  int Pixel = random(NUM_LEDS);
  setPixel(Pixel, red, green, blue);
  showStrip();
  delay(SpeedDelay);
  setPixel(Pixel, 0, 0, 0);
}

void RunningLightsT4A(byte red, byte green, byte blue, int WaveDelay) {
  int Position = 0;

  for (int j = 0; j < NUM_LEDS * 2; j++)
  {
    Position++; // = 0; //Position + Rate;
    for (int i = 0; i < NUM_LEDS; i++) {
      // sine wave, 3 offset waves make a rainbow!
      //float level = sin(i+Position) * 127 + 128;
      //setPixel(i,level,0,0);
      //float level = sin(i+Position) * 127 + 128;
      setPixel(i, ((sin(i + Position) * 127 + 128) / 255)*red,
               ((sin(i + Position) * 127 + 128) / 255)*green,
               ((sin(i + Position) * 127 + 128) / 255)*blue);
    }

    showStrip();
    delay(WaveDelay);
  }
}

void colorWipeOnOffT4A() {
  colorWipeT4A(red, green, blue, speedDelay);
  colorWipeT4A(0x00, 0x00, 0x00, speedDelay);
}

void colorWipeT4A(byte red, byte green, byte blue, int SpeedDelay) {
  for (uint16_t i = 0; i < NUM_LEDS; i++) {
    setPixel(i, red, green, blue);
    showStrip();
    delay(SpeedDelay);
  }
}

void rainbowCycleT4A(int SpeedDelay) {
  byte *c;
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < NUM_LEDS; i++) {
      c = WheelT4A(((i * 256 / NUM_LEDS) + j) & 255);
      setPixel(i, *c, *(c + 1), *(c + 2));
    }
    showStrip();
    delay(SpeedDelay);
  }
}

byte * WheelT4A(byte WheelPos) {
  static byte c[3];

  if (WheelPos < 85) {
    c[0] = WheelPos * 3;
    c[1] = 255 - WheelPos * 3;
    c[2] = 0;
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    c[0] = 255 - WheelPos * 3;
    c[1] = 0;
    c[2] = WheelPos * 3;
  } else {
    WheelPos -= 170;
    c[0] = 0;
    c[1] = WheelPos * 3;
    c[2] = 255 - WheelPos * 3;
  }

  return c;
}

void theaterChaseT4A(byte red, byte green, byte blue, int SpeedDelay) {
  for (int j = 0; j < 10; j++) { //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < NUM_LEDS; i = i + 3) {
        setPixel(i + q, red, green, blue);  //turn every third pixel on
      }
      showStrip();

      delay(SpeedDelay);

      for (int i = 0; i < NUM_LEDS; i = i + 3) {
        setPixel(i + q, 0, 0, 0);    //turn every third pixel off
      }
    }
  }
}

void BouncingColoredBallsT4A(int BallCount, byte colors[][3]) {
  float Gravity = -9.81;
  int StartHeight = 1;
  int loopEnd = 0;

  float Height[BallCount];
  float ImpactVelocityStart = sqrt( -2 * Gravity * StartHeight );
  float ImpactVelocity[BallCount];
  float TimeSinceLastBounce[BallCount];
  int   Position[BallCount];
  long  ClockTimeSinceLastBounce[BallCount];
  float Dampening[BallCount];

  for (int i = 0 ; i < BallCount ; i++) {
    ClockTimeSinceLastBounce[i] = millis();
    Height[i] = StartHeight;
    Position[i] = 0;
    ImpactVelocity[i] = ImpactVelocityStart;
    TimeSinceLastBounce[i] = 0;
    Dampening[i] = 0.90 - float(i) / pow(BallCount, 2);
  }

  while (loopEnd < 3000) {
    for (int i = 0 ; i < BallCount ; i++) {
      TimeSinceLastBounce[i] =  millis() - ClockTimeSinceLastBounce[i];
      Height[i] = 0.5 * Gravity * pow( TimeSinceLastBounce[i] / 1000 , 2.0 ) + ImpactVelocity[i] * TimeSinceLastBounce[i] / 1000;

      if ( Height[i] < 0 ) {
        Height[i] = 0;
        ImpactVelocity[i] = Dampening[i] * ImpactVelocity[i];
        ClockTimeSinceLastBounce[i] = millis();

        if ( ImpactVelocity[i] < 0.01 ) {
          ImpactVelocity[i] = ImpactVelocityStart;
        }
      }
      Position[i] = round( Height[i] * (NUM_LEDS - 1) / StartHeight);
    }

    for (int i = 0 ; i < BallCount ; i++) {
      setPixel(Position[i], colors[i][0], colors[i][1], colors[i][2]);
    }

    showStrip();
    setAll(0, 0, 0);
    loopEnd++;
  }
}

void meteorRainT4A(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay) {
  setAll(0, 0, 0);

  for (int i = 0; i < NUM_LEDS + NUM_LEDS; i++) {


    // fade brightness all LEDs one step
    for (int j = 0; j < NUM_LEDS; j++) {
      if ( (!meteorRandomDecay) || (random(10) > 5) ) {
        fadeToBlackT4A(j, meteorTrailDecay );
      }
    }

    // draw meteor
    for (int j = 0; j < meteorSize; j++) {
      if ( ( i - j < NUM_LEDS) && (i - j >= 0) ) {
        setPixel(i - j, red, green, blue);

      }
    }

    showStrip();
    delay(SpeedDelay);
  }
}

void fadeToBlackT4A(int ledNo, byte fadeValue) {
#ifdef ADAFRUIT_NEOPIXEL_H
  // NeoPixel
  uint32_t oldColor;
  uint8_t r, g, b;
  int value;

  oldColor = strip.getPixelColor(ledNo);
  r = (oldColor & 0x00ff0000UL) >> 16;
  g = (oldColor & 0x0000ff00UL) >> 8;
  b = (oldColor & 0x000000ffUL);

  r = (r <= 10) ? 0 : (int) r - (r * fadeValue / 256);
  g = (g <= 10) ? 0 : (int) g - (g * fadeValue / 256);
  b = (b <= 10) ? 0 : (int) b - (b * fadeValue / 256);

  strip.setPixelColor(ledNo, r, g, b);
#endif
#ifndef ADAFRUIT_NEOPIXEL_H
  // FastLED
  leds[ledNo].fadeToBlackBy( fadeValue );
#endif
}

/*void pacManStart(){
  int i = 0;
  posTemp = rand() % NUM_LEDS;
  
  while(i < 6){
    
    posTemp = rand() % NUM_LEDS;    
    
    if(posTemp == pacPos[j]){
      posTemp = rand() % NUM_LEDS;  
    }else{
      i++;
    }
  } 
  */
