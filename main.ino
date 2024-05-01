#include <Ps3Controller.h>

// -- Define -- //
#define MAC_ADDRESS "FC:B4:67:4E:99:F6"
#define IN1_CHANNEL 12
#define IN2_CHANNEL 14
#define IN3_CHANNEL 18
#define IN4_CHANNEL 19
#define CONV_A 34
#define CONV_B 35

// -- Functions -- //
void __MOTOR(int16_t ySpeed, int16_t xSpeed)
{
  if(ySpeed > 50)
  {
    analogWrite(IN1_CHANNEL, ySpeed);
    analogWrite(IN2_CHANNEL, 0);
    analogWrite(IN3_CHANNEL, ySpeed);
    analogWrite(IN4_CHANNEL, 0);
  }
  else if(ySpeed < -50)
  {
    analogWrite(IN1_CHANNEL, 0);
    analogWrite(IN2_CHANNEL, abs(ySpeed));
    analogWrite(IN3_CHANNEL, 0);
    analogWrite(IN4_CHANNEL, abs(ySpeed));
  }
  else
  {
    analogWrite(IN1_CHANNEL, 0);
    analogWrite(IN2_CHANNEL, 0);
    analogWrite(IN3_CHANNEL, 0);
    analogWrite(IN4_CHANNEL, 0);
  }
  if(xSpeed > 50)
  {
    analogWrite(IN3_CHANNEL, xSpeed);
    analogWrite(IN4_CHANNEL, 0);
    analogWrite(IN3_CHANNEL, 0);
    analogWrite(IN4_CHANNEL, xSpeed);
  }
  else if(xSpeed < -50)
  {
    analogWrite(IN3_CHANNEL, 0);
    analogWrite(IN4_CHANNEL, abs(xSpeed));
    analogWrite(IN3_CHANNEL, abs(xSpeed));
    analogWrite(IN4_CHANNEL, 0);
  }
  else
  {
    analogWrite(IN1_CHANNEL, 0);
    analogWrite(IN2_CHANNEL, 0);
    analogWrite(IN3_CHANNEL, 0);
    analogWrite(IN4_CHANNEL, 0);
  } 
}

void __ROLL()
{
  if ( Ps3.event.button_down.start )
  {
    if (roll_activate){
      analogWrite(CONV_A, 100);
      analogWrite(CONV_B, 0);
    }
    else{
      analogWrite(CONV_A, 0);
      analogWrite(CONV_B, 0);
    }
  }
}


void Ps3Controller()
{
  int16_t JoyLeft, JoyRight;
  int16_t xSpeed, ySpeed;

  JoyLeft = Ps3.data.analog.stick.ly;
  JoyRight = Ps3.data.analog.stick.rx;
  ySpeed = map(JoyLeft, -128, 128, -255, 255);
  xSpeed = map(JoyRight, -128, 128, -255, 255);

  // Serial.println(String(xSpeed) + "\t" + String(ySpeed));

  __MOTOR(xSpeed, ySpeed);
  __ROLL();
}

void onConnect()
{
  if(Ps3.isConnected()){
    Serial.println("Successfully connecting to " + String(MAC_ADDRESS));
    analogWrite(CONV_A, 0);
    analogWrite(CONV_B, 0);

    analogWrite(IN1_CHANNEL, 0);
    analogWrite(IN2_CHANNEL, 0);

    analogWrite(IN3_CHANNEL, 0);
    analogWrite(IN4_CHANNEL, 0);
  }

}

void onDisconnect(){
  analogWrite(CONV_A, 0);
  analogWrite(CONV_B, 0);

  analogWrite(IN1_CHANNEL, 128);
  analogWrite(IN2_CHANNEL, 0);

  analogWrite(IN3_CHANNEL, 128);
  analogWrite(IN4_CHANNEL, 0);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(IN1_CHANNEL, OUTPUT);
  pinMode(IN2_CHANNEL, OUTPUT);
  pinMode(IN3_CHANNEL, OUTPUT);
  pinMode(IN4_CHANNEL, OUTPUT);
  pinMode(CONV_A, OUTPUT);
  pinMode(CONV_B, OUTPUT);

  Ps3.begin(MAC_ADDRESS);
  Ps3.attachOnConnect(onConnect);
  Ps3.attachOnDisconnect(onDisconnect);
  Ps3.attach(Ps3Controller);
}


void loop{
  if (!Ps3.isConnected() && !connected) return;

  

}
