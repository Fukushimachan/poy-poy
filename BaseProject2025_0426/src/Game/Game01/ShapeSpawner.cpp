#include "ShapeSpawner.h"
#include "SimpleObjects.h"  
#include "Player.h"
#include <System/Time.h>
#include <DxLib.h>

namespace Game01 {

bool ShapeSpawner::Init()
{
    Super::Init();
    return true;
}

void ShapeSpawner::Update()
{
    Super::Update();

    // 経過時間を加算（フレーム時間から取得）
    timer_++;

    if(timer_ >= interval_) {
        timer_ = 0.0f;

        // ランダムな位置（X: -50〜50, Z: -30〜30）
        float x = (float)(GetRand(100) - 50);
        float z = (float)(GetRand(60) - 30);
        float y = 60.0f;

        // オブジェクトを生成
        auto obj = Scene::Object::Create<SimpleObjects>();
        obj->SetTranslate({x, y, z});

        // ランダムに形状を選ぶ（0 or 1）
        int type = GetRand(1);
        if(type == 0) {
            obj->SetShape(SimpleObjects::ShapeType::Tetrahedron);
        }
        else {
            obj->SetShape(SimpleObjects::ShapeType::Sphere);
        }
    }
   
}

}    // namespace Game01
