#include "Game.h"
#include "Ring.h"

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);

#define ADD_PUBLIC_FUNC(func) Mod.AddPublicFunction(#func, (void *)(func))
#endif

void (*Ring_State_Attracted)(void);
void (*Ring_Collect)(void);
void (*Ring_State_Lost)(void);
void (*Player_GiveRings)(EntityPlayer *player, int32 amount, bool32 playSfx);
bool32 (*Player_CheckCollisionTouch)(EntityPlayer *player, void *e, Hitbox *entityHitbox);
void (*Ring_Draw_Normal)(void);
void (*Ring_State_Normal)(void);
void (*Ring_Draw_Sparkle)(void);
void (*Ring_State_Sparkle)(void);

void InitModAPI(void)
{
    Ring_State_Attracted       = Mod.GetPublicFunction(NULL, "Ring_State_Attracted");
    Ring_Collect               = Mod.GetPublicFunction(NULL, "Ring_Collect");
    Ring_State_Lost            = Mod.GetPublicFunction(NULL, "Ring_State_Lost");
    Player_GiveRings           = Mod.GetPublicFunction(NULL, "Player_GiveRings");
    Ring_Draw_Normal           = Mod.GetPublicFunction(NULL, "Ring_Draw_Normal");
    Ring_Draw_Sparkle          = Mod.GetPublicFunction(NULL, "Ring_Draw_Sparkle");
    Ring_State_Sparkle         = Mod.GetPublicFunction(NULL, "Ring_State_Sparkle");
    Ring_State_Normal          = Mod.GetPublicFunction(NULL, "Ring_State_Normal");
    Player_CheckCollisionTouch = Mod.GetPublicFunction(NULL, "Player_CheckCollisionTouch");
    
    Mod.RegisterStateHook(Ring_State_Normal, Ring_State_Normal_RP, true);
}

#if RETRO_USE_MOD_LOADER
void InitModAPI(void);

bool32 LinkModLogic(EngineInfo *info, const char *id)
{
#if MANIA_USE_PLUS
    LinkGameLogicDLL(info);
#else
    LinkGameLogicDLL(*info);
#endif

    globals = Mod.GetGlobals();

    modID = id;

    InitModAPI();

    return true;
}
#endif
