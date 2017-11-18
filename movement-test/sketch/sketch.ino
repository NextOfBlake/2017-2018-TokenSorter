#include "ScrapController.h"
#include "sensorbar.h"

#define ENCODER_LEFT_INT 4
#define ENCODER_LEFT_DIG 5
#define ENCODER_RIGHT_INT 6
#define ENCODER_RIGHT_DIG 7
#define MOTOR_LEFT_D 9
#define MOTOR_LEFT_PWM 8
#define MOTOR_RIGHT_D 11
#define MOTOR_RIGHT_PWM 10



ScrapEncoder encoderL = ScrapEncoder(ENCODER_LEFT_INT,ENCODER_LEFT_DIG);
ScrapEncoder encoderR = ScrapEncoder(ENCODER_RIGHT_INT,ENCODER_RIGHT_DIG);


ScrapMotorSinglePin motorL = ScrapMotorSinglePin(MOTOR_LEFT_D,MOTOR_LEFT_PWM,-1);
ScrapMotorSinglePin motorR = ScrapMotorSinglePin(MOTOR_RIGHT_D,MOTOR_RIGHT_PWM);

ScrapMotorControl motorControlL = ScrapMotorControl(motorL, encoderL);
ScrapMotorControl motorControlR = ScrapMotorControl(motorR, encoderR);


//ScrapController singleControl = ScrapController(motorControlL);
//ScrapDualController controller = ScrapDualController(motorControlL,motorControlR);

unsigned long currentTime;
unsigned long previousTime;

SensorBar* lineSensor;


void setup() {
	lineSensor = new SensorBar(0x3E);
	lineSensor->clearBarStrobe();
	lineSensor->clearInvertBits();
	lineSensor->begin();
	motorControlL.setMinPower(35);
	motorControlR.setMinPower(45);
	motorControlL.setMinSpeed(160);
	motorControlL.setMaxSpeed(1800);
	motorControlR.setMinSpeed(160);
	motorControlR.setMaxSpeed(1800);
	initEncoders();
	//motorControlL.stop();
	//motorControlR.stop();
	motorControlL.setControl(1800);
	motorControlR.setControl(1800);
	motorControlL.stop();
	motorControlR.stop();
	Serial.begin(9600);
	unsigned long previousTime = millis();
}


void loop() {
	if (Serial.available()) {
		followLineUntilPerpendicular();
	}
	while (Serial.available()) {
		Serial.read();
		delay(1);
	}
	delay(1);
}

void followLineUntilPerpendicular() {
	int normalSpeed = 1500;
	int offset = 0;
	motorControlL.setControl(normalSpeed);
	motorControlR.setControl(normalSpeed);
	while (lineSensor->getDensity() < 3) {
		int position = lineSensor->getPosition();
		Serial.println(position);
		offset = map(position, -127, 127, -300,300);
		motorControlL.setControl(normalSpeed-offset);
		motorControlR.setControl(normalSpeed+offset);
		motorControlL.performMovement();
		motorControlR.performMovement();

	}
	Serial.println("DONE");
	motorControlL.stop();
	motorControlR.stop();
}


void initEncoders() {
	attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT_INT),checkEncoderL,CHANGE);
	attachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT_INT),checkEncoderR,CHANGE);
}

void checkEncoderL() {
	encoderL.checkEncoderFlipped();
}

void checkEncoderR() {
	encoderR.checkEncoder();
}
