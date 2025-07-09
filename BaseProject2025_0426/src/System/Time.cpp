#include "Time.h"
#include <DxLib.h>

namespace Game01 {

static unsigned int nowTime   = 0;
static unsigned int prevTime  = 0;
static float        deltaTime = 0.0f;

void InitTime()
{
    nowTime   = GetNowCount();
    prevTime  = nowTime;
    deltaTime = 0.0f;
}

void UpdateTime()
{
    prevTime  = nowTime;
    nowTime   = GetNowCount();
    deltaTime = (nowTime - prevTime) / 1000.0f;
}

unsigned int GetTimeMs()
{
    return nowTime;
}

float GetDeltaTime()
{
    return deltaTime;
}

}    // namespace Game01
