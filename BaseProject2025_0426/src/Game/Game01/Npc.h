#pragma once
#pragma once
#include <System/Scene.h>

//! @brief チュートリアルシーン
namespace Game01 {
USING_PTR(Npc);
class Npc : public Object
{
public:
    BP_OBJECT_DECL(Npc, u8"Groundのシーン");

    float3 pos_;
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
