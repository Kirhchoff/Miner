#pragma once

#include <string>
#include "cinder/gl/gl.h"
#include "cinder/app/MouseEvent.h"
#include "boost/optional.hpp"

class BoxGrid
{
public:
	BoxGrid();
	explicit BoxGrid(size_t size);
	BoxGrid(size_t size, ci::vec2 pos);
	~BoxGrid();

	void setup();
	void mouseDown(ci::app::MouseEvent event);
	void update();
	void draw();

	bool boxClicked() const;
	bool boxFlagged() const;
	size_t lastClickedBox() const;

	void setBoxLabel(size_t boxId, const std::string& label);

	size_t addBox(const ci::vec2 &pos, std::string label = "");



private:

	struct MineBox
	{
		ci::Rectf bounds;
		ci::vec2 pos;
		std::string label;
		size_t id;
		int color;
	};

	size_t gridSize;
	ci::vec2 pos;
	std::vector<MineBox> boxes;
	boost::optional<size_t> clickedBox;
	bool isFlagged;
};

