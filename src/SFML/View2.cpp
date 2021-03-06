#include "View2.h"
#include "Game.h"
#include "GameUtils.h"

sf::Vector2f View2::getPosition(const sf::Vector2f& point) const
{
	sf::Vector2f mousePosition =
		view.getCenter() -
		(view.getSize() / 2.f) +
		(point * zoomFactor) -
		(position * zoomFactor);
	mousePosition.x = std::round(mousePosition.x);
	mousePosition.y = std::round(mousePosition.y);
	return mousePosition;
}

void View2::setSize(float width, float height)
{
	sizeNoZoom.x = width;
	sizeNoZoom.y = height;
	if (forceEvenSize == true)
	{
		roundedSizeNoZoom.x = ((float)((int)(width * 0.5f)) * 2);
		roundedSizeNoZoom.y = ((float)((int)(height * 0.5f)) * 2);
	}
	else
	{
		roundedSizeNoZoom = sizeNoZoom;
	}
	view.setSize(roundedSizeNoZoom.x, roundedSizeNoZoom.y);
}

void View2::setSize(sf::Vector2f size_)
{
	sizeNoZoom = size_;
	if (forceEvenSize == true)
	{
		roundedSizeNoZoom.x = ((float)((int)(size_.x * 0.5f)) * 2);
		roundedSizeNoZoom.y = ((float)((int)(size_.y * 0.5f)) * 2);
	}
	else
	{
		roundedSizeNoZoom = sizeNoZoom;
	}
	view.setSize(roundedSizeNoZoom.x, roundedSizeNoZoom.y);
}

void View2::setViewport(const Game& game)
{
	const auto& drawRegionSize = game.DrawRegionSize();
	const auto& gameWindowSize = game.WindowSize();
	auto x = position.x;
	if (drawRegionSize.x > gameWindowSize.x)
	{
		x += ((float)drawRegionSize.x / 2.f) - ((float)gameWindowSize.x / 2.f);
	}
	x /= (float)drawRegionSize.x;
	auto y = position.y;
	if (drawRegionSize.y > gameWindowSize.y)
	{
		y += ((float)drawRegionSize.y / 2.f) - ((float)gameWindowSize.y / 2.f);
	}
	y /= (float)drawRegionSize.y;

	auto w = roundedSizeNoZoom.x / (float)drawRegionSize.x;
	auto h = roundedSizeNoZoom.y / (float)drawRegionSize.y;

	view.setViewport(sf::FloatRect(x, y, w, h));
}

void View2::updateSize(const Game& game)
{
	if (game.StretchToFit() == true)
	{
		setViewport(game);
		return;
	}
	auto pos2 = getPosition();
	auto size2 = getSize();
	GameUtils::setAnchorPosSize(anchor, pos2, size2, game.OldWindowSize(), game.WindowSize());
	setPosition(pos2);
	setSize(size2);
	setViewport(game);
	view.zoom(zoomFactor);
}

void View2::updateViewport(const Game& game)
{
	setSize(sizeNoZoom);
	setViewport(game);
	view.zoom(zoomFactor);
}

void View2::reset()
{
	const auto& vSize = view.getSize();
	view.reset(sf::FloatRect(0, 0, vSize.x, vSize.y));
}
