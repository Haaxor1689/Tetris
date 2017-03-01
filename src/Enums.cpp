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