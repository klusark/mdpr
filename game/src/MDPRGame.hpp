#ifndef MDPRGame_hpp
#define MDPRGame_hpp


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
