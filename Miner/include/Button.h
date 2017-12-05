#pragma once

#include <string>
#include "cinder/gl/gl.h"
#include "cinder/app/MouseEvent.h"

class Button
{
public:
	Button(ci::vec2 pos, std::function<void()> onClick);

	void setLabel(std::string l);
	void mouseDown(ci::app::MouseEvent event);
	void draw();

private:
	ci::Rectf box;
	std::function<void()> clickHandler;
	std::string label;
};