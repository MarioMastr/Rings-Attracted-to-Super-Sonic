#include "Game.h"

ObjectRing *Ring;
ObjectPlayer *Player;
ObjectZone *Zone;

#if RETRO_MOD_LOADER_VER == 2
bool32 Ring_State_Normal_Lost_Hook(bool32 skipped)
{
    RSDK_THIS(Ring);

    foreach_active(Player, player)
    {
        if (self->state != Ring_State_Attracted && player->superState == SUPERSTATE_SUPER
                 && RSDK.CheckObjectCollisionTouchCircle(self, TO_FIXED(80), player, TO_FIXED(1))) {
            self->drawPos.x    = 0;
            self->state        = Ring_State_Attracted;
            self->stateDraw    = Ring_Draw_Normal;
            self->active       = ACTIVE_NORMAL;
            self->storedPlayer = player;
            return true;
        }
    }

    return false;
}
#endif

bool32 Ring_State_Attracted_Hook(bool32 skipped)
{
    RSDK_THIS(Ring);
    EntityPlayer *player = self->storedPlayer;
    if (player->superState == SUPERSTATE_SUPER) {
        int32 startX = self->position.x;
        int32 startY = self->position.y;
        
        if (self->position.x <= player->position.x) {
            if (self->velocity.x >= 0)
                self->velocity.x += 0x3000;
            else
                self->velocity.x += 0xC000;
        }
        else {
            if (self->velocity.x <= 0)
                self->velocity.x -= 0x3000;
            else
                self->velocity.x -= 0xC000;
        }
        
        if (startY <= player->position.y) {
            if (self->velocity.y >= 0)
                self->velocity.y += 0x3000;
            else
                self->velocity.y += 0xC000;
        }
        else {
            if (self->velocity.y <= 0)
                self->velocity.y -= 0x3000;
            else
                self->velocity.y -= 0xC000;
        }
        
        self->position.x = startX + self->velocity.x;
        self->position.y = startY + self->velocity.y;

        Ring_Collect();

        self->animator.frameID = Zone->ringFrame;

        return true;
    }
    
    return false;
}
