#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_SUBTRACT);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	float span = 4;
	vector<ofColor> color_list = { ofColor(255, 0, 0), ofColor(0, 255, 0), ofColor(0, 0, 255) };
	for (int i = 0; i < color_list.size(); i++) {

		ofMesh mesh;
		auto noise_value = ofRandom(1000);
		
		for (float x = 10; x < ofGetWindowWidth() -10 - span; x += span) {

			for (float y = 10; y < ofGetWindowHeight() - 10 - span; y += span) {

				mesh.addVertex(glm::vec3(x, y, 0));
				mesh.addVertex(glm::vec3(x + span, y, 0));
				mesh.addVertex(glm::vec3(x + span, y + span, 0));
				mesh.addVertex(glm::vec3(x, y + span, 0));

				for (int k = mesh.getNumVertices() - 4; k < mesh.getNumVertices(); k++) {

					auto noise_value = ofNoise(mesh.getVertex(k).x * 0.0025, mesh.getVertex(k).y * 0.0025, ofGetFrameNum() * 0.015 + i * 0.08);
					int int_noise_value = noise_value;
					float param = noise_value - int_noise_value;
					param = abs(param - 0.5);

					auto color = ofColor(color_list[i], param < 0.15 ? ofMap(param, 0, 0.15, 255, 0) : 0);
					mesh.addColor(color);
				}

				mesh.addIndex(mesh.getNumVertices() - 1); mesh.addIndex(mesh.getNumVertices() - 2); mesh.addIndex(mesh.getNumVertices() - 3);
				mesh.addIndex(mesh.getNumVertices() - 1); mesh.addIndex(mesh.getNumVertices() - 3); mesh.addIndex(mesh.getNumVertices() - 4);
			}
		}

		mesh.draw();
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}