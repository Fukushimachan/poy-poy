#include "Wall.h"
#include "Npc.h"
#include <System/Component/ComponentModel.h>
#include <System/Component/ComponentCollisionModel.h>
#include <System/Component/ComponentCollisionCapsule.h>
//! @brief 初期化
//! @return 初期化済み

namespace Game01 {
float3 memory_pos_wall;
bool   Wall::Init()
{
    Super::Init();
    SetName("Wall");
    //カメラオブジェクト

    auto coll = AddComponent<ComponentCollisionCapsule>();
    coll->SetRadius(5.0f);
    coll->SetHeight(200.0f);
    coll->SetCollisionGroup(ComponentCollision::CollisionGroup::WALL);
    // memory_pos_wall = GetTranslate();
    return true;
}

//! @brief 更新
void Wall::Update()
{
    // 毎フレーム動作する
    Super::Update();
    auto wall = Scene::Object::Get<Wall>();
}
void Wall::Draw()
{
}
void Wall::Exit()
{
}
}    // namespace Game01
