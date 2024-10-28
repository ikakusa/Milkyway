#pragma once

#include <MemUtils.h>

struct ActorRotationComponent {
public:
    vec2 rotation;
    vec2 oldRotation;

    ActorRotationComponent(const vec2& rotation) : rotation(rotation), oldRotation(rotation) {}

    [[nodiscard]] const vec2& Get() const
    {
        return this->rotation;
    }

    void Set(vec2 rots)
    {
        this->rotation = rots;
    }
};