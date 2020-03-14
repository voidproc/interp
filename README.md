# numpy.interpみたいなやつで遊ぶ with OpenSiv3D

## 概要

```
#include <Siv3D.hpp> // OpenSiv3D v0.4.2

#include "Interpolation.h"

using Vec2Interp = interp::Interp<Duration, Vec2>;

Vec2Interp interp(
    0s, Vec2(0, 0), // 経過時間と座標
    1s, Vec2(20, 30), "EaseInOutCubic", //イージング関数を指定できたり
    2.5s, Vec2(100, 100),
    4s, Vec2(80, 0),
    ...
);

Stopwatch time{true};

while (System::Update())
{
    // 時間で変化する値が得られるのでこれでなんかして遊ぶ
    const auto p = interp.get(time.elapsed());

    // 以下楽しいコード
    ...

}

```
