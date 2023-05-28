#include "../GameAPI/C/GameAPI/Game.h"
#include "Ring.h"

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);

#define ADD_PUBLIC_FUNC(func) Mod.AddPublicFunction(#func, (void *)(func))
#endif

void (*Ring_Collect)(void);
void (*Ring_State_Normal)(void);
void (*Ring_State_Lost)(void);
void (*Ring_State_Attracted)(void);
void (*Ring_Draw_Normal)(void);

void InitModAPI(void)
{
    Ring_State_Normal = Mod.GetPublicFunction(NULL, "Ring_State_Normal");
    Ring_State_Lost = Mod.GetPublicFunction(NULL, "Ring_State_Lost");
    Ring_State_Attracted = Mod.GetPublicFunction(NULL, "Ring_State_Attracted");
    Ring_Draw_Normal = Mod.GetPublicFunction(NULL, "Ring_Draw_Normal");
    Ring_Collect = Mod.GetPublicFunction(NULL, "Ring_Collect");
    
    Mod.RegisterStateHook(Ring_State_Normal, Ring_Collect_RP, true);
    Mod.RegisterStateHook(Ring_State_Attracted, Ring_State_Attracted_RP, true);
    Mod.RegisterStateHook(Ring_State_Lost, Ring_Collect_RP, true);
    
    MOD_REGISTER_OBJECT_HOOK(Ring);
    MOD_REGISTER_OBJECT_HOOK(Player);
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
