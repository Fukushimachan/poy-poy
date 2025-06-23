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
    
    float  h       = sqrtf(pos_dis.x * pos_dis.x + pos_dis.y * pos_dis.y + pos_dis.z * pos_dis.z);
    auto   coll    = AddComponent<ComponentCollisionCapsule>();
    SetTranslate({pos_dis.x, pos_dis.y, pos_dis.z/h/2});
    coll->SetRadius(5);
    coll->SetHeight(h);
  
    return true;
}

//! @brief 更新
void Cone::Update()
{
    Super::Update();
  //  float3 pos_dis = pos2 - pos;
   // float  h       = sqrtf(pos_dis.x * pos_dis.x + pos_dis.y * pos_dis.y + pos_dis.z * pos_dis.z);
    auto player = Scene::Object::Get<Object>("Player");
    auto npc = Scene::Object::Get<Object>("NPC");
    auto obj = Scene::Object::Get<Object>("obj");
  
   if(player) {
       
        SetRotationToPositionWithLimit(player->GetTranslate(), 3.0f);
        //AddTranslate({0, 0, -enemy_speed * speed_}, true);
    }
    if(npc) {
        float3 pos_ = npc->GetTranslate();
        if(IsKeyRepeat(KEY_INPUT_P)) {
          
            obj->SetTranslate({pos_dis.x + pos_.x, pos_dis.y + 10.0f + pos_.y, pos_dis.z+ pos_.z});
        }
        else {
            if(obj) {
                obj->SetTranslate(pos_dis);
                //AddTranslate({0, 0, -enemy_speed * speed_}, true);
            }
        }
     
        //AddTranslate({0, 0, -enemy_speed * speed_}, true);
    }
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
    if(obj) {
        float3 pos_ = obj->GetTranslate();
        DrawCone3D(cast(pos + pos_), cast(pos2 + pos_), 5, 10, GetColor(0, 0, 0), GetColor(0, 0, 0), TRUE);
    }
}

void Cone::Draw()
{
    Super::Draw();
    //auto obj = Scene::Object::Get<Object>("obj");
 //   if(obj) {
 //       float3 pos_ = obj->GetTranslate();
//        DrawCone3D(cast(pos + pos_), cast(pos2 + pos_), 5, 10, GetColor(0, 0, 0), GetColor(0, 0, 0), TRUE);
 //   }
}

void Cone::Exit()
{
}
}    // namespace Game01
