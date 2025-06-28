#include "Camera.h"
#include <System/Component/ComponentModel.h>
#include <System/Component/ComponentCollisionModel.h>
#include <System/Component/ComponentCamera.h>
#include <System/Component/ComponentSpringArm.h>

//! @brief 初期化
//! @return 初期化済み
namespace Game01 {

bool Camera::Init()
{
    // 最初に1回動作する
    // ただし trueを返さなければ Initに何回も来る仕様。

    // __super::Init();    //Object::Init();と同じ
    Super::Init();

    //カメラオブジェクト
    auto cam_comp = AddComponent<ComponentCamera>();
    cam_comp->SetPositionAndTarget({0.0f, 100.0f, +300.0f}, {0.0f, 0.0f, 0.0f});

    //auto cam_lock = AddComponent<ComponentSpringArm>();
    // cam_lock->SetSpringArmObject("Player");
    return true;
}

//! @brief 更新
void Camera::Update()
{
    // 毎フレーム動作する
    Super::Update();
}
void Camera::Draw()
{
}
void Camera::Exit()
{
}
}    // namespace Game01
