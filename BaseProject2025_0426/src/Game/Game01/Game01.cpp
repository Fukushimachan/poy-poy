#include "Game01.h"
#include "Cone.h"
#include "Npc.h"
#include "Camera.h"
#include "Ground.h"

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

    auto wall = Scene::Object::Get<Walls>();

    // 毎フレーム動作する
}
void Game01::Draw()
{
}
void Game01::Exit()
{
}
}    // namespace Game01
