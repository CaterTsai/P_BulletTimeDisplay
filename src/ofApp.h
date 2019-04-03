#pragma once

#include "constParameter.h"
#include "gifMgr.h"
class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);

private:
	gifMgr _gifMgr;
	float _mainTimer;
};
