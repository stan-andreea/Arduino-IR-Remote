#include <IRremote.h>
#include <Servo.h>

#define BLUE_LED_PIN1 4
#define GREEN_LED_PIN 5
#define YELLOW_LED_PIN1 2
#define ORANGE_LED_PIN1 3
#define BLUE_LED_PIN2 6
#define ORANGE_LED_PIN2 7
#define YELLOW_LED_PIN2 9
#define RED_LED_PIN 12


Servo myservo;
int servoPin = 8;
int val;
bool rotationL, rotationR;

bool orange1 = false;
bool blue1 = false;
bool yellow1 = false;


const int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;

byte greenLedState = LOW;
byte redLedState = LOW;
byte yellowLedState1 = LOW;
byte yellowLedState2 = LOW;
byte blueLedState1 = LOW;
byte blueLedState2 = LOW;
byte orangeLedState1 = LOW;
byte orangeLedState2 = LOW;

int relayPattern = 0;
bool chase = false;
bool chase2 = false;
bool pulse = false;
bool breathing = false;
bool on = false;


int newPos;
int oldPos = 90;
int inc;
int angle = 45;


int ledPins[] = {
  YELLOW_LED_PIN1, ORANGE_LED_PIN1, BLUE_LED_PIN1, GREEN_LED_PIN, BLUE_LED_PIN2, ORANGE_LED_PIN2, YELLOW_LED_PIN2
};
int numLeds = sizeof(ledPins) / sizeof(int);



