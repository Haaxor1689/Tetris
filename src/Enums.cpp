#include "Enums.hpp"

gridBlock toGridBlock(tetroType value) {
	switch (value) {
	case tetroType::I:
		return gridBlock::Teal;
	case tetroType::O:
		return gridBlock::Yellow;
	case tetroType::T:
		return gridBlock::Purple;
	case tetroType::J:
		return gridBlock::Blue;
	case tetroType::L:
		return gridBlock::Orange;
	case tetroType::S:
		return gridBlock::Green;
	case tetroType::Z:
		return gridBlock::Red;
	case tetroType::None:
		return gridBlock::Empty;
	default:
		return gridBlock::Empty;
	}
}

eventType toEventType(Uint32 value) {
	switch (value) {
	case SDL_KEYDOWN:
		return eventType::KeyDown;
	case SDL_KEYUP:
		return eventType::KeyUp;
	case SDL_MOUSEMOTION:
		return eventType::MouseMotion;
	case SDL_MOUSEBUTTONDOWN:
		return eventType::MouseButtonDown;
	case SDL_MOUSEBUTTONUP:
		return eventType::MouseButtonUp;
	case SDL_QUIT:
		return eventType::Quit;
	default:
		return eventType::Unused;
	}
}

std::array<Position, 4> toArray(tetroType value) {
	switch (value) {
	case tetroType::I:
		return { { { 0, 0 },{ -1, 0 },{ 1, 0 },{ 2, 0 } } };
	case tetroType::O:
		return { { { 0, 0 },{ 1, 1 },{ 1, 0 },{ 0, 1 } } };
	case tetroType::T:
		return { { { 0, 0 },{ -1, 0 },{ 1, 0 },{ 0, 1 } } };
	case tetroType::J:
		return { { { 0, 0 },{ -1, 0 },{ 1, 0 },{ 1, 1 } } };
	case tetroType::L:
		return { { { 0, 0 },{ -1, 0 },{ 1, 0 },{ -1, 1 } } };
	case tetroType::S:
		return { { { 0, 0 },{ -1, 1 },{ 1, 0 },{ 0, 1 } } };
	case tetroType::Z:
		return { { { 0, 0 },{ -1, 0 },{ 1, 1 },{ 0, 1 } } };
	default:
		return { { { 0, 0 },{ 0, 0 },{ 0, 0 },{ 0, 0 } } };
	}
}

std::string toString(tetroType value) {
	switch (value) {
	case tetroType::I:
		return "TealBlock";
	case tetroType::O:
		return "YellowBlock";
	case tetroType::T:
		return "PurpleBlock";
	case tetroType::J:
		return "BlueBlock";
	case tetroType::L:
		return "OrangeBlock";
	case tetroType::S:
		return "GreenBlock";
	case tetroType::Z:
		return "RedBlock";
	case tetroType::None:
		return "EmptyBlock";
	default:
		return "";
	}
}

std::string toString(gridBlock value) {
	switch (value) {
	case gridBlock::Teal:
		return "TealBlock";
	case gridBlock::Yellow:
		return "YellowBlock";
	case gridBlock::Purple:
		return "PurpleBlock";
	case gridBlock::Blue:
		return "BlueBlock";
	case gridBlock::Orange:
		return "OrangeBlock";
	case gridBlock::Green:
		return "GreenBlock";
	case gridBlock::Red:
		return "RedBlock";
	case gridBlock::Empty:
		return "EmptyBlock";
	default:
		return "";
	}
}

std::string toString(eventType value) {
	switch (value) {
	case eventType::KeyDown:
		return "KeyDown";
	case eventType::KeyUp:
		return "KeyUp";
	case eventType::MouseMotion:
		return "MouseMotion";
	case eventType::MouseButtonDown:
		return "MouseButtonDown";
	case eventType::MouseButtonUp:
		return "MouseButtonUp";
	case eventType::Quit:
		return "QuitEvent";
	default:
		return "Unused";
	}
}
