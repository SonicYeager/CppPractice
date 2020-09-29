#include <Wt/WAnchor.h>
#include <Wt/WApplication.h>
#include <Wt/WContainerwidget.h>
#include <Wt/WLink.h>
#include <Wt/WText.h>
#include <Wt/cpp17/any.hpp>
#include <memory>

class ControlExample : public Wt::WApplication {
private:
    std::string appName;
    std::unique_ptr<Wt::WContainerWidget> _content = nullptr;

public:
    ControlExample(const Wt::WEnvironment& env)
        : WApplication(env) 
    {
        appName = "Application Name";
        setTitle(appName);
        internalPathChanged().connect(this, &ControlExample::onInternalPathChange);

        SetHeader();
        SetHome();
        SetSidebar();
        SetFooter();
        UpdateRoot();
    }

    void AddContent(std::unique_ptr<Wt::WWidget> widget) 
    {
        if (_content == nullptr) 
        {
            _content = std::make_unique<Wt::WContainerWidget>();
            _content->setId("content");
        }
        _content->addWidget(std::move(widget));
    }

    void UpdateRoot()
    {
        root()->addWidget(std::move(_content));
    }

    void onInternalPathChange() //navigate
    {
        if (internalPath() == "/") 
            SetHome();
        else if (internalPath() == "/page") 
            SetPage_1();
    }

    void SetHeader()
    {
        std::unique_ptr<Wt::WContainerWidget> header = std::make_unique<Wt::WContainerWidget>();
        header->setId("header");
        header->addWidget(std::make_unique<Wt::WText>("<h1>" + appName + "</h1>"));
        AddContent(std::move(header));
    }

    void SetSidebar() 
    {
        std::unique_ptr<Wt::WContainerWidget> sidebar = std::make_unique<Wt::WContainerWidget>();
        sidebar->setId("sidebar");
        sidebar->addWidget(std::make_unique<Wt::WText>("Sidebar Information"));
        AddContent(std::move(sidebar));
    }

    void SetFooter()
    {
        std::unique_ptr<Wt::WContainerWidget> footer = std::make_unique<Wt::WContainerWidget>();
        footer->setId("footer");
        footer->addWidget(std::make_unique<Wt::WText>("Developed using C++/Wt"));
        AddContent(std::move(footer));
    }

    void SetHome() 
    {
        Wt::WLink link = Wt::WLink(Wt::LinkType::InternalPath, "/page");
        link.setInternalPath("/page");

        std::unique_ptr<Wt::WAnchor> a = std::make_unique<Wt::WAnchor>(std::move(link), "<strong>Page</strong>");
        AddContent(std::move(a));
        UpdateRoot();
    }

    void SetPage_1()
    {
        Wt::WLink link = Wt::WLink(Wt::LinkType::InternalPath, "/");
        link.setInternalPath("/");

        std::unique_ptr<Wt::WAnchor> a = std::make_unique<Wt::WAnchor>(std::move(link), "<strong>Home</strong>");
        root()->addWidget(std::move(a));
        UpdateRoot();
    }

};

int main(int argc, char** argv) 
{
    auto creator = [](const Wt::WEnvironment& env) {return std::move(std::make_unique<ControlExample>(env)); };
    return Wt::WRun(argc, argv, creator);
}