#include "Player.h"
#include "SimpleObjects.h"
#include <DxLib.h>
#include <System/Component/ComponentModel.h>
#include <System/Component/ComponentCollisionModel.h>
#include <System/Component/ComponentCollisionCapsule.h>
#include <System/Component/ComponentObjectController.h>

// 角度をラジアンに変換する関数
constexpr float TO_RADIAN(float degree)
{
    return degree * 3.1415926f / 180.0f;
}

namespace Game01 {

bool Player::Init()
{
    Super::Init();

    SetName("Player");
    SetTranslate({0.0f, -7.0f, 0.0f});

    auto col = AddComponent<ComponentCollisionCapsule>();
    col->SetHeight(20.0f);
    col->SetRadius(4.0f);
    col->UseGravity();
    col->SetCollisionGroup(ComponentCollision::CollisionGroup::PLAYER);

    auto model_comp = AddComponent<ComponentModel>("data/Sample/Player/model.mv1");
    model_comp->UseShader(false);
    model_comp->SetAnimation({
        {"idle", "data/Sample/Player/Anim/anim_stand.mv1", 1, 1.0f},
        {"walk",  "data/Sample/Player/Anim/anim_walk.mv1", 1, 1.0f},
        {"jump",  "data/Sample/Player/Anim/anim_jump.mv1", 1, 1.0f},
    });
    model_comp->PlayAnimation("idle");

    auto obj_control = AddComponent<ComponentObjectController>();
    obj_control->SetMoveSpeed(1.0f);
    obj_control->SetRotateSpeed(20.0f);

    return true;
}

void Player::Update()
{
    __super::Update();

    float3 pos = GetTranslate();

    if(CheckHitKey(KEY_INPUT_SPACE)) {
        auto&          objects      = SimpleObjects::GetAll();
        SimpleObjects* liftedObject = nullptr;

        // 既に持ち上げられているオブジェクトがあるか確認
        for(auto obj : objects) {
            if(obj->IsLifted()) {
                liftedObject = obj;
                break;
            }
        }

        if(liftedObject) {
        }
        else {
            // 持ち上げられていない場合、一番近いオブジェクトを探して持ち上げる
            SimpleObjects* closestObj = nullptr;
            float          minDist    = 10.0f;    // 持ち上げ可能な最大距離

            for(auto obj : objects) {
                if(!obj->IsLifted()) {
                    float dist = length(obj->GetTranslate() - pos);
                    if(dist < minDist) {
                        minDist    = dist;
                        closestObj = obj;
                    }
                }
            }

            if(closestObj) {
                closestObj->Lift();    // 一番近いオブジェクトを持ち上げる
            }
        }
    }
}
}    // namespace Game01
