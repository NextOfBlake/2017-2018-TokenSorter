#ifndef MOVEMENT_H
#define MOVEMENT_H
#include "Arduino.h"
#include "ScrapController.h"

/// namespace to access Turn and Approach enumerations
namespace moveOptions {
	enum Turn { Left45, Right45, Left90, Right90, Left135, Right135, Left180, Right180 };
	enum Approach { NoFollowUntilPerpendicularLine, FollowUntilPerpendicularLine, FollowUntilPerpendicularLineOnLeft,
					FollowUntilPerpendicularLineOnRight, FollowUntilCrossingY, FollowUntilSeparatingY };
}

using namespace moveOptions;

class Movement {
	public:
		Movement() {};
		void performTurn(Turn turnType);
		void performApproach(Approach approachType);
		// Turn methods
		void turnLeft45() { Serial.println("Turning 45 deg to the left"); };
		void turnRight45() { Serial.println("Turning 45 deg to the right"); };
		void turnLeft90() { Serial.println("Turning 90 deg to the left"); };
		void turnRight90() { Serial.println("Turning 90 deg to the right"); };
		void turnLeft135() { Serial.println("Turning 135 deg to the left"); };
		void turnRight135() { Serial.println("Turning 135 deg to the right"); };
		void turnLeft180() { Serial.println("Turning 180 deg to the left"); };
		void turnRight180() { Serial.println("Turning 180 deg to the right"); };
		// Approach functions
		void approachNoFollowUntilPerpendicularLine() { Serial.println("Not following line until perpendicular line is hit"); };
		void approachFollowUntilPerpendicularLine() { Serial.println("Following line until perpendicular line is hit"); };
		void approachFollowUntilPerpendicularLineOnLeft() { Serial.println("Following line until perpendicular line is hit on the left"); };
		void approachFollowUntilPerpendicularLineOnRight() { Serial.println("Following line until perpendicular line is hit on the right"); };
		void approachFollowUntilCrossingY() { Serial.println("Following line until two lines of Y start to cross"); };
		void approachFollowUntilSeparatingY() { Serial.println("Following line until two liens of Y start to separate"); };
};





#endif