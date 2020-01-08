#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif


//#define SERIAL_RX_BUFFER_SIZE 16


#include <DMXSerial.h>

const int DMXA = 20;
const int DMXB = 21;
String inputString = "";         // a String to hold incoming data
boolean stringComplete = false;  // whether the string is complete
byte inByte[3];
byte rxindex = 0;
int REDVALUE = 0;
int GREENVALUE = 0;
int BLUEVALUE = 0;
int Channel = 0;
int Value = 0;
int FXmode = 0;

byte oldChannel = 0;
byte oldValue = 0;
byte fadespeed = 10;
byte strobespeed = 10;
byte tronspeed = 15;
byte scrollspeed = 50;
byte ripplespeed = 50;


// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

//from wearers perspective
Adafruit_NeoPixel strip = Adafruit_NeoPixel(100, 6, NEO_GRB + NEO_KHZ800);  //ARM  right D6 is right ARM
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(55, 7, NEO_GRB + NEO_KHZ800);  //front both
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(55, 3, NEO_GRB + NEO_KHZ800); //ARM  right D6 is right ARM

Adafruit_NeoPixel strip4 = Adafruit_NeoPixel(55, 8, NEO_GRB + NEO_KHZ800);  //LAPEL
//Adafruit_NeoPixel strip4 = Adafruit_NeoPixel(55, 3, NEO_GRB + NEO_KHZ800);  //epaulettes


Adafruit_NeoPixel strip5 = Adafruit_NeoPixel(55, 4, NEO_GRB + NEO_KHZ800);  //LEFT ARM





// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  DMXSerial.init(DMXReceiver);
  Serial.begin(115200);
  // set some default values
  // DMXSerial.write(1, 11);
  // DMXSerial.write(2, 0);


  // initialize serial:
  // DMXSerial.init(DMXReceiver);
  //
  // reserve 200 bytes for the inputString:
  inputString.reserve(255);


  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  // strip2.begin();

  /*strip2.show(); // Initialize all pixels to 'off'

    strip3.begin();
    strip3.show(); // Initialize all pixels to 'off'
    strip4.begin();
    strip4.show(); // Initialize all pixels to 'off'

    strip5.begin();
    strip5.show(); // Initialize all pixels to 'off'

    // .begin();
    //strip6.show(); // Initialize all pixels to 'off'


  */

  //alloff();  // turn off all elements
  Serial.println("starting");

}

void loop() {


  unsigned long lastPacket = DMXSerial.noDataSince();
  if (lastPacket < 5000) {
    // read recent DMX values and set pwm levels
    Channel = DMXSerial.read(DMXA);
    Value = DMXSerial.read(DMXB);
    delay(10);
  }








  if ((Channel != oldChannel) || (Value != oldValue)) {
    //  Serial.print("Ch 1: "); Serial.print(Channel); Serial.print(" Ch 2: "); Serial.println(Value);

    //Serial.println("in loop");

    /*
      if (stringComplete) {
        // clear the string:
        //effect1(Channel, Value);

       Serial.print("BYTE 1: ");Serial.print(inByte[0]);
      Serial.print("    BYTE 2: "); Serial.println(inByte[1]);
        inputString = "";
        stringComplete = false;


      }

    */

    if (Channel != 0) {


      if ((Channel > 0) && (Channel < 11)) {
        effect1(Channel, Value);
        Serial.println("effect1");

      }



      if ((Channel > 10) && (Channel < 21)) {
        turnoff();
        Serial.println("turn off elements");
      }

      if ((Channel > 20) && (Channel < 31)) {
        //effect5();

        scroll(Channel, Value);

        Serial.println("scroll");
      }



      if ((Channel > 30) && (Channel < 41)) {
        strobe(10, 10);
        Serial.println("strobbing");
      }



      if ((Channel > 40) && (Channel < 51)) {
        //theaterChase(strip.Color(127, 127, 127), 50); // White
        ripple(Channel, Value);

        Serial.println("Ripple");
      }





      if ((Channel > 50) && (Channel < 61)) {
        fadein(Channel, Value);
        Serial.println("fadding in ");
      }

      if ((Channel > 60) && (Channel < 71)) {
        fadeout(Channel, Value);


        Serial.println("fadding out ");
      }




      if ((Channel > 70) && (Channel < 81)) {
        //tron
        effect7(Channel, Value);
        /// tron(10);
        Serial.println("tron Up ");

      }


      if ((Channel > 80) && (Channel < 91)) {
        //tron
        effect8(Channel, Value);
        Serial.println("tron down ");

        /// tron(10);
      }


      if ((Channel > 90) && (Channel < 101)) {
        //tron
        Serial.println("rainbow ");

        if ((Channel > 90) && (Channel < 98)) {
          rainbow(30);
        }
        else {
          rainbow(Value);
          Serial.print("rainbow spd: ");                Serial.println(Value);



        }

        /// tron(10);
      }



      if ((Channel > 100) && (Channel < 111)) {
        effect4(Channel, Value);
      }

      if ((Channel > 110) && (Channel < 121)) {
        colorWipe(Value, 100);
      }




      if ((Channel > 120) && (Channel < 131)) {
        Indy_Pixel(Channel, Value);


      }




      if (Channel == 255) {
        Serial.println("global off ");

        for (uint16_t i = 0; i < 60; i++) {
          //global all  off
          strip.setPixelColor(i, 0, 0, 0);   //turn every third pixel off


        }
        strip.show();

      }



      /*
        if ((Channel > 70) && (Channel < 81)) {
          effect7(Channel, Value);
        }
      */
      oldChannel = Channel;
      oldValue = Value;

    }

  }
  else {
    //Serial.println(" SAME ");
  }



}


