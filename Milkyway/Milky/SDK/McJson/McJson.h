#pragma once

namespace MCJson {
	class Value {
	public:
		std::string toStyledString() {
			std::string out;

			using toStyled = std::string*(__fastcall*)(void*, std::string*);
			static toStyled toStyledStrFunc = reinterpret_cast<toStyled>(SigScan("4C 8B DC 49 89 5B 18 57 48 81 EC B0 00 00 00 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 84 24 A0 00 00 00 48 8B FA"));
			return *toStyledStrFunc(this, &out);
		}
	};
}