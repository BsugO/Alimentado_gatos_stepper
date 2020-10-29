/*
 Name:		Alimentado_gatos_stepper.ino
 Created:	10/29/2020 2:04:57 PM
 Author:	PTL21166W-PAN006
*/
#include <AccelStepper.h>
#include <Servo.h>
#include <Ultrasonic.h>
// Motor pin definitions:
#define MG90  4				 // Direction		 // Step
#define triger  2			 // Trigger
#define echo  3              // Echo
#define stepPin 8
#define DirPin 9
float Distancia = 0;
int DistServo = 0;

#define MotorInterfaceType 1
AccelStepper stepper = AccelStepper(MotorInterfaceType, stepPin, DirPin);
Servo servo_rot;
Ultrasonic ultra(triger, echo);

void setup() {
	servo_rot.attach(MG90);
	stepper.setMaxSpeed(200);
	stepper.setAcceleration(50);
	Serial.begin(9600);
	servo_rot.write(90);
}
void loop() {
	Distancia = ultra.read();
	Serial.println("stand-by");
	Serial.println(Distancia);
	if (Distancia < 20 & Distancia > 10) {
		stepper.enableOutputs();
		stepper.move(3000);
		cabeca();
		Serial.println(Distancia);
		stepper.runToPosition();
		stepper.disableOutputs();
	}
	delay(500);
	cabeca();
}

void cabeca() {
	DistServo = map(Distancia, 5, 357, 60, 120);
	servo_rot.write(DistServo);
	Serial.println(DistServo);
}