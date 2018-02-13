/*
  FOLLOW THE TRACK!
*/


int volatile leftEncoderCount = 0;
int volatile rightEncoderCount = 0;
void leftIncrement(){
   leftEncoderCount++;
}
void rightIncrement(){  
   rightEncoderCount++;
}

int LEFT_ENCODER = 2;
int RIGHT_ENCODER = 3;

int LEFT_WHEEL = 5;
int RIGHT_WHEEL = 3;

int RIGHT_RECEIVER = A7;
int MIDDLE_RECEIVER = A4;
int LEFT_RECEIVER = A1;

int BLUE_LED = 7;
int GREEN_LED = 8; 
int RED_LED = 4;

int LEFT_WHITE = 108;
int MIDDLE_WHITE = 155;
int RIGHT_WHITE = 126;

int LEFT_BLACK = 74;
int MIDDLE_BLACK = 91;
int RIGHT_BLACK = 84;

int LEFT_NORM1 = LEFT_WHITE - LEFT_BLACK;
int MIDDLE_NORM1 = MIDDLE_WHITE - MIDDLE_BLACK;
int RIGHT_NORM1 = RIGHT_WHITE - RIGHT_BLACK;

float LEFT_NORM = 1.0/LEFT_NORM1;
float MIDDLE_NORM = 1.0/MIDDLE_NORM1;
float RIGHT_NORM = 1.0/RIGHT_NORM1;

byte right_high = 0;
byte middle_high = 0;
byte left_high = 0;

float right_val;
float middle_val;
float left_val;

int STOP_THRESHOLD = 120;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  // initialize analog pins left n right wheels as an output.
  pinMode(LEFT_WHEEL, OUTPUT);
  pinMode(RIGHT_WHEEL, OUTPUT);

  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  pinMode(LEFT_ENCODER, INPUT_PULLUP);
  pinMode(RIGHT_ENCODER, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(LEFT_ENCODER), leftIncrement, CHANGE);
  attachInterrupt(digitalPinToInterrupt(RIGHT_ENCODER), rightIncrement, CHANGE);

 // analogWrite(LEFT_WHEEL, 205); //out of 255
 // analogWrite(RIGHT_WHEEL, 255);
  
}

void STOP(){
  analogWrite(LEFT_WHEEL, 0); //out of 255
  analogWrite(RIGHT_WHEEL, 0);

  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(BLUE_LED, HIGH);
  delay(5000);
  if((analogRead(LEFT_RECEIVER)+analogRead(MIDDLE_RECEIVER)+analogRead(RIGHT_RECEIVER)) < STOP_THRESHOLD ){
    analogWrite(LEFT_WHEEL, 0); //out of 255
    analogWrite(RIGHT_WHEEL, 0);
    delay(500);
  }
 /* delay(50);
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  delay(50);  */
  
}

void START(){
  analogWrite(LEFT_WHEEL, 255); //out of 255
  analogWrite(RIGHT_WHEEL, 255); //was 200
  delay(22);
  //Serial.print("START");
}

int t = 0;
int T_THRESH = 50;
void TURN_LEFT(){
    digitalWrite(BLUE_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
  if(t < T_THRESH){
    analogWrite(LEFT_WHEEL, 15); //out of 255
    analogWrite(RIGHT_WHEEL, 25);
    delay(7);
  } else {
    t = 0;
     analogWrite(LEFT_WHEEL, 15); //out of 255
    analogWrite(RIGHT_WHEEL, 255);
    delay(22);
   }
    
//  delay(3);

}

void TURN_RIGHT(){
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
  if(t < T_THRESH){
    analogWrite(LEFT_WHEEL, 25); //out of 255 was 100,15
    analogWrite(RIGHT_WHEEL, 15);
    delay(8);
  }
  else {
    t=0;
     analogWrite(LEFT_WHEEL, 255); //out of 255 was 100,15
    analogWrite(RIGHT_WHEEL, 15);
    delay(22);
   }
}
void GO_STRAIGHT(){
  analogWrite(RIGHT_WHEEL, 66);
  analogWrite(LEFT_WHEEL, 74);
  delay(22);
  if(t > 20){
    t=0;
    analogWrite(RIGHT_WHEEL, 255);
    analogWrite(LEFT_WHEEL, 255);
    }
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  delay(24);
}


int stop_soon = 0;

int lastLeft = 0;
int lastRight = 0;
// the loop function runs over and over again forever
void loop() {

  int left_val = analogRead(LEFT_RECEIVER);
  int right_val = analogRead(RIGHT_RECEIVER);
  int middle_val = analogRead(MIDDLE_RECEIVER);

  /*
  Serial.print(left_val);
  Serial.print(" ");
  Serial.print(middle_val);
  Serial.print(" ");
  Serial.print(right_val);
  Serial.print(" t: ");
  Serial.print(t);
  Serial.print(" ");
  Serial.print((analogRead(LEFT_RECEIVER)+analogRead(MIDDLE_RECEIVER)+analogRead(RIGHT_RECEIVER)));
  Serial.print(" "); 
  Serial.println();
  */


 // Serial.print(bias);
 // Serial.println();
  if(analogRead(LEFT_RECEIVER)>55 || analogRead(MIDDLE_RECEIVER) > 55 || analogRead(RIGHT_RECEIVER) > 45 ){
    
      if( (right_val - left_val )> 10) TURN_LEFT();
      else if( (left_val - right_val) > 35) TURN_RIGHT();
      else  GO_STRAIGHT();
    

    if(leftEncoderCount == lastLeft) t++;
    if(rightEncoderCount == lastRight) t++;
    t++;
  }
  else //if((analogRead(LEFT_RECEIVER)+analogRead(MIDDLE_RECEIVER)+analogRead(RIGHT_RECEIVER)) < STOP_THRESHOLD ){
    //  stop_soon = 1;
    //  if((analogRead(LEFT_RECEIVER)+analogRead(MIDDLE_RECEIVER)+analogRead(RIGHT_RECEIVER)) < STOP_THRESHOLD && stop_soon == 1 )
        STOP();
  /*} else {
    stop_soon = 0;
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
    GO_STRAIGHT();
  } */

   //delay(20); //maybe remove? was 30
  


}
