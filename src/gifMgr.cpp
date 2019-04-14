#include "gifMgr.h"
#include <random>
//--------------------------------------
gifMgr::gifMgr()
	:_isLoad(false)
	, _addIndex(0)
	,_rowNum(cGifRow)
	,_colNum(cGifCol)
	, _animIdx(-1)
	, _eState(eAnimFinish)
{
	_default[0].load("d1.jpg");
	_default[1].load("d2.jpg");
	_unitW = 120;
	_unitH = _unitW / 1.5f;
	_intervalW = _intervalH = 0;

	initOrder();
	animInit();
	ofAddListener(_gifLoader.onGifLoaded, this, &gifMgr::onGifOnload);
}

//--------------------------------------
gifMgr::~gifMgr()
{

}

//--------------------------------------
void gifMgr::load()
{

}

//--------------------------------------
void gifMgr::update(float delta)
{
	animUpdate(delta);
}

//--------------------------------------
void gifMgr::draw(int x, int y)
{
	ofPushMatrix();
	ofTranslate(x, y);
	ofPushStyle();
	ofSetColor(255);
	
	bool drawDefault = false;
	ofVec2f drawPos(_intervalW, _intervalH);
	for (int y = 0; y < _rowNum; y++)
	{
		drawPos.y = y * (_unitH + _intervalH);
		for (int x = 0; x < _colNum; x++)
		{
			drawPos.x = x * (_unitW + _intervalW);
			int index = y * _colNum + x;

			if (index == _animIdx && _eState != eAnimFinish)
			{
				animDraw(drawPos.x + _unitW * 0.5f, drawPos.y + _unitH * 0.5f);
			}
			else {
				if (_gifContainer[index].getWidth() > 0 && _gifContainer[index].getHeight() > 0)
				{
					_gifContainer[index].draw(drawPos.x, drawPos.y, _unitW, _unitH);
				}
				else
				{
					_default[(x + y) % 2].draw(drawPos, _unitW, _unitH);
				}
			}
		}
	}

	ofPopStyle();
	ofPopMatrix();
}


//--------------------------------------
void gifMgr::addNewGif(string path)
{
	if (_isLoad)
	{
		ofLog(OF_LOG_WARNING, "[[gifMgr::addNewGif]waiting loading finish");
		return;
	}

	ofLog(OF_LOG_NOTICE, "[gifMgr::addNewGif]start load :" + path);
	_isLoad = true;
	_gifLoader.decodeThreaded(path);
}

//--------------------------------------
void gifMgr::initOrder()
{
	for (int i = 0; i < cGifNum; i++)
	{
		_gifOrder[i] = i;
	}
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	shuffle(_gifOrder.begin(), _gifOrder.end(), default_random_engine(seed));
}

//--------------------------------------
void gifMgr::onGifOnload(ofxGifFile & gif)
{
	ofLog(OF_LOG_NOTICE, "[gifMgr::onGifOnload]load finish");
	
	if (_gifContainer[_gifOrder[_addIndex]].getWidth() > 0)
	{
		auto frame = _gifContainer[_gifOrder[_addIndex]].getFrameNow();
		ofImage temp;
		temp.setFromPixels(frame.getRawPixels());
		setAnimation(_gifOrder[_addIndex], temp);
	}
	else {
		auto index = _gifOrder[_addIndex];
		int y = (float)index / cGifCol;
		int x = index % cGifCol;
		setAnimation(_gifOrder[_addIndex], _default[(x + y) % 2]);
	}
	
	
	_gifContainer[_gifOrder[_addIndex]] = gif;
	_addIndex = (_addIndex + 1) % _gifOrder.size();
	_isLoad = false;
}

void gifMgr::animInit()
{
	_animSize.setCurve(AnimCurve::EASE_IN_BACK);
	_animSize.setDuration(0.5f);
	_animSize.setRepeatType(AnimRepeat::PLAY_ONCE);
}

void gifMgr::animUpdate(float delta)
{
	_animSize.update(delta);

	switch (_eState)
	{
	case eAnimExit:
	{
		if (_animSize.hasFinishedAnimating() && _animSize.getPercentDone() == 1.0)
		{
			_eState = eAnimEnter;
			_animSize.animateFromTo(0.0f, 1.0f);
		}
		break;
	}
	case eAnimEnter:
	{
		if (_animSize.hasFinishedAnimating() && _animSize.getPercentDone() == 1.0)
		{
			_eState = eAnimFinish;
			_animIdx = -1;
		}
		break;
	}
	}
}

void gifMgr::animDraw(int x, int y)
{
	ofPushMatrix();
	ofTranslate(x, y);
	ofScale(_animSize.getCurrentValue(), _animSize.getCurrentValue());
	
	if (_eState == eAnimExit)
	{
		_tempImg.draw(_unitW * -0.5f, _unitH * -0.5f, _unitW, _unitH);
	}
	else if (_eState == eAnimEnter)
	{
		_gifContainer[_animIdx].draw(_unitW * -0.5f, _unitH * -0.5f, _unitW, _unitH);
	}

	ofPopMatrix();
}

void gifMgr::setAnimation(int index, ofImage& temp)
{
	_tempImg = temp;
	_animIdx = index;
	_eState = eAnimExit;
	_animSize.animateFromTo(1.0f, 0.0f);
}

