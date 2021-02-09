#include <QDesktopServices>

#include "welcomepage.h"
#include "theme.h"
#include "wizard/owncloudwizard.h"
#include "wizard/slideshow.h"

namespace OCC {

WelcomePage::WelcomePage(OwncloudWizard *ocWizard)
    : QWizardPage()
    , _ocWizard(ocWizard)
{
    setupUi();
}

void WelcomePage::setupUi()
{
    _ui.setupUi(this);
    setupSlideShow();
    setupLoginButton();
    setupCreateAccountButton();
    setupHostYourOwnServerButton();
}

void WelcomePage::initializePage()
{
    customizeStyle();
}

void WelcomePage::styleSlideShow()
{
    const auto backgroundColor = palette().window().color();
    _ui.slideShow->addSlide(Theme::hidpiFileName("wizard-nextcloud.png", backgroundColor), tr("Keep your data secure and under your control"));
    _ui.slideShow->addSlide(Theme::hidpiFileName("wizard-files.png", backgroundColor), tr("Secure collaboration & file exchange"));
    _ui.slideShow->addSlide(Theme::hidpiFileName("wizard-groupware.png", backgroundColor), tr("Easy-to-use web mail, calendaring & contacts"));
    _ui.slideShow->addSlide(Theme::hidpiFileName("wizard-talk.png", backgroundColor), tr("Screensharing, online meetings & web conferences"));

    const auto theme = Theme::instance();
    const auto isDarkBackground = Theme::isDarkColor(backgroundColor);
    _ui.slideShowNextButton->setIcon(theme->uiThemeIcon(QString("control-next.svg"), isDarkBackground));
    _ui.slideShowPreviousButton->setIcon(theme->uiThemeIcon(QString("control-prev.svg"), isDarkBackground));
}

void WelcomePage::setupSlideShow()
{
    connect(_ui.slideShow, &SlideShow::clicked, _ui.slideShow, &SlideShow::stopShow);
    connect(_ui.slideShowNextButton, &QPushButton::clicked, _ui.slideShow, &SlideShow::nextSlide);
    connect(_ui.slideShowPreviousButton, &QPushButton::clicked, _ui.slideShow, &SlideShow::prevSlide);
}

void WelcomePage::setupLoginButton()
{
    const auto appName = Theme::instance()->appNameGUI();

    _ui.loginButton->setText(tr("Log in to your %1").arg(appName));
    connect(_ui.loginButton, &QPushButton::clicked, this, [this](bool /*checked*/) {
        _nextPage = WizardCommon::Page_ServerSetup;
        _ocWizard->next();
    });
}

void WelcomePage::setupCreateAccountButton()
{
    connect(_ui.createAccountButton, &QPushButton::clicked, this, [this](bool /*checked*/) {
        _ocWizard->setRegistration(true);
        _nextPage = WizardCommon::Page_WebView;
        _ocWizard->next();
    });
}

void WelcomePage::setupHostYourOwnServerButton()
{
    connect(_ui.hostYourOwnServerButton, &QPushButton::clicked, this, [] {
        QDesktopServices::openUrl(QUrl("https://docs.nextcloud.com/server/latest/admin_manual/installation/#installation"));
    });
}

int WelcomePage::nextId() const
{
    return _nextPage;
}

void WelcomePage::customizeStyle()
{
    WizardCommon::customizeSecondaryButtonStyle(_ui.createAccountButton);
    WizardCommon::customizeSecondaryButtonStyle(_ui.hostYourOwnServerButton);
    WizardCommon::customizePrimaryButtonStyle(_ui.loginButton);
    styleSlideShow();
}
}
