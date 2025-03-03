#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;

class puzzleCollection;

class PuzzleFactory {
public:
	std::unique_ptr<puzzleCollection> CreatePuzzle15();
};
