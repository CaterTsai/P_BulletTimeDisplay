#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(13, 121, 59);
	ofSetFrameRate(60);

	_config.load();
	initUdp();


	ofSetWindowPosition(0, 0);

	_mainTimer = ofGetElapsedTimef();

	_isShowCursor = true;
	ofHideCursor();

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

	ofSetColor(255);

	_gifMgr.draw(60, 220);
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
		_isShowCursor = !_isShowCursor;
		_isShowCursor ? ofShowCursor() : ofHideCursor();
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
