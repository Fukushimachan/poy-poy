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

int    count_click;
float3 pos_obj_;
float3 pos_npc_;
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
                //obj_pos_ = GetTranslate() + float3{0, 30.0f, 0};
                //obj->SetTranslate(obj_pos_);
                //auto model = GetComponent<ComponentModel>();
                //auto dir   = -model->GetWorldMatrix().axisZ();
                //obj->SetDirectior(dir * 15);
                //Get_col->UseGravity(true);
                //up_obj = false;
                ////   get_coll_obj->UseGravity(true);
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
            // obj_pos_ = GetTranslate() + float3{0, 30.0f, 0};
            // obj->SetTranslate(obj_pos_);
            // auto model = GetComponent<ComponentModel>();
            // auto dir   = -model->GetWorldMatrix().axisZ();
            // obj->SetDirectior(dir * 15);
            // Get_col->UseGravity(true);
            // up_obj = false;
        }
        //  obj->AddTranslate(obj_dir_move_ * obj_speed_);
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
void Npc::OnHit(const ComponentCollision::HitInfo& hit_info)
{
    //
    __super::OnHit(hit_info);
    auto hit_object = hit_info.hit_collision_->GetOwner();
    printfDx("HIT: %s\n", hit_object->GetNameDefault().data());

    auto   obj            = Scene::Object::Get<Cone>("obj");
    auto   hit_owner_name = hit_info.hit_collision_->GetOwner()->GetName();
    float3 obj_pos_;
    float3 obj_dir_move_;
    float  obj_speed_;
    auto   Get_col = hit_object->GetComponent<ComponentCollisionSphere>();
    if(hit_owner_name == "obj") {
        auto obj_get = hit_object;
        if(IsKeyOn(KEY_INPUT_P) && _isholding == IDLE) {
            _isholding = HOLDING;
        }
        else if(IsKeyOn(KEY_INPUT_P) && _isholding == HOLDING) {
            _isholding = THROWING;
        }

        if(_isholding == IDLE) {
            count_not_graund_hit_obj = 0;
        }
        if(_isholding == HOLDING) {
            pos_ = GetTranslate();
            hit_object->SetTranslate({0, 0, pos_npc_.y + 30.0f});
            //hit_object->SetTranslate(hit_object);
            auto model = hit_object->GetComponent<ComponentModel>();
            // auto dir   = -model->GetWorldMatrix().axisZ();
            Get_col->UseGravity(false);

            up_obj = true;
        }
        if(_isholding == THROWING) {
            graund_hit = true;

            obj_pos_ = GetTranslate() + float3{0, 30.0f, 0};
            hit_object->SetTranslate(obj_pos_);
            auto model = GetComponent<ComponentModel>();
             auto dir   = -model->GetWorldMatrix().axisZ();
              obj->SetDirectior(dir * 15);
            Get_col->UseGravity(true);
            up_obj = false;
        }
        if(up_obj == true) {
            //  obj_speed_ = 0.0f;
            hit_object->SetTranslate({pos_.x, pos_npc_.y + 26.0f, pos_.z});
            //  obj->SetSpeed(obj_speed_);
        }
    }
    if(graund_hit == true) {
        count_not_graund_hit_obj++;
    }
    if(hit_owner_name == "Ground" || count_not_graund_hit_obj > 180) {
        _isholding = IDLE;
        graund_hit = false;
    }

    // hit_object->SetTranslate();
    //--------------------------------------------------------------------------
    // 地形と当たった場合は、ジャンプしてないようにする　④
    //--------------------------------------------------------------------------

    //--------------------------------------------------------------------------
}
}    // namespace Game01
