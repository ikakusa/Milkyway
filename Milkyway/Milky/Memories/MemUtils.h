#pragma once
#include "../../dllmain.h"
#include "../Hooks/Hooks.h"
#include "../Logger/Logger.h"
class FuncHook;
class MemoryUtils {
public:
	static inline bool isInitialized = false;
	static void init();
	static void restore();

#define INRANGE(x, a, b) (x >= a && x <= b)
#define GET_BYTE(x) (GET_BITS(x[0]) << 4 | GET_BITS(x[1]))
#define GET_BITS(x) (INRANGE((x & (~0x20)), 'A', 'F') ? ((x & (~0x20)) - 'A' + 0xa) : (INRANGE(x, '0', '9') ? x - '0' : 0))
public:
	static uintptr_t FindSignatureOrig(const char* sig, const char* szSignature);
};

class FuncHook {
public:
	void* funcPtr;
	void* funcReal;

	FuncHook(void* func, void* hooked) {
		funcPtr = func;

		MH_STATUS ret = MH_CreateHook(func, hooked, &funcReal);
		if (ret == MH_OK && (__int64)func > 10) {
		}
	};

	FuncHook(uintptr_t func, void* hooked) {
		funcPtr = reinterpret_cast<void*>(func);

		MH_STATUS ret = MH_CreateHook(funcPtr, hooked, &funcReal);
		if (ret == MH_OK && (__int64)funcPtr > 10) {
		}
	};

	bool enableHook(bool enable = true) {
		if (funcPtr != nullptr) {
			if (enable) { return MH_EnableHook(funcPtr) == MH_OK; }
			else { return MH_DisableHook(funcPtr) == MH_OK; }
		}
		return false;
	}

	~FuncHook() {
		Restore();
	}

	void Restore() {
		if (funcPtr != nullptr)
			MH_DisableHook(funcPtr);
	}

	template <typename TRet, typename... TArgs>
	inline auto* GetFastcall() {
		using Fn = TRet(__fastcall*)(TArgs...);
		return reinterpret_cast<Fn>(funcReal);
	};
};

#pragma region DirectClassAccess

template <typename Ret, typename Type>
Ret& DirectAccess(Type* type, size_t offset) {
	union {
		size_t raw;
		Type* source;
		Ret* target;
	} u;
	u.source = type;
	u.raw += offset;
	return *u.target;
}

#define AS_FIELD(type, name, fn) __declspec(property(get = fn, put = set##name)) type name
#define DEF_FIELD_RW(type, name) __declspec(property(get = get##name, put = set##name)) type name

#define FAKE_FIELD(type, name)                                                                                       \
AS_FIELD(type, name, get##name);                                                                                     \
type get##name()

#define BUILD_ACCESS(type, name, offset)                                                                             \
AS_FIELD(type, name, get##name);                                                                                     \
type get##name() const { return DirectAccess<type>(this, offset); }												 \
void set##name(type v) const { DirectAccess<type>(this, offset) = v; }

#pragma endregion

__forceinline static bool CreateHook(std::unique_ptr<FuncHook>& breh, void* func, void* hooked, bool first = false) {
	breh = std::make_unique<FuncHook>(func, hooked);
	if (!first) return &breh;
	return breh->enableHook(true);
}
__forceinline static uintptr_t findSig(const char* sig) {
	return MemoryUtils::FindSignatureOrig("Minecraft.Windows.exe", sig);
}

__forceinline static uintptr_t getBaseAddress() {
	static const auto rangeStart = (uintptr_t)GetModuleHandleA("Minecraft.Windows.exe");
	return rangeStart;
}

template <unsigned int IIdx, typename TRet, typename... TArgs>
__forceinline static auto CallVFunc(void* thisptr, TArgs... argList) -> TRet {
	using Fn = TRet(__thiscall*)(void*, decltype(argList)...);
	return (*static_cast<Fn**>(thisptr))[IIdx](thisptr, argList...);
}

static __forceinline void nopBytes(void* dst, unsigned int size) {
	if (dst == nullptr) return;
	DWORD oldprotect;
	if (!VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect)) return;
	memset(dst, 0x90, size);
	if (!VirtualProtect(dst, size, oldprotect, &oldprotect)) return;
}
static __forceinline void copyBytes(void* src, void* dst, unsigned int size) {
	if (dst == nullptr || src == nullptr) return;
	DWORD oldprotect;
	if (!VirtualProtect(src, size, PAGE_EXECUTE_READWRITE, &oldprotect)) return;
	memcpy(dst, src, size);
	if (!VirtualProtect(src, size, oldprotect, &oldprotect)) return;
}
static __forceinline void patchBytes(void* dst, void* src, unsigned int size) {
	if (dst == nullptr || src == nullptr) return;
	DWORD oldprotect;
	if (!VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect)) return;
	memcpy(dst, src, size);
	if (!VirtualProtect(dst, size, oldprotect, &oldprotect)) return;
}
__forceinline static uintptr_t** getVtable(const char* szSignature, int offset) {
	uintptr_t** signatureOffset = 0x0;
	if (signatureOffset == 0x0) {
		uintptr_t sigOffset = findSig(szSignature);
		if (sigOffset != 0x0) {
			int finalOffset = *reinterpret_cast<int*>((sigOffset + offset));                      // Get Offset from code
			signatureOffset = reinterpret_cast<uintptr_t**>(sigOffset + finalOffset + /*length of instruction*/ 7);
			return signatureOffset;
		}
	}
	writelog("faild to get vtable");
	return 0u;
}