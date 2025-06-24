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
    Scene::Object::Create<Npc>();
    for(int i = 0; i < 10; ++i) {
        Scene::Object::Create<Cone>();
    }
    for(int x = 0; x < ground_w_max; ++x) {
        for(int z = 0; z < ground_h_max; ++z) {
            auto ground = Scene::Object::Create<Ground>();
            ground->SetTranslate(
                {x * ground_size - ground_w_max / 2 * ground_size + ground_size / 2, 0.0f, z * ground_size - ground_h_max / 2 * ground_size + ground_size / 2});
        }
    }
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
