#include "Player.h"
#include <DxLib.h>
#include <System/Component/ComponentCollisionCapsule.h>
#include <System/Component/ComponentObjectController.h>

namespace Game01 {

bool Player::Init()
{
    Super::Init();

    SetName("Player");
    SetTranslate({0.0f, 5.0f, 0.0f});

    auto col = AddComponent<ComponentCollisionCapsule>();
    col->SetHeight(20.0f);
    col->SetRadius(8.0f);
    col->UseGravity();
    col->SetCollisionGroup(ComponentCollision::CollisionGroup::PLAYER);

    auto obj_control = AddComponent<ComponentObjectController>();
    obj_control->SetMoveSpeed(1.0f);
    obj_control->SetRotateSpeed(20.0f);

    return true;
}

void Player::Update()
{
    Super::Update();

    float3 pos = GetTranslate();

    //三角形の座標を設定
    VECTOR top   = VGet(pos.x, pos.y + 7, pos.z);
    VECTOR front = VGet(pos.x, pos.y, pos.z - 6);
    VECTOR left  = VGet(pos.x - 6, pos.y, pos.z + 6);
    VECTOR right = VGet(pos.x + 6, pos.y, pos.z + 6);

    unsigned int color = GetColor(255, 0, 0);

    // 三角形の描画
    DrawTriangle3D(top, front, left, color, TRUE);
    DrawTriangle3D(top, left, right, color, TRUE);
    DrawTriangle3D(top, right, front, color, TRUE);
    DrawTriangle3D(front, right, left, color, TRUE);
}

}    // namespace Game01
