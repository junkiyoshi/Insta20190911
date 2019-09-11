#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(2);
	ofNoFill();
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	int span = 120;
	for (int x = span * 0.5; x <= ofGetWidth() - span * 0.5; x += span) {

		for (int y = span * 0.5; y <= ofGetHeight() - span * 0.5; y += span) {

			auto base_location = glm::vec3(x, y, 0);
			for (int len = 20; len < 120; len += 20) {

				vector<glm::vec3> vertices;
				for (int param = 0; param < 100; param++) {

					glm::vec3 location = glm::vec3(this->make_point(len, param), 0);
					auto rotation_x = glm::rotate(glm::mat4(), ofMap(ofNoise((base_location.x + location.x) * 0.003, ofGetFrameNum() * 0.003), 0, 1, -PI, PI), glm::vec3(1, 0, 0));
					auto rotation_y = glm::rotate(glm::mat4(), ofMap(ofNoise((base_location.y + location.y) * 0.003, ofGetFrameNum() * 0.003), 0, 1, -PI, PI), glm::vec3(0, 1, 0));
					auto rotation_z = glm::rotate(glm::mat4(), ofMap(ofNoise((base_location.z + location.z) * 0.003, ofGetFrameNum() * 0.003), 0, 1, -PI, PI), glm::vec3(0, 0, 1));
					glm::vec3 tmp_location = glm::vec4(location, 0) * rotation_z * rotation_y * rotation_x;

					vertices.push_back(base_location + tmp_location);
				}

				ofBeginShape();
				ofVertices(vertices);
				ofEndShape(true);
			}
		}
	}
}

//--------------------------------------------------------------
glm::vec2 ofApp::make_point(int len, int param) {

	param = param % 100;
	if (param < 25) {

		return glm::vec2(ofMap(param, 0, 25, -len * 0.5, len * 0.5), -len * 0.5);
	}
	else if (param < 50) {

		return glm::vec2(len * 0.5, ofMap(param, 25, 50, -len * 0.5, len * 0.5));
	}
	else if (param < 75) {

		return glm::vec2(ofMap(param, 50, 75, len * 0.5, -len * 0.5), len * 0.5);
	}
	else {

		return glm::vec2(-len * 0.5, ofMap(param, 75, 100, len * 0.5, -len * 0.5));
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}