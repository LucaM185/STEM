// Define the pins for the stepper motor
const int motor1Pins[] = {4, 5, 6, 7};
const int motor2Pins[] = {9, 10, 11, 12};
const int MAX_SPEED = 10;

const int joystickXPin = A0;
const int joystickYPin = A1;
const int joystickThreshold = 100;

void setup() {
  Serial.begin(115200);  // Set the baud rate for serial communication
  // Set the motor pins as outputs
  for (int i = 0; i < 4; i++) {
    pinMode(motor1Pins[i], OUTPUT);
  }
  for (int i = 0; i < 4; i++) {
    pinMode(motor2Pins[i], OUTPUT);
  }
}

int topXThresh = 1120;
int bottomXThresh = 880;
int topYThresh = 1120;
int bottomYThresh = 880;

float pos1 = 1000.0;
float pos2 = 1000.0;
int number1 = 5; 
int number2 = 5; 
void loop() {
  if (Serial.available() >= 2) {  // Check if at least 2 bytes are available
    number1 = Serial.read() - '0'; 
    number2 = Serial.read() - '0'; 
    while (Serial.available() >= 2){
      number1 = Serial.read() - '0';  // Read the first digit and convert it to an integer
      number2 = Serial.read() - '0';  // Read the second digit and convert it to an integer
    }
  
    // Ensure the values are within the valid range
    number1 = constrain(number1, 1, 9);
    number2 = constrain(number2, 1, 9);
  }
  int joystickXValue = analogRead(joystickXPin);
  int joystickYValue = analogRead(joystickYPin);
  for (int i = 0; i < 2; i++) {  
    if (number1 <= 4 and pos1 < topXThresh and joystickXValue < 900 or joystickXValue < 100){
      setMotor1Step(int(pos1));
      if(joystickXValue < 100){
        pos1++;
      }else{
        pos1+=0.25*(5-number1);
      }
    }else if (number1 >= 6 and pos1 > bottomXThresh and joystickXValue > 100 or joystickXValue > 900){
      setMotor1Step(int(pos1));
      if(joystickXValue > 900){
        pos1--;
      }else{
        pos1-=0.25*(number1-5);
      }
    }
    if (number2 <= 4 and pos2 < topYThresh and joystickYValue > 100 or joystickYValue > 900){
      setMotor2Step(int(pos2));
      if(joystickYValue > 900){
        pos2++;
      }else{
        pos2+=0.25*(5-number2);
      }
    }else if (number2 >= 6 and pos2 > bottomYThresh and joystickYValue < 900 or joystickYValue < 100){
      setMotor2Step(int(pos2));
      if(joystickYValue < 100){
        pos2--;
      }else{
        pos2-=0.25*(number2-5);
      }
    }
    delayMicroseconds(2200); // Adjust the delay between steps as desired
  }
}

void setMotor1Step(int step) {
  for (int i = 0; i < 4; i++) {
    digitalWrite(motor1Pins[i], (i == step or i == (step+1)%4) ? HIGH : LOW);
  }
}
void setMotor2Step(int step) {
  for (int i = 0; i < 4; i++) {
    digitalWrite(motor2Pins[i], (i == step or i == (step+1)%4) ? HIGH : LOW);
  }
}
