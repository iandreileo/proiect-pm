//SENZOR BARIERA
const unsigned int TRIG_PIN=9;
const unsigned int ECHO_PIN=8;

// BARIERA
#include <Servo.h>
Servo servo;

// LCD
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

// TEXT LCD
char text = "OCUPAT";

// BAREIRA
int angle = 0;
int inAction = 0;

// COD LED
int red_light_pin= 11;
int green_light_pin = 10;
int blue_light_pin = 9;

int red = 0;
int blue = 0;
int green = 0;

// COD SENZOR DISTANTA
#define echoPin 2 
#define trigPin 3 

long duration; 
int distance;


void setup() {
  // BARIERA
  servo.attach(13);
  servo.write(angle);
  
  // LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();

  // PIN MODE SENZOR BARIERA
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // SETUP PIN MODE LED
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);

  // SETUP PIN MODE DISTANTA
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 
  Serial.begin(9600);
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

  if(inAction == 0) {
     // Calculam distanta senzor pt bariera
    calcul_distanta_bariera(); 
  }

}

void calcul_distanta_bariera() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
 const unsigned long duration= pulseIn(ECHO_PIN, HIGH);
 int distance= duration/29/2;
 if(duration==0){
   Serial.println("Warning: no pulse from sensor");
   } else {
     Serial.println(distance);
    if(distance < 10 && inAction == 0) {
      inAction = 1;
      lcd.clear();
      lcd.print("Ai 10 secunde");
      lcd.setCursor(2, 1);
      lcd.print("sa intrii!");
      for(angle = 10; angle < 90; angle++)  {                                  
        servo.write(angle);               
        delay(15);                   
      }
      delay(10000); 
      // now scan back from 180 to 0 degrees
      for(angle = 90; angle > 10; angle--){                                
        servo.write(angle);           
        delay(15);       
      } 
      inAction = 0;
    }
  }
}

void actiune_parcare(int distance) {
    if (distance < 10) {
    red = 255;
    blue = 0;
    green = 0;
    if(inAction == 0) {
    lcd.clear();
    lcd.print("OCUPAT!"); 
    }
  } else {
    red = 0;
    blue = 0;
    green = 255;
    if(inAction == 0) {
    lcd.clear();
    lcd.print("LIBER!");
    }
  }
}

void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}

int calculate_distance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  return duration;
}
