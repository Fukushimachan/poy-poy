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
    bool    Init() override;
    Object* holding_object = NULL;

    //! @brief 更新
    void Update() override;
    void Draw() override;
    void Exit() override;
    bool up_obj     = false;
    int  _isholding = 0;

    int  count = 0;
    bool check(bool check);
    enum
    {
        IDLE,
        HOLDING,
        THROWING,
    };
    void OnHit(const ComponentCollision::HitInfo& hit_info) override;

private:
    bool check_ = false;
    // 必要であれば変数をここに追加する
};
}    // namespace Game01
