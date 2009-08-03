#ifndef ListItem_hpp
#define ListItem_hpp


class ListItem : public CEGUI::ListboxTextItem
{
public:
	ListItem(const CEGUI::String& text) : ListboxTextItem(text)
	{
        setTextColours(CEGUI::colour(0,0,0));
		setSelectionBrushImage("WindowsLook", "MultiListSelectionBrush");
	}
};

#endif