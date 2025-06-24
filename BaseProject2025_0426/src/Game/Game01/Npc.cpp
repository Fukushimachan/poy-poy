#include "Npc.h"
#include <System/Component/ComponentModel.h>
#include <System/Component/ComponentCollisionModel.h>
#include <System/Component/ComponentObjectController.h>
#include <System/Component/ComponentCollisionCapsule.h>

//! @brief 初期化
//! @return 初期化済み
//! int
float3 set_obj_pos;
bool   check_key = false;

bool   up_obj = false;
int    count_click;
float3 pos_obj_;
float3 pos_npc_;

float3 player_move_pos;

namespace Game01 {

bool Npc::Init()
{
    Super::Init();
    SetName("NPC");
    //エネミーのオブジェクト
    SetTranslate({0.0f, 0.0f, 0.0f});
    auto enemy = AddComponent<ComponentModel>("data/Sample/Enemy/Model.mv1");
    enemy->SetAnimation({

        {"walk", "data/Sample/Enemy/Anim/Walk.mv1", 0, 1.0f},
    });
    //コリジョンの追加
    auto coll = AddComponent<ComponentCollisionCapsule>();
    coll->SetRadius(4.0f);
    coll->SetHeight(23.0f);
    coll->UseGravity(true);
    //とりあえず十字キーで動く処理
    auto pla_move = this->AddComponent<ComponentObjectController>();
    pla_move->SetMoveSpeed(1.0f);
    pla_move->SetRotateSpeed(20.0f);

    auto npc = Scene::Object::Get<Object>("NPC");
    auto obj = Scene::Object::Get<Object>("obj");
    if(obj) {
        pos_obj_ = obj->GetTranslate();
    }
    if(npc) {
        pos_npc_ = npc->GetTranslate();
    }
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
    pos_     = GetTranslate();
    auto npc = Scene::Object::Get<Object>("NPC");
    auto obj = Scene::Object::Get<Object>("obj");
    if(npc) {
        pos_npc_ = npc->GetTranslate();
    }
    if(obj) {
        if(IsKeyOn(KEY_INPUT_P)) {
            check_key = true;
            count_click++;
            if(count_click % 2 == 1) {
                pos_obj_.y = pos_npc_.y + pos_obj_.y + 30.0f/*+( pos_npc_.x - player_move_pos.x)*/;
                pos_obj_.x =/* pos_npc_.x*/ + pos_obj_.x -  player_move_pos.x;
                pos_obj_.z =/* pos_npc_.z +*/ pos_obj_.z -  player_move_pos.z;
                up_obj     = true;
            }
            if(count_click % 2 == 0) {
                pos_obj_.y      = +pos_obj_.y - 30.0f;
                pos_obj_.x      = +pos_obj_.x;
                pos_obj_.z      = +pos_obj_.z;
                player_move_pos = pos_obj_;
               // player_move_pos = {0.0f, 0.0f, 0.0f};
                up_obj          = false;
            }
        }
        else {
            check_key = false;
            if(obj) {

                //  obj->SetTranslate({pos_obj_.x, pos_obj_.y, pos_obj_.z});
                //AddTranslate({0, 0, -enemy_speed * speed_}, true);
            }
        }
        if(up_obj == true) {
            obj->SetTranslate({pos_obj_.x + pos_npc_.x, pos_obj_.y, pos_obj_.z + pos_npc_.z});
        }
        if(check_key == false) {
            //set_obj_pos = pos_;
        }
        if(up_obj == false) {
            obj->SetTranslate({pos_obj_.x, pos_obj_.y, pos_obj_.z});
        }

        //AddTranslate({0, 0, -enemy_speed * speed_}, true);
    }
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

        prev_pos = curr_pos;
    }
}

void Npc::Exit()
{
}
}    // namespace Game01
