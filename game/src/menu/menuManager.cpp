#include <Poco/SharedPtr.h>
#include <Poco/Util/Application.h>
#include "menuManager.hpp"
#include <CEGUIDefaultResourceProvider.h>
#include <CEGUI.h>
#include <elements/CEGUITabControl.h>

Poco::SharedPtr<MenuManager> menu;

MenuManager::MenuManager(sf::RenderWindow &App)
	:	active(false),
		App(App)
{

	mInput = &App.GetInput();
	initializeMaps();


	try
	{
		GUIRenderer = new CEGUI::OpenGLRenderer(0, App.GetWidth(), App.GetHeight());
		MenuSystem = new CEGUI::System(GUIRenderer);
		MenuWindowManager = CEGUI::WindowManager::getSingletonPtr();
		CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*> (MenuSystem->getResourceProvider());
		rp->setDefaultResourceGroup("data");
		rp->setResourceGroupDirectory("data", "data/");
		CEGUI::SchemeManager::getSingleton().loadScheme("WindowsLook.scheme");
		CEGUI::FontManager::getSingleton().createFont("DejaVuSans-10.font");
		CEGUI::Window* sheet = MenuWindowManager->loadWindowLayout("mdpr.layout");
		MenuSystem->setGUISheet(sheet);
		//MenuSystem->setDefaultMouseCursor("WindowsLook", "MouseArrow");

		CEGUI::TabControl *tc = static_cast<CEGUI::TabControl *>(MenuWindowManager->getWindow("MainTabbedWindow"));
		

		// Add some pages to tab control
		CEGUI::String prefix = "MainTabbedWindow/";
		tc->addTab(MenuWindowManager->loadWindowLayout("ServerBrowser.layout", prefix));
		tc->addTab(MenuWindowManager->loadWindowLayout("Options.layout", prefix));
		/*CEGUI::WindowManager::WindowIterator it =  CEGUI::WindowManager::getSingleton().getIterator();
        for(; !it.isAtEnd() ; ++it) {
            const char* windowName = it.getCurrentValue()->getName().c_str();
            printf("Name: %s\n", windowName);
        }*/
		static_cast<CEGUI::PushButton*>(MenuWindowManager->getWindow("MainTabbedWindow/ServerBrowser/ConnectButton"))->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::SubscriberSlot(&MenuManager::button, this));
		CEGUI::Listbox* box = static_cast<CEGUI::Listbox*>(MenuWindowManager->getWindow("MainTabbedWindow/ServerBrowser/ServerList"));
		//box->
	}
	catch (CEGUI::Exception& e)
	{
		printf("CEGUI Exception: %s\n", e.getMessage().c_str());
		
	}
}

bool MenuManager::button(const CEGUI::EventArgs& e)
{
	printf("Pressed");
	return true;
}

MenuManager::~MenuManager()
{
}

void MenuManager::logic()
{
	currentMenu->logic();
}

void MenuManager::draw()
{
	//currentMenu->draw();
	MenuSystem->renderGUI();
}

void MenuManager::handleEvent(sf::Event& Event)
{
	switch (Event.Type)
	{
	case sf::Event::TextEntered:
		MenuSystem->injectChar(Event.Text.Unicode);
		break;
	case sf::Event::KeyPressed:
		MenuSystem->injectKeyDown(toCEGUIKey(Event.Key.Code));
		break;
	case sf::Event::KeyReleased:
		MenuSystem->injectKeyUp(toCEGUIKey(Event.Key.Code));
		break;
	case sf::Event::MouseMoved:
		MenuSystem->injectMousePosition(static_cast<float>(Event.MouseMove.X), static_cast<float>(Event.MouseMove.Y));
		break;
	case sf::Event::MouseButtonPressed:
		MenuSystem->injectMouseButtonDown(toCEGUIMouseButton(Event.MouseButton.Button));
		break;
	case sf::Event::MouseButtonReleased:
		MenuSystem->injectMouseButtonUp(toCEGUIMouseButton(Event.MouseButton.Button));
		break;
	case sf::Event::MouseWheelMoved:
		MenuSystem->injectMouseWheelChange(static_cast<float>(Event.MouseWheel.Delta));
		break;
	}
}

CEGUI::Key::Scan MenuManager::toCEGUIKey(sf::Key::Code Code)
{
	if (mKeyMap.find(Code) == mKeyMap.end()){
		return (CEGUI::Key::Scan)0;
	}

	return mKeyMap[Code];
}

CEGUI::MouseButton MenuManager::toCEGUIMouseButton(sf::Mouse::Button Button)
{
	if (mMouseButtonMap.find(Button) == mMouseButtonMap.end()){
		return (CEGUI::MouseButton)0;
	}

	return mMouseButtonMap[Button];
}

void MenuManager::changeCurrentMenu(std::string menuName)
{
	menuContainer::iterator iterator = menus.find(menuName);
	if (iterator != menus.end()){
		currentMenu = iterator->second;
		currentMenu->onChange();
	}else{
		Poco::Util::Application::instance().logger().warning("Could not find menu: " + menuName);
		//std::cout << "Could not find menu." << std::endl;
	}
}

bool MenuManager::isActive()
{
	return active;
}

void MenuManager::setActive(bool toggle)
{
	active = toggle;
}

void MenuManager::initializeMaps()
{
	mKeyMap[sf::Key::Escape]		= CEGUI::Key::Escape;
	mKeyMap[sf::Key::Num1]			= CEGUI::Key::One;
	mKeyMap[sf::Key::Num2]			= CEGUI::Key::Two;
	mKeyMap[sf::Key::Num3]			= CEGUI::Key::Three;
	mKeyMap[sf::Key::Num4]			= CEGUI::Key::Four;
	mKeyMap[sf::Key::Num5]			= CEGUI::Key::Five;
	mKeyMap[sf::Key::Num6]			= CEGUI::Key::Six;
	mKeyMap[sf::Key::Num7]			= CEGUI::Key::Seven;
	mKeyMap[sf::Key::Num8]			= CEGUI::Key::Eight;
	mKeyMap[sf::Key::Num9]			= CEGUI::Key::Nine;
	mKeyMap[sf::Key::Num0]			= CEGUI::Key::Zero;
	mKeyMap[sf::Key::Dash]			= CEGUI::Key::Minus;
	mKeyMap[sf::Key::Equal]			= CEGUI::Key::Equals;
	mKeyMap[sf::Key::Back]			= CEGUI::Key::Backspace;
	mKeyMap[sf::Key::Tab]			= CEGUI::Key::Tab;
	mKeyMap[sf::Key::Q]				= CEGUI::Key::Q;
	mKeyMap[sf::Key::W]				= CEGUI::Key::W;
	mKeyMap[sf::Key::E]				= CEGUI::Key::E;
	mKeyMap[sf::Key::R]				= CEGUI::Key::R;
	mKeyMap[sf::Key::T]				= CEGUI::Key::T;
	mKeyMap[sf::Key::Y]				= CEGUI::Key::Y;
	mKeyMap[sf::Key::U]				= CEGUI::Key::U;
	mKeyMap[sf::Key::I]				= CEGUI::Key::I;
	mKeyMap[sf::Key::O]				= CEGUI::Key::O;
	mKeyMap[sf::Key::P]				= CEGUI::Key::P;
	mKeyMap[sf::Key::LBracket]		= CEGUI::Key::LeftBracket;
	mKeyMap[sf::Key::RBracket]		= CEGUI::Key::RightBracket;
	mKeyMap[sf::Key::Return]		= CEGUI::Key::Return;
	mKeyMap[sf::Key::LControl]		= CEGUI::Key::LeftControl;
	mKeyMap[sf::Key::A]				= CEGUI::Key::A;
	mKeyMap[sf::Key::S]				= CEGUI::Key::S;
	mKeyMap[sf::Key::D]				= CEGUI::Key::D;
	mKeyMap[sf::Key::F]				= CEGUI::Key::F;
	mKeyMap[sf::Key::G]				= CEGUI::Key::G;
	mKeyMap[sf::Key::H]				= CEGUI::Key::H;
	mKeyMap[sf::Key::J]				= CEGUI::Key::J;
	mKeyMap[sf::Key::K]				= CEGUI::Key::K;
	mKeyMap[sf::Key::L]				= CEGUI::Key::L;
	mKeyMap[sf::Key::SemiColon]		= CEGUI::Key::Semicolon;
	mKeyMap[sf::Key::LShift]		= CEGUI::Key::LeftShift;
	mKeyMap[sf::Key::BackSlash]		= CEGUI::Key::Backslash;
	mKeyMap[sf::Key::Z]				= CEGUI::Key::Z;
	mKeyMap[sf::Key::X]				= CEGUI::Key::X;
	mKeyMap[sf::Key::C]				= CEGUI::Key::C;
	mKeyMap[sf::Key::V]				= CEGUI::Key::V;
	mKeyMap[sf::Key::B]				= CEGUI::Key::B;
	mKeyMap[sf::Key::N]				= CEGUI::Key::N;
	mKeyMap[sf::Key::M]				= CEGUI::Key::M;
	mKeyMap[sf::Key::Comma]			= CEGUI::Key::Comma;
	mKeyMap[sf::Key::Period]		= CEGUI::Key::Period;
	mKeyMap[sf::Key::Slash]			= CEGUI::Key::Slash;
	mKeyMap[sf::Key::RShift]		= CEGUI::Key::RightShift;
	mKeyMap[sf::Key::Multiply]		= CEGUI::Key::Multiply;
	mKeyMap[sf::Key::LAlt]			= CEGUI::Key::LeftAlt;
	mKeyMap[sf::Key::Space]			= CEGUI::Key::Space;
	mKeyMap[sf::Key::F1]			= CEGUI::Key::F1;
	mKeyMap[sf::Key::F2]			= CEGUI::Key::F2;
	mKeyMap[sf::Key::F3]			= CEGUI::Key::F3;
	mKeyMap[sf::Key::F4]			= CEGUI::Key::F4;
	mKeyMap[sf::Key::F5]			= CEGUI::Key::F5;
	mKeyMap[sf::Key::F6]			= CEGUI::Key::F6;
	mKeyMap[sf::Key::F7]			= CEGUI::Key::F7;
	mKeyMap[sf::Key::F8]			= CEGUI::Key::F8;
	mKeyMap[sf::Key::F9]			= CEGUI::Key::F9;
	mKeyMap[sf::Key::F10]			= CEGUI::Key::F10;
	mKeyMap[sf::Key::Numpad7]		= CEGUI::Key::Numpad7;
	mKeyMap[sf::Key::Numpad8]		= CEGUI::Key::Numpad8;
	mKeyMap[sf::Key::Numpad9]		= CEGUI::Key::Numpad9;
	mKeyMap[sf::Key::Subtract]		= CEGUI::Key::Subtract;
	mKeyMap[sf::Key::Numpad4]		= CEGUI::Key::Numpad4;
	mKeyMap[sf::Key::Numpad5]		= CEGUI::Key::Numpad5;
	mKeyMap[sf::Key::Numpad6]		= CEGUI::Key::Numpad6;
	mKeyMap[sf::Key::Add]			= CEGUI::Key::Add;
	mKeyMap[sf::Key::Numpad1]		= CEGUI::Key::Numpad1;
	mKeyMap[sf::Key::Numpad2]		= CEGUI::Key::Numpad2;
	mKeyMap[sf::Key::Numpad3]		= CEGUI::Key::Numpad3;
	mKeyMap[sf::Key::Numpad0]		= CEGUI::Key::Numpad0;
	mKeyMap[sf::Key::F11]			= CEGUI::Key::F11;
	mKeyMap[sf::Key::F12]			= CEGUI::Key::F12;
	mKeyMap[sf::Key::F13]			= CEGUI::Key::F13;
	mKeyMap[sf::Key::F14]			= CEGUI::Key::F14;
	mKeyMap[sf::Key::F15]			= CEGUI::Key::F15;
	mKeyMap[sf::Key::RControl]		= CEGUI::Key::RightControl;
	mKeyMap[sf::Key::Divide]		= CEGUI::Key::Divide;
	mKeyMap[sf::Key::RAlt]			= CEGUI::Key::RightAlt;
	mKeyMap[sf::Key::Pause]			= CEGUI::Key::Pause;
	mKeyMap[sf::Key::Home]			= CEGUI::Key::Home;
	mKeyMap[sf::Key::Up]			= CEGUI::Key::ArrowUp;
	mKeyMap[sf::Key::PageUp]		= CEGUI::Key::PageUp;
	mKeyMap[sf::Key::Left]			= CEGUI::Key::ArrowLeft	;
	mKeyMap[sf::Key::Right]			= CEGUI::Key::ArrowRight;
	mKeyMap[sf::Key::End]			= CEGUI::Key::End;
	mKeyMap[sf::Key::Down]			= CEGUI::Key::ArrowDown;
	mKeyMap[sf::Key::PageDown]		= CEGUI::Key::PageDown;
	mKeyMap[sf::Key::Insert]		= CEGUI::Key::Insert;
	mKeyMap[sf::Key::Delete]		= CEGUI::Key::Delete;

	mMouseButtonMap[sf::Mouse::Left]		= CEGUI::LeftButton;
	mMouseButtonMap[sf::Mouse::Middle]		= CEGUI::MiddleButton;
	mMouseButtonMap[sf::Mouse::Right]		= CEGUI::RightButton;
	mMouseButtonMap[sf::Mouse::XButton1]	= CEGUI::X1Button;
	mMouseButtonMap[sf::Mouse::XButton2]	= CEGUI::X2Button;
}
