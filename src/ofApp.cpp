#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);
	ofSetFrameRate(60);

	_mainTimer = ofGetElapsedTimef();

}

//--------------------------------------------------------------
void ofApp::update(){
	float delta = ofGetElapsedTimef() - _mainTimer;
	_mainTimer += delta;

	_gifMgr.update(delta);

	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw(){

	_gifMgr.draw(10, 10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key)
	{
	case 'q':
	{
		_gifMgr.addNewGif("test.gif");
		break;
	}
	case 'w':
	{
		_gifMgr.play(0.2);
		break;
	}
	case 'e':
	{
		_gifMgr.stop();
		break;
	}
	}
	
}
