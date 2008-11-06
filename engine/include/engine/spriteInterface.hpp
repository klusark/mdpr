#ifndef spriteInterface_hpp
#define spriteInterface_hpp

namespace engine
{
	class spriteInterface
	{
	protected :
		spriteInterface * pcChild;
	public :
		virtual ~spriteInterface(){};
		virtual void DynamicFunction1() =0;
		virtual void DynamicFunction2() =0;
		virtual void DynamicFunction3() =0;
		virtual void DynamicFunction4() =0;
	};
}

#endif
