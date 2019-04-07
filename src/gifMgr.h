#pragma once


#include "constParameter.h"
#include "ofxGifDecoder.h"
#include "ofxGifFile.h"
#include "ofxAnimatableFloat.h"
class gifMgr {
public:
	gifMgr();
	~gifMgr();

	void load();
	void update(float delta);
	void draw(int x, int y);

	void addNewGif(string path);

private:
	void initOrder();
	void onGifOnload(ofxGifFile& gif);

private:
	bool _isLoad;
	int _addIndex;
	int _rowNum, _colNum;

	ofImage _default;
	ofxGifDecoder _gifLoader;
	array<ofxGifFile, cGifNum> _gifContainer;
	array<int, cGifNum> _gifOrder;

	int _unitW, _unitH;
	int _intervalW, _intervalH;

#pragma region Animation
private:
	void animInit();
	void animUpdate(float delta);
	void animDraw(int x, int y);
	void setAnimation(int index, ofImage& temp);

private:
	enum eAnimState {
		eAnimExit = 0,
		eAnimEnter,
		eAnimFinish
	}_eState;

	int _animIdx;
	ofImage _tempImg;
	ofxAnimatableFloat	_animSize;

#pragma endregion


};