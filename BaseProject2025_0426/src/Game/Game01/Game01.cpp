#include "Game01.h"
#include "Npc.h"
#include "Camera.h"
#include "Ground.h"
#include "Cone.h"
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
    for(int x = 0; x < ground_w_max; ++x) {
        for(int z = 0; z < ground_h_max; ++z) {
            auto ground = Scene::Object::Create<Ground>()->SetName("Ground");

            ground->SetTranslate(
                {x * ground_size - ground_w_max / 2 * ground_size + ground_size / 2, 0.0f, z * ground_size - ground_h_max / 2 * ground_size + ground_size / 2});
        }
    }
    return true;
}

//! @brief 更新
void Game01::Update()
{
    auto object = Scene::Object::Get<Cone>();
    auto npc    = Scene::Object::Get<Npc>();
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
