#pragma once
#include <utility>
#include "GuiData.h"
#include "MinecraftGame.h"
#include "LevelRenderer.h"
#include <Math/Math.h>
#include <glm/glm.hpp>

class BlockSource;
class LevelRenderer;
class LevelRendererPlayer;
class LoopbackPacketSender;
class ClientInstance {
public:
	BUILD_ACCESS(GuiData*, guiData, 0x590);
	BUILD_ACCESS(LoopbackPacketSender*, loopbackSender, 0xF8);
	BUILD_ACCESS(float, fovX, 0x728);
	BUILD_ACCESS(float, fovY, 0x738);
	BUILD_ACCESS(glmatrixf, GLMatrix, 0x364);
	BUILD_ACCESS(class LevelRenderer*, levelRenderer, 0xE8);//0xD0
	BUILD_ACCESS(Minecraft*, minecraft, 0xD0);//0xD0
	BUILD_ACCESS(const char*, serverIP, 0x8A8);
	BUILD_ACCESS(const char*, lastServerName, 0x968);
	BUILD_ACCESS(MinecraftGame*, mcGame, 0xD0);

	vec2 getFov() {
		return vec2(fovX, fovY);
	}

    static std::shared_ptr<Packet> createPacket(int packetId) {
        static uintptr_t Address;

        if (Address == NULL) {
            Address = SigScan("48 89 5C 24 ?? 48 89 6C 24 ?? 48 89 74 24 ?? 57 48 81 EC ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 84 24 ?? ?? ?? ?? 48 8B F9 48 89 4C 24 ?? 33 ED 81");
        }

        std::shared_ptr<Packet>* result = nullptr;
        auto pFunction = reinterpret_cast<std::shared_ptr<Packet>(__fastcall*)(int)>(Address);
        return pFunction(packetId);
    }

	//LevelRenderer* getLevelRenderer() {
	//	return reinterpret_cast<LevelRenderer*>(*(uintptr_t*)this + 0xE0);
	//}

	inline bool WorldToScreen(vec3 pos, vec2& screen)
	{ // pos = pos 2 w2s, screen = output screen coords
		if (!guiData) {
			return false;
		}
		vec2 displaySize = guiData->windowSizeReal;
		LevelRenderer* lr = levelRenderer;
		vec3 origin = lr->getLevelRendererPlayer()->cameraPos;
		vec2 fov = getFov();

		pos.x -= origin.x;
		pos.y -= origin.y;
		pos.z -= origin.z;

		auto glmatrix = GLMatrix;
		std::shared_ptr<glmatrixf> matrix = std::shared_ptr<glmatrixf>(glmatrix.correct());

		float x = matrix->transformx(pos);
		float y = matrix->transformy(pos);
		float z = matrix->transformz(pos);

		if (z > 0) return false;

		float mX = (float)displaySize.x / 2.0F;
		float mY = (float)displaySize.y / 2.0F;

		screen.x = mX + (mX * x / -z * fov.x);
		screen.y = mY - (mY * y / -z * fov.y);

		return true;
	}

    MinecraftGame* getMinecraftGame() {
        return *reinterpret_cast<MinecraftGame**>(this + 0xD0); //1.21.4x
    }

	class LocalPlayer* getLocalPlayer() {
		if (this != nullptr) return CallVFunc<30, class LocalPlayer*>(this); //ClientInstance::getLocalPlayer();
		return nullptr;
	}// unused

	void grabCursor()
	{
		return CallVFunc<338, void>(this); //ClientInstance::grabMouse(); 1.21.4x
	}

	BlockSource* getRegion() {
		return CallVFunc<28, BlockSource*>(this); //ClientInstance::getRegion();
	}

	void releaseCursor()
	{
		return CallVFunc<339, void>(this); //ClientInstance::releaseMouse(); 1.21.4x
	}
};

using HashType64 = uint64_t; // Define HashType64 to be a 64-bit unsigned integer

class HashedString {
public:
    static HashedString defaultErrorValue;
    static const HashedString EMPTY;

private:
    HashType64 mStrHash;
    std::string mStr;
    mutable const HashedString* mLastMatch;

public:
    // Default constructor
    HashedString() : mStrHash(0), mStr(""), mLastMatch(nullptr) {}

    // Constructor from nullptr_t
    HashedString(std::nullptr_t) : mStrHash(0), mStr(""), mLastMatch(nullptr) {}

    // Copy constructor
    HashedString(const HashedString& o)
        : mStrHash(o.mStrHash), mStr(o.mStr), mLastMatch(nullptr) {}

    // Move constructor
    HashedString(HashedString&& o) noexcept
        : mStrHash(o.mStrHash), mStr(std::move(o.mStr)), mLastMatch(nullptr) {
        o.mStrHash = 0;
    }

    // Copy assignment operator
    HashedString& operator=(const HashedString& o) {
        if (this != &o) {
            mStrHash = o.mStrHash;
            mStr = o.mStr;
        }
        return *this;
    }

    // Move assignment operator
    HashedString& operator=(HashedString&& o) noexcept {
        if (this != &o) {
            mStrHash = o.mStrHash;
            mStr = std::move(o.mStr);
            o.mStrHash = 0;
        }
        return *this;
    }

    // Constructor from std::string
    HashedString(std::string str)
        : HashedString(computeHash(str), std::move(str)) {}

    // Constructor from hash and std::string
    HashedString(HashType64 hash, std::string str)
        : mStrHash(hash), mStr(std::move(str)) {}

    // Equality operator
    bool operator==(const HashedString& rhs) const {
        if (mStrHash != rhs.mStrHash) return false;
        if (mLastMatch == &rhs && rhs.mLastMatch == this) return true;
        if (mStr != rhs.mStr) return false;
        const_cast<HashedString*>(this)->mLastMatch = &rhs;
        const_cast<HashedString*>(&rhs)->mLastMatch = this;
        return true;
    }

    // Less-than operator
    bool operator<(const HashedString& o) const {
        if (mStrHash < o.mStrHash) return true;
        if (mStrHash == o.mStrHash) return mStr < o.mStr;
        return false;
    }

    // Conversion operator to string_span (custom type, needs implementation)
    // Note: `string_span` needs to be defined or replaced with appropriate type
    operator std::string_view() const {
        return std::string_view(mStr);
    }

    // Get hash value
    HashType64 getHash() const {
        return mStrHash;
    }

    // Get string reference
    const std::string& getString() const {
        return mStr;
    }

    // Get C-style string
    const char* c_str() const {
        return mStr.c_str();
    }

    // Check if the string is empty
    bool isEmpty() const {
        return mStr.empty();
    }

    // Alias for isEmpty()
    bool empty() const {
        return isEmpty();
    }

    // Clear the object
    void clear() {
        mStrHash = 0;
        mStr.clear();
    }

    // Compute hash from std::string_view
    static HashType64 computeHash(const std::string_view str) {
        if (str.empty()) return 0;
        uint64_t hash = 0xCBF29CE484222325;
        for (const char c : str) {
            hash *= 0x100000001B3; // 64bit Prime Multiplier
            hash ^= static_cast<uint64_t>(c);
        }
        return hash;
    }
};