#pragma once
#include <System/Scene.h>
#include <System/Component/ComponentCamera.h>
#include <System/Component/ComponentModel.h>
#include <System/Component/ComponentObjectController.h>
#include <System/Component/ComponentCollisionModel.h>
#include <System/Component/ComponentCollisionCapsule.h>
#include <System/Component/ComponentSpringArm.h>

//! @brief チュートリアルシーン
namespace Game01 {

class Game01 : public Scene::Base
{
public:
    BP_CLASS_DECL(Game01, u8"Tutorialのシーン");
    const int ground_w_max = 10;
    const int ground_h_max = 10;
    const int ground_size = 20;
    //! @brief 初期化
    //! @return 初期化済み
    bool Init() override;

    //! @brief 更新
    void Update() override;
    void Draw() override;
    void Exit() override;

private:
    // 必要であれば変数をここに追加する
};
}    // namespace Game01