void Indy_Pixel(uint32_t Ch, uint8_t Val) {

if (Ch == 121){
    strip.setPixelColor(Val, strip.Color(REDVALUE, GREENVALUE, BLUEVALUE));
    strip.show();
 }
 
if (Ch == 122){
    REDVALUE=Val;
 }

 if (Ch == 123){
    GREENVALUE=Val;
 }

 if (Ch == 124){
    BLUEVALUE=Val;
 }


 if (Ch==128){
    globalcolour(Val);

  
  }

 
 
}


// Fill the dots one after the other with a color
void colorWipe(uint32_t val, uint8_t wait) {
  globalcolour(val);

  for (uint16_t i = 80; i > 0; i--) {
    strip.setPixelColor(i, strip.Color(REDVALUE, GREENVALUE, BLUEVALUE));
    strip.show();
    delay(scrollspeed);


  }





}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));


    }
    strip.show();

    delay(wait);
  }
  fadeout(61, 70);

}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j = 0; j < 10; j++) { //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, REDVALUE, GREENVALUE, BLUEVALUE); //turn every third pixel on
        strip2.setPixelColor(i + q, REDVALUE, GREENVALUE, BLUEVALUE); //turn every third pixel on
        strip3.setPixelColor(i + q, REDVALUE, GREENVALUE, BLUEVALUE); //turn every third pixel on
        strip4.setPixelColor(i + q, REDVALUE, GREENVALUE, BLUEVALUE); //turn every third pixel on
        strip5.setPixelColor(i + q, REDVALUE, GREENVALUE, BLUEVALUE); //turn every third pixel on
        //  strip6.setPixelColor(i + q, REDVALUE, GREENVALUE, BLUEVALUE); //turn every third pixel on

      }
      strip.show();
      strip2.show();
      strip3.show();
      strip4.show();
      strip5.show();
      //  strip6.show();

      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0, 0, 0);    //turn every third pixel off
        strip2.setPixelColor(i + q, 0, 0, 0);    //turn every third pixel off
        strip3.setPixelColor(i + q, 0, 0, 0);    //turn every third pixel off
        strip4.setPixelColor(i + q, 0, 0, 0);    //turn every third pixel off
        strip5.setPixelColor(i + q, 0, 0, 0);    //turn every third pixel off
        // strip6.setPixelColor(i + q, 0, 0, 0);    //turn every third pixel off



      }
    }
  }
}





