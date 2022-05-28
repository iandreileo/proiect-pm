
// LCD
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// TEXT LCD
char text = "OCUPAT";

// COD LED
int red_light_pin= 11;
int green_light_pin = 10;
int blue_light_pin = 9;

int red = 0;
int blue = 0;
int green = 0;

// COD SENZOR DISTANTA
#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement


void setup() {
  // LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();

  // SETUP PIN MODE LED
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);

  // SETUP PIN MODE DISTANTA
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
}

void loop() {

  // RANDAM TEXT
  lcd.setCursor(2, 0);
  
  // RANDAM CULOAREA LEDULUI
  RGB_color(red, green, blue); // Red
  delay(1000);

  // Calculam distanta pana la obiectul de peste senzor
  distance = calculate_distance() * 0.034 / 2;

  // Actiune parcare
  actiune_parcare(distance);

}

void actiune_parcare(int distance) {
    if (distance < 10) {
    red = 255;
    blue = 0;
    green = 0;
    lcd.clear();
    lcd.print("OCUPAT!"); // Print the string "Hello World!"
  } else {
    red = 0;
    blue = 0;
    green = 255;
    lcd.clear();
    lcd.print("LIBER!"); // Print the string "Hello World!"
  }
}

void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}

int calculate_distance() {
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance

  return duration;
}
