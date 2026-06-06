#include "Game.h"

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);

#define ADD_PUBLIC_FUNC(func) Mod.AddPublicFunction(#func, (void *)(func))
#endif

void (*Ring_Collect)(void);
void (*Ring_State_Attracted)(void);
void (*Ring_Draw_Normal)(void);

DEFINE_GAME_HOOK_FUNC(Ring_Collect, void, void) //  bool32 Ring_Collect_RP(bool32 skipped)
{
    RSDK_THIS(Ring);

    Original_Ring_Collect();

    foreach_active(Player, player)
    {
        if (self->state != Ring_State_Attracted && player->superState == SUPERSTATE_SUPER
                 && RSDK.CheckObjectCollisionTouchCircle(self, TO_FIXED(80), player, TO_FIXED(1))) {
            self->drawPos.x    = 0;
            self->state        = Ring_State_Attracted;
            self->stateDraw    = Ring_Draw_Normal;
            self->active       = ACTIVE_NORMAL;
            self->storedPlayer = player;
        }
    }
}

void InitModAPI(void)
{
    Ring_State_Attracted = Mod.GetPublicFunction(NULL, "Ring_State_Attracted");
    Ring_Draw_Normal = Mod.GetPublicFunction(NULL, "Ring_Draw_Normal");
    Ring_Collect = Mod.GetPublicFunction(NULL, "Ring_Collect");
    
    Mod.RegisterStateHook(Ring_State_Attracted, Ring_State_Attracted_RP, true);
    
    MOD_REGISTER_OBJECT_HOOK(Ring);
    MOD_REGISTER_OBJECT_HOOK(Player);

    REGISTER_HOOK_FUNC(Ring_Collect);
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
