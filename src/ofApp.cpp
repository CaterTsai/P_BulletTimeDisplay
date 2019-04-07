#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);
	ofSetFrameRate(60);

	_config.load();
	initUdp();

	_mainTimer = ofGetElapsedTimef();

}

//--------------------------------------------------------------
void ofApp::update(){
	float delta = ofGetElapsedTimef() - _mainTimer;
	_mainTimer += delta;


	checkUdp(delta);
	_gifMgr.update(delta);

	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw(){

	_gifMgr.draw(360, 170);
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
	}
	
}

//--------------------------------------------------------------
void ofApp::initUdp()
{
	_udpReceiver.Create();
	_udpReceiver.Bind(_config.port);
	_udpReceiver.SetNonBlocking(true);
	_checkTimer = cUdpCheckTime;

}

//--------------------------------------------------------------
void ofApp::checkUdp(float delta)
{
	_checkTimer -= delta;

	if (_checkTimer <= 0.0f)
	{
		char udpMsg[50];
		_udpReceiver.Receive(udpMsg, 50);
		string msg = udpMsg;

		if (msg != "")
		{
			string path = _config.gifFolderPath + msg + ".gif";
			_gifMgr.addNewGif(path);
		}

		_checkTimer = cUdpCheckTime;
	}
}
