#include "MazeFactoryImp.h"

MazeFactory* MazeFactory::_instance = nullptr;

MazeFactory* MazeFactory::instance()
{
	if (!_instance)
	{
		_instance = new MazeFactoryImp;
	}
	return _instance;
}
