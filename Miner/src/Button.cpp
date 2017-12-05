#include "Button.h"

Button::Button(ci::vec2 pos, std::function<void()> onClick) : box(pos, ci::vec2(pos.x+100, pos.y + 30)),
	clickHandler(onClick),
	label("Click me!")
{
}

void Button::setLabel(std::string l)
{
	label = l;
}

void Button::mouseDown(ci::app::MouseEvent event)
{
	if (box.contains(event.getPos()))
	{
		clickHandler();
	}
}

void Button::draw()
{
	static const ci::Font font = ci::Font("Arial", 24);
	static const ci::Color fontColor = ci::Color(1.0f, 1.0f, 1.0f);
	static const ci::Color boxColor = ci::Color(0.3f, 0.3f, 0.3f);

	ci::gl::color(boxColor);
	ci::gl::drawSolidRect(box);
	ci::gl::drawStringCentered(label, ci::vec2((box.getX2() + box.getX1())/2, box.getY1()+6), fontColor, font);
}
