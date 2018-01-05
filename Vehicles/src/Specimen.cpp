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
	ofVec2f velocity;
	ofVec2f acceleration;
	
	int height = 20;
	int width = 10;
	float rotation = 0.0;
	
	ofPath coord;
	ofVec2f target;
	
	constexpr static float maxForce = 0.2;
	constexpr static float maxSpeed = 5.0;
	constexpr static float maxDist = 1132;
	
	void updateCoordinates() {
		coord.clear();
		coord.lineTo(ofPoint(0, -height/2));
		coord.lineTo(ofPoint(-width/2, height/2));
		coord.lineTo(ofPoint(width/2, height/2));
		coord.close();
	}
	
public:
	Specimen() {
		acceleration = ofVec2f(0, 0);
		velocity = ofVec2f(0, -2);
		location = ofVec2f(0, 0);
		updateCoordinates();
	}
	
	Specimen(int x, int y) {
		acceleration = ofVec2f(0, 0);
		velocity = ofVec2f(0, -2);
		location = ofVec2f(x, y);
		updateCoordinates();
	}
	
	void applyForce(const ofVec2f &force) {
		acceleration += force;
	}
	
	void applyBehaviors(vector<Specimen> &population) {
		// Calculate forces
		ofVec2f separateForce = separateFrom(population);
		ofVec2f seekForce = seek(ofVec2f(ofGetMouseX(), ofGetMouseY()));
		
		// Apply genome
		separateForce *= 2;
		seekForce *= 1;
		
		// Apply
		applyForce(separateForce);
		applyForce(seekForce);
	}
	
	ofVec2f separateFrom(vector<Specimen> &population) {
		float range = 40;
		ofVec2f steeringForce = {0, 0};
		ofVec2f sum = {0, 0};
		int count = 0;
		
		// Get the sum of the desired separate direction
		for (auto& other : population) {
			float distance = location.distance(other.location);
			if (distance > 0 and distance < range) {
				ofVec2f desired = location - other.location;
				
				// Shorter distances apply more force
				desired = desired.getNormalized() / distance;
				
				sum += desired;
				count++;
			}
		}
		
		if (count > 0) {
			// We want the average of the desired separation
			sum /= count;
			
			// This is desired, so we normalize
			sum = sum.getNormalized() * maxSpeed;
			
			// Apply Reynolds --> steering = desired - velocity
			steeringForce = sum - velocity;
			steeringForce.limit(maxForce);
		}
		
		return steeringForce;
	}
	
	ofVec2f seek(const ofVec2f &target) {
		// Points from position to target
		this->target = target;
		ofVec2f desired = target - location;
		
		// Reduce if it has arrived
		float m = ofMap(desired.length(), 0, 100, 0, maxSpeed);
		desired = desired.getNormalized() * m;
		
		// Apply Reynolds --> steering = desired - velocity
		ofVec2f steeringForce = desired - velocity;
		steeringForce.limit(maxForce);
		
		return steeringForce;
	}
	
	void update() {
		// Update velocity
		velocity += acceleration;
		
		// Limit speed
		velocity.limit(maxSpeed);
		
		// Update location
		location += velocity;
		
		// reset
		acceleration.set(0, 0);
		
		
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
	
	void draw() {
		rotation = -velocity.angle(ofVec2f(0,-1));
		ofPushMatrix();
		
		ofTranslate(location.x,location.y, 0);
		ofRotateZ(rotation);
		
		float d = location.distance(target);
		coord.setFillColor(ofColor(ofMap(d, 0, 500, 0, 255, true),
								   ofMap(d, 0, 500, 255, 0, true),
								   rand() % 255));
		coord.draw();
		
		ofPopMatrix();
	}
};
