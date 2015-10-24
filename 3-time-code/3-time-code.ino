#define CLOCKDIR_PIN 5
#define CLOCKSTEP_PIN 6
#define SITTING_PIN 4
#define PLUS_PIN 3
#define MINUS_PIN 2
#define LED_PIN 13

int CLOCKDIR = LOW;
int CLOCKTIMESAT = 0;
float CLOCKSPEED = 0.001;
int SITTING = LOW;
int PLUS = LOW;
int MINUS = LOW;


unsigned long TIMER;
boolean GOINGBACK = false;
boolean BUTTONRELEASED = true;

//speed is any number from .01 -> 1 with 1 being fastest - Slower is stronger,
//the clock stepper works from 0.00000001 to 0,4 with external power, 0,00000001-0,25 with battery


void setup() {
//  Serial.begin(9600);


  pinMode(CLOCKDIR_PIN, OUTPUT);
  pinMode(CLOCKSTEP_PIN, OUTPUT);
  pinMode(SITTING_PIN, INPUT);

}

void loop() {

  SITTING = digitalRead(SITTING_PIN);
  PLUS = digitalRead(PLUS_PIN);
  MINUS = digitalRead(MINUS_PIN);


  if (SITTING == HIGH) {

    if (CLOCKSPEED <= 0.5) {
      CLOCKSPEED = (CLOCKSPEED + 0.001);
    }
//    Serial.println(CLOCKSPEED);
    rotate(22, CLOCKSPEED, HIGH, CLOCKDIR_PIN, CLOCKSTEP_PIN);
    CLOCKTIMESAT++;
    GOINGBACK = true;

  }  else if (GOINGBACK) {
    delay (20);
    if (CLOCKSPEED > 0.4) {
      CLOCKSPEED = 0,3;
    }
    //
    //      for (int i = 0; i<CLOCKTIMESAT;i++){
    //          if (CLOCKSPEED > 0.3) {
    //            CLOCKSPEED = 0,01;
    //          }
    //
    //          if (CLOCKSPEED <= 0.3) {
    //            CLOCKSPEED = (CLOCKSPEED + 0.01);
    //          }
//    Serial.println(CLOCKSPEED);
    rotate((22 * CLOCKTIMESAT), CLOCKSPEED, LOW, CLOCKDIR_PIN, CLOCKSTEP_PIN);
    CLOCKTIMESAT = 0;
    CLOCKSPEED = 0.01;
    GOINGBACK = false;

  } else if (PLUS == HIGH) {

    if (CLOCKSPEED <= 0.5) {
      CLOCKSPEED = (CLOCKSPEED + 0.001);
      BUTTONRELEASED = true;
    }

    rotate(22, CLOCKSPEED, HIGH, CLOCKDIR_PIN, CLOCKSTEP_PIN);

  } else if (MINUS == HIGH) {

    if (CLOCKSPEED <= 0.5) {
      CLOCKSPEED = (CLOCKSPEED + 0.001);
      BUTTONRELEASED = true;
    }

    rotate(22, CLOCKSPEED, LOW, CLOCKDIR_PIN, CLOCKSTEP_PIN);

  } else if (BUTTONRELEASED) {
    CLOCKSPEED = 0.01;
    BUTTONRELEASED = false;
  }





  //
  //  rotate(524, CLOCKSPEED, HIGH, CLOCKDIR_PIN, CLOCKSTEP_PIN);
  //  delay(1000);
  //
  //  rotate(6288, CLOCKSPEED, HIGH, CLOCKDIR_PIN, CLOCKSTEP_PIN);
  //  delay(1000);
  //
  //  rotate(6288, CLOCKSPEED, LOW, CLOCKDIR_PIN, CLOCKSTEP_PIN);
  //  delay(1000);
  //
  //  rotate(6288, CLOCKSPEED, LOW, CLOCKDIR_PIN, CLOCKSTEP_PIN);
  //  delay(1000);



  // make 1/60th turn with the big hand every minute



}








void rotate(int steps, float speed, int dir, int DIR_PIN, int STEP_PIN) {
  //rotate a specific number of microsteps (8 microsteps per step) - (negative for reverse movement)


  digitalWrite(DIR_PIN, dir);

  float usDelay = (1 / speed) * 70;

  for (int i = 0; i < steps; i++) {

    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(usDelay);

    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(usDelay);
  }
}