void ripple(byte ch, byte val ) {
  globalcolour(val);

  //rIPPLE both front on
  for (int j = 0; j < 10; j++) { //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, REDVALUE, GREENVALUE, BLUEVALUE); //turn every third pixel on


      }
      strip.show();


      delay(ripplespeed);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0, 0, 0);    //turn every third pixel off




      }
    }
  }
}









//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {


  for (int j = 0; j < 256; j++) {   // cycle all 256 colors in the wheel
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < 100; i = i + 3) {
        strip.setPixelColor(i + q, Wheel( (i + j) % 255)); //turn every third pixel on

      }
      strip.show();
      delay(wait);
      for (uint16_t i = 0; i < 100; i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
        strip.show();


      }

    }
  }









}








// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}






void fadein(byte ch, byte val ) {
  globalcolour(val);
  int kk = 0;
  int r = 0;
  int g = 0;
  int b = 0;

  if ((ch > 50) && (ch < 58)) {
    while (kk < 255) { //Front Fade in
      if (REDVALUE > kk) {
        r++;
      } if (GREENVALUE > kk) {
        g++;
      } if (BLUEVALUE > kk) {
        b++;
      }
      for (uint16_t i = 0; i < 80; i++) {
        strip.setPixelColor(i, r, g, b);   //turn every third pixel off
      }
      strip.show();

      delay(fadespeed);
      kk++;
    }
    //Serial.print("rgb:  ");       Serial.print(r); Serial.print(" "); Serial.print(g); Serial.print(" "); Serial.println(b);

  }

  if (ch == 58) { // sets the fade on speed
    Serial.print("fade on spd: ");

    if (val < 5) {
      val = 5;
    }
    if (val > 5) {
      fadespeed = val;

    }
    fadespeed = val;

    Serial.println(fadespeed);
  }


}






void fadeout(byte ch, byte val ) {
  globalcolour(val);
  int kk = 255;
  int r = REDVALUE;
  int g = GREENVALUE;
  int b = BLUEVALUE;

  if ((ch > 60) && (ch < 68)) {
    for (uint16_t i = 0; i < 80; i++) {
      strip.setPixelColor(i, r, g, b);   //turn every third pixel off
    }
    strip.show();


    while (kk > 0) { //Front Fade in
      if (REDVALUE > kk) {
        r--;
      } if (GREENVALUE > kk) {
        g--;
      } if (BLUEVALUE > kk) {
        b--;
      }
      for (uint16_t i = 0; i < 80; i++) {
        strip.setPixelColor(i, r, g, b);   //turn every third pixel off
      }
      strip.show();

      delay(fadespeed);
      kk--;
    }
    for (uint16_t i = 0; i < 80; i++) {
      strip.setPixelColor(i, 0, 0, 0);   //turn every third pixel off
    }
    strip.show();

    //Serial.print("rgb:  ");       Serial.print(r); Serial.print(" "); Serial.print(g); Serial.print(" "); Serial.println(b);


  }

  if (ch == 68) { // sets the fade on speed
    Serial.print("fade off spd: ");

    if (val < 5) {
      val = 5;
    }



    fadespeed = val;

    Serial.println(fadespeed);

  }
}





void strobe(int fadespeed, int t) {


  if (Channel == 38) {


    if (Value < 5) {
      strobespeed = 5;
    }
    else {
      strobespeed = Value;
    }


  }
  else {
    globalcolour(Value);
  }
  Serial.print("strobe spd: ");
  Serial.println(strobespeed);


  //Serial.println("strobe function");


  if ((Channel > 30) || (Channel < 37)) { // strobing front
    while (t > 0) {
      for (uint16_t i = 0; i < 80; i++) {
        strip.setPixelColor(i, REDVALUE, GREENVALUE, BLUEVALUE);   //turn everypixel off
      }
      strip.show();


      delay(strobespeed);

      for (uint16_t i = 0; i < 80; i++) {
        strip.setPixelColor(i, 0, 0, 0);   //turn every  pixel off
      }

      strip.show();

      delay(strobespeed);
      t--;
    }
  }






}



















