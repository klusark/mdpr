#ifndef listBox_hpp
#define listBox_hpp

namespace GUI{
	class listBox : public widget, clickable
	{
	public:
		listBox();
		~listBox();
		void draw();
		window suroundingBox;
	};
}

#endif // ifndef listBox_hpp