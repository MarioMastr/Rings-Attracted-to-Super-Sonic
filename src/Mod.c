#include "Game.h"
#include "All.h"

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);

#define ADD_PUBLIC_FUNC(func) Mod.AddPublicFunction(#func, (void *)(func))
#endif

void (*Ring_Collect)(void);
void (*Ring_State_Attracted)(void);
void (*Ring_Draw_Normal)(void);
#if RETRO_MOD_LOADER_VER == 2
void (*Ring_State_Normal)(void);
void (*Ring_State_Lost)(void);
#endif

void InitModAPI(void)
{
    Ring_Collect = Mod.GetPublicFunction(NULL, "Ring_Collect");
    Ring_State_Attracted = Mod.GetPublicFunction(NULL, "Ring_State_Attracted");
    Ring_Draw_Normal = Mod.GetPublicFunction(NULL, "Ring_Draw_Normal");
#if RETRO_MOD_LOADER_VER == 2
    Ring_State_Normal = Mod.GetPublicFunction(NULL, "Ring_State_Normal");
    Ring_State_Lost = Mod.GetPublicFunction(NULL, "Ring_State_Lost");
#endif
    
    Mod.RegisterStateHook(Ring_State_Attracted, Ring_State_Attracted_Hook, true);
#if RETRO_MOD_LOADER_VER == 2
    Mod.RegisterStateHook(Ring_State_Normal, Ring_State_Normal_Lost_Hook, true);
    Mod.RegisterStateHook(Ring_State_Lost, Ring_State_Normal_Lost_Hook, true);
#endif

    MOD_REGISTER_OBJECT_HOOK(Ring);
    MOD_REGISTER_OBJECT_HOOK(Player);
    MOD_REGISTER_OBJECT_HOOK(Zone);

#if RETRO_MOD_LOADER_VER == 3
    REGISTER_FUNC_HOOK(Ring_Collect);
#endif
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
