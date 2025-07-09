#include "SimpleObjects.h"
#include "Player.h"
#include <DxLib.h>
#include <System/Component/ComponentCollisionCapsule.h>

namespace Game01 {

std::vector<SimpleObjects*> SimpleObjects::allObjects_;

bool SimpleObjects::Init()
{
    // 自分をリストに追加
    allObjects_.push_back(this);
    Super::Init();
    SetName("Shape");

    // 初期位置を設定
    SetTranslate({0.0f, 40.0f, 0.0f});

    //当たり判定コンポーネントを追加
    auto col = AddComponent<ComponentCollisionCapsule>();
    col->SetHeight(10.0f);
    col->SetRadius(4.0f);
    col->UseGravity();    // 物体に重力を与える
    col->SetCollisionGroup(ComponentCollision::CollisionGroup::ENEMY);

    return true;
}

// 描画する形状（球 or 三角錐）を指定
void SimpleObjects::SetShape(ShapeType shape)
{
    shape_ = shape;
}

void SimpleObjects::Update()
{
    Super::Update();

    VECTOR       pos   = VGet(GetTranslate().x, GetTranslate().y, GetTranslate().z);
    unsigned int color = GetColor(0, 0, 255);

    // 🔺 三角錐の場合
    if(shape_ == ShapeType::Tetrahedron) {
        VECTOR top   = VAdd(pos, VGet(0, 5, 0));
        VECTOR front = VAdd(pos, VGet(0, 0, -4));
        VECTOR left  = VAdd(pos, VGet(-4, 0, 4));
        VECTOR right = VAdd(pos, VGet(4, 0, 4));

        DrawTriangle3D(top, front, left, color, TRUE);
        DrawTriangle3D(top, left, right, color, TRUE);
        DrawTriangle3D(top, right, front, color, TRUE);
        DrawTriangle3D(front, right, left, color, TRUE);
    }
    // ⚪ 球の場合
    else if(shape_ == ShapeType::Sphere) {
        // 球体を描画
        VECTOR drawPos = VAdd(pos, VGet(0, 4.0f, 0));
        DrawSphere3D(drawPos, 4.0f, 16, color, color, TRUE);
    }

    if(isLifted_) {
        liftTimer_ += 0.05f;
        if(liftTimer_ > 1.0f)
            liftTimer_ = 1.0f;

        // プレイヤーを取得
        auto player = Scene::Object::Get<Player>("Player");
        if(player) {
            float3 ppos   = player->GetTranslate();
            float3 target = ppos + float3(0, 20.0f, 0);
            float3 nowPos = GetTranslate();

            nowPos = nowPos * (1.0f - liftTimer_) + target * liftTimer_;
            SetTranslate(nowPos);
        }
    }
    if(isThrown_) {
        if(throwTimer_ > 0.0f) {
            SetTranslate(GetTranslate() + throwDirection_ * 0.1f);
            throwDirection_.y -= 0.1f;     
            throwTimer_       -= 0.02f;    
        }
        else {
            isThrown_ = false;    
        }
    }
}
void SimpleObjects::Lift()
{
    isLifted_  = true;
    liftTimer_ = 0.0f;
    isThrown_  = false;

    if(auto col = GetComponent<ComponentCollisionCapsule>()) {
        col->UseGravity(false);    
    }
}

bool SimpleObjects::IsLifted() const
{
    return isLifted_;
}

void SimpleObjects::Throw(const float3& direction)
{
    isLifted_ = false;
    isThrown_ = true;

    if(auto col = GetComponent<ComponentCollisionCapsule>()) {
        col->UseGravity(true);    // 重力を有効にする
    }

    throwDirection_ = direction * 5.0f;
    throwTimer_     = 1.0f;
}

}    // namespace Game01
