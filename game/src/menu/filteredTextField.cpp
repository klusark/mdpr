#include "filteredTextField.hpp"
#include <iostream>

FilteredTextField::FilteredTextField()
	:	maxCharacters(-1), noNumbers(false), noLetters(false)
{
}

FilteredTextField::~FilteredTextField()
{
}

void FilteredTextField::keyPressed(gcn::KeyEvent& keyEvent)
{
	if(!keyEvent.getKey().isCharacter()){
		gcn::TextField::keyPressed(keyEvent);
		return;
	}
	if((keyEvent.getKey().isNumber() && !noNumbers) || (keyEvent.getKey().isLetter() && !noLetters)){
		if (getText().length() < maxCharacters){
			gcn::TextField::keyPressed(keyEvent);
		}
	}
	
	
}

void FilteredTextField::setMaxCharacters(unsigned short max)
{
	maxCharacters = max;
}

void FilteredTextField::setAllowedCharacters(std::string characters, bool noNumber, bool noLetter)
{
	noNumbers = noNumber;
	noLetters = noLetter;
	allowedCharacters = characters;
}