/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
/*
  void serialEvent() {

  while (Serial.available()) {
    // get the new byte:
    Channel = Serial.parseInt();  // add it to the inputString:
    Serial.print(Channel);
    Value = Serial.parseInt();
    Serial.print(Value);


    if (Serial.read() == '\n') {
      // if the incoming character is a newline, set a flag so the main loop can
      // do something about it:

      stringComplete = true;
    }


  }

  while (Serial1.available()) {
    // get the new byte:
    Channel = Serial1.parseInt();  // add it to the inputString:
    Serial.print(Channel);
    Value = Serial1.parseInt();
    Serial.print(Value);


    if (Serial1.read() == '\n') {
      // if the incoming character is a newline, set a flag so the main loop can
      // do something about it:

      stringComplete = true;
    }


  }






  }
*/



void globalcolour(byte Colour_val) {

  if (0 <= Colour_val && Colour_val <= 5) { // all colours off
    REDVALUE = 0;
    GREENVALUE = 0;
    BLUEVALUE = 0;
  }

  if (5 < Colour_val && Colour_val <= 16) { //purple
    REDVALUE = 150; //was 128
    GREENVALUE = 0; //was 0
    BLUEVALUE = 150; //was 255
  }

  if (17 <= Colour_val && Colour_val <= 32) { //deep blue
    REDVALUE = 0;
    GREENVALUE = 10;
    BLUEVALUE = 255;
  }

  if (33 <= Colour_val && Colour_val <= 64) { //cyan
    REDVALUE = 0;
    GREENVALUE = 200;
    BLUEVALUE = 200;
  }

  if (65 <= Colour_val && Colour_val <= 87) { //red
    REDVALUE = 200;
    GREENVALUE = 0;
    BLUEVALUE = 0;
  }

  if (88 <= Colour_val && Colour_val <= 119) { //green
    REDVALUE = 0;
    GREENVALUE = 200;
    BLUEVALUE = 0;
  }

  if (120 <= Colour_val && Colour_val <= 151) { //orange
    REDVALUE = 230;
    GREENVALUE = 50;
    BLUEVALUE = 0;
  }

  if (152 <= Colour_val && Colour_val <= 183) { //pink
    REDVALUE = 255;
    GREENVALUE = 40;
    BLUEVALUE = 128;
  }

  if (184 <= Colour_val && Colour_val <= 200) { //yellow
    REDVALUE = 255;
    GREENVALUE = 128;
    BLUEVALUE = 0;
  }

  if (201 <= Colour_val && Colour_val <= 216) { //WHITE
    REDVALUE = 255;
    GREENVALUE = 153;
    BLUEVALUE = 128;
  }

  if (201 <= Colour_val && Colour_val <= 216) { //WHITE
    // REDVALUE = 255;
    //    GREENVALUE = 153;
    //  BLUEVALUE = 128;

    REDVALUE = 100;
    GREENVALUE = 60;
    BLUEVALUE = 40;

  }


















  ////////Serial.print("REDVALUE :"); ////////Serial.println(REDVALUE);
  ////////Serial.print("GREENVALUE :"); ////////Serial.println(GREENVALUE);
  ////////Serial.print("BLUEVALUE :"); ////////Serial.println(BLUEVALUE);




}




void effect4(byte ch, byte val ) {
  //threater fx

  globalcolour(val);

  theaterChaseRainbow(10);

}







void effect7(byte ch, byte val ) {
  //tron bottom to top

  globalcolour(val);


  if ((ch > 70) && (ch < 78)) { //  Serial.println("tron 71 ");
    for (uint16_t i = 0; i < 80; i++) {
      strip.setPixelColor(i, REDVALUE, GREENVALUE, BLUEVALUE);   //turn everypixel off
      strip.setPixelColor(i + 1, REDVALUE, GREENVALUE, BLUEVALUE); //turn everypixel off
      strip.setPixelColor(i + 2, REDVALUE, GREENVALUE, BLUEVALUE); //turn everypixel off
      strip.setPixelColor(i - 1, 0, 0, 0); //turn everypixel off
      //strip6.setPixelColor(i - 1, 0, 0, 0); //turn everypixel off
      strip.show();
      delay(tronspeed);
    }
    delay(tronspeed);
    alloff();
  }

  if (ch == 78) { // sets the scroll speed
    Serial.print("tron spd: ");

    Serial.println(val);

    tronspeed = val;
  }


}




