#pragma once
#include <MemUtils.h>

class UIScene {
public:
	bool isPlayScreen() {
		return CallVFunc<55, bool>(this);
	}

	void getScreenName(std::string* txt) {
		CallVFunc<69, void, std::string*>(this, txt);
	}
};