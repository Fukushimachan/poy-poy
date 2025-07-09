#pragma once

namespace Game01 {
void         InitTime();        // 初期化
void         UpdateTime();      // 毎フレーム更新
unsigned int GetTimeMs();       // 現在の時間（ミリ秒）
float        GetDeltaTime();    // フレーム間の経過時間（秒）
}    // namespace Game01
