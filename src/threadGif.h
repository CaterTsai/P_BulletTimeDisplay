#pragma once

#include "ofxGif.h"
#include "ofMain.h"

class threadGif : public ofxGIF::fiGifLoader {
public:
	threadGif() :
		fiGifLoader()
		, _isAllocation(false)
		, _isLoading(false)
		, _isWait(false)
	{}
	void asynLoad(string filename) {
		_isLoading = true;
		thread t(
			[&](string filename) {
				load(filename);
				_isWait = true;
		}, filename);
		t.detach();
	}

	bool update() {
		if (!_isLoading)
		{
			return false;
		}

		if (!_isWait) {
			for (auto& iter : pages)
			{
				iter.update();
			}
			_isLoading = true;
			return true;
		}
		return false;
	}

private:
	bool _isAllocation;
	bool _isLoading, _isWait;
};