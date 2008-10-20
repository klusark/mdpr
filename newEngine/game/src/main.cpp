#include "engine/engine.hpp"
#include "stdio.h"
int main()
{
	if (!engine::window::createWindow(300, 300, 32, "test")){
		return 0;
	}
	while (1){

	}
	
	return 1;
}