#include "Wall.h"
#include "Walls.h"
#include <System/Component/ComponentModel.h>
#include <System/Component/ComponentCollisionModel.h>
#include <System/Component/ComponentCollisionCapsule.h>
#include <vector>
//! @brief 初期化
//! @return 初期化済み
namespace Game01 {

bool Walls::Init()
{
    Super::Init();
    SetName("Walls");
    //カメラオブジェクト
    /* AddComponent<ComponentModel>("data/Sample/SwordBout/Stage/ground.mv1");
    AddComponent<ComponentCollisionModel>()->AttachToModel();*/
    
    //coll->UseGravity(true);
    float3 pos[4][4];
    float  r_size_half = 10.0;
    for(int i = 0; i < 4; ++i) {
        pos[0][i] = {100.0f, r_size_half*i, -100.0f};
        pos[1][i] = {-100.0f, r_size_half*i, 100.0f};
        pos[2][i] = {-100.0f, r_size_half*i, -100.0f};
        pos[3][i] = {-100.0f, r_size_half*i, -100.0f};
    }
    float3 rot[4][4];
    for(int i = 0; i < 4; ++i) {
        rot[0][i] = {90.0f, 0.0f, 0.0f};
        rot[1][i] = {90.0f, 90.0f, 0.0f};
        rot[2][i] = {90.0f, 0.0f, 0.0f};
        rot[3][i] = {90.0f, 90.0f, 0.0f};
    }
    for(int a = 0; a < 4; ++a) {
        for(int i = 0; i < 4; ++i) {
            auto wall = Scene::Object::Create<Wall>()->SetName("Walls");

            std::vector<ObjectPtr> *wallVector = new std::vector<ObjectPtr>();
            wallVector->push_back(wall);
            auto a = wallVector[0];

            wall->SetTranslate(pos[i][a]);
            //wall->SetScaleAxisXYZ({1.0f, 10.0f, 10.0f});
            wall->SetRotationAxisXYZ(rot[i][a]);
        }
    }

    return true;
}

//! @brief 更新
void Walls::Update()
{
    // 毎フレーム動作する
    Super::Update();
     
  float3 pos[4][4];
    float  r_size_half = 10.0;
    for(int i = 0; i < 4; ++i) {
        pos[0][i] = {100.0f, r_size_half * i, -100.0f};
        pos[1][i] = {-100.0f, r_size_half * i, 100.0f};
        pos[2][i] = {-100.0f, r_size_half * i, -100.0f};
        pos[3][i] = {-100.0f, r_size_half * i, -100.0f};
    }
    float3 rot[4][4];
    for(int i = 0; i < 4; ++i) {
        rot[0][i] = {90.0f, 0.0f, 0.0f};
        rot[1][i] = {90.0f, 90.0f, 0.0f};
        rot[2][i] = {90.0f, 0.0f, 0.0f};
        rot[3][i] = {90.0f, 90.0f, 0.0f};
    }
    for(int a = 0; a < 4; ++a) {
        for(int i = 0; i < 4; ++i) {
          //  auto wall = Scene::Object::Create<Wall>()->SetName("Walls");
            auto wall = Scene::Object::Get<Walls>();

            wall->SetTranslate(pos[i][a]);
            //wall->SetScaleAxisXYZ({1.0f, 10.0f, 10.0f});
            wall->SetRotationAxisXYZ(rot[i][a]);
        }
    }
        
    
}
void Walls::Draw()
{
}
void Walls::Exit()
{
}
}    // namespace Game01
