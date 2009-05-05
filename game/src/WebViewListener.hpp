#include <WebCore.h>

class WebViewListener : public Awesomium::WebViewListener
{
public:
	WebViewListener();

	void onBeginNavigation(const std::string& url);

	void onBeginLoading(const std::string& url, int statusCode, const std::wstring& mimeType);

	void onFinishLoading();

	void onCallback(const std::string& name, const Awesomium::JSArguments& args);
	
	void onReceiveTitle(const std::wstring& title);

	void onChangeTooltip(const std::wstring& tooltip);

#if defined(_WIN32)
	void onChangeCursor(const HCURSOR& cursor);
#endif

	void onChangeKeyboardFocus(bool isFocused);
};