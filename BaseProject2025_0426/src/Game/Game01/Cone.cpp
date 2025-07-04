#include "Cone.h"
#include "Npc.h"
#include <System/Component/ComponentModel.h>
#include <System/Component/ComponentCollisionModel.h>
#include <System/Component/ComponentObjectController.h>
#include <System/Component/ComponentCollisionSphere.h>
float3  position_;
float3  pos_;
float3  npc_pos;
Object* _owner;
//! @brief 初期化
//! @return 初期化済み
namespace Game01 {
//float Cone::speed_    = 1.0f;
float Cone::radius_ = 5.0f;
bool  Cone::Init()
{
    // 最初に1回動作する
    // ただし trueを返さなければ Initに何回も来る仕様。

    // __super::Init();    //Object::Init();と同じ
    Super::Init();

    pos_ = GetTranslate();
    // pos_.x = GetRand(30);
    // pos_.z = GetRand(30);
    //position_ = GetTranslate();
    SetName("obj");
    count_click = 0;
    float h     = sqrtf(pos_dis.x * pos_dis.x + pos_dis.y * pos_dis.y + pos_dis.z * pos_dis.z);
    auto  coll  = AddComponent<ComponentCollisionSphere>();
    coll->SetTranslate({pos_.x, pos_.y, pos_.z});
    coll->SetRadius(radius_);
    //coll->SetHeight(h + 1);
    coll->UseGravity(true);
    jump_speed_ = 1.0f;
    coll->SetHitCollisionGroup((u32)ComponentCollision::CollisionGroup::ENEMY | (u32)ComponentCollision::CollisionGroup::GROUND |
                                      (u32)ComponentCollision::CollisionGroup::ITEM);
    return true;
}

//! @brief 更新
void Cone::Update()
{
    Super::Update();
    //  float3 pos_dis = pos2 - pos;
    // float  h       = sqrtf(pos_dis.x * pos_dis.x + pos_dis.y * pos_dis.y + pos_dis.z * pos_dis.z);
    auto player = Scene::Object::Get<Object>("Player");
    auto npc    = Scene::Object::Get<Object>("NPC");
    auto obj    = Scene::Object::Get<Object>("obj");
    npc_pos     = npc->GetTranslate();
    if(player) {
        //SetRotationToPositionWithLimit(player->GetTranslate(), 3.0f);
        //AddTranslate({0, 0, -enemy_speed * speed_}, true);
    }
    if(Input::IsKeyDown(KEY_INPUT_SPACE)) {
        // ジャンプを開始する
        is_jump_    = true;
        jump_speed_ = 1.0f;
    }
    if(Input::IsKeyDown(KEY_INPUT_P)) {
        count_click++;
        auto Get_col = GetComponent<ComponentCollisionSphere>();
        if(count_click % 2 == 1) {
            up_obj = true;
            // Get_col-> UseGravity(false);
        }
        else if(count_click % 2 == 0) {
            // SetSpeed(1.0f);
            up_obj = false;
            //Get_col->UseGravity(true);
        }
    }
    if(up_obj == true) {
        // SetTranslate({pos_.x + npc_pos.x, pos_.y, npc_pos.z + pos_.z});
    }

    if(is_jump_ == true) {
        // jump_speed_ = 1.0f;
    }
    if(is_jump_ == false) {
        // jump_speed_ = 0.0f;
    }
    // AddTranslate({0, jump_speed_, 0});

    //auto obj = Scene::Object::Get<Object>("obj");
    if(auto collision = collision_.lock()) {
        collision->SetRadius(radius_);
    }
    AddTranslate(direction_ * speed_);
}

void Cone::Draw()
{
    Super::Draw();

    auto scale = GetScaleAxisXYZ();
    auto color = GetColor(255, 255, 255);
    auto pos   = GetTranslate();
    DrawSphere3D(cast(pos), 5, 20, color, color, TRUE);
}

void Cone::Exit()
{
}

void Cone::OnHit(const ComponentCollision::HitInfo& hit_info)
{
    Super::OnHit(hit_info);
    auto hit_object = hit_info.hit_collision_->GetOwner();
    printfDx("HIT: %s\n", hit_object->GetNameDefault().data());
    //--------------------------------------------------------------------------
    // 地形と当たった場合は、ジャンプしてないようにする　④
    //--------------------------------------------------------------------------
    auto hit_owner_name = hit_info.hit_collision_->GetOwner()->GetNameDefault();
    if(hit_owner_name == "Ground") {
        // ジャンプを終了する
        // is_jump_ = false;
    }
    auto npc = Scene::Object::Get<Npc>("NPC");
    if(hit_owner_name == "NPC") {
      
        if(npc->count == 0) {
            check_ = true;
            npc->check(check_);

        }
    }
    else {
        check_ = false;
        npc->check(check_);
    }
    //--------------------------------------------------------------------------
}
void Cone::SetDirectior(float3 dir)
{
    direction_ = dir;
}
void Cone::SetSpeed(float speed)
{
    speed_ = 1.0f;
}

bool Cone::Check()
{
    return check_;
}

}    // namespace Game01
