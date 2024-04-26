/*  Arduino DC Motor Control - PWM | H-Bridge | L298N  -  Example 01

    by Dejan Nedelkovski, www.HowToMechatronics.com
*/

#define enA 9
#define in1 8
#define in2 7
#define enB 11
#define in3 13
#define in4 12

#define MOTOR_PROTOCOL_PACKET_SIZE (4)

typedef enum protocols_e 
{
  MOTOR = 0,
  
} protocols_t;


char protocol;

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  protocol = 0;

  Serial.begin(9600);
  Serial.setTimeout(1000); 

  analogWrite(enA, 255);
  analogWrite(enB, 255);

  digitalWrite(in2, HIGH);
  digitalWrite(in1, LOW);

  digitalWrite(in4, LOW);
  digitalWrite(in3, HIGH);
}

void loop() {
  while(!Serial.available())
  {}

  Serial.readBytes(&protocol, 1);
//
//  switch(protocol)
//  {
//    case MOTOR:
//      handle_motor_protocol();
//      break;
//    default:
//      Serial.print("unknown protocol: ");
//      Serial.println(protocol);
//      break;
//  }
}

void handle_motor_protocol()
{
  char buffer_[MOTOR_PROTOCOL_PACKET_SIZE] = { 0 };
  Serial.readBytes(buffer_, MOTOR_PROTOCOL_PACKET_SIZE);
  analogWrite(enA, buffer_[0]/*0-255*/); // Send PWM signal to L298N Enable pin
  analogWrite(enB, buffer_[2]/*0-255*/); // Send PWM signal to L298N Enable pin

  Serial.println(buffer_[1]);
  digitalWrite(in1, HIGH * buffer_[1]);
  digitalWrite(in2, HIGH * !buffer_[1]);

  digitalWrite(in3, HIGH * buffer_[3]);
  digitalWrite(in4, HIGH * !buffer_[3]);
}