void effect8(byte ch, byte val ) {
  //tron bottom to top

  globalcolour(val);

  if ((ch > 80) && (ch < 88)) { //  Serial.println("tron 81 ");

    for (uint16_t i = 80; i > 0; i--) {
      strip.setPixelColor(i, REDVALUE, GREENVALUE, BLUEVALUE);   //turn everypixel off
      strip.setPixelColor(i - 1, REDVALUE, GREENVALUE, BLUEVALUE); //turn everypixel off
      strip.setPixelColor(i - 2, REDVALUE, GREENVALUE, BLUEVALUE); //turn everypixel off
      strip.setPixelColor(i , 0, 0, 0); //turn everypixel off
      strip.show();// strip6.show();//strip4.show();
      delay(tronspeed);
    }
    delay(tronspeed);
    alloff();
  }



  if (ch == 88) { // sets the scroll speed
    Serial.print("tron spd: ");

    Serial.println(val);

    tronspeed = val;
  }



}









void effect1(byte ch, byte val ) {
  globalcolour(val);

  //FADEON both front on
  for (uint16_t i = 0; i < 80; i++) {

    strip.setPixelColor(i, REDVALUE, GREENVALUE, BLUEVALUE);   //turn everypixel off
  }
  strip.show();


}





void scroll(byte ch, byte val ) {
  globalcolour(val);

  //scroll both front on

  // colorWipe(strip.Color(REDVALUE, GREENVALUE, BLUEVALUE), scrollspeed); // Red

  for (uint16_t i = 0; i < 80; i++) {
    strip.setPixelColor(i, strip.Color(REDVALUE, GREENVALUE, BLUEVALUE));
    strip.show();
    delay(scrollspeed);
  }



}






void effect5( void) {
  //fadeon effect 5

  Serial.println(" effect5");
  //alloff();

  byte fadespeed = Value;
  byte kk = 0;


  switch (Channel) {
    case 21:    // your hand is on the sensor
      //FADEON bOTH fRONT
      while (kk < 200) {
        for (uint16_t i = 0; i < 40; i++) {
          strip3.setPixelColor(i, 0, kk, kk);   //turn every third pixel off
        }
        strip3.show();
        delay(fadespeed);
        kk++;
      }
      break;

    case 22:    // your hand is close to the sensor
      //FADEON   both front
      while (kk < 200) {
        for (uint16_t i = 0; i < 40; i++) {
          strip3.setPixelColor(i, 0, kk, kk);   //turn every third pixel off
        }
        strip3.show();
        delay(fadespeed);
        kk++;
      }
      break;

    case 23:    // your hand is a few inches from the sensor
      //FADEON LEFT ARM
      while (kk < 200) {
        for (uint16_t i = 0; i < 40; i++) {
          strip5.setPixelColor(i, 0, kk, kk);   //turn every third pixel off
        }
        strip5.show();
        delay(fadespeed);
        kk++;
      }
      break;

    case 24:    // your hand is nowhere near the sensor
      //FADEON LEFT ARM
      while (kk < 200) {
        for (uint16_t i = 0; i < 40; i++) {
          strip.setPixelColor(i, 0, kk, kk);   //turn every third pixel off
        }
        strip.show();
        delay(fadespeed);
        kk++;
      }
      break;


    case 25:    // your hand is nowhere near the sensor
      //FADEON back
      while (kk < 200) {
        for (uint16_t i = 0; i < 60; i++) {
          strip2.setPixelColor(i, 0, kk, kk);   //turn every third pixel off
        }
        strip2.show();
        delay(fadespeed);
        kk++;
      }
      break;

    case 26:    // your hand is nowhere near the sensor
      //FADEON Lapel
      while (kk < 200) {
        for (uint16_t i = 0; i < 40; i++) {
          strip4.setPixelColor(i, 0, kk, kk);   //turn every third pixel off
        }
        strip4.show();
        delay(fadespeed);
        kk++;
      }
      break;

    case 27:    // your hand is nowhere near the sensor

      //FADEON epulate
      while (kk < 200) {
        for (uint16_t i = 0; i < 40; i++) {
          strip4.setPixelColor(i, 0, kk, kk);   //turn every third pixel off
        }
        strip4.show();
        delay(fadespeed);
        kk++;
      }
      break;

    case 28:    // your hand is nowhere near the sensor
      fadein(50, Value);
      break;

    case 29:    // your hand is nowhere near the sensor
      alloff();

      break;

    case 30:    // your hand is nowhere near the sensor
      //fadein(50, 50);
      //FADEON all
      while (kk < 20) {  //KK IS HOW MANY TIMES IT DOES IT
        for (uint16_t i = 0; i < 60; i++) {
          strip.setPixelColor(i, 0, kk, kk);   //turn every third pixel off
          strip2.setPixelColor(i, 0, kk, kk);   //turn every third pixel off
          strip3.setPixelColor(i, 0, kk, kk);   //turn every third pixel off
          strip4.setPixelColor(i, 0, kk, kk);   //turn every third pixel off
          strip5.setPixelColor(i, 0, kk, kk);   //turn every third pixel off

        }
        strip4.show();        strip.show();        strip3.show();        strip2.show();        strip5.show();




        delay(fadespeed);
        kk++;
      }

      break;

  }

  Serial.println(" end effect5");



  // end effect 5
}




