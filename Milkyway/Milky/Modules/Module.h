#pragma once
#include "../Notify/Notification.h"

enum class Category {
	COMBAT = 0,
	RENDER = 1,
	MISC = 2,
	OTHER = 3
};

enum class SettingType {
	INT = 0,
	FLOAT = 1,
	BOOL = 2,
	GROUP = 3,
	COLOR = 4
};

class Entry {
private:
	const char* name;
	int val;
public:
	int getValue() { return val; }
	const char* getName() { return name; }
};

class Module;
class Mode {
public:
	Module* mod = nullptr;
	const char* name;
	int selected = -1;
	std::vector<Entry> entries;
	void addMode(const char* name, int index) {  };
	const char* getName() { return name; }
};

struct SettingValue {
	union {
		float _float;
		double _double;
		__int64 int64;
		int _int;
		bool _bool;
		const char* text;
		Mode* Enum;
		Color color;
	};
	SettingValue() {};
};

class Setting {
public:
	char name[0x20] = "";
	SettingType valueType;
	SettingValue* value = nullptr;
	SettingValue* defaultValue = nullptr;
	SettingValue* minValue = nullptr;
	SettingValue* maxValue = nullptr;
};

class Module {
public:
	Module() {};
	Module(int keybind, Category cat, const char* name, const char* tooltip) { this->name = name; this->category = cat; this->tooltip = tooltip; this->keybind = keybind; };
	~Module() {};
private:
	const char* tooltip = "";
	bool enabled = false;
	bool visible = false;
	int keybind = 0x0;
	Category category = Category::OTHER;
	const char* name = "";
	std::vector<Setting*> settings;
public:
	const char* getModuleName() { return this->name; };
	Category getCategory() { return this->category; }
	void toggle() { this->setEnabled(!this->enabled); }
	void setEnabled(bool which) { if (which == true) this->onEnable(); else this->onDisable(); this->enabled = which; notify.addNotify(new Notification(3.f, "", StringUtils::combine(this->getModuleName(), " has been ", enabled ? "enabled." : "disabled."))); }
	bool isEnabled() { return this->enabled; }
	int getKeybind() { return this->keybind; }
	void setKeybind(int key) { this->keybind = key; }
	auto getSetting() { return settings; }

	//
	void addInt(const char* name, int* intPtr, int defaultVal, int minVal, int maxVal) {
		auto setting = new Setting();
		strcpy_s(setting->name, 19, name);
		setting->valueType = SettingType::INT;
		setting->value = (SettingValue*)intPtr;

		SettingValue* defaultV = new SettingValue();
		defaultV->_int = defaultVal;
		setting->defaultValue = defaultV;

		SettingValue* minV = new SettingValue();
		minV->_int = minVal;
		setting->minValue = minV;

		SettingValue* maxV = new SettingValue();
		maxV->_int = maxVal;
		setting->maxValue = maxV;
		settings.push_back(setting);
	};

	void addFloat(const char* name, float* floatPtr, float defaultVal, float minVal, float maxVal) {
		auto setting = new Setting();
		strcpy_s(setting->name, 19, name);
		setting->valueType = SettingType::FLOAT;
		setting->value = (SettingValue*)floatPtr;

		SettingValue* defaultV = new SettingValue();
		defaultV->_float = defaultVal;
		setting->defaultValue = defaultV;

		SettingValue* minV = new SettingValue();
		minV->_float = minVal;
		setting->minValue = minV;

		SettingValue* maxV = new SettingValue();
		maxV->_float = maxVal;
		setting->maxValue = maxV;
		settings.push_back(setting);
	};
	void addBool(const char* name, bool* boolPtr, bool defaultValue = false) {
		auto setting = new Setting();
		strcpy_s(setting->name, 19, name);
		setting->valueType = SettingType::BOOL;
		setting->value = (SettingValue*)boolPtr;

		SettingValue* defaultV = new SettingValue();
		defaultV->_bool = defaultValue;
		setting->defaultValue = defaultV;
		settings.push_back(setting);
	};
	void addEnum() {};
	void addColor() {};
public:
	virtual void onEnable() {};
	virtual void onDisable() {};
	virtual void onMiddleClick() {};
	virtual void onTick(GameMode* gm) {};
	virtual void onPreTick(GameMode* gm) {};
	virtual void onImGuiRender(ImDrawList* d) {};
	virtual void onSendPacket(Packet* packet) {};
	virtual void onKey(int key, bool isDown) {
		if (isDown && key == this->keybind) {
			toggle();
		}
	};
};