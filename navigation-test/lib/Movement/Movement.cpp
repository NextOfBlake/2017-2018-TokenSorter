#include "Movement.h"


void Movement::performTurn(Turn turnType) {
	switch (turnType) {
		case Left45:
			turnLeft45();
			break;
		case Right45:
			turnRight45();
			break;
		case Left90:
			turnLeft90();
			break;
		case Right90:
			turnRight90();
			break;
		case Left135:
			turnLeft135();
			break;
		case Right135:
			turnRight135();
			break;
		case Left180:
			turnLeft180();
			break;
		case Right180:
			turnRight180();
			break;
		default:
			Serial.println("Turn type does not exist");
			break;
	}

}


void Movement::performApproach(Approach approachType) {
	switch (approachType) {
		case NoFollowUntilPerpendicularLine:
			approachNoFollowUntilPerpendicularLine();
			break;
		case FollowUntilPerpendicularLine:
			approachFollowUntilPerpendicularLine();
			break;
		case FollowUntilPerpendicularLineOnLeft:
			approachFollowUntilPerpendicularLineOnLeft();
			break;
		case FollowUntilPerpendicularLineOnRight:
			approachFollowUntilPerpendicularLineOnRight();
			break;
		case FollowUntilCrossingY:
			approachFollowUntilCrossingY();
			break;
		case FollowUntilSeparatingY:
			approachFollowUntilSeparatingY();
			break;
		default:
			Serial.println("Approach type does not exist");
			break;
	}
}
