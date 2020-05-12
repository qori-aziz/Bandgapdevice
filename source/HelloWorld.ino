
#include <LiquidCrystal_I2C.h>
#include <STM32F4ADC.h>

//STM32ADC myADC(ADC1);


// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 20, 4);
int s = 0;
int i = 0;
int LM35 = PA0;
float tempc, tempf, vout;
int reading;
int pinRelay = PD7;
unsigned long relaymillisb = 0;
unsigned long relaymillis;
int relstate=LOW;
long relayinterval=2000;
long reloff=2000;
long relon=2000;


void setup()
{
  Serial.begin(9600);
  pinMode(PD12, OUTPUT);
  // initialize the LCD
  lcd.init();
  pinMode(LM35, INPUT_ANALOG);
  pinMode(pinRelay, OUTPUT);

  // Turn on the blacklight and print a message.
  lcd.backlight();

}

void loop()
{
  digitalWrite(pinRelay, relstate);
  relaymillis = millis();
  

  if ((unsigned long)(relaymillis - relaymillisb) >= relayinterval) {
    // Change wait interval, based on current LED state
    if (relstate) {
      // LED is currently on, set time to stay off
      relayinterval = reloff;
      //Serial.println("on");
    } else {
      // LED is currently off, set time to stay on
      relayinterval = relon;
      //Serial.println("off");
    }
    // Toggle the LED's state, Fancy, eh!?
    relstate = !(relstate);

    // Save the current time to compare "later"
    relaymillisb = relaymillis;
  }
  delay(300);

  //unsigned long currentmillis=millis();
  lcd.clear();
  digitalWrite(PD12, HIGH);
  reading = 0;
  for (int i = 0; i < 20; i++) {
    reading += analogRead(LM35);
    delay(3);
  }
  float voltage = (float(reading) / 4096 * 3.3 * 100 / 20) - 2;


  lcd.setCursor(0, 0);
  lcd.print("TempC=");
  lcd.setCursor(8, 0);
  lcd.print(voltage, 1);
  lcd.setCursor(0, 3);
  lcd.print(reading);
  lcd.setCursor(0, 1);
  lcd.print("Volt= ");
  delay(1000);
  digitalWrite(PD12, LOW);
  delay(500);
}

//void readtemp(unsigned long currentmillis, int i){
//  int reading;
//  long prevmillis=0;
//  long interval=10;
//
//  if (currentmillis-prevmillis>interval){
//    i+=1;
//    reading+=analogRead(LM35);
//    prevmillis=currentmillis;
//  }
//
//  if (i=20){
//    i=0;
//    float voltage =(float(reading)/4096*3.3*100/20)-2;
//    reading=0;
//  }
//
//  for (i=0; i<20; i++){
//    reading+=analogRead(LM35);
//    delay(10);
//  }
//}


