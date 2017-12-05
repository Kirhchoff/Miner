#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "BoxGrid.h"
#include "MineMap.h"
#include "FileMineMap.h"
#include "ProxyMap.h"
#include "Flags.h"
#include "Button.h"

class MinerApp : public ci::app::App {
public:
	void setup() override;
	void mouseDown( ci::app::MouseEvent event ) override;
	void update() override;
	void draw() override;
private:
	void start(size_t size, size_t noMines);
	void toggleBoxFlag(size_t boxId);
	std::string msg{ "" };
	BoxGrid grid;
	std::unique_ptr<Labels> labels;
	std::unique_ptr<Flags> flags;
	std::unique_ptr<Button> startButton;
};

void MinerApp::start(size_t size, size_t noMines)
{
	msg = "";
	grid = BoxGrid(size, ci::vec2(100, 100));
	grid.setup();
	labels = std::make_unique<Labels>(std::make_shared<RandomMineMap>(size, noMines), size);
	//labels = std::make_unique<Labels>(std::make_shared<FileMineMap>("..\\assets\\mines.txt"), size);
	flags = std::make_unique<Flags>();
	startButton = std::make_unique<Button>(ci::vec2(125, 50), [this] {start(7,12); });
	startButton->setLabel("Start");
}

void MinerApp::setup()
{
	start(7, 12);
}

void MinerApp::mouseDown( ci::app::MouseEvent event )
{
	grid.mouseDown(event);
	startButton->mouseDown(event);
}

void MinerApp::update()
{
	if (grid.boxClicked())
	{
		auto boxId = grid.lastClickedBox();
		if (!flags->isFlagged(boxId)) {
			auto label = labels->uncover(boxId);
			grid.setBoxLabel(boxId, label);
			if (label == "X")
			{
				msg = "BOOM!!!";
			}
		}
	}
	else if (grid.boxFlagged()) {
		auto boxId = grid.lastClickedBox();
		if (!labels->isUncovered(boxId)) 
		{
			toggleBoxFlag(boxId);
		}
	}

	grid.update();
}

void MinerApp::toggleBoxFlag(size_t boxId)
{
	if (flags->isFlagged(boxId)) {
		grid.setBoxLabel(boxId, "");
	}
	else {
		grid.setBoxLabel(boxId, "!");
	}
	flags->toggleFlag(boxId);
}

void MinerApp::draw()
{
	static const ci::Font font = ci::Font("Arial", 42);
	ci::gl::clear();
	grid.draw();
	startButton->draw();
	ci::gl::drawString(msg, ci::vec2(115, 155), ci::Color(1, 0, 0), font);
}

CINDER_APP( MinerApp, ci::app::RendererGl )
