#include "Wall.h"
#include <System/Component/ComponentCollision.h>


//! @brief 初期化
//! @return 初期化済み
namespace Game01 {

bool Wall::Init()
{
    Super::Init();

    //カメラオブジェクト
    auto coll = AddComponent<ComponentCollision>();
   // coll->SetRadius(4.0f);
    //coll->SetHeight(23.0f);
    //coll->UseGravity(true);
    return true;
}

//! @brief 更新
void Wall::Update()
{
    // 毎フレーム動作する
    Super::Update();
}
void Wall::Draw()
{
}
void Wall::Exit()
{
}
}    // namespace Game01
