#include <Siv3D.hpp> // OpenSiv3D v0.4.2

#include "Interpolation.h"
#include "GraphArea.h"

namespace app
{
	// 動く点P
	struct P
	{
		using Vec2Interp = interp::Interp<Duration, Vec2>;
		Vec2Interp interp;

		Stopwatch time;

		template <class ... Args>
		P(Args&& ... args)
		{
			interp.set(std::forward<Args>(args)...);
		}

		void start()
		{
			time.restart();
		}

		const Vec2 get() const
		{
			return interp.get(time.elapsed());
		}
	};
}

void Main()
{
	Scene::SetBackground(ColorF(.25));

	// これ(xp,yp)に沿って点Pが動きます
	const Array<Duration> xp{
		0s,
		1s,
		1.5s,
		2s,
		3s,
		3.6s,
		4.5s
	};

	const Array<Vec2> yp{
		Vec2(0, 50),
		Vec2(20, 35),
		Vec2(30, 30),
		Vec2(40, 5),
		Vec2(60, 70),
		Vec2(80, 90),
		Vec2(100, 40)
	};

	// いろんなイージングでやってみる
	using EasingFunction = interp::EasingFunction;
	Array<EasingFunction> ef{
		EaseInOutLinear,
		EaseInOutSine,
		EaseInOutCubic,
		EaseInOutExpo,
		EaseOutBounce,
		EaseOutElastic
	};

	// いろんな点Pをつくる（イージングの種類分）
	Array<app::P> pp;

	for (auto i : step(ef.size()))
	{
		pp.emplace_back(
			Array<Duration>(xp.size(),
				Arg::indexedGenerator = [&xp, &i](auto idx) { return xp[idx] + i * 1.2s; }),
			yp,
			Array<EasingFunction>(xp.size(), ef[i]));
	}

	// こんな感じでもいい
	//pp.emplace_back(
	//	0s, Vec2(0, 0), "EaseInOutCubic",
	//	0.5s, Vec2(50, 80), "EaseInOutCirc",
	//	0.8s, Vec2(100, 20));

	// グラフっぽくかいてみる
	app::GraphAreaSettings s;
	app::GraphArea g(s);

	while (System::Update())
	{
		if (KeyEnter.down())
		{
			for (auto& p : pp)
			{
				p.start();
			}
		}

		{
			// まんなかに持ってくる
			const auto t = Transformer2D(Mat3x2::Translate((Scene::Size() - s.size) / 2));

			// グラフの外枠とか目盛線
			g.drawArea();

			// 点Pが通るところを線引いておく
			for (int i : step(yp.size() - 1))
			{
				g.drawLine(yp[i], yp[i+1], ColorF(0.4));
			}

			// うごく点Pたち
			for (auto i : step(pp.size()))
			{
				g.drawPoint(pp[i].get(), 14, ColorF(0.85));
			}
		}
	}
}
