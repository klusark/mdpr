#ifndef MDPRGame_hpp
#define MDPRGame_hpp
#if _MSC_VER > 1000
#pragma once
#endif

class MDPRGame
{
public:
	MDPRGame();
	~MDPRGame();
	void run();
	void onWindowClose();
private:
	bool quit;
};

#endif
