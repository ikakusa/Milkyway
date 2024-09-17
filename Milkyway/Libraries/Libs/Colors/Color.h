#pragma once
#include <Math/Math.h>
class Color {
public:
	union {
		struct {
			float r, g, b, a;
		};
		float arr[4];
	};
	bool shouldDelete = true;

	Color() {
		this->r = 1;
		this->g = 1;
		this->b = 1;
		this->a = 1;
	};

	Color(const Color& other) {
		this->r = other.r;
		this->g = other.g;
		this->b = other.b;
		this->a = other.a;
		this->shouldDelete = other.shouldDelete;
	}

	Color(const float* arr) {
		this->arr[0] = arr[0];
		this->arr[1] = arr[1];
		this->arr[2] = arr[2];
		this->arr[3] = arr[3];
	};

	Color(const float r, const float g, const float b, const float a = 1) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	};

	Color(const int r, const int g, const int b, const int a = 255) {
		this->r = r / 255.0f;
		this->g = g / 255.0f;
		this->b = b / 255.0f;
		this->a = a / 255.0f;
	};

	Color(const float r, const float g, const float b, const float a, const bool shouldDelete) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
		this->shouldDelete = shouldDelete;
	};
};
struct rgb {
	union {
		struct { float r, g, b, a; };
		float arr[4]{};
	};
	bool shouldDelete = true;

	rgb() {
		this->r = 1;
		this->g = 1;
		this->b = 1;
		this->a = 1;
	}

	rgb(float x) {
		this->r = x;
		this->g = x;
		this->b = x;
		this->a = 1;
	}

	rgb(const rgb& other) {
		this->r = other.r;
		this->g = other.g;
		this->b = other.b;
		this->a = other.a;
		this->shouldDelete = other.shouldDelete;
	}

	rgb(const float r, const float g, const float b, const float a = 255) {
		this->r = r / 255.0f;
		this->g = g / 255.0f;
		this->b = b / 255.0f;
		this->a = a / 255.0f;
	}

	rgb(const int r, const int g, const int b, const int a = 255) {
		this->r = r / 255.0f;
		this->g = g / 255.0f;
		this->b = b / 255.0f;
		this->a = a / 255.0f;
	}

	rgb(const float r, const float g, const float b, const float a, const bool shouldDelete) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
		this->shouldDelete = shouldDelete;
	}

	// Type Conversions

	operator ImVec4() const {
		return ImVec4(r, g, b, a);
	}

	operator ImColor() const {
		return ImColor(r, g, b, a);
	}

	operator ImU32() const {
		return ImGui::ColorConvertFloat4ToU32(ImVec4(r, g, b, a));
	}

	// Custom Functions

	// ToHSV

	vec3 GetHSV() {
		float h, s, v;
		ImGui::ColorConvertHSVtoRGB(r, g, b, h, s, v);
		return vec3(h, s, v);
	}

	std::string ToString() {
		return std::to_string(r) + ", " + std::to_string(g) + ", " + std::to_string(b) + ", " + std::to_string(a);
	}
};

struct UIColor {
	int r = 255;
	int g = 255;
	int b = 255;
	int a = 255;
	UIColor(int red, int green, int blue, int alpha = 255) {
		this->r = red;
		this->g = green;
		this->b = blue;
		this->a = alpha;
	}
	Color toColor() {
		return Color((float)this->r / 255.f, (float)this->g / 255.f, (float)this->b / 255.f, (float)this->a / 255.f);
	}
	ImColor toImColor() {
		return ImColor(this->r, this->g, this->b, this->a);
	}
	static UIColor fromImU32(ImU32 color) {
		int r = (color >> IM_COL32_R_SHIFT) & 0xFF;
		int g = (color >> IM_COL32_G_SHIFT) & 0xFF;
		int b = (color >> IM_COL32_B_SHIFT) & 0xFF;
		int a = (color >> IM_COL32_A_SHIFT) & 0xFF;
		return UIColor(r, g, b, a);
	}
};

enum ColorType {
	CUSTOM,
	RAINBOW,
	ASTOLFO,
};

class ColorUtils {
private:

	static __int64 getCurrentMs() {
		FILETIME f;
		GetSystemTimeAsFileTime(&f);
		(long long)f.dwHighDateTime;
		__int64 nano = ((__int64)f.dwHighDateTime << 32LL) + (__int64)f.dwLowDateTime;
		return (nano - 116444736000000000LL) / 10000;
	}
public:

	static UIColor rainbowColor(float seconds, float saturation, float brightness, long index, int alpha = 255) {
		float hue6 = (((getCurrentMs() + index) % (int)(6000)) / (float)(6000));
		float r, g, b = 0;
		ImGui::ColorConvertHSVtoRGB(hue6, saturation, brightness, r, g, b);

		return UIColor(static_cast<int>(r * 255.f), static_cast<int>(g * 255.f), static_cast<int>(b * 255.f), alpha);
	}
	static UIColor waveColor(int red, int green, int blue, int red2, int green2, int blue2, long index, int alpha = 255) {
		double offset = ((getCurrentMs() - index) / 8) / (double)120;
		double aids123 = ((getCurrentMs() - index) % 1000 / 1000.000f);
		float aids1234 = (float)(((getCurrentMs() - index) % 2000 / 2000) * 2);
		aids123 = (int)aids1234 % 2 == 0 ? aids123 : 1 - aids123;
		double inverse_percent = 1 - aids123;
		int redPart = (int)(red * inverse_percent + red2 * aids123);
		int greenPart = (int)(green * inverse_percent + green2 * aids123);
		int bluePart = (int)(blue * inverse_percent + blue2 * aids123);

		return UIColor(redPart, greenPart, bluePart, alpha);
	}

	static UIColor astolfoRainbow(int yOffset, int yTotal, int alpha = 255) {
		float speed = 3000;
		float hue = (float)(getCurrentMs() % (int)speed) + ((yTotal - yOffset) * 9);
		while (hue > speed) { hue -= speed; } hue /= speed;
		if (hue > 0.5) { hue = 0.5F - (hue - 0.5f); } hue += 0.5f;
		float r, g, b = 0;
		ImGui::ColorConvertHSVtoRGB(hue, 0.5, 1.f, r, g, b);

		return UIColor((int)(r * 255.f), (int)(g * 255.f), (int)(b * 255.f), alpha);
	}

	static UIColor newrainbowColor(float seconds, float saturation, float brightness, long index, int alpha = 255) {
		float hue6 = (((getCurrentMs() + index) % (int)(seconds * 1000)) / (float)(seconds * 1000));
		float r, g, b = 0;
		ImGui::ColorConvertHSVtoRGB(hue6, saturation, brightness, r, g, b);

		return UIColor(static_cast<int>(r * 255.f), static_cast<int>(g * 255.f), static_cast<int>(b * 255.f), alpha);
	}

public:
	static UIColor getColor(ColorType type, int index = 0, int alpha = 255) {
		switch (type)
		{
		case RAINBOW: {
			return rainbowColor(8, 1.f, 1.f, (long)(-index * 4.f), alpha);
			break;
		}
		case ASTOLFO: {
			return astolfoRainbow(index / 5, 1000, alpha);
			break;
		}
		}
		return UIColor(255, 0, 0);
	};
};
__forceinline static UIColor getUIColor(Color col) {
	return UIColor((int)(col.r * 255.f), (int)(col.g * 255.f), (int)(col.b * 255.f), (int)(col.a * 255.f));
}