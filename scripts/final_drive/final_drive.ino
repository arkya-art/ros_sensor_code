#include <ros.h>
#include <std_msgs/UInt16.h>
#include <drive/drive_msg.h>
#include <geometry_msgs/Point.h>
//#define RH_ENCODER_A 3
//#define RH_ENCODER_B 5
//#define LH_ENCODER_A 2
//#define LH_ENCODER_B 4
#define Pwm1a 12
#define Pwm2a 10
#define Dir1a 11
#define Dir2a 9

#define Pwm1b 8
#define Pwm2b 6
#define Dir1b 7
#define Dir2b 5

#define Pwm1c 4
#define Pwm2c 2
#define Dir1c 30
#define Dir2c 22


#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

bool d1,d2;


ros::NodeHandle  nh;
//drive::drive_msg rpm_msg;
//ros::Publisher chatter("rpm_drive", &rpm_msg);
geometry_msgs::Point feedback;
ros::Publisher chatter("feedback_motor", &feedback);
int encoder0PinA = 20;   //left orange ->3
int encoder0PinB = 21;   //left red    ->2
int encoder1PinA = 18; //right orange ->19
int encoder1PinB = 19;  //right red   ->18


volatile float encoder0Pos = 0;
volatile int encoder0PinALast = LOW;
volatile int n = LOW;
volatile int m = LOW;

volatile float encoder1Pos = 0;
volatile int encoder1PinALast = LOW;
volatile int n1 = LOW;
volatile int m1 = LOW;

unsigned long previousMillis = 0; 
const long interval = 1200; 

void CountA()
{
  n = digitalRead(encoder0PinA); 
  if ((encoder0PinALast == LOW) && (n == HIGH)) { 
    if (m == LOW) { 
      encoder0Pos--; 
    } 
    else { 
      encoder0Pos++; 
    } 
  }
}

void Count1A()
{
  n1 = digitalRead(encoder1PinA); 
  if ((encoder1PinALast == LOW) && (n1 == HIGH)) { 
    if (m1 == LOW) { 
      encoder1Pos--; 
    } 
    else { 
      encoder1Pos++; 
    } 
  }
}

void StateB()
{
  m = digitalRead(encoder0PinB);
}

void State1B()
{
  m1 = digitalRead(encoder1PinB);
}

void servo_cb( const drive::drive_msg & mg)
{
                d1=mg.ldir;
                d2=mg.rdir;
                //ros::loginfo(mg.lpwm);
                analogWrite(Pwm1a,mg.lpwm);
                analogWrite(Pwm1b,mg.lpwm);
                analogWrite(Pwm1c,mg.lpwm);
                
                analogWrite(Pwm2a,mg.rpwm);
                analogWrite(Pwm2b,mg.rpwm);
                analogWrite(Pwm2c,mg.rpwm); 
                
                digitalWrite(Dir1a,mg.ldir);
                digitalWrite(Dir1b,mg.ldir);
                digitalWrite(Dir1c,mg.ldir);
                
                digitalWrite(Dir2a,mg.rdir);
                digitalWrite(Dir2b,mg.rdir);
                digitalWrite(Dir2c,mg.rdir);      
    
}


ros::Subscriber<drive::drive_msg> sub("rover_drive", servo_cb);


//long previousMillis = 0;
//long currentMillis = 0;
 
// variables to store the number of encoder pulses
// for each motor
//volatile unsigned long leftCount = 0;
//volatile unsigned long rightCount = 0;

// encoder event for the interrupt call

/*void leftEncoderEvent() {
  if (digitalRead(LH_ENCODER_A) == HIGH) {
    if (digitalRead(LH_ENCODER_B) == LOW) {
      leftCount++;
    } else {
      leftCount--;
    }
  } else {
    if (digitalRead(LH_ENCODER_B) == LOW) {
      leftCount--;
    } else {
      leftCount++;
    }
  }
}
 
// encoder event for the interrupt call
void rightEncoderEvent() {
  if (digitalRead(RH_ENCODER_A) == HIGH) {
    if (digitalRead(RH_ENCODER_B) == LOW) {
      rightCount++;
    } else {
      rightCount--;
    }
  } else {
    if (digitalRead(RH_ENCODER_B) == LOW) {
      rightCount--;
    } else {
      rightCount++;
    }
  }
}
*/

void setup() {
          Serial.begin(9600);
          //pinMode(LH_ENCODER_A, INPUT);
          //pinMode(LH_ENCODER_B, INPUT);
          //pinMode(RH_ENCODER_A, INPUT);
          //pinMode(RH_ENCODER_B, INPUT);
          //previousMillis = millis();
  // initialize hardware interrupts
          //attachInterrupt(0, leftEncoderEvent, RISING);
          //attachInterrupt(1, rightEncoderEvent, RISING);
          pinMode (encoder0PinA,INPUT); 
          pinMode (encoder0PinB,INPUT);

          pinMode (encoder1PinA,INPUT); 
          pinMode (encoder1PinB,INPUT);
  
          pinMode(Pwm1a,OUTPUT);
          pinMode(Pwm2a,OUTPUT);
          pinMode(Dir1a,OUTPUT);
          pinMode(Dir2a,OUTPUT);
          pinMode(Pwm1b,OUTPUT);
          pinMode(Pwm2b,OUTPUT);
          pinMode(Dir1b,OUTPUT);
          pinMode(Dir2b,OUTPUT);
          pinMode(Pwm1c,OUTPUT);
          pinMode(Pwm2c,OUTPUT);
          pinMode(Dir1c,OUTPUT);
          pinMode(Dir2c,OUTPUT);
          attachInterrupt(3, CountA, CHANGE);
          attachInterrupt(2, StateB, FALLING);
          attachInterrupt(4, Count1A, CHANGE);
          attachInterrupt(5, State1B, FALLING);
          nh.initNode();
          nh.subscribe(sub);
          nh.advertise(chatter);
}

float t=0;
float w=0;
float dist=0;
float w1=0;
float dist1=0;

void loop() {

  
  /*if(Serial.available() > 0) 
  {
    char buffer[] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}; // Receive up to 1 bytes
                while (!Serial.available()); // Wait for characters
                Serial.readBytesUntil('\0', buffer, 19);
                  int x=0,i=0,j=0,y=0,val3=0,val4=0;
                  while(buffer[i]!=' ')
                 {
                   dataL[x]=buffer[i];
                   i++;
                   x++;
                 }
                   dataL[x]='\0';
                    i++;
                 
                 while(buffer[i]!=' ')
                 {
                   dataR[j]=buffer[i];
                   i++;
                   j++;
                 }
                   dataR[j]='\0';
                   i++;
                 if(buffer[i]=='1')
                   val3=1;
                 i=i+2;
                 if(buffer[i]=='1')
                    val4=1;
                 
                 int val1 = atoi(dataL);
                 int val2 = atoi(dataR);
                 
                 //dataD=totaldata%1000;
                 //totaldata
                
                val1=(int(val1/10))*10;
                val2=(int(val2/10))*10;
                
                //Serial.print(val1);
                //Serial.print(",");
                //Serial.print(val2);
                //Serial.print("'");
                //Serial.print(val3);
                //Serial.print("'");
                //Serial.println(val4);
                analogWrite(Pwm1,val1);
                analogWrite(Pwm2,val2); 
                digitalWrite(Dir1,val3);
                digitalWrite(Dir2,val4);
  }*/
  
  
  //delay(1);
  //int interval = 500;
  //currentMillis = millis();
  
  /*if(currentMillis - previousMillis > interval)
  {
    float lRpm = (leftCount/(696.5))*60*2;
    float rRpm = (rightCount/(696.5))*60*2;
    //Serial.print("lrpm : ");
    //char *sendbyte = itoa(lrpm) + 
    rpm_msg.lpwm = lRpm;
    rpm_msg.rpwm = lRpm;
    rpm_msg.ldir = d1;
    rpm_msg.rdir = d2;
    chatter.publish( &rpm_msg );
    
    //Serial.print("Right Count: ");
    //Serial.println(rightCount);
    //Serial.print("Left Count: ");
    //Serial.println(leftCount);
    rightCount = 0;
    leftCount = 0;
    //Serial.println();
    //delay(500);
    previousMillis = currentMillis;
  }*/
  unsigned long currentMillis = millis();
  encoder0PinALast = n;
  encoder1PinALast = n1;
  //valNew = encoder0Pos;
    
    if(currentMillis - previousMillis >= interval)
    {
       previousMillis = currentMillis;
        dist = (encoder0Pos)/696.5;
        dist1 = (encoder1Pos)/696.5;
       //Serial.println(encoder0Pos);
       //Serial.println(dist);
        encoder0Pos=0;
        encoder1Pos=0;
        //w = 60*dist/interval;
        //rial.print(",");
        //Serial.println(dist1);
       feedback.x=dist*100;
       feedback.y=dist1*(-100);       
   
    }
    //Serial.println(currentMillis);
    //Serial.print (m);
    //Serial.println (".");
    //valOld = valNew;
  chatter.publish( &feedback);
  nh.spinOnce(); 
}
