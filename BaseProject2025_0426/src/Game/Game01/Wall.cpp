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
    /* AddComponent<ComponentModel>("data/Sample/SwordBout/Stage/ground.mv1");
    AddComponent<ComponentCollisionModel>()->AttachToModel();*/
    auto coll = AddComponent<ComponentCollisionCapsule>();
    /*std::vector<ObjectPtr> *wallVector = new std::vector<ObjectPtr>();
    wallVector->push_back(coll);
    auto a = wallVector[0];*/
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
    //  auto get_pos = GetTranslate();

    //  SetTranslate(memory_pos_wall);
    //float3 pos[4];
    //float  r_size_half = 5.0;
    //pos[0]             = {100.0f, r_size_half * 2, -100.0f};
    //pos[1]             = {-100.0f, r_size_half * 2, 100.0f};
    //pos[2]             = {-100.0f, r_size_half * 2, -100.0f};
    //pos[3]             = {-100.0f, r_size_half * 2, -100.0f};
    //float3 rot[4];
    //rot[0] = {90.0f, 0.0f, 0.0f};
    //rot[1] = {90.0f, 90.0f, 0.0f};
    //rot[2] = {90.0f, 0.0f, 0.0f};
    //rot[3] = {90.0f, 90.0f, 0.0f};
    //for(int i = 0; i < 4; ++i) {
    //    this->SetTranslate(pos[i]);
    //    //wall->SetScaleAxisXYZ({1.0f, 10.0f, 10.0f});
    //    this->SetRotationAxisXYZ(rot[i]);
    //}
}
void Wall::Draw()
{
}
void Wall::Exit()
{
}
}    // namespace Game01
