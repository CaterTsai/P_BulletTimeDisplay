#pragma once

#include "threadGif.h"
#include "constParameter.h"

class gifMgr {
public:
	gifMgr();

	void load();
	void update(float delta);
	void draw(int x, int y);

	void play(float intervalT);
	void stop();

	void addNewGif(string path);

private:
	void checkGifLoad();

private:
	bool _isPlay;
	int _addIndex;
	int _rowNum, _colNum;

	ofImage _default;
	vector<threadGif> _gifContainer;

	int _frameIdx;
	float _timer, _intervalT;
	int _miniumFrameNum;
	int _unitW, _unitH;
	int _intervalW, _intervalH;

};