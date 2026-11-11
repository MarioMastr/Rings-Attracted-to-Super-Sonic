#include "Ring.hpp"
#include "Zone.hpp"

using namespace RSDK;

namespace GameLogic
{

// -------------------
// Object Registration
// -------------------

MOD_REGISTER_OBJECT(Ring);

// -------------
// Extra Entity Functions
// -------------

// -------------
// Object States
// -------------

// -------------
// Object Draw States
// -------------

// -------------------
// Function Hooks
// -------------------

bool32 Ring::State_Attracted_Hook(bool32 skipped)
{
    Player *player = this->storedPlayer;
    if (player->superState == Player::SUPERSTATE_SUPER) {
        int32 startX = this->position.x;
        int32 startY = this->position.y;
        
        if (this->position.x <= player->position.x) {
            if (this->velocity.x >= 0)
                this->velocity.x += 0x3000;
            else
                this->velocity.x += 0xC000;
        }
        else {
            if (this->velocity.x <= 0)
                this->velocity.x -= 0x3000;
            else
                this->velocity.x -= 0xC000;
        }
        
        if (startY <= player->position.y) {
            if (this->velocity.y >= 0)
                this->velocity.y += 0x3000;
            else
                this->velocity.y += 0xC000;
        }
        else {
            if (this->velocity.y <= 0)
                this->velocity.y -= 0x3000;
            else
                this->velocity.y -= 0xC000;
        }
        
        this->position.x = startX + this->velocity.x;
        this->position.y = startY + this->velocity.y;

        this->animator.frameID = Zone::sVars->ringFrame;

        return true;
    }

    return false;
}

#if RETRO_MOD_LOADER_VER == 2
bool32 Ring::State_Normal_Lost_Hook(bool32 skipped)
{
    foreach_active(Player, player)
    {
        if (!this->state.Matches(&Ring::State_Attracted) && player->superState == Player::SUPERSTATE_SUPER
                 && this->CheckCollisionTouchCircle(TO_FIXED(80), player, TO_FIXED(1))) {
            this->drawPos.x    = 0;
            this->state.Set(&Ring::State_Attracted);
            this->stateDraw.Set(&Ring::Draw_Normal);
            this->active       = ACTIVE_NORMAL;
            this->storedPlayer = player;
            foreach_return true;
        }
    }

    return false;
}
#elif RETRO_MOD_LOADER_VER == 3
DEFINE_PUBLIC_FUNC_HOOK(Ring::Collect_Hook, void, Ring *self)
{
	Original(self);

    foreach_active(Player, player)
    {
        if (!self->state.Matches(&Ring::State_Attracted) && player->superState == Player::SUPERSTATE_SUPER
                 && self->CheckCollisionTouchCircle(TO_FIXED(80), player, TO_FIXED(1))) {
            self->drawPos.x    = 0;
            self->state.Set(&Ring::State_Attracted);
            self->stateDraw.Set(&Ring::Draw_Normal);
            self->active       = ACTIVE_NORMAL;
            self->storedPlayer = player;
            foreach_return;
        }
    }
}
#endif

} // namespace GameLogic
