#include "Game01.h"
#include "Npc.h"
#include "Camera.h"
#include "Ground.h"
#include "Player.h"
#include "ShapeSpawner.h"
#include "SimpleObjects.h"
//! @brief 初期化
//! @return 初期化済み
namespace Game01 {

bool Game01::Init()
{
    Scene::Object::Create<Camera>();
    Scene::Object::Create<Npc>();
    for(int x = 0; x < ground_w_max; ++x) {
        for(int z = 0; z < ground_h_max; ++z) {
            auto ground = Scene::Object::Create<Ground>();
            ground->SetTranslate(
                {x * ground_size - ground_w_max / 2 * ground_size + ground_size / 2, 0.0f, z * ground_size - ground_h_max / 2 * ground_size + ground_size / 2});
        }
    }

    //プレイヤー
    Scene::Object::Create<Player>();

    Scene::Object::Create<ShapeSpawner>();


    //三角形と球体
    auto obj1 = Scene::Object::Create<SimpleObjects>();
    obj1->SetShape(SimpleObjects::ShapeType::Tetrahedron);
    obj1->SetTranslate({-20.0f, 60.0f, 0.0f});

    auto obj2 = Scene::Object::Create<SimpleObjects>();
    obj2->SetShape(SimpleObjects::ShapeType::Sphere);
    obj2->SetTranslate({20.0f, 60.0f, 0.0f});

    return true;
}

//! @brief 更新
void Game01::Update()
{
    // 毎フレーム動作する
}
void Game01::Draw()
{
}
void Game01::Exit()
{
}
}    // namespace Game01