void alloff(void) {
  for (uint16_t i = 0; i < 80; i++) {
    strip.setPixelColor(i, 0, 0, 0);   //turn everypixel off
    strip2.setPixelColor(i, 0, 0, 0);   //turn everypixel off
    strip3.setPixelColor(i, 0, 0, 0);   //turn everypixel off
    strip4.setPixelColor(i, 0, 0, 0);   //turn everypixel off
    strip5.setPixelColor(i, 0, 0, 0);   //turn everypixel off
    //strip6.setPixelColor(i, 0, 0, 0);   //turn everypixel off
  }
  strip.show();
  strip2.show();
  strip3.show();
  strip4.show();
  strip5.show();
  //strip6.show();
}

void allon(void) {

  for (uint16_t i = 0; i < 40; i++) {
    strip.setPixelColor(i, 100, 100, 100);   //turn everypixel off
    strip2.setPixelColor(i, 100, 100, 100);   //turn everypixel off
    strip3.setPixelColor(i, 100, 100, 100);   //turn everypixel off
    strip4.setPixelColor(i, 100, 100, 100);   //turn everypixel off
    strip5.setPixelColor(i, 100, 100, 100);   //turn everypixel off
    // strip6.setPixelColor(i, 100, 100, 100);   //turn everypixel off

  }
  strip.show();  strip2.show();  strip3.show();  strip4.show();  strip5.show();  //strip6.show();
  //  strip5.show();
}

