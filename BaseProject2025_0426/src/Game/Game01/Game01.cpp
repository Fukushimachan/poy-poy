#include "Game01.h"
#include "Cone.h"
#include "Npc.h"
#include "Camera.h"
#include "Ground.h"

#include "Walls.h"
#include "Player.h"
#include "ShapeSpawner.h"
#include "SimpleObjects.h"
//! @brief 初期化
//! @return 初期化済み

namespace Game01 {

bool Game01::Init()
{
    SetUseLighting(TRUE);
    SetLightEnable(TRUE);

    SetLightDirection(VGet(-1.0f, -1.0f, -1.0f));

    SetLightDifColor({0.8f, 0.8f, 0.8f, 1.0f});

    SetLightAmbColor({0.4f, 0.4f, 0.4f, 1.0f});

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

    //プレイヤー
    Scene::Object::Create<Player>();

    Scene::Object::Create<ShapeSpawner>();

    //三角形と球体
    auto obj1 = Scene::Object::Create<SimpleObjects>();
    obj1->SetShape(SimpleObjects::ShapeType::Tetrahedron);
    obj1->SetTranslate({-20.0f, 60.0f, 0.0f});
    auto ground = Scene::Object::Create<Ground>()->SetName("Ground");

    auto obj2 = Scene::Object::Create<SimpleObjects>();
    obj2->SetShape(SimpleObjects::ShapeType::Sphere);
    obj2->SetTranslate({20.0f, 60.0f, 0.0f});

    // -----------------------------------------------------------------------------------------
    // 空オブジェクト(SkyDome)の追加 ④
    // -----------------------------------------------------------------------------------------
    {
        auto obj = Scene::Object::Create<Object>()    //< Object作成
                       ->SetName("Sky");

        // オブジェクトにモデル能力を追加します
        obj->AddComponent<ComponentModel>("data/Sample/SwordBout/Stage/Stage00_sky.mv1");
        obj->SetTranslate({0, -300.0f, 0});
    }


    ground->SetTranslate({0.0f, 0.0f, 0.0f});
    auto walls = Scene::Object::Create<Walls>()->SetName("Walls");
  
    return true;
}

//! @brief 更新
void Game01::Update()
{
    // 毎フレーム動作する
    //--------------------------------------------------------------
    // 雲を動かすように空をY軸で少しづつ回転させます　⑤
    //--------------------------------------------------------------
    if(auto sky = Scene::Object::Get<Object>("Sky")) {
        sky->AddRotationAxisXYZ({0, 0.1f, 0});
    }
    //--------------------------------------------------------------
}
void Game01::Draw()
{
}
void Game01::Exit()
{
}
}    // namespace Game01
