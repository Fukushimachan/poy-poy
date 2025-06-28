#pragma once
#include <System/Scene.h>

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

private:
    ShapeType shape_ = ShapeType::Tetrahedron;
};

}    // namespace Game01
