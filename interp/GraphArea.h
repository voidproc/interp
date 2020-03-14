#pragma once

namespace app
{
	struct GraphAreaSettings
	{
		// グラフの大きさ[px]
		Vec2 size{ 700.0, 500.0 };

		// グラフの表示範囲
		RectF range{ Vec2(0, -20), Vec2(100, 120) };

		//目盛線の間隔
		double gridSize = 20.0;

		// グラフの1単位が何pxか
		const Vec2 unitInPixels() const { return size / range.size; }
	};

	struct GraphArea
	{
		GraphArea(const GraphAreaSettings& settings);

		void drawArea() const;

		void drawPoint(const Vec2& xy, double size, const ColorF& color) const;

		void drawLine(const Vec2& xy1, const Vec2& xy2, const ColorF& color) const;

		const Vec2 posInPixels(const Vec2& pos) const;

		GraphAreaSettings settings;
	};
}
