//constants
const int myLed=7;
 
 
 
//includes
#include <SD.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
 
#define I2C_ADDR    0x3F // <<----- Add your address here.  Find it from I2C Scanner
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7
 
//variables
int n = 1;
int p = digitalRead(8);
//int buttonInput = *;
 
//RESERVED 
//***************
File myFile;
LiquidCrystal_I2C  lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);
 
void setup()
{
 
 lcd.begin (16,2); 
 lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
lcd.setBacklight(HIGH);
lcd.home ();
pinMode(myLed, OUTPUT);
 Serial.begin(9600); 
 while (!Serial) {
  Serial.print("Initializing SD card...");
  lcd.setCursor (0,1);
  lcd.print("Initializing") 
  lcd.setCursor(1,1);
  lcd.println("SD card...");
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    lcd.setCursor(0,1);
    lcd.println("Initialization:");
    lcd.setCursor(1,1);
    lcd.println("failed!!!!");
    return;
  }
 Serial.println("initialization done.");
 lcd.home():
 lcd clear();
 lcd.println("Initialization");
 lcd.setCursor("completed.....");
 
 myFile = SD.open("test.txt", FILE_WRITE);
 
  if (myFile) {
    Serial.print("Writing to test.txt...");
    lcd.home();
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Writing to SD");
    myFile.println("testing 1, 2, 3.");
    // close the file:
    myFile.close();
    Serial.println("done.");
    lcd.home();
    lcd.setCursor(0,1);
    lcd.clear();
    lcd.print("Done!!");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
    lcd.home();
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Error openeing file.");
    lcd.setCursor(1,1);
    lcd.clear();
    lcd.print("USER ERROR!!!");  
  }
 
  // re-open the file for reading:
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");
    lcd.home();
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("test.txt:");
    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
      lcd.home();
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
    lcd.home();
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Error openeing file.");
    lcd.setCursor(1,1);
    lcd.clear();
    lcd.print("USER ERROR!!!");  
  }
 }
void loop()
{   
//  Start the LEds
digitalWrite(myLed, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(50);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(50);  
 
    lcd.setCursor (0,1);
    lcd.println("The area of the sphere is " area);
    delay(3000);
    lcd.setBacklight(LOW);      // Backlight off
    delay(3000);
    lcd.setCursor (1,1);
    lcd.setBacklight(HIGH);     // Backlight on
    lcd.println("The area of the sphere is " area);
    delay(3000);
    return 0;
}
