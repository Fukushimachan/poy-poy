#include "Cone.h"
#include <System/Component/ComponentModel.h>
#include <System/Component/ComponentCollisionModel.h>
#include <System/Component/ComponentObjectController.h>
#include <System/Component/ComponentCollisionCapsule.h>

//! @brief 初期化
//! @return 初期化済み
namespace Game01 {

bool Cone::Init()
{
    // 最初に1回動作する
    // ただし trueを返さなければ Initに何回も来る仕様。

    // __super::Init();    //Object::Init();と同じ
    Super::Init();

    SetName("obj");
    count_click = 0;
    float h    = sqrtf(pos_dis.x * pos_dis.x + pos_dis.y * pos_dis.y + pos_dis.z * pos_dis.z);
    auto  coll = AddComponent<ComponentCollisionCapsule>();
    SetTranslate({pos_dis.x, pos_dis.y, pos_dis.z});
    coll->SetRadius(5);
    coll->SetHeight(h + 1);
    coll->UseGravity(true);
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
    float3 npc_pos_;
    if(player) {
        //SetRotationToPositionWithLimit(player->GetTranslate(), 3.0f);
        //AddTranslate({0, 0, -enemy_speed * speed_}, true);
    }
    if(Input::IsKeyDown(KEY_INPUT_SPACE)) {
        // ジャンプを開始する
        is_jump_ = true;
        jump_speed_ = 1.0f;
    }
    if(Input::IsKeyDown(KEY_INPUT_P)) {
        count_click++;
    }
    if(is_jump_) {
        // move_.y += jump_speed_ ;
        AddTranslate({0, jump_speed_, 0});
    }
    if(is_jump_ == false) {
        npc_pos_   = npc->GetTranslate();
        float3 pos_obj = GetTranslate();
        pos_obj.y      = +pos_obj.y - 30.0f;
        pos_obj.x      = +npc_pos_.x;
        pos_obj.z      = npc_pos_.z;
        //jump_speed_    = 0.0f;
        SetTranslate(pos_obj);
    }
    // ジャンプしていたら慣性の法則にしたがって上に移動させる
    
    // if(check_hit == false) {

    //  }
    //  else {
    //if(auto model = GetComponent<ComponentModel>()) {
    // if(auto model = model_.lock()) {
    //     if(!model->IsPlaying()) {
    //         Scene::Object::Release(SharedThis());
    //     }
    // }

    // }

    //auto obj = Scene::Object::Get<Object>("obj");
}

void Cone::Draw()
{
    Super::Draw();

    float3 pos_ = GetTranslate();
    float3 position_;
    float  h    = sqrtf(pos_dis.x * pos_dis.x + pos_dis.y * pos_dis.y + pos_dis.z * pos_dis.z);
    position_.x = pos_.x - h / 2;
    position_.y = pos_.y - h / 2;
    position_.z = pos_.z;
    DrawCone3D(cast((float3)pos + position_ ), cast((float3)pos2 + position_ ), 5, 30, GetColor(0, 0, 0), GetColor(0, 0, 0), TRUE);
}

void Cone::Exit()
{
}

void Cone::OnHit(const ComponentCollision::HitInfo& hit_info)
{
    __super::OnHit(hit_info);
    auto hit_object = hit_info.hit_collision_->GetOwner();
    printfDx("HIT: %s\n", hit_object->GetNameDefault().data());
    //--------------------------------------------------------------------------
    // 地形と当たった場合は、ジャンプしてないようにする　④
    //--------------------------------------------------------------------------
    auto hit_owner_name = hit_info.hit_collision_->GetOwner()->GetName();
    if(hit_owner_name == "Ground") {
        // ジャンプを終了する
        is_jump_ = false;
    }
    //--------------------------------------------------------------------------
}

}    // namespace Game01
