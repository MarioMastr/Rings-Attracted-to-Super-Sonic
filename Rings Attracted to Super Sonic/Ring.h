#ifndef OBJ_RING_H
#define OBJ_RING_H

#include "Game.h"
#include "Player.h"

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
typedef struct {
    RSDK_OBJECT
    Hitbox hitbox;
    int32 pan;
    uint16 aniFrames;
    uint16 sfxRing;
} ObjectRing;

// Entity Class
typedef struct {
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
} EntityRing;

// Object Struct
extern ObjectRing *Ring;

// Standard Entity Events
void Ring_Update(void);
void Ring_LateUpdate(void);
void Ring_StaticUpdate(void);
void Ring_Draw(void);
void Ring_Create(void *data);
void Ring_StageLoad(void);
#if RETRO_INCLUDE_EDITOR
void Ring_EditorDraw(void);
void Ring_EditorLoad(void);
#endif
void Ring_Serialize(void);

// Extra Entity Functions
void Ring_DebugSpawn(void);
void Ring_DebugDraw(void);

extern void (*Ring_Collect)(void);
void Ring_Collect_RP(void);
void Ring_Set_Attraction(void);
void Ring_LoseRings(EntityPlayer *player, int32 rings, uint8 cPlane);
void Ring_LoseHyperRings(EntityPlayer *player, int32 rings, uint8 cPlane);
void Ring_FakeLoseRings(Vector2 *position, int32 ringCount, uint8 drawGroup);

void Ring_CheckObjectCollisions(int32 x, int32 y);

// States
extern void (*Ring_State_Normal)(void);
void Ring_State_Normal_RP(void);
void Ring_State_Linear(void);
void Ring_State_Circular(void);
void Ring_State_Path(void);
void Ring_State_Track(void);
extern void (*Ring_State_Lost)(void);
void Ring_State_LostFX(void);
void Ring_State_Big(void);
extern void (*Ring_State_Attracted)(void);
void Ring_State_Attracted_RP(void);
extern void (*Ring_State_Sparkle)(void);

// Draw States
extern void (*Ring_Draw_Normal)(void);
void Ring_Draw_Oscillating(void);
extern void (*Ring_Draw_Sparkle)(void);

#endif //! OBJ_RING_H
