#ifndef spriteCollision_hpp
#define spriteCollision_hpp
#include <map>
class genericSprite;
class spriteCollision
{
public:
	typedef std::map<int, boost::shared_ptr<genericSprite> > spriteContainer;
	spriteCollision(spriteContainer &Sprites);
	~spriteCollision();
	void update(int spriteID);
	void before();

	struct collisionInfo
	{
		float x, y;
	};
	typedef std::map<int, boost::shared_ptr<collisionInfo> > collisionInfoContainer;
	collisionInfoContainer infos;
	spriteContainer &Sprites;

};

#endif // ifndef spriteCollision_hpp
