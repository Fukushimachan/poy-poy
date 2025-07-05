#include "Game01.h"
#include "Npc.h"
#include "Camera.h"
#include "Ground.h"
#include "Cone.h"
#include "Walls.h"
//! @brief 初期化
//! @return 初期化済み

namespace Game01 {

bool Game01::Init()
{
    //Scene::Object::Create<Npc>();
    Scene::Object::Create<Camera>();
    auto npc = Scene::Object::Create<Npc>();
    for(int i = 0; i < 10; ++i) {
        auto   object = Scene::Object::Create<Cone>();
        float3 pos_;
        pos_.x = GetRand(100);
        pos_.y = 1.0f;
        pos_.z = GetRand(100);
        object->SetTranslate(pos_);
    }

    auto ground = Scene::Object::Create<Ground>()->SetName("Ground");

    ground->SetTranslate({0.0f, 0.0f, 0.0f});
    auto walls = Scene::Object::Create<Walls>()->SetName("Walls");
 //   memory_pos_wall = walls->GetTranslate();
    return true;
}

//! @brief 更新
void Game01::Update()
{
    auto object = Scene::Object::Get<Cone>();
    auto npc    = Scene::Object::Get<Npc>();
   
    auto wall    = Scene::Object::Get<Walls>();
   

    //wall->SetTranslate(memory_pos_wall); 

    //float3 pos[4];
    //float  r_size_half = 5.0;
    //pos[0]             = {100.0f, r_size_half*2, -100.0f};
    //pos[1]             = {-100.0f, r_size_half*2, 100.0f};
    //pos[2]             = {-100.0f, r_size_half * 2, -100.0f};
    //pos[3]             = {-100.0f, r_size_half * 2, -100.0f};
    //float3 rot[4];
    //rot[0] = {90.0f, 0.0f, 0.0f};
    //rot[1] = {90.0f, 90.0f, 0.0f};
    //rot[2] = {90.0f, 0.0f, 0.0f};
    //rot[3] = {90.0f, 90.0f, 0.0f};
    //for(int i = 0; i < 4; ++i) {
    //

    //    wall->SetTranslate(pos[0]);
    //    //wall->SetScaleAxisXYZ({1.0f, 10.0f, 10.0f});
    //    wall->SetRotationAxisXYZ(rot[0]);
    //}
    //   object      = npc->holding_object;
    // 毎フレーム動作する
}
void Game01::Draw()
{
}
void Game01::Exit()
{
}

//---------------------------------------------------------------------------------
//	度をラジアンに変換する関数
//---------------------------------------------------------------------------------
float TO_RADIAN(float degree)
{
    return degree * 3.14159265f / 180.0f;
}
//---------------------------------------------------------------------------------
//	ラジアンを度に変換する関数
//---------------------------------------------------------------------------------
float TO_DEGREE(float radian)
{
    return radian * 180.0f / 3.14159265f;
}
void DrawCircle3D_XZ(float3 center, float radius, int color, bool fill)
{
    VECTOR pos1;
    VECTOR pos2;
    for(int i = 0; i < 36; i++) {
        pos1.x = center.x + radius * sinf(TO_RADIAN(i * 10.0f));
        pos1.y = center.y;
        pos1.z = center.z + radius * cosf(TO_RADIAN(i * 10.0f));

        pos2.x = center.x + radius * sinf(TO_RADIAN((i + 1) * 10.0f));
        pos2.y = center.y;
        pos2.z = center.z + radius * cosf(TO_RADIAN((i + 1) * 10.0f));

        if(fill) {
            DrawTriangle3D(cast(center), pos1, pos2, color, TRUE);
        }
        else {
            DrawLine3D(pos1, pos2, color);
        }
    }
}
}    // namespace Game01