void tron(int cycle) {
  for (uint16_t i = 0; i < 40; i++) {
    if (i < 18) {
      strip2.setPixelColor(i, REDVALUE, GREENVALUE, BLUEVALUE);   //turn everypixel off
      strip2.setPixelColor(i + 1, REDVALUE, GREENVALUE,  BLUEVALUE); //turn everypixel off
      strip2.setPixelColor(i + 2, REDVALUE, GREENVALUE,  BLUEVALUE); //turn everypixel off
      strip2.setPixelColor(i + 20, REDVALUE, GREENVALUE, BLUEVALUE); //turn everypixel off
      strip2.setPixelColor(i + 20 + 1, REDVALUE, GREENVALUE,  BLUEVALUE); //turn everypixel off
      strip2.setPixelColor(i + 20 + 2, REDVALUE, GREENVALUE,  BLUEVALUE); //turn everypixel off

    }

    strip.setPixelColor(40 - i, REDVALUE, REDVALUE,  BLUEVALUE); //turn everypixel off
    strip.setPixelColor(40 - i - 1, REDVALUE, GREENVALUE,  BLUEVALUE); //turn everypixel off
    strip.setPixelColor(40 - i - 2, REDVALUE, GREENVALUE,  BLUEVALUE); //turn everypixel off




    strip5.setPixelColor(40 - i, REDVALUE, GREENVALUE,  BLUEVALUE); //turn everypixel off
    strip5.setPixelColor(40 - i - 1, REDVALUE, GREENVALUE,  BLUEVALUE); //turn everypixel off
    strip5.setPixelColor(40 - i - 2, REDVALUE, GREENVALUE,  BLUEVALUE); //turn everypixel off

    strip3.setPixelColor(i, REDVALUE, GREENVALUE, BLUEVALUE);   //turn everypixel off
    strip3.setPixelColor(i + 1, REDVALUE, GREENVALUE, BLUEVALUE); //turn everypixel off
    strip3.setPixelColor(i + 2, REDVALUE, GREENVALUE, BLUEVALUE); //turn everypixel off

    strip5.show(); strip.show(); strip2.show(); strip3.show();  //strip6.show();//strip4.show();
    delay(cycle);


    strip5.setPixelColor(40 - i, 0, 0, 0); //turn everypixel off

    strip.setPixelColor(40 - i, 0, 0, 0); //turn everypixel off
    //strip6.setPixelColor(40 - i, 0, 0, 0); //turn everypixel off

    if (i < 22) {
      strip2.setPixelColor(i - 1, 0, 0, 0); //turn everypixel off
      strip2.setPixelColor(i + 20 - 1, 0, 0, 0); //turn everypixel off

    }
    /*
        if(i>19 && i<20 ){

             for (int z=0; z <= 40; z++){

            strip2.setPixelColor(i, 0, 0, 0); //turn everypixel off
        }
        }
    */

    strip3.setPixelColor(i - 1, 0, 0, 0); //turn everypixel off
    //strip6.setPixelColor(i - 1, 0, 0, 0); //turn everypixel off
    strip.show(); strip2.show(); strip3.show();// strip6.show();//strip4.show();
    delay(cycle);

  }

  for (uint16_t i = 0; i < 20; i++) {
    strip4.setPixelColor(i, REDVALUE, GREENVALUE, BLUEVALUE);   //turn everypixel off
    strip4.setPixelColor(i + 1, REDVALUE, GREENVALUE, BLUEVALUE); //turn everypixel off
    strip4.setPixelColor(i + 2, REDVALUE, GREENVALUE, BLUEVALUE); //turn everypixel off
    strip4.setPixelColor(42 - i, REDVALUE, GREENVALUE, BLUEVALUE); //turn everypixel off
    strip4.setPixelColor(42 - i - 1, REDVALUE, GREENVALUE, BLUEVALUE); //turn everypixel off
    strip4.setPixelColor(42 - i - 2, REDVALUE, GREENVALUE, BLUEVALUE); //turn everypixel off


    strip2.setPixelColor(i + 42, REDVALUE, GREENVALUE, BLUEVALUE); //turn everypixel off
    strip2.setPixelColor(i + 42 - 1, REDVALUE, GREENVALUE, BLUEVALUE); //turn everypixel off
    strip2.setPixelColor(i + 42 - 2, REDVALUE, GREENVALUE, BLUEVALUE); //turn everypixel off

    strip4.show(); strip2.show();
    delay(cycle);



    strip4.setPixelColor(i - 1, 0, 0, 0); //turn everypixel off
    strip4.setPixelColor(42 - i + 1, 0, 0, 0); //turn everypixel off
    strip2.setPixelColor(i + 39 - 1, 0, 0, 0); //turn everypixel off
    delay(cycle);



    strip4.show(); strip2.show();
  }




  delay(cycle);
  alloff();
}






void turnoff(void) {




  for (uint16_t i = 0; i < 80; i++) {
    strip.setPixelColor(i, 0, 0, 0);   //turn every  pixel off
  }

  strip.show();



}
