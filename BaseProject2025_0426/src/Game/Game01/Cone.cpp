#include "Cone.h"
#include "Npc.h"
#include <System/Component/ComponentModel.h>
#include <System/Component/ComponentCollisionModel.h>
#include <System/Component/ComponentObjectController.h>
#include <System/Component/ComponentCollisionSphere.h>

float3  pos_;



//! @brief 初期化
//! @return 初期化済み
namespace Game01 {
//float Cone::speed_    = 1.0f;
float Cone::radius_ = 5.0f;
//float3 Cone::direction_ = {0, 0, 0};
bool Cone::Init()
{
    // 最初に1回動作する
    // ただし trueを返さなければ Initに何回も来る仕様。

    // __super::Init();    //Object::Init();と同じ
    Super::Init();
    Cone_Mode = IDLE;
    pos_      = GetTranslate();
  
    SetName("obj");
  
    float h     = sqrtf(pos_dis.x * pos_dis.x + pos_dis.y * pos_dis.y + pos_dis.z * pos_dis.z);
    auto  coll  = AddComponent<ComponentCollisionSphere>();
    coll->SetTranslate({pos_.x, pos_.y, pos_.z});
    coll->SetRadius(radius_);
    //coll->SetHeight(h + 1);
    coll->UseGravity(true);
    
    coll->SetCollisionGroup(ComponentCollision::CollisionGroup::ITEM);
    coll->SetHitCollisionGroup((u32)ComponentCollision::CollisionGroup::ENEMY | (u32)ComponentCollision::CollisionGroup::GROUND |
                               (u32)ComponentCollision::CollisionGroup::ITEM | (u32)ComponentCollision::CollisionGroup::WALL);
    return true;
}

//! @brief 更新
void Cone::Update()
{
  
    if(auto collision = collision_.lock()) {
        collision->SetRadius(radius_);
    }
    AddTranslate(direction_ * 15.0f);
}

void Cone::Draw()
{
    Super::Draw();

    auto scale = GetScaleAxisXYZ();
    auto color = GetColor(0, 0, 0);
    auto pos   = GetTranslate();
    DrawSphere3D(cast(pos), 5, 20, color, color, TRUE);
}

void Cone::Exit()
{
}

void Cone::OnHit(const ComponentCollision::HitInfo& hit_info)
{
    Super::OnHit(hit_info);
   
  
    auto hit_owner_name = hit_info.hit_collision_->GetOwner()->GetNameDefault();
   
 
    if(hit_owner_name == "Wall") {
        direction_ = 0;
        //Cone_Mode = IDLE;
    }
    if(hit_owner_name == "Ground") {
        direction_ = 0;
        //Cone_Mode = IDLE;
    }    //--------------------------------------------------------------------------
}
void Cone::SetDirectior(float3 dir)
{
    direction_ = dir;
}


}    // namespace Game01
