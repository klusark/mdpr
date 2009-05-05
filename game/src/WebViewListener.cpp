#include "MDPRGame.hpp"
#include "WebViewListener.hpp"

WebViewListener::WebViewListener()
{
}

void WebViewListener::onBeginNavigation(const std::string& url)
{
	std::cout << "Navigating to URL: " << url << std::endl;
}

void WebViewListener::onBeginLoading(const std::string& url, int statusCode, const std::wstring& mimeType)
{
	std::cout << "Begining to load URL: " << url;
	std::cout << "\n\twith status code: " << statusCode;
	std::wcout << L"\n\twith mime-type: " << mimeType << std::endl;
}

void WebViewListener::onFinishLoading()
{
	std::cout << "Finished loading the page!" << std::endl;

	MDPR->isRunning = true;
}

void WebViewListener::onCallback(const std::string& name, const Awesomium::JSArguments& args)
{
	if (name == "Quit"){
		MDPR->quitGame();
	}else if (name == "populateResolution"){
		MDPR->webView->executeJavascript("document.getElementById('Resolution').options.length = 0;");
	}
}

void WebViewListener::onReceiveTitle(const std::wstring& title)
{
}

void WebViewListener::onChangeTooltip(const std::wstring& tooltip)
{
}

#if defined(_WIN32)
void WebViewListener::onChangeCursor(const HCURSOR& cursor)
{
}
#endif

void WebViewListener::onChangeKeyboardFocus(bool isFocused)
{
}