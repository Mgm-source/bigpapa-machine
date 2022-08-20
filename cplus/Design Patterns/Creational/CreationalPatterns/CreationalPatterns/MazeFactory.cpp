#include "MazeFactory.h"

MazeFactory* MazeFactory::_instance = nullptr;

MazeFactory* MazeFactory::Instance()
{
	if (!_instance)
	{
		_instance = new MazeFactory;
	}
	return _instance;
}
