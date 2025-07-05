#include "Ground.h"
#include <System/Component/ComponentModel.h>
#include <System/Component/ComponentCollisionModel.h>
#include <System/Component/ComponentCamera.h>
#include <System/Component/ComponentCollisionCapsule.h>

//! @brief 初期化
//! @return 初期化済み
namespace Game01 {

bool Ground::Init()
{
    Super::Init();
    // 最初に1回動作する
    SetName("Ground");
    // ただし trueを返さなければ Initに何回も来る仕様。
    AddComponent<ComponentModel>("data/Sample/SwordBout/Stage/ground.mv1");
    AddComponent<ComponentCollisionModel>()->AttachToModel();
    SetScaleAxisXYZ({20.0, 1.0, 20.0});
    // __super::Init();    //Object::Init();と同じ

    //グラウンドオブジェクト
    // AddComponent<ComponentModel>("data/Sample/SwordBout/Stage/ground.mv1");

    //auto cam_lock = AddComponent<ComponentSpringArm>();
    // cam_lock->SetSpringArmObject("Player");
    return true;
}

//! @brief 更新
void Ground::Update()
{
    // 毎フレーム動作する
    Super::Update();
}
void Ground::Draw()
{
    Super::Draw();
}
void Ground::Exit()
{
    Super::Exit();
}
}    // namespace Game01
