#include <boost/bind.hpp>
#include "textBox.hpp"
#include "../../MDPRGame.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace GUI
{
	textBox::textBox(sf::IntRect rect)
		:	widget(),
			rect(rect),
			textArea(rect, sf::Color(0,0,0,255)),
			clickable(rect)
	{
		if (!font.LoadFromFile("data/mdpr/DejaVuSansMono.ttf", 120)){
			
		}
		boost::shared_ptr<sf::Drawable> newText(new sf::String("test", font, 15));
		text = newText;
		ptrToTextString = dynamic_cast<sf::String *>(text.get());

		text->SetX(100);
		text->SetY(300);

		onDown.connect(boost::bind(&textBox::mouseDown, this));
		onClick.connect(boost::bind(&textBox::clicked, this));
		//position = //sf::Shape::Line(sf::Vector2f(100,305), sf::Vector2f(100,315), 1, sf::Color(255,255,255,255));
	}

	textBox::~textBox()
	{
	}

	void textBox::mouseDown()
	{

	}

	void textBox::clicked()
	{
		int index;
		int mouseX = MDPR->App.GetInput().GetMouseX() - int(text->GetPosition().x);
		int end = 4;
		for(index = 0; index < end; ++index){
			sf::Vector2f before = ptrToTextString->GetCharacterPos(index);
			sf::Vector2f after =  ptrToTextString->GetCharacterPos(index + 1);
			if (before.x < mouseX && after.x > mouseX){
				std::cout<<index;
				position.SetX(floor(after.x));
			}
		}
	}
	
	void textBox::draw()
	{
		MDPR->App.Draw(*textArea.drawable.get());
		MDPR->App.Draw(*text.get());
		MDPR->App.Draw(position);
	}

	void textBox::update()
	{
		clickable::update();
	}

}
