#pragma once
#include <MemUtils.h>
#include <Math/Math.h>

class GuiData {
private:
	char pad_0x0000[0x30];  //0x0000
public:
	union {
		struct {
			float widthReal;   //0x0018
			float heightReal;  //0x001C
		};
		vec2 windowSizeReal;  //0x0018
	};

	float widthReal2;   //0x0020
	float heightReal2;  //0x0024
	union {
		struct {
			float widthGame;   //0x0028
			float heightGame;  //0x002C
		};
		vec2 windowSize;  //0x0028
	};
private:
	char pad_0x0048[0x4]; //0x0048
public:
	float GuiScale; //0x004C 

	void displayClientMessage(const char* fmt, ...) {
		va_list arg;
		va_start(arg, fmt);
		auto lengthNeeded = _vscprintf(fmt, arg) + 1;
		if (lengthNeeded >= 300) return;
		char message[300];
		vsprintf_s(message, 300, fmt, arg);
		std::string msg(message);
		using DisplayClientMessage3 = void (*)(GuiData*, std::string const&);
		static DisplayClientMessage3 displayClientMessage4 = reinterpret_cast<DisplayClientMessage3>(SigScan("40 55 53 56 57 41 56 48 8D AC 24 F0 FE FF FF 48 81 EC ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 85 ?? ?? ?? ?? 41")); // 1.20.8x
		displayClientMessage4(this, msg);
		va_end(arg);
	}
};
