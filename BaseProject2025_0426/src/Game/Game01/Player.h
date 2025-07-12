#pragma once
#include <System/Scene.h>

namespace Game01 {
USING_PTR(Player);

class Player : public Object
{
public:
    BP_OBJECT_DECL(Player, u8"Game01のplayer");

    bool Init() override;

    void Update() override;

private:
    bool is_grounded_ = false;    // 地面にいるか
};
}    // namespace Game01
