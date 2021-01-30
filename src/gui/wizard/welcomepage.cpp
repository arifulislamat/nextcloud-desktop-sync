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
    customizeStyle();
}

void WelcomePage::setupUi()
{
    _ui.setupUi(this);
    setupSlideShow();
    setupLoginButton();
    setupCreateAccountButton();
    setupHostYourOwnServerButton();
}

void WelcomePage::setupSlideShow()
{
    const auto isDarkBackground = Theme::isDarkColor(QGuiApplication::palette().window().color());

    _ui.slideShow->addSlide(Theme::hidpiFileName(":/client/theme/white/wizard-nextcloud.png"), tr("Keep your data secure and under your control"));
    _ui.slideShow->addSlide(Theme::hidpiFileName(":/client/theme/white/wizard-files.png"), tr("Secure collaboration & file exchange"));
    _ui.slideShow->addSlide(Theme::hidpiFileName(":/client/theme/white/wizard-groupware.png"), tr("Easy-to-use web mail, calendaring & contacts"));
    _ui.slideShow->addSlide(Theme::hidpiFileName(":/client/theme/white/wizard-talk.png"), tr("Screensharing, online meetings & web conferences"));

    const auto theme = Theme::instance();
    _ui.slideShowNextButton->setIcon(theme->uiThemeIcon(QString("control-next.svg"), isDarkBackground));
    _ui.slideShowPreviousButton->setIcon(theme->uiThemeIcon(QString("control-prev.svg"), isDarkBackground));

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
        _nextPage = WizardCommon::Page_WebView;
        _ocWizard->next();
    });
}

void WelcomePage::setupHostYourOwnServerButton()
{
    auto hostYourOwnServerButtonPalette = _ui.hostYourOwnServerButton->palette();
    hostYourOwnServerButtonPalette.setColor(QPalette::ButtonText, Theme::instance()->wizardHeaderTitleColor());
    _ui.hostYourOwnServerButton->setPalette(hostYourOwnServerButtonPalette);

    connect(_ui.hostYourOwnServerButton, &QPushButton::clicked, this, []() {
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
}
}
