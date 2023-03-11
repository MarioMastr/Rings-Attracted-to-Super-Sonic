#include "Player.h"
#include "Ring.h"

ObjectRing *Ring;
ObjectPlayer *Player;

void Ring_Collect_RP(void)
{
    RSDK_THIS(Ring);
    ObjectZone *Zone = Mod.FindObject("Zone");
    ObjectPlayer *Player = Mod.FindObject("Player");

    int32 storeX = self->position.x;
    int32 storeY = self->position.y;

    if (self->drawPos.x)
        self->position = self->drawPos;

    foreach_active(Player, player)
    {
        if (Player_CheckCollisionTouch(player, self, &Ring->hitbox)) {
            if (!self->planeFilter || player->collisionPlane == (((uint8)self->planeFilter - 1) & 1)) {
                if (player->sidekick)
                    player = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);

                int32 ringAmount = 1;
                if (self->type == RING_TYPE_BIG) {
                    player->ringExtraLife += 100 * (self->ringAmount / 100);
                    ringAmount = self->ringAmount;
                }
                Player_GiveRings(player, ringAmount, true);

                int32 max = TO_FIXED(8);
                if (self->type == RING_TYPE_BIG)
                    max = TO_FIXED(16);

                int32 cnt = 4 * (self->type == RING_TYPE_BIG) + 4;
                int32 min = -max;
                for (int32 i = 0; i < cnt; ++i) {
                    int32 x             = self->position.x + RSDK.Rand(min, max);
                    int32 y             = self->position.y + RSDK.Rand(min, max);
                    EntityRing *sparkle = CREATE_ENTITY(Ring, NULL, x, y);

                    sparkle->state     = Ring_State_Sparkle;
                    sparkle->stateDraw = Ring_Draw_Sparkle;
                    sparkle->active    = ACTIVE_NORMAL;
                    sparkle->visible   = false;
                    if (self->drawGroup == 1)
                        sparkle->drawGroup = 1;
                    else
                        sparkle->drawGroup = Zone->objectDrawGroup[1];

                    RSDK.SetSpriteAnimation(Ring->aniFrames, RING_TYPE_SPARKLE1 + (i % 3), &sparkle->animator, true, 0);
                    int32 frameCount = sparkle->animator.frameCount;
                    if (sparkle->animator.animationID == 2) {
                        sparkle->alpha = 0xE0;
                        frameCount >>= 1;
                    }
                    sparkle->maxFrameCount  = frameCount - 1;
                    sparkle->animator.speed = RSDK.Rand(6, 8);
                    sparkle->timer          = 2 * i++;
                }

                destroyEntity(self);
                self->active = ACTIVE_DISABLED; // not sure what the purpose of this is but sure
                foreach_return;
            }
        }
        else if (self->state != Ring_State_Attracted && (player->shield == SHIELD_LIGHTNING || player->superState == SUPERSTATE_SUPER)
                 && RSDK.CheckObjectCollisionTouchCircle(self, TO_FIXED(80), player, TO_FIXED(1))) {
            self->drawPos.x    = 0;
            self->state        = Ring_State_Attracted;
            self->stateDraw    = Ring_Draw_Normal;
            self->active       = ACTIVE_NORMAL;
            self->storedPlayer = player;
            foreach_return;
        }
    }

    self->position.x = storeX;
    self->position.y = storeY;
}

void Ring_State_Normal_RP(void)
{
    RSDK_THIS(Ring);
    EntityPlayer *player = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
    ObjectZone *Zone = Mod.FindObject("Zone");
    Ring_Collect();
    self->animator.frameID = Zone->ringFrame;
    if (self->state != Ring_State_Attracted && (player->shield == SHIELD_LIGHTNING || player->superState == SUPERSTATE_SUPER)
             && RSDK.CheckObjectCollisionTouchCircle(self, TO_FIXED(80), player, TO_FIXED(1)))
        self->state        = Ring_State_Attracted_RP;
}

void Ring_State_Attracted_RP(void)
{
    RSDK_THIS(Ring);
    ObjectZone *Zone = Mod.FindObject("Zone");
    EntityPlayer *player = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
    if (player->shield == SHIELD_LIGHTNING) {
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
    }
    else {
        self->state          = Ring_State_Lost;
        self->animator.speed = 0x80;
        self->alpha          = 0x100;
        self->inkEffect      = INK_ALPHA;
    }

    Ring_Collect_RP();

    self->animator.frameID = Zone->ringFrame;
}
