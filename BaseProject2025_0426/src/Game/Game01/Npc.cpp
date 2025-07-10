#include "Npc.h"
#include "Cone.h"
#include <System/Component/ComponentModel.h>
#include <System/Component/ComponentCollisionModel.h>
#include <System/Component/ComponentObjectController.h>
#include <System/Component/ComponentCollisionCapsule.h>
#include <System/Component/ComponentCollisionSphere.h>
//! @brief 初期化
//! @return 初期化済み
//! int
float3 set_obj_pos;
bool   check_key = false;

int        count_click;
float3     pos_obj_;
float3     pos_npc_;
static int count = 0;
namespace Game01 {

bool Npc::Init()
{
    Super::Init();
    _isholding = IDLE;
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
    auto pla_move = AddComponent<ComponentObjectController>();
    pla_move->SetMoveSpeed(1.0f);
    pla_move->SetRotateSpeed(20.0f);

    coll->SetCollisionGroup(ComponentCollision::CollisionGroup::ENEMY);

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

    auto npc          = Scene::Object::Get<Object>("NPC");
    auto npc_move_get = GetComponent<ComponentObjectController>();

    auto obj = Scene::Object::Get<Cone>("obj");
    if(npc) {
        pos_npc_ = npc->GetTranslate();
    }

    if(obj) {
    }
    // 毎フレーム動作する
}    // namespace Game01

void Npc::Draw()
{
    DrawFormatString(30, 30, GetColor(255, 255, 255), "%d", _isholding);
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
bool Npc::check(bool check)
{
    check_ = check;
    return check_;
}
void Npc::OnHit(const ComponentCollision::HitInfo& hit_info)
{
    Super::OnHit(hit_info);

    auto npc_move_get = GetComponent<ComponentObjectController>();
    auto obj          = Scene::Object::Get<Cone>("obj");
    auto hit_owner_name  = hit_info.hit_collision_->GetOwner()->GetName();
    auto hit_owner_name2 = hit_info.hit_collision_->GetOwner()->GetNameDefault();
    if(obj->check_ == false && _isholding != HOLDING) {
        _isholding     = IDLE;
        obj->Cone_Mode = IDLE;
    }
    if(IsKeyOn(KEY_INPUT_P) && _isholding == IDLE && obj->Cone_Mode == IDLE) {
        if(hit_owner_name2 == "obj") {
            auto hit_object = hit_info.hit_collision_->GetOwner();

            _isholding = HOLDING;
            npc_move_get->SetMoveSpeed(0.0f);
            count = 1;
        }
    }
    else if(IsKeyOn(KEY_INPUT_O) && _isholding == HOLDING && obj->Cone_Mode == HOLDING) {
        if(hit_owner_name2 == "obj") {
            _isholding     = THROWING;
            obj->Cone_Mode = THROWING;
        }
    }

    if(obj->Cone_Mode == IDLE) {
        obj->SetDirectior(0 * 15);
    }

    if(_isholding == HOLDING) {
        auto hit_object = hit_info.hit_collision_->GetOwner();
        if(obj->Cone_Mode == HOLDING) {
            if(hit_owner_name2 == "obj") {
                auto Get_col = hit_object->GetComponent<ComponentCollisionSphere>();

                auto obj_get = hit_object;
                  hit_object->SetTranslate({0, 0, pos_npc_.y + 25.0f});

                Get_col->UseGravity(false);
            }
        }
        up_obj = true;

        npc_move_get->SetMoveSpeed(1.0f);
    }

    if(_isholding == THROWING) {
        if(obj->Cone_Mode == THROWING) {
            count = 0;
            throwing_time++;
            float3 obj_pos_;
            if(hit_owner_name2 == "obj") {
                auto hit_object = hit_info.hit_collision_->GetOwner();
                auto Get_col    = hit_object->GetComponent<ComponentCollisionSphere>();
                auto obj_get    = hit_object;

                obj_pos_ = GetTranslate() + float3{0, 30.0f, 0};

                hit_object->SetTranslate(obj_pos_);
                auto model = GetComponent<ComponentModel>();
                auto dir   = -model->GetWorldMatrix().axisZ();
                obj->SetDirectior(dir * 15);

                Get_col->UseGravity(true);
                up_obj = false;
            }
            if(throwing_time > 90) {
                _isholding    = IDLE;
                throwing_time = 0;
            }
        }
    }
    if(up_obj == true) {
        if(hit_owner_name2 == "obj") {
            if(obj->Cone_Mode == HOLDING) {
                auto hit_object = hit_info.hit_collision_->GetOwner();
                auto obj_get    = hit_object;
                hit_object->SetTranslate({pos_.x, pos_npc_.y + 26.0f, pos_.z});
            }
        }
    }

    //auto obj = Scene::Object::Get<Cone>("obj");
    //auto hit_owner_name = hit_info.hit_collision_->GetOwner()->GetName();
}
}    // namespace Game01
