#pragma once

#include "ofxUDPManager.h"
#include "constParameter.h"
#include "gifMgr.h"
#include "config.h"

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);

private:
	float _mainTimer, _autoTimer;
	ofImage _bg, _title;
	bool _isShowCursor;
	config _config;
	gifMgr _gifMgr;


public:
	void initUdp();
	void checkUdp(float delta);
private:
	float _checkTimer;
	ofxUDPManager _udpReceiver;
};
