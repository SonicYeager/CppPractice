#include <Wt/WAnchor.h>
#include <Wt/WApplication.h>
#include <Wt/WContainerwidget.h>
#include <Wt/WLink.h>
#include <Wt/WText.h>
#include <memory>

using namespace Wt;

class ControlExample : public WApplication {
private:
    std::string appName;
    WContainerWidget* _content;

public:
    ControlExample(const WEnvironment& env) : WApplication(env) {
        appName = "Application Name";
        setTitle(appName);
        _content = 0;
        internalPathChanged().connect(this, &ControlExample::onInternalPathChange);

        header();
        home();
        sidebar();
        footer();
    }

    WContainerWidget* content() {
        if (_content == 0) {
            _content = new WContainerWidget(root());
            _content->setId("content");
        }
        return _content;
    }

    void onInternalPathChange() {
        content()->clear();
        if (internalPath() == "/") {
            home();
        }
        else if (internalPath() == "/page1") {
            page1();
        }
    }

    void header() {
        std::unique_ptr<WContainerWidget> header = std::make_unique<Wt::WContainerWidget>(root());
        header->setId("header");
        header->addWidget(std::make_unique<Wt::WText>(WText("<h1>" + appName + "</h1>")));
    }

    void sidebar() {
        std::unique_ptr<WContainerWidget> sidebar = std::make_unique<Wt::WContainerWidget>(root());
        sidebar->setId("sidebar");
        sidebar->addWidget(std::make_unique<Wt::WText>(WText("Sidebar Information")));
    }

    void footer() {
        std::unique_ptr<WContainerWidget> footer = std::make_unique<Wt::WContainerWidget>(root());
        footer->setId("footer");
        footer->addWidget(std::make_unique<Wt::WText>(WText("Developed using C++/Wt")));
    }

    void home() {
        std::unique_ptr<Wt::WText> t = std::make_unique<Wt::WText>(Wt::WText("<strong>Home</strong> content and a link to <a href='#/page1'>page1</a>"));
        t->setInternalPathEncoding(true);
        content()->addWidget(t);

    }

    void page1() {
        content()->addWidget(std::make_unique<Wt::WText>(Wt::WText("<strong>Home</strong> content and a link to ")));
        std::unique_ptr<Wt::WAnchor> a = std::make_unique<Wt::WAnchor>(Wt::WLink(Wt::LinkType::InternalPath, "/"), "home", content());
    }

};

std::unique_ptr<Wt::WApplication> createApplication(const WEnvironment& env) {
    return std::make_unique<Wt::WApplication>(ControlExample(env));
}

int main(int argc, char** argv) {
    return WRun(argc, argv, &createApplication);
}