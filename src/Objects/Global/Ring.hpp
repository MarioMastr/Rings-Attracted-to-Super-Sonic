#pragma once
#include "Game.hpp"

#include "Player.hpp"

using namespace RSDK;

// ------------------
// Macros/Definitions
// ------------------

namespace GameLogic
{
struct Ring : GameObject::Entity {

    // ---------------
    // Enums & Structs
    // ---------------

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

    // ----------------
    // Static Variables
    // ----------------

    struct Static : GameObject::Static {
        Hitbox hitbox;
        int32 pan;
        SpriteAnimation aniFrames;
        SoundFX sfxRing;
    };

    struct ModStatic {
    };

    // ----------------
    // Entity Variables
    // ----------------

    StateMachine<Ring> state;
    StateMachine<Ring> stateDraw;
    RingTypes type;
    ManiaPlaneFilterTypes planeFilter;
    int32 ringAmount;
    int32 timer;
    int32 maxFrameCount;
    int32 sparkleType;
    Player *storedPlayer;
    RingMoveTypes moveType;
    Vector2 amplitude;
    int32 speed;
    Vector2 drawPos;
    Animator animator;

    // ----------------------
    // Standard Entity Events
    // ----------------------

    // ----------------------
    // Extra Entity Functions
    // ----------------------

    // -------------
    // Object States
    // -------------

    static inline void (Ring::*State_Attracted)() = nullptr;
#if RETRO_MOD_LOADER_VER == 2
    static inline void (Ring::*Ring_State_Normal)() = nullptr;
    static inline void (Ring::*Ring_State_Lost)() = nullptr;
#endif

    // ------------------
    // Object Draw States
    // ------------------

    static inline void (Ring::*Draw_Normal)() = nullptr;

    // -------------------
    // Function Hooks
    // -------------------

    bool32 State_Attracted_Hook(bool32 skipped);
#if RETRO_MOD_LOADER_VER == 2
    bool32 Ring_State_Normal_Hook(bool32 skipped);
    bool32 Ring_State_Lost_Hook(bool32 skipped);
#elif RETRO_MOD_LOADER_VER == 3
    DECLARE_GAME_FUNC_HOOK("Ring_Collect", Collect_Hook, void, Ring *self);
#endif

    // -------------------
    // Static Declarations
    // -------------------

    MOD_DECLARE(Ring);
};
} // namespace GameLogic
