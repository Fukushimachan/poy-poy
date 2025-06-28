#include "SimpleObjects.h"
#include <DxLib.h>
#include <System/Component/ComponentCollisionCapsule.h>

namespace Game01 {

bool SimpleObjects::Init()
{
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
}

}    // namespace Game01