void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN2, OUTPUT);
  pinMode(YELLOW_LED_PIN1, OUTPUT);
  pinMode(BLUE_LED_PIN1, OUTPUT);
  pinMode(ORANGE_LED_PIN1, OUTPUT);
  pinMode(YELLOW_LED_PIN2, OUTPUT);
  pinMode(ORANGE_LED_PIN2, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);



  myservo.attach(servoPin);
  pinMode(servoPin, OUTPUT);
  myservo.write(0);
}
//results.value
void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume();
    Serial.println("on is ");
    Serial.println(on);


    switch (results.value) {

      case 0xFFC23D:
        {

          on = (on == false) ? true : false;
          relayPattern = 0;
          pulse = false;
          chase = false;
          breathing = false;
          chase2 = false;
          digitalWrite(RED_LED_PIN, LOW);

          digitalWrite(GREEN_LED_PIN, LOW);
          digitalWrite(BLUE_LED_PIN1, LOW);
          digitalWrite(BLUE_LED_PIN2, LOW);
          digitalWrite(YELLOW_LED_PIN1, LOW);
          digitalWrite(ORANGE_LED_PIN1, LOW);
          digitalWrite(YELLOW_LED_PIN2, LOW);
          digitalWrite(ORANGE_LED_PIN2, LOW);
          myservo.write(0);

          digitalWrite(RED_LED_PIN, HIGH);
          delay(100);
          digitalWrite(RED_LED_PIN, LOW);
          delay(100);
          digitalWrite(RED_LED_PIN, HIGH);
          delay(100);
          digitalWrite(RED_LED_PIN, LOW);
          delay(100);
          if (on) {
            digitalWrite(RED_LED_PIN, HIGH);
          }
          else digitalWrite(RED_LED_PIN, LOW);

          break;
        }

        ////CH

      case 0xFF629D:
        {
          if(on){

          myservo.write(0);
          rotationR = false;
          rotationL = false;
          delay(1000);
          }
          break;
        }

        ///// CH+
      case 0xFFE21D:
        {

          if (on) {
            rotationR = !rotationR;
            rotationL = false;
          }
          break;
        }

        ////CH-
      case 0xFFA25D:
        {
          if(on){
          rotationL = !rotationL;
          rotationR = false;
          }
          break;
        }
        ////1
      case 0xFF30CF:
        {
          if(on){
          relayPattern = 0;
          pulse = false;
          chase = false;
          breathing = false;
          chase2 = false;
          yellowLedState1 = (yellowLedState1 == LOW) ? HIGH : LOW;
          digitalWrite(YELLOW_LED_PIN1, yellowLedState1);
          }

          break;
        }

      case 0xFF52AD:
        {
          if(on){
          relayPattern = 0;
          breathing = false;
          chase = false;
          chase2 = false;
          pulse = (pulse == false) ? true : false;
          }
          break;
        }

      case 0xFF906F:
        {
          if(on){
          relayPattern = 0;
          pulse = false;
          breathing = false;
          chase2 = false;
          chase = (chase == false) ? true : false;
          }
          break;
        }
      case 0xFF9867:
        {
          if(on){
          relayPattern = 0;
          pulse = false;
          chase = false;
          chase2 = false;
          breathing = (breathing == false) ? true : false;
          }
          break;
        }
      case 0xFFB04F:
        {
          if(on){
          relayPattern = 0;
          pulse = false;
          breathing = false;
          chase = false;
          chase2 = (chase2 == false) ? true : false;
          }
          break;
        }


      case 0xFF18E7:
        {
          if(on){
          relayPattern = 0;
          pulse = false;
          chase = false;
          breathing = false;
          chase2 = false;
          orangeLedState1 = (orangeLedState1 == LOW) ? HIGH : LOW;
          digitalWrite(ORANGE_LED_PIN1, orangeLedState1);
          }
          break;
        }
      case 0xFF7A85:
        {
          if(on){
          relayPattern = 0;
          pulse = false;
          chase = false;
          breathing = false;
          chase2 = false;
          blueLedState1 = (blueLedState1 == LOW) ? HIGH : LOW;
          digitalWrite(BLUE_LED_PIN1, blueLedState1);
          }
          break;
        }
      case 0xFF10EF:
        {
          if(on){
          relayPattern = 0;
          pulse = false;
          chase = false;
          breathing = false;
          chase2 = false;
          greenLedState = (greenLedState == LOW) ? HIGH : LOW;
          digitalWrite(GREEN_LED_PIN, greenLedState);
          }
          break;
        }

      case 0xFF38C7:
        {
          if(on){
          relayPattern = 0;
          pulse = false;
          chase = false;
          breathing = false;
          chase2 = false;
          blueLedState2 = (blueLedState2 == LOW) ? HIGH : LOW;
          digitalWrite(BLUE_LED_PIN2, blueLedState2);
          }
          break;
        }

      case 0xFF5AA5:
        {
          if(on){
          relayPattern = 0;
          pulse = false;
          chase = false;
          breathing = false;
          chase2 = false;
          orangeLedState2 = (orangeLedState2 == LOW) ? HIGH : LOW;
          digitalWrite(ORANGE_LED_PIN2, orangeLedState2);
          }
          break;
        }

      case 0xFF42BD:
        {
          if(on){
          relayPattern = 0;
          pulse = false;
          chase = false;
          breathing = false;
          chase2 = false;
          yellowLedState2 = (yellowLedState2 == LOW) ? HIGH : LOW;
          digitalWrite(YELLOW_LED_PIN2, yellowLedState2);
          }
          break;
        }

      case 0xFFE01F:
        {
          if(on){
          relayPattern = 0;
          pulse = false;
          chase = false;
          breathing = false;
          chase2 = false;
          Serial.println("idk");

          digitalWrite(GREEN_LED_PIN, LOW);
          digitalWrite(BLUE_LED_PIN1, LOW);
          digitalWrite(BLUE_LED_PIN2, LOW);
          digitalWrite(YELLOW_LED_PIN1, LOW);
          digitalWrite(ORANGE_LED_PIN1, LOW);
          digitalWrite(YELLOW_LED_PIN2, LOW);
          digitalWrite(ORANGE_LED_PIN2, LOW);
          }
          break;
        }
      case 0xFFA857:
        {
          if(on){
          relayPattern = 0;
          pulse = false;
          chase = false;
          breathing = false;
          chase2 = false;
          digitalWrite(GREEN_LED_PIN, HIGH);
          digitalWrite(BLUE_LED_PIN1, HIGH);
          digitalWrite(BLUE_LED_PIN2, HIGH);
          digitalWrite(YELLOW_LED_PIN1, HIGH);
          digitalWrite(ORANGE_LED_PIN1, HIGH);
          digitalWrite(YELLOW_LED_PIN2, HIGH);
          digitalWrite(ORANGE_LED_PIN2, HIGH);
          }
          break;
        }
      case 0xFF4AB5:
        {
          if(on){
          pulse = false;
          chase = false;
          breathing = false;
          chase2 = false;
          if (relayPattern == 0)
            relayPattern = 1;
          else relayPattern = 0;
          }

          Serial.println(relayPattern);
        }


      default:
        {
          // do nothing
        }
    }
  }

  if (pulse && on) {
    for (int brightness = 0; brightness < 255; brightness++) {
      analogWrite(GREEN_LED_PIN, brightness);
      delay(10);  // adjust the delay time to change the speed of the pulse
    }
    // Turn off the green LED with a fading effect
    for (int brightness = 255; brightness >= 0; brightness--) {
      analogWrite(GREEN_LED_PIN, brightness);
      delay(10);  // adjust the delay time to change the speed of the pulse
    }

    // Turn on the blue1 LED with a fading effect
    for (int brightness = 0; brightness < 255; brightness++) {
      analogWrite(BLUE_LED_PIN2, brightness);
      delay(10);  // adjust the delay time to change the speed of the pulse
    }
    // Turn off the blue1 LED with a fading effect
    for (int brightness = 255; brightness >= 0; brightness--) {
      analogWrite(BLUE_LED_PIN2, brightness);
      delay(10);
    }
  }

  if (chase && on) {
    for (int i = 0; i < numLeds; i++) {
      digitalWrite(ledPins[i], HIGH);
      delay(100);
      digitalWrite(ledPins[i], LOW);
    }
    for (int i = numLeds - 1; i >= 0; i--) {
      digitalWrite(ledPins[i], HIGH);
      delay(100);
      digitalWrite(ledPins[i], LOW);
    }
  }

  if (chase2 && on) {

    for (int i = 0; i < numLeds; i++) {
      digitalWrite(ledPins[i], HIGH);
      delay(100);
    }
    delay(100);
    for (int i = 0; i < numLeds; i++) {
      digitalWrite(ledPins[i], LOW);
      delay(100);
    }
    delay(100);
    for (int i = numLeds - 1; i >= 0; i--) {
      digitalWrite(ledPins[i], HIGH);
      delay(100);
    }
    delay(100);
    for (int i = numLeds - 1; i >= 0; i--) {
      digitalWrite(ledPins[i], LOW);
      delay(100);
    }
    delay(100);
  }

  if (relayPattern == 1 && on) {
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(BLUE_LED_PIN1, LOW);
    digitalWrite(BLUE_LED_PIN2, LOW);
    digitalWrite(YELLOW_LED_PIN1, LOW);
    digitalWrite(ORANGE_LED_PIN1, LOW);
    digitalWrite(YELLOW_LED_PIN2, LOW);
    digitalWrite(ORANGE_LED_PIN2, LOW);
    delay(100);

    digitalWrite(GREEN_LED_PIN, HIGH);
    delay(200);
    digitalWrite(BLUE_LED_PIN1, HIGH);
    digitalWrite(BLUE_LED_PIN2, HIGH);
    delay(200);
    digitalWrite(ORANGE_LED_PIN1, HIGH);
    digitalWrite(ORANGE_LED_PIN2, HIGH);
    delay(200);
    digitalWrite(YELLOW_LED_PIN1, HIGH);
    digitalWrite(YELLOW_LED_PIN2, HIGH);
    delay(200);
    digitalWrite(YELLOW_LED_PIN1, LOW);
    digitalWrite(YELLOW_LED_PIN2, LOW);
    delay(200);
    digitalWrite(ORANGE_LED_PIN1, LOW);
    digitalWrite(ORANGE_LED_PIN2, LOW);
    delay(200);
    digitalWrite(BLUE_LED_PIN1, LOW);
    digitalWrite(BLUE_LED_PIN2, LOW);
    delay(200);
    digitalWrite(GREEN_LED_PIN, LOW);
    delay(200);
  }

  if (blue1 && orange1 && yellow1 && on) {
    if (angle == 180)
      angle = 0;
    myservo.write(angle);
    angle += 45;
    delay(1000);
    blue1 = false;
    orange1 = false;
    yellow1 = false;
  }

  // check for activation of blue1, orange1, and yellow1 in the correct order
  if (digitalRead(BLUE_LED_PIN1) == HIGH && digitalRead(ORANGE_LED_PIN1) == LOW && digitalRead(YELLOW_LED_PIN1) == LOW && on) {
    blue1 = true;
  } else if (digitalRead(BLUE_LED_PIN1) == HIGH && digitalRead(ORANGE_LED_PIN1) == HIGH && digitalRead(YELLOW_LED_PIN1) == LOW && blue1 && on) {
    orange1 = true;
  } else if (digitalRead(BLUE_LED_PIN1) == HIGH && digitalRead(ORANGE_LED_PIN1) == HIGH && digitalRead(YELLOW_LED_PIN1) == HIGH && blue1 && orange1 && on) {
    yellow1 = true;
  }

  if (breathing && on) {
    int brightness = 0;
    int fadeAmount = 5;

    // gradually increase the brightness
    while (brightness < 255) {
      analogWrite(BLUE_LED_PIN2, brightness);
      brightness += fadeAmount;
      delay(20);
    }

    // gradually decrease the brightness
    while (brightness > 0) {
      analogWrite(BLUE_LED_PIN2, brightness);
      brightness -= fadeAmount;
      delay(20);
    }
  }

  if (rotationR && (val != 175) && on) {
    val++;  //for colockwise button
    myservo.write(val);
  }
  if (rotationL && (val != 0) && on) {
    val--;  //for counter colockwise button
    myservo.write(val);
  }

  delay(20);  //General speed
}