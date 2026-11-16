#pragma once
#include "Game.hpp"

namespace GameAPI::RSDK {
    template <typename T> void (T::*ToMemberPtr(void *ptr))()
	{
        union {
            void* in;
            void (T::*out)();
        } u;

        u.in = ptr;
        return u.out;
    }
}

#define RSDK_SELF(obj)  auto *self = (obj *)sceneInfo->entity
#define RSDK_SELF_GEN() GameObject::Entity *self = (GameObject::Entity *)sceneInfo->entity

extern bool* usePathTracer;

typedef struct {
    uint32 realRotation;
} StockValues;

enum RotateSpeeds {
        Speed0,
        Speed1,
        SpeedMax,
};

static StockValues stockValues;

