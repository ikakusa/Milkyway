#pragma once

class Minecraft
{
private:
	virtual void D0Func(); // 0
public:
	virtual uintptr_t getEntityRegistry();
	virtual uintptr_t getEntityRegistry2();

private:
	char pad_0x0000[0xD0]; //0x0000
public:
	float* timer; //0x00D8 
	float* renderTimer;

	void setTimerSpeed(float tps) {
		*this->timer = tps;
		*this->renderTimer = tps;
	};
};

class MinecraftGame {
public:
	BUILD_ACCESS(bool, canMove, 0x1A8);
public:
	std::string* getPlayerName() {
		std::string out;
		using playerName = std::string* (*)(MinecraftGame*, std::string*);
		static playerName func = reinterpret_cast<playerName>(SigScan("48 89 5C 24 ?? 55 56 57 48 83 EC ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 44 24 ?? 48 8B FA 48 8B F1 48 89 54 24 ?? 33 ED 0F"));
		return func(this, &out);
	}
};