#ifndef FILTEREDTEXTFIELD_HPP
#define FILTEREDTEXTFIELD_HPP

#include <boost/signal.hpp>
#include <guichan.hpp>
#include <string>

class FilteredTextField : public gcn::TextField
{
public:
	FilteredTextField();
	~FilteredTextField();
	void keyPressed(gcn::KeyEvent& keyEvent);
	void setMaxCharacters(unsigned short max);
	void setAllowedCharacters(std::string characters, bool noNumber = false, bool noLetter = false);
private:
	std::string allowedCharacters;
	unsigned short maxCharacters;
	bool noNumbers, noLetters;


};

#endif // #ifndef FILTEREDTEXTFIELD_HPP