#pragma once

#include "constParameter.h"
#include "ofxXmlSettings.h"
class config {
public:
	config() {
		port = 0;
		gifFolderPath = "";
	}

	void load(string path = "_config.xml")
	{
		ofxXmlSettings xml;
		if (!xml.load(path)) {
			return;
		}

		port = xml.getValue("UdpPort", 2233);
		gifFolderPath = xml.getValue("gifFolderPath", "");

	}
public:
	int port;
	string gifFolderPath;
	ofVec2f windowPos;
};