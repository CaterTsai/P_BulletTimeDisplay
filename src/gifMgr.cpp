#include "gifMgr.h"

//--------------------------------------
gifMgr::gifMgr()
	:_isPlay(false)
	, _addIndex(0)
	,_rowNum(5)
	,_colNum(10)
	, _frameIdx(0)
	, _intervalT(0.5f)
	, _timer(0.0f)
	, _miniumFrameNum(0)
{
	_default.load("default.jpg");
	_unitW = 181;
	_unitH = _unitW / 1.5f;
	_intervalW = _intervalH = 10;
}

//--------------------------------------
void gifMgr::load()
{

}

//--------------------------------------
void gifMgr::update(float delta)
{
	if (!_isPlay)
	{
		return;
	}

	_timer -= delta;
	if (_timer <= 0.0f)
	{
		_timer = _intervalT;
		_frameIdx =( _frameIdx + 1) % _miniumFrameNum;
	}
	checkGifLoad();
}

//--------------------------------------
void gifMgr::draw(int x, int y)
{
	ofPushMatrix();
	ofTranslate(x, y);
	ofPushStyle();
	ofSetColor(255);
	
	bool drawDefault = false;
	ofVec2f drawPos(0, 0);
	for (int y = 0; y < _rowNum; y++)
	{
		drawPos.y = y * (_unitH + _intervalH);
		for (int x = 0; x < _colNum; x++)
		{
			drawPos.x = x * (_unitW + _intervalW);
			int index = y * _colNum + x;
			if (index >= _gifContainer.size())
			{
				drawDefault = true;
			}

			if (drawDefault)
			{
				_default.draw(drawPos, _unitW, _unitH);
			}
			else
			{
				_gifContainer[index].pages[_frameIdx].draw(drawPos, _unitW, _unitH);
			}
		}
	}

	ofPopStyle();
	ofPopMatrix();
}

//--------------------------------------
void gifMgr::play(float intervalT)
{
	_isPlay = true;
	_intervalT = intervalT;
	_timer = _intervalT;
}

//--------------------------------------
void gifMgr::stop()
{
	_isPlay = false;
}

//--------------------------------------
void gifMgr::addNewGif(string path)
{
	threadGif gif;
	gif.asynLoad(path);
	_gifContainer.push_back(gif);
	if (gif.pages.size() > 0)
	{
		if (_gifContainer.size() == 1 || gif.pages.size() < _miniumFrameNum)
		{
			_miniumFrameNum = gif.pages.size();
		}
	}
}

void gifMgr::checkGifLoad()
{
	for (auto& iter : _gifContainer)
	{
		if (iter.update())
		{
			if (iter.pages.size() == 1 || iter.pages.size() < _miniumFrameNum)
			{
				_miniumFrameNum = iter.pages.size();
			}
			break;
		}
	}
}
