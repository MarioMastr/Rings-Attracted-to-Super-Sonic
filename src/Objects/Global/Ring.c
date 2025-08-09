#include "Game.h"

ObjectRing *Ring;
ObjectPlayer *Player;
ObjectZone *Zone;

bool32 Ring_State_Attracted_RP(bool32 skipped)
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
