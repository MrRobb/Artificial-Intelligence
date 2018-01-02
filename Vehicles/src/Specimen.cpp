//
//  Specimen.cpp
//  Vehicles
//
//  Created by Roberto Ariosa Hernández on 02/01/2018.
//

#include "Specimen.hpp"

class Specimen {
private:
	ofVec2f location;
	float speed = 0.0;
	int height = 20;
	int width = 10;
	float rotation = 0.0;
	ofPath coord;
	ofVec2f target;
	ofVec2f velocity;
	constexpr static const float maxSteering = 5.0;
	
	void updateCoordinates() {
		coord.clear();
		coord.lineTo(ofPoint(0, -height/2));
		coord.lineTo(ofPoint(-width/2, height/2));
		coord.lineTo(ofPoint(width/2, height/2));
		coord.close();
	}
	
public:
	Specimen() {
		location = ofVec2f(0,0);
		updateCoordinates();
	}
	
	Specimen(int x, int y) {
		location = ofVec2f(x, y);
		updateCoordinates();
	}
	
	Specimen(const ofVec2f &location) {
		this->location = location;
		updateCoordinates();
	}
	
	void setSpeed(float velocity) {
		this->speed = velocity;
	}
	
	void rotateLeft() {
		rotation -= speed;
	}
	
	void rotateRight() {
		rotation += speed;
	}
	
	void increaseSpeed() {
		speed++;
	}
	
	void decreaseSpeed() {
		speed--;
	}
	
	void draw() {
		ofPushMatrix();
		ofTranslate(location.x,location.y, 0);
		ofRotateZ(rotation);
		coord.draw();
		ofPopMatrix();
	}
	
	void setTarget(int x, int y) {
		target = ofVec2f(x, y);
	}
	
	void setVelocity() {
		velocity = ofVec2f(speed * sin(ofDegToRad(rotation)), -speed * cos(ofDegToRad(rotation)));
	}
	
	void update() {
		// Update target
		setTarget(ofGetMouseX(), ofGetMouseY());
		setVelocity();
		
		// Calculate desire velocity
		ofVec2f desired = target - location;
		
		// Calculate steering force
		ofVec2f steeringForce = desired - velocity;
		steeringForce.limit(maxSteering);
		
		// Update
		location += steeringForce;
		
		// Constrain
		if (location.x < 0) {
			location.x = 0;
		}
		if (location.x > ofGetWidth()) {
			location.x = ofGetWidth();
		}
		if (location.y < 0) {
			location.y = 0;
		}
		if (location.y > ofGetHeight()) {
			location.y = ofGetHeight();
		}
	}
};
