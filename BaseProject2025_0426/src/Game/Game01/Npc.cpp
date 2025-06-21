#include "Npc.h"
#include <System/Component/ComponentModel.h>
#include <System/Component/ComponentCollisionModel.h>
#include <System/Component/ComponentObjectController.h>
#include <System/Component/ComponentCollisionCapsule.h>

//! @brief 初期化
//! @return 初期化済み
namespace Game01 {

bool Npc::Init()
{
    // 最初に1回動作する
    // ただし trueを返さなければ Initに何回も来る仕様。

    // __super::Init();    //Object::Init();と同じ
    Super::Init();

    //グラウンドオブジェクト

    //グラウンドオブジェクト
    // auto ground = Scene::Object::Create<Object>();
    // /*this->*/ SetName("Ground");    //this->はつけてもつけなくてもいい
    /*this->*/
    // /*this->*/ AddComponent<ComponentCollisionModel>()->AttachToModel();    //
    SetTranslate({0.0f, 0.0f, 0.0f});
    auto enemy = AddComponent<ComponentModel>("data/Sample/Enemy/Model.mv1");
    enemy->SetAnimation({
    //    //{"Attack", "data/Sample/Enemy/Anim/Attack.mv1", 1, 1.0f},
       { "walk",  "data/Sample/Enemy/Anim/Walk.mv1", 0, 1.0f},
    //    {"Death", "data/Sample/Enemy/Anim/Death.mv1", 0, 1.0f},
    //    //	{"walk", "data/Sample/Enemy/Anim/Walk.mv1", 0, 1.0f},
    });
    // enemy->PlayAnimation("walk", TRUE);
    //auto move = this->AddComponent<ComponentObjectController>();
    auto coll = AddComponent<ComponentCollisionCapsule>();
    coll->SetRadius(4.0f);
    coll->SetHeight(23.0f);
    coll->UseGravity(true);
    //move->SetMoveSpeed(0.3f);
    //move->SetRotateSpeed(20.0f);
    auto pla_move = this->AddComponent<ComponentObjectController>();
    pla_move->SetMoveSpeed(1.0f);
    pla_move->SetRotateSpeed(20.0f);
    
    // auto cam_comp = AddComponent<ComponentCamera>();

    //  SetTranslate({GetRand(500) - 200, 15.0f, GetRand(500) - 200});
    //auto cam_lock = AddComponent<ComponentSpringArm>();
    // cam_lock->SetSpringArmObject("Player");
    return true;
}

//! @brief 更新
void Npc::Update()
{
    Super::Update();

    // 毎フレーム動作する
}    // namespace Game01

void Npc::Draw()
{
    float3 vx  = float3(1.0f, 0.0f, 0.0f);
    float3 vy  = float3(0.0f, 0.0f, 1.0f);
    float3 pos = float3(0.0f, -0.0f, 0.0f);

    float3 prev_pos = pos + vx;

    for(int a = 0; a <= 90; ++a) {
        float radian = (float(a) / 90) * (2.0f * PI);

        float  x        = cosf(radian) * 150;
        float  y        = sinf(radian) * 150;
        float3 curr_pos = pos + (vx * x) + (vy * y);

        DxLib::DrawLine3D(cast(prev_pos), cast(curr_pos), GetColor(0, 255, 255));
        //  DxLib::DrawLine3D(cast(prev_pos1), cast(curr_pos1), color);
        //DxLib::DrawLine3D(cast(prev_pos2), cast(curr_pos2), color);
        prev_pos = curr_pos;
        //prev_pos2 = curr_pos2;
        //prev_pos1 = curr_pos1;
    }
    //DrawSphere3D(cast(pos), 150,10, GetColor(0, 255, 255), GetColor(0, 255, 255), TRUE);
}

void Npc::Exit()
{
}
}    // namespace Game01
