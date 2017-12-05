#include "BoxGrid.h"

#include "cinder/Font.h"
#include "cinder/Color.h"

namespace {
	constexpr float BOX_SIZE = 20;
	constexpr float CELL_SIZE = BOX_SIZE + 3.0f;
}

BoxGrid::BoxGrid(size_t size) : gridSize(size), pos(0, 0)
{
}

BoxGrid::BoxGrid(size_t size, ci::vec2 pos) : gridSize(size), pos(pos)
{
}

BoxGrid::BoxGrid() : gridSize(0), pos(0, 0)
{
}

BoxGrid::~BoxGrid()
{
}

void BoxGrid::setup()
{
	for (size_t i = 0; i < gridSize * gridSize; ++i)
	{
		addBox(ci::vec2((i % gridSize) * CELL_SIZE, (i / gridSize) * CELL_SIZE));
	}
}

void BoxGrid::mouseDown(ci::app::MouseEvent event)
{
	auto clicked = std::find_if(boxes.begin(), boxes.end(), [&event, this](MineBox& box) {
		return box.bounds.contains(event.getPos());
	});
	if (clicked != boxes.end())
	{
		clickedBox = clicked->id;
		isFlagged = event.isRight();
	}
}

void BoxGrid::update()
{
	clickedBox.reset();
}

void BoxGrid::draw()
{
	static const ci::Font font = ci::Font("Arial", BOX_SIZE - 1);
	static const ci::Color fontColor = ci::Color(1.0f, 1.0f, 1.0f);
	static const ci::Color boxColorBomb = ci::Color(0.85f, 0.2f, 0.0f);
	static const ci::Color boxColorClean = ci::Color(0.2f, 0.65f, 0.2f);
	static const ci::Color boxColorFlagged = ci::Color(0.8f, 0.8f, 0.1f);
	static const ci::Color boxColorDefault = ci::Color(0.8f, 0.8f, 0.8f);

	for (const auto &box : boxes) {
		ci::gl::pushModelMatrix();
		switch (box.color) {
		case 0:
		default:
			ci::gl::color(boxColorDefault);
			break;
		case 1:
			ci::gl::color(boxColorClean);
			break;
		case 2:
			ci::gl::color(boxColorFlagged);
			break;
		case -1:
			ci::gl::color(boxColorBomb);
			break;

		}
		ci::gl::translate(pos.x + box.pos.x, pos.y + box.pos.y);
		ci::gl::drawSolidRect(ci::Rectf(0, 0, BOX_SIZE, BOX_SIZE));
		ci::gl::drawStringCentered(box.label, ci::vec2(BOX_SIZE / 2, BOX_SIZE / 5), fontColor, font);
		ci::gl::popModelMatrix();
	}
}

bool BoxGrid::boxClicked() const
{
	return !isFlagged && !!clickedBox;
}

bool BoxGrid::boxFlagged() const
{
	return isFlagged && !!clickedBox;
}

size_t BoxGrid::lastClickedBox() const
{
	if (clickedBox) return *clickedBox;
	return 0;
}

void BoxGrid::setBoxLabel(size_t boxId, const std::string & label)
{
	boxes[boxId].label = label;
	if (label.empty())
		boxes[boxId].color = 0;
	else if (label.find_first_not_of("0123456789") == std::string::npos)
		boxes[boxId].color = 1;
	else if (label == "!")
		boxes[boxId].color = 2;
	else
		boxes[boxId].color = -1;
}

size_t BoxGrid::addBox(const ci::vec2 & boxPos, std::string label)
{
	ci::vec2 boxRect1 = { boxPos.x + pos.x, boxPos.y + pos.y };
	boxes.push_back({ ci::Rectf(boxRect1.x, boxRect1.y, boxRect1.x + BOX_SIZE, boxRect1.y + BOX_SIZE), boxPos, label, boxes.size() });
	return boxes.size() - 1;
}
