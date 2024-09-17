#pragma once
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