#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	ofGLFWWindowSettings settings;
	settings.width = 1920;
	settings.height = 1080;
	settings.decorated = false;
	settings.windowMode = OF_WINDOW;
	ofCreateWindow(settings);
	ofRunApp(new ofApp());

}
