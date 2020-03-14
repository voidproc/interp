#include "GraphArea.h"

namespace app
{
	GraphArea::GraphArea(const GraphAreaSettings& settings)
		: settings(settings)
	{
	}

	void GraphArea::drawArea() const
	{
		// 枠
		RectF(settings.size).drawFrame(3.0, Palette::Gray);

		// 目盛線
		for (auto ix : step((int)(settings.range.w / settings.gridSize)))
		{
			const auto x = (ix * settings.gridSize + Abs(Fmod(settings.range.x, settings.gridSize))) * settings.unitInPixels().x;
			Line(x, 0, x, settings.size.y).draw(2.0, Palette::Gray);
		}

		for (auto iy : step((int)(settings.range.h / settings.gridSize)))
		{
			const auto y = (iy * settings.gridSize + Abs(Fmod(settings.range.y, settings.gridSize))) * settings.unitInPixels().y;
			Line(0, y, settings.size.x, y).draw(2.0, Palette::Gray);
		}
	}

	void GraphArea::drawPoint(const Vec2& xy, double size, const ColorF& color) const
	{
		Circle(posInPixels(xy), size).drawFrame(2.0, ColorF(color, 0.5)).draw(color);
	}

	void GraphArea::drawLine(const Vec2& xy1, const Vec2& xy2, const ColorF& color) const
	{
		Line(posInPixels(xy1), posInPixels(xy2)).draw(2.0, color);
	}

	const Vec2 GraphArea::posInPixels(const Vec2& pos) const
	{
		return Vec2(
			pos.x * settings.unitInPixels().x,
			(settings.range.h + settings.range.y - pos.y) * settings.unitInPixels().y);
	}
}
