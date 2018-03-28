/*

*/
#include "LineIntersection.h"

LineIntersection::LineIntersection()
{


}


LineIntersection::LineIntersection(int pin) {
	mySensorBar = new SensorBar(SX1509_ADDRESS);
	mySensorBar->clearBarStrobe();
	mySensorBar->clearInvertBits();
	mySensorBar->begin();
	//setLineByte();

	// set middlePin
	middlePin = pin;
}

//raw data for sensor bar
String LineIntersection::getArrayDataInString() {
	String lineData = "";
	int bit_value;
	// get data
	line_byte = mySensorBar->getRaw();

	for (int8_t i = BYTE_SIZE-1; i >= 0; i--) {
		bit_value = bitRead(line_byte,i);
		lineData += (bit_value ? ON_LINE : OFF_LINE);
	}
	return lineData;
}

//true if middle is on a line
bool LineIntersection::getMiddleState() {
	return analogRead(middlePin) >= middleThreshold;
}

//creates a variable called data_sum_vector which is
int8_t LineIntersection::getArrayDataSum() {
	String line_data = getArrayDataInString();
	int8_t data_sum_vector = 0;
	for (int8_t i = BYTE_SIZE-1; i >= 0; i--) {
		if (line_data[i] == ON_LINE && i >= 4) {
			data_sum_vector++;
		}
		else if (line_data[i] == ON_LINE) { // Implying that i <= 3.
			data_sum_vector--;
		}
	}
}



//generate lineData w/ middle pin so that string is 9 bits long
String LineIntersection::getFullArrayInString() {
	String lineData = "";
	density = 0;
	int bit_value;
	// get data
	line_byte = mySensorBar->getRaw();
	bool state = getMiddleState();

	for (int8_t i = BYTE_SIZE-1; i >= 0; i--) {
		bit_value = bitRead(line_byte,i);
		lineData += (bit_value ? ON_LINE : OFF_LINE);
		density += bit_value;
		if (i == 4) {
			lineData += (state ? ON_LINE : OFF_LINE);
			density += state;
		}

	}
	lastFullReading = lineData;
	return lineData;
}

//calculating position variable more negetive when lastFullReading is lower and more postive versa
int LineIntersection::getLinePosition(bool getNewData) {
	int position = 0;
	// get new data if requested then it updates the sensor values
	if (getNewData) {
		getFullArrayInString();
	}
	//if middle is online then check to see if left or right is too
	if (lastFullReading[4] == ON_LINE) {
		// if on the line, only worry about closest two sensors
		if (lastFullReading[3] == ON_LINE) position -= 1;
		if (lastFullReading[5] == ON_LINE) position += 1;
	}
	else {
		// otherwise, worry about all
		if (lastFullReading[3] == ON_LINE || lastFullReading[5] == ON_LINE) {
			if (lastFullReading[3] == ON_LINE) position -= 4;
			if (lastFullReading[5] == ON_LINE) position += 4;
		}
		else if (lastFullReading[2] == ON_LINE || lastFullReading[6] == ON_LINE) {
			if (lastFullReading[2] == ON_LINE) position -= 8;
			if (lastFullReading[6] == ON_LINE) position += 8;
		}
		else if (lastFullReading[1] == ON_LINE || lastFullReading[7] == ON_LINE) {
			if (lastFullReading[1] == ON_LINE) position -= 12;
			if (lastFullReading[7] == ON_LINE) position += 12;
		}
		else if (lastFullReading[0] == ON_LINE || lastFullReading[8] == ON_LINE) {
			if (lastFullReading[0] == ON_LINE) position -= 16;
			if (lastFullReading[8] == ON_LINE) position += 16;
		}
		// remember last position if no IRs are on_line
		if (position == 0) {
			position = lastPosition;
		}
	}
	// set lastPosition to most recent position
	lastPosition = position;
	return lastPosition;
}

//if density is higher than 5 then return true
bool LineIntersection::getIfAtPerpendicular() {
	int required_density = 5;
	return getDensity() >= required_density;
}


bool LineIntersection::getIfAtSeparatingY() {
	return (lastFullReading[2] == ON_LINE && lastFullReading[6] == ON_LINE)
			|| (lastFullReading[1] == ON_LINE && lastFullReading[7] == ON_LINE);
}


bool LineIntersection::getIfAtCrossingY() {
	return getIfAtSeparatingY();
}


bool LineIntersection::getIfAtRightY() {
	return getIfAtPerpendicular();
}


bool LineIntersection::getIfAtLeftY() {
	return getIfAtPerpendicular();
}
