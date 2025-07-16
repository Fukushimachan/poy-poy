#pragma once
#include <System/Scene.h>

namespace Game01 {

USING_PTR(ShapeSpawner);

class ShapeSpawner : public Object
{
public:
    BP_OBJECT_DECL(ShapeSpawner, u8"ランダムで図形を落とす");

    bool Init() override;
    void Update() override;

private:
    float timer_    = 0.0f;      // 経過時間
    float interval_ = 300.0f;    // 生成間隔（フレーム）
};

}    // namespace Game01
