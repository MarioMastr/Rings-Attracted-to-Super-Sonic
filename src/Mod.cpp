#include "Game.hpp"
#include "All.hpp"

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);

#define ADD_PUBLIC_FUNC(func) Mod::PublicFunctions::Add(#func, &func)
#define REGISTER_STATE_HOOK(state, priority) Mod::RegisterStateHook<&state##_Hook>(state, priority)
#endif

using namespace GameLogic;

void InitModAPI(void)
{
    Ring::State_Attracted = Mod::PublicFunctions::Get(nullptr, "Ring_State_Attracted");
    Ring::Draw_Normal = Mod::PublicFunctions::Get(nullptr, "Ring_Draw_Normal");
    REGISTER_STATE_HOOK(Ring::State_Attracted, true);
#if RETRO_MOD_LOADER_VER == 2
    Ring::State_Normal = Mod::PublicFunctions::Get(nullptr, "Ring_State_Normal");
    Ring::State_Lost = Mod::PublicFunctions::Get(nullptr, "Ring_State_Lost");
    REGISTER_STATE_HOOK(Ring::State_Normal, true);
    REGISTER_STATE_HOOK(Ring::State_Lost, true);
#elif RETRO_MOD_LOADER_VER == 3
    REGISTER_FUNC_HOOK(Ring::Collect_Hook);
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

    globals = Mod::GetGlobals<GlobalVariables>();

	Mod::modID = id;

    InitModAPI();

    return true;
}
#endif
