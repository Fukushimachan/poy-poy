#pragma once
#include <System/Scene.h>
#include <vector>

namespace Game01 {

USING_PTR(SimpleObjects);

class SimpleObjects : public Object
{
public:
    enum class ShapeType
    {
        Tetrahedron,
        Sphere
    };

    BP_OBJECT_DECL(SimpleObjects, u8"三角锥や球を描画する物体");

    bool Init() override;
    void Update() override;

    void SetShape(ShapeType shape);

    bool  isLifted_  = false;    // 現在持ち上げられているかどうかのフラグ
    float liftTimer_ = 0.0f;     // 上昇アニメーション用の時間カウンター

    void Lift();              // 持ち上げ開始関数
    bool IsLifted() const;    // 状態取得

    void Throw(const float3& dir);

    bool isThrown_ = false;    // 投げられたかどうか

    float3 throwDirection_{};
    float  throwTimer_ = 0.0f;


    
    static const std::vector<SimpleObjects*>& GetAll() { return allObjects_; }

private:
    ShapeType shape_ = ShapeType::Tetrahedron;
    static std::vector<SimpleObjects*> allObjects_;    // 全オブジェクトリスト
};

}    // namespace Game01
