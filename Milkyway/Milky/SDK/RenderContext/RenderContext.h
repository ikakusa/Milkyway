#pragma once
#include <MemUtils.h>
#include <Math/Math.h>
#include <xorstr.hpp>

class MemUtils;
class ComponentRenderBatch;
class ClientInstance;
class NinesliceInfo;
struct TextMeasureData {
	float textSize;
	int idk;
	bool shadow;
	bool bool2;
};
class CaretMeasureData
{
public:
	int Position;
	bool isSingleline;// false|insert

	CaretMeasureData()
	{
		CaretMeasureData(0xFFFFFFFF, true);
	};

	CaretMeasureData(int position, bool singlelines)
	{
		this->Position = position;
		this->isSingleline = singlelines;
	};
};

class FilePath {
private:
	uint64_t type;
	std::string filePath;  //0x0008
public:
	FilePath(std::string filePath, bool system = false) {
		memset(this, 0, sizeof(FilePath));
		this->filePath = filePath;
		if (system)
			this->type = 2;
	};
};
class FontBitmap
{
private:
	char pad_0x0000[0x290];
public:
	char FontPath[32];
};
class FontRepos
{
public:
	std::vector<FontBitmap*> fonts;

	const char* FontName(FontBitmap* font)
	{
		if (font->FontPath[0] == 'f')
			return "Mojangles";

		return "Unknown";
	}

	void PutFont(FontBitmap* font)
	{
		bool fontExists = false;
		for (FontBitmap* fontPtr : fonts)
		{
			if (font == fontPtr)
				fontExists = true;
		}

		if (!fontExists)
		{
			fonts.push_back(font);
		}
	}

	FontBitmap* GetFont(const char* font)
	{
		for (FontBitmap* fontPtr : fonts)
		{
			if (strcmp(FontName(fontPtr), font) == 0)
				return fontPtr;
		}

		return nullptr;
	}

	FontBitmap* GetClientFont()
	{
		return GetFont("Mojangles");
	}
};

class ResourceLocation {
public:
	char pad[10];
	uint64_t type;        //0x0000
	std::string filePath;  //0x0008
public:
	ResourceLocation(std::string filePath, bool external) {
		memset(this, 0, sizeof(ResourceLocation));
		this->filePath = filePath;
		if (external)
			this->type = 2;
	};
};
class TexturePtr {
public:
	char padding[24];

	ResourceLocation* path;
	char padding2[32];

public:
	std::string getFilePath() const {
		return path->filePath;
	}
};
class UIScene;
class Color;
class ScreenContext;
class MinecraftUIRenderContext {
public:
	ClientInstance* clientInstance;
	BUILD_ACCESS(ClientInstance*, clientInstance, 0x8);
	BUILD_ACCESS(ScreenContext*, screenCtx, 0x10);
	BUILD_ACCESS(UIScene*, currentScene, 0x100);

private:
	virtual void Destructor() = 0;
public:
	virtual float getLineLength(void* font, std::string* str, float measureCalculation, bool calculateWidth) = 0;
private:
	virtual int getTextAlpha() = 0;
	virtual void setTextAlpha() = 0;
	virtual void drawDebugText() = 0;
public:
	virtual void drawText(void* font, const float* pos, std::string* text, const float* color, float alpha, unsigned int textAlignment, const TextMeasureData* textMeasureData, const uintptr_t* caretMeasureData) = 0;
	virtual void flushText(float flushDelta) = 0;

	virtual void drawImage(const TexturePtr* a2, vec2 const& ImagePos, vec2 const& ImageDimension, vec2 const& uvPos, vec2 const& uvSize) = 0;
	virtual void drawNineslice() = 0;
	virtual void flushImages(Color& color, float opacity, HashedString& hashedString) = 0;
private:
	virtual void beginSharedMeshBatch() = 0;
	virtual void endSharedMeshBatch() = 0;
public:
	virtual void drawRectangle(vec4 const& rect, Color const& colour, float alpha, int width) = 0;
	virtual void fillRectangle(vec4 const& rect, Color const& colour, float alpha) = 0;

	TexturePtr* getTexture(TexturePtr* texture, ResourceLocation* resourceLocation)
	{
		return CallVFunc<29, TexturePtr*, TexturePtr*, ResourceLocation*>(this, texture, resourceLocation);
	};
};