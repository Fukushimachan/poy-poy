#include "Ufo.h"
#include <System/Component/ComponentModel.h>
#include <System/Component/ComponentCollisionModel.h>
//! @brief 初期化
//! @return 初期化済み
namespace Game01 {

bool Ufo::Init()
{
    // 最初に1回動作する
    // ただし trueを返さなければ Initに何回も来る仕様。

    // __super::Init();    //Object::Init();と同じ
    Super::Init();
    //ufo
    SetName("Ufo");

    return true;
}

//! @brief 更新
void Ufo::Update()
{
    // 毎フレーム動作する
    Super::Update();
  
    AddRotationAxisXYZ({0, 0.1f, 0});
}
void Ufo::Draw()
{
    auto pos = GetTranslate();
    auto scale = GetScaleAxisXYZ();
    auto lp1 = pos + float3(5.0f, 30.0f, 0.0f) * scale;
    auto lp2 = pos + float3(0.0f, 30.0f, -5.0f) * scale;
    auto lp3 = pos + float3(0.0f, 30.0f, 5.0f) * scale;

    auto rp1 = pos + float3(-5.0f,30.0f, 0.0f) * scale;
    auto rp2 = pos + float3(0.0f, 30.0f, -5.0f) * scale;
    auto rp3 = pos + float3(0.0f, 30.0f, 5.0f) * scale;

    DrawTriangle3D(cast(lp1), cast(lp2), cast(lp3), GetColor(255, 255, 255), TRUE);//左辺の三角形
    DrawTriangle3D(cast(rp1), cast(rp2), cast(rp3), GetColor(255, 255, 255), TRUE);//右辺の三角形
}
void  Ufo::Exit()
{
}
}    // namespace Game01
