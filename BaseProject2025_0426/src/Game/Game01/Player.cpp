#include "Player.h"
#include "SimpleObjects.h"
#include <DxLib.h>
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
    SetTranslate({0.0f, 5.0f, 0.0f});

    auto col = AddComponent<ComponentCollisionCapsule>();
    col->SetHeight(9.0f);
    col->SetRadius(4.0f);
    col->UseGravity();
    col->SetCollisionGroup(ComponentCollision::CollisionGroup::PLAYER);

    auto obj_control = AddComponent<ComponentObjectController>();
    obj_control->SetMoveSpeed(1.0f);
    obj_control->SetRotateSpeed(20.0f);

    return true;
}

void Player::Update()
{
    Super::Update();

    float3 pos = GetTranslate();

    //三角形の座標を設定
    VECTOR top   = VGet(pos.x, pos.y + 7, pos.z);
    VECTOR front = VGet(pos.x, pos.y, pos.z - 6);
    VECTOR left  = VGet(pos.x - 6, pos.y, pos.z + 6);
    VECTOR right = VGet(pos.x + 6, pos.y, pos.z + 6);

    unsigned int color = GetColor(255, 0, 0);

    // 三角形の描画
    DrawTriangle3D(top, front, left, color, TRUE);
    DrawTriangle3D(top, left, right, color, TRUE);
    DrawTriangle3D(top, right, front, color, TRUE);
    DrawTriangle3D(front, right, left, color, TRUE);

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
            //// 既に持ち上げている場合、もう一度押すと投げる
            //float3 dir = float3(0.0f, 1.2f, 0.0f);
            //liftedObject->Throw(dir);
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
