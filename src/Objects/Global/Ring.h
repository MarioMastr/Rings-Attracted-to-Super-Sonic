#ifndef OBJ_RING_H
#define OBJ_RING_H

#include "Game.h"

typedef enum {
    RING_TYPE_NORMAL,
    RING_TYPE_BIG,
    RING_TYPE_SPARKLE1,
    RING_TYPE_SPARKLE2,
    RING_TYPE_SPARKLE3,
} RingTypes;

typedef enum {
    RING_MOVE_FIXED,
    RING_MOVE_LINEAR,
    RING_MOVE_CIRCLE,
    RING_MOVE_TRACK,
    RING_MOVE_PATH,
} RingMoveTypes;

// Object Class
struct ObjectRing {
    RSDK_OBJECT
    Hitbox hitbox;
    int32 pan;
    uint16 aniFrames;
    uint16 sfxRing;
};

// Entity Class
struct EntityRing {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(stateDraw);
    RingTypes type;
    ManiaPlaneFilterTypes planeFilter;
    int32 ringAmount;
    int32 timer;
    int32 maxFrameCount;
    int32 sparkleType;
    EntityPlayer *storedPlayer;
    RingMoveTypes moveType;
    Vector2 amplitude;
    int32 speed;
    Vector2 drawPos;
    Animator animator;
};

// Object Struct
extern ObjectRing *Ring;

// Extra Entity Functions
extern void (*Ring_Collect)(void);

// States
extern void (*Ring_State_Normal)(void);
extern void (*Ring_State_Lost)(void);
extern void (*Ring_State_Attracted)(void);

// State Hooks
bool32 Ring_State_Attracted_Hook(bool32 skipped);
bool32 Ring_State_Normal_Lost_Hook(bool32 skipped);

// Draw States
extern void (*Ring_Draw_Normal)(void);

#endif //! OBJ_RING_H
