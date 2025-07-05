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
    graund_hit = false;
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

    auto npc = Scene::Object::Get<Object>("NPC");
    auto obj = Scene::Object::Get<Cone>("obj");
    if(npc) {
        pos_npc_ = npc->GetTranslate();
    }

    if(obj) {
        if(IsKeyOn(KEY_INPUT_P)) {
            check_key = true;

            if(count_click % 2 == 1) {
                //// obj_pos_.y = pos_npc_.y + 30.0f;
                //// obj_pos_.x = 0;
                //// obj_pos_.z = 0;
                //// obj->SetTranslate(obj_pos_);
                //// auto model = GetComponent<ComponentModel>();
                //// auto dir   = -model->GetWorldMatrix().axisZ();
                //// Get_col->UseGravity(false);
                ////
                //// up_obj = true;
            }
            else if(count_click % 2 == 0) {
            }
        }
        else {
            check_key = false;
        }

        if(up_obj == false) {
            // obj_speed_ = 1.0f;
            //obj->SetSpeed(obj_speed_);
        }
        if(up_obj == true) {
            //  obj_speed_ = 0.0f;
            //  SetTranslate({obj_pos_.x + pos_.x, obj_pos_.y, obj_pos_.z + pos_.z});
            //  obj->SetSpeed(obj_speed_);
        }
        if(_isholding == IDLE) {
        }
        if(_isholding == HOLDING) {
            //obj_pos_.y = pos_npc_.y + 30.0f;
            //obj_pos_.x = 0;
            //obj_pos_.z = 0;
            //obj->SetTranslate(obj_pos_);
            //auto model = GetComponent<ComponentModel>();
            //auto dir   = -model->GetWorldMatrix().axisZ();
            //Get_col->UseGravity(false);
            //
            //up_obj = true;
        }
        if(_isholding == THROWING) {
        }
        //  obj->AddTranslate(obj_dir_move_ * obj_speed_);
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

    //printfDx("HIT: %s\n", hit_object->GetNameDefault().data());
    auto npc_move_get    = GetComponent<ComponentObjectController>();
    auto obj             = Scene::Object::Get<Cone>("obj");
    auto hit_owner_name  = hit_info.hit_collision_->GetOwner()->GetName();
    auto hit_owner_name2 = hit_info.hit_collision_->GetOwner()->GetNameDefault();
    if(obj->check_ == false && _isholding != HOLDING) {
        _isholding     = IDLE;
        obj->Cone_Mode = IDLE;
    }
    //
  

    if(IsKeyOn(KEY_INPUT_P) && _isholding == IDLE && obj->Cone_Mode == IDLE) {
        if(hit_owner_name2 == "obj") {
            auto hit_object = hit_info.hit_collision_->GetOwner();
            //const std::string eff = "data/Sample/Effects/Laser01.efkefc";
            _isholding     = HOLDING;
            npc_move_get->SetMoveSpeed(0.0f);
            count = 1;
        }
    }
    else if(IsKeyOn(KEY_INPUT_P) && _isholding == HOLDING && obj->Cone_Mode == HOLDING) {
        if(hit_owner_name2 == "obj") {
            _isholding = THROWING;
        }
    }

    if(obj->Cone_Mode == IDLE) {
        // if(_isholding == IDLE) {
        count_not_graund_hit_obj = 0;
        graund_hit               = false;
        count_xz_move            = 0;
        obj->SetDirectior(0 * 15);

        // }
    }

    if(_isholding == HOLDING) {
        if(count == 1) {
            if(obj->Cone_Mode == HOLDING) {
                if(hit_owner_name2 == "obj") {
                    auto hit_object = hit_info.hit_collision_->GetOwner();
                auto Get_col = hit_object->GetComponent<ComponentCollisionSphere>();

              
                    auto obj_get = hit_object;
                    pos_         = GetTranslate();
                    hit_object->SetTranslate({0, 0, pos_npc_.y + 25.0f});
                    Get_col->UseGravity(false);
                }

                up_obj = true;
            }
        }
        npc_move_get->SetMoveSpeed(1.0f);
    }
    if(hit_owner_name == "Ground" /* || count_not_graund_hit_obj > 60*/) {
    }
    if(_isholding == THROWING) {
        count = 0;

        float3 obj_pos_;
        if(hit_owner_name2 == "obj") {
            auto hit_object = hit_info.hit_collision_->GetOwner();
            count_xz_move++;
            auto Get_col = hit_object->GetComponent<ComponentCollisionSphere>();
            auto obj_get = hit_object;
            graund_hit   = true;
            obj_pos_     = GetTranslate() + float3{0, 30.0f, 0};

            hit_object->SetTranslate(obj_pos_);
            auto model = GetComponent<ComponentModel>();
            auto dir   = -model->GetWorldMatrix().axisZ();
            obj->SetDirectior(dir * 15);

            //if(count_xz_move > 60) {
            Get_col->UseGravity(true);
            // }
            up_obj = false;
        }
    }
    if(up_obj == true) {
        if(hit_owner_name2 == "obj") {
            if(obj->Cone_Mode == HOLDING) {
                auto hit_object = hit_info.hit_collision_->GetOwner();
                auto obj_get = hit_object;
                hit_object->SetTranslate({pos_.x, pos_npc_.y + 26.0f, pos_.z});
            }
        }
    }

    if(graund_hit == true) {
        count_not_graund_hit_obj++;
    }
    //auto obj = Scene::Object::Get<Cone>("obj");
    //auto hit_owner_name = hit_info.hit_collision_->GetOwner()->GetName();
}
}    // namespace Game01
