#pragma once
#pragma once
#include <System/Scene.h>

//! @brief チュートリアルシーン
namespace Game01 {
USING_PTR(Cone);
class Cone : public Object
{
public:
    BP_OBJECT_DECL(Cone, u8"Groundのシーン");
    float3 pos  = float3(0.0f, 10.0f, 0.0f);
    float3 pos2 = float3(10.0f, 10.0f, 0.0f);
    float3 pos_dis = pos2 - pos;
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
