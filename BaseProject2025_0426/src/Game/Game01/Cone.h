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
    float3 pos     = float3(0.0f, 10.0f, 0.0f);
    float3 pos2    = float3(10.0f, 10.0f, 0.0f);
    float3 pos_dis = pos2 - pos;
    float3 move_   = float3(0.0f, 0.0f, 0.0f);
    int    count_click;
    //! @brief 初期化
    //! @return 初期化済み
    bool Init() override;

    //! @brief 更新
    void Update() override;
    void Draw() override;
    void Exit() override;

    void OnHit(const ComponentCollision::HitInfo& hit_info) override;
    bool up_obj = false;
    void SetDirectior(float3 dir);
    void SetSpeed(float speed);
    bool Check();
    bool check_;

private:
    // ジャンプしていることを示します
    float3       direction_ = {0, 0, 0};
    float        speed_     = 1.0f;
    static float radius_;

    ComponentCollisionSphereWeakPtr collision_;
    bool                            is_jump_ = false;
    // ジャンプスピード
    float jump_speed_ = 1.0f;
    // 必要であれば変数をここに追加する
};
}    // namespace Game01
