#pragma once
#include "Module.h"

#include "Combat/ReachDisplay.h"
#include "Visual/Brightness.h"
#include "Visual/BetterHoverText.h"
#include "Visual/NotificationMod.h"
#include "Visual/ClickGui.h"
#include "Misc/AutoGG.h"
#include "Misc/AutoReQueue.h"
#include "Visual/HUDEditor.h"

using json = nlohmann::json;
extern class ModuleManager moduleMgr;
class ModuleManager {
public:
	json configObj;
	bool initialized = false;
	std::vector<Module*> moduleList;
	std::vector<Module*> getModuleList() {
		return moduleList;
	}
	void clearModuleList() {
		moduleMgr.moduleList.clear();
	}
	bool Initialize();
	bool isInitialized() { return initialized; }
	template <typename T>
	bool add() {
		if (std::is_base_of<T, Module>::value) return false;
		moduleList.push_back(new T());
		std::string name = typeid(T).name();
		writelog("Loaded %s", name.substr(6, name.length()).c_str());
		return true;
	}
	template <typename T>
	T* get() {
		for (auto& mod : moduleMgr.getModuleList()) {
			if (dynamic_cast<T*>(mod)) {
				return (T*)mod;
			}
		}
		return nullptr;
	}

	void uninitialize() {
		initialized = false;
		for (auto& mod : moduleMgr.getModuleList()) {
			mod->setEnabled(false);
			delete mod;
		}
		clearModuleList();
	}
#pragma warning(push)
#pragma warning(disable : 26444)
	void saveConfig() {
		configObj = {};
		json o = {};
		for (auto mod : moduleList) {
			o["enabled"] = mod->isEnabled();
			o["key"] = mod->getKeybind();

			for (auto set : mod->getSetting()) {
				switch (set->valueType)
				{
				case SettingType::INT: {
					o[set->name] = set->value->_int;
					break;
				}
				case SettingType::FLOAT: {
					o[set->name] = set->value->_float;
					break;
				}
				case SettingType::BOOL: {
					o[set->name] = set->value->_bool;
					break;
				}
				case SettingType::GROUP: {
					o[set->name] = set->value->_int;
					break;
				}
				case SettingType::COLOR: {
					json uuuu = {};
					uuuu["Red"] = set->value->color.r;
					uuuu["Green"] = set->value->color.g;
					uuuu["Blue"] = set->value->color.b;
					uuuu["Alpha"] = set->value->color.a;

					o.emplace(set->name, uuuu);
					break;
				}
				default:
					break;
				}
			}
			configObj[mod->getModuleName()] = o;
			o.clear();
		}

		char* value;
		size_t size;

		_dupenv_s(&value, &size, "APPDATA");

		std::string roam = (value + std::string("\\..\\Local\\Packages\\Microsoft.MinecraftUWP_8wekyb3d8bbwe\\RoamingState\\Milkyway\\Configs\\"));
		std::string filePath = roam + "configs.txt";

		std::ofstream outputFile(filePath);
		if (outputFile.is_open()) {
			outputFile << std::setw(4) << configObj << std::endl;
			outputFile.flush();
			outputFile.close();
		}
		else {
		}

		free(value);
	}

	void loadConfig() {
		configObj = {};

		char* value;
		size_t size;

		_dupenv_s(&value, &size, "APPDATA");

		std::string roam = (value + std::string("\\..\\Local\\Packages\\Microsoft.MinecraftUWP_8wekyb3d8bbwe\\RoamingState\\Milkyway\\Configs\\"));
		std::string filePath = roam + "configs.txt";

		std::ifstream ifs(filePath.c_str());
		if (ifs.good())
		{
			try {
				ifs >> configObj;
			}
			catch (json::parse_error&) {

			}
			for (auto mod : moduleList) {
				if (!configObj[mod->getModuleName()].is_null()) {
					json obj = configObj[mod->getModuleName()];
					mod->setEnabled(obj["enabled"].is_null() ? false : obj.at("enabled").get<bool>());
					mod->setKeybind(obj["key"].is_null() ? 0x0 : obj.at("key").get<int>());
					for (auto set : mod->getSetting()) {
						if (!obj[set->name].is_null()) {
							switch (set->valueType)
							{
							case SettingType::INT: {
								set->value->_int = obj.at(set->name).get<int>();
								break;
							}
							case SettingType::FLOAT: {
								set->value->_float = obj.at(set->name).get<float>();
								break;
							}
							case SettingType::BOOL: {
								set->value->_bool = obj.at(set->name).get<bool>();
								break;
							}
							case SettingType::GROUP: {
								set->value->_int = obj.at(set->name).get<int>();

								break;
							}
							case SettingType::COLOR: {
								set->value->color.r = obj[set->name].at("Red").get<float>();
								set->value->color.g = obj[set->name].at("Green").get<float>();
								set->value->color.b = obj[set->name].at("Blue").get<float>();
								set->value->color.a = obj[set->name].at("Alpha").get<float>();
								break;
							}
							default:
								break;
							}
						}
					}
				}
			}
		}

		free(value);
	}
public:
	void onKey(int key, bool isDown) {
		for (auto mod : moduleList) {
			mod->onKey(key, isDown);
		}
	}
	void onMiddleClick() {
		for (auto mod : moduleList) {
			mod->onMiddleClick();
		}
	}
	void onImGuiRender(ImDrawList* d) {
		for (auto mod : moduleList) {
			if (mod->isEnabled()) mod->onImGuiRender(d);
		}
		moduleMgr.get<HUDEditor>()->setPosition();
	}
	void onSendPacket(Packet* packet) {
		for (auto mod : moduleList) {
			if (mod->isEnabled()) mod->onSendPacket(packet);
		}
	}
};