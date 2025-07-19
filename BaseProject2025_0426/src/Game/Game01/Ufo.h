#pragma once

//! @brief 
namespace Game01 {
USING_PTR(Ufo);
class Ufo : public Object
{
public:
    BP_OBJECT_DECL(Ufo, u8"Ufoのシーン");

    //! @brief 初期化
    //! @return 初期化済み
    bool Init() override;

    //! @brief 更新
    void Update() override;
    void Draw() override;
    void Exit() override;

private:
    // 必要であれば変数をここに追加する
    float3 targetPos_;

};
}    // namespace Game01
