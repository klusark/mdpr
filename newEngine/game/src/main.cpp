#include "engine/engine.hpp"
#include "stdio.h"
int main()
{
	if (!engine::createWindow(300, 300, 32, "test")){
		return 0;
	}
	
	return 1;
}