#ifndef ListItem_hpp
#define ListItem_hpp


class ListItem : public CEGUI::ListboxTextItem
{
public:
	ListItem(const CEGUI::String& text, void* userData = 0) : ListboxTextItem(text)
	{
        setTextColours(CEGUI::colour(0,0,0));
		setSelectionBrushImage("WindowsLook", "MultiListSelectionBrush");
		setUserData(userData);
	}
};

#endif