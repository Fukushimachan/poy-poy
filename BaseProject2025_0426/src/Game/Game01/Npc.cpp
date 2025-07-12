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
    
    if(npc) {
        pos_npc_ = npc->GetTranslate();
    }
  
   

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

void Npc::OnHit(const ComponentCollision::HitInfo& hit_info)
{
    Super::OnHit(hit_info);

    float   max_dir = 100.0f;//一番遠くに距離のの初期値を置くを置く
    ConePtr Get_obj      = nullptr;//一番近くのオブジェクトの保管
 
    //すべて見て行って一番近くのオブジェクトを取得
    for(auto obj_ : Scene::Object::GetArray<Cone>()) {
        // ここに来る場合 obj がEnemyクラスということが保証されます。
        // nameは、必ず存在するため、オブジェクトの名前を取得できます。
        auto name = obj_->GetName();
        auto   get_obj_pos = obj_->GetTranslate();
        auto   get_npc_pos = float3{pos_npc_.x, pos_npc_.y + 28.0f, pos_npc_.z};
        float3 dis         = get_obj_pos - get_npc_pos;
        float  dir         = sqrtf(dis.x * dis.x + dis.y * dis.y + dis.z * dis.z);
        if(dir < max_dir) {
            max_dir = dir;
            Get_obj = obj_;
        }
    }
 
    auto& obj = Get_obj;//一番近くのオブジェクトを取得
    auto  Get_col    = Get_obj->GetComponent<ComponentCollisionSphere>();//重力を帰るために必要

    auto hit_owner_name2 = hit_info.hit_collision_->GetOwner()->GetNameDefault();//npcがあたっているものの名前を取得
    //地面に当たっているobjをIDLE状態にする
    if(hit_owner_name2 == "Ground") {
        for(auto obj_ : Scene::Object::GetArray<Cone>()) {
            if(Get_obj != obj_) {
                obj_->Cone_Mode = IDLE;
            }
        }
    }
    //もしnpcの状態がHOLDING状態なら一番近くで当たってるものをHOLDING状態にする
    if(_isholding == HOLDING) {
        for(auto obj_ : Scene::Object::GetArray<Cone>()) {
            if(Get_obj == obj_) {
                obj_->Cone_Mode = HOLDING;
            }
        }
    }
    //もしnpcの状態がTHROWING状態なら一番近くで当たってるものをTHROWING状態にする
    if(_isholding == THROWING) {
        for(auto obj_ : Scene::Object::GetArray<Cone>()) {
            if(Get_obj == obj_) {
                obj_->Cone_Mode = THROWING;
            }
        }
    }
    //IDLE状態のときPキー押した時HOLDING状態にする
    if(IsKeyOn(KEY_INPUT_P) && _isholding == IDLE) {
        if(hit_owner_name2 == "obj") {
            _isholding = HOLDING;
        }
    }
    //HOLDING状態のときOキー押した時THROWING状態にする
    if(IsKeyOn(KEY_INPUT_O) && _isholding == HOLDING) {
        _isholding = THROWING;
    }
    //IDLE状態のときオブジェクトを移動するのをやめさせる
    if(obj->Cone_Mode == IDLE) {
        obj->SetDirectior(0 * 15);
    }
    //HOLDING状態のとき重力をなくす
    if(_isholding == HOLDING) {
        if(obj->Cone_Mode == HOLDING) {
            Get_col->UseGravity(false);
        }
        up_obj = true;
    }
    //THROWING状態のとき投げる処理
    if(_isholding == THROWING) {
        if(obj->Cone_Mode == THROWING) {

            obj->SetTranslate(GetTranslate() + float3{0, 30.0f, 0});
            auto model = GetComponent<ComponentModel>();
            auto dir   = -model->GetWorldMatrix().axisZ();
            obj->SetDirectior(dir * 1.0f);
            Get_col->UseGravity(true);
            up_obj = false;
            
               
            _isholding = IDLE;
        }
    }
    //up_obj==true状態のときnpcの頭上に置く
    if(up_obj == true) {
        for(auto obj_ : Scene::Object::GetArray<Cone>()) {
            if(obj_->Cone_Mode == HOLDING)
                obj_->SetTranslate({pos_npc_.x, pos_npc_.y + 28.0f, pos_npc_.z});
        }
    }
}
}    // namespace Game01
