#pragma once
#include <filesystem>
#include "StringUtils.h"

namespace fs = std::filesystem;
namespace FileUtils {
	static bool createFolder(std::string folderName) {
		char* value;
		size_t size;

		_dupenv_s(&value, &size, "APPDATA");

		std::string roam = (value + std::string("\\..\\Local\\Packages\\Microsoft.MinecraftUWP_8wekyb3d8bbwe\\RoamingState\\"));
		fs::create_directory(StringUtils::combine(roam, folderName));
		return true;
	}

	static bool createAssetsFolder(std::string folderName) {
		char* value;
		size_t size;

		_dupenv_s(&value, &size, "APPDATA");

		std::string roam = (value + std::string("\\..\\Local\\Packages\\Microsoft.MinecraftUWP_8wekyb3d8bbwe\\RoamingState\\Milkyway\\"));
		fs::create_directory(StringUtils::combine(roam, folderName));
		return true;
	}
}