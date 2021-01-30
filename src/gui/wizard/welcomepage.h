/*
 * Copyright (C) 2021 by Felix Weilbach <felix.weilbach@nextcloud.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 */

#pragma once

#include <QWizardPage>

#include "ui_welcomepage.h"
#include "wizard/owncloudwizardcommon.h"

namespace OCC {

class OwncloudWizard;

class WelcomePage : public QWizardPage
{
    Q_OBJECT

public:
    WelcomePage(OwncloudWizard *ocWizard);
    int nextId() const override;

private:
    void setupUi();
    void customizeStyle();
    void setupSlideShow();
    void setupLoginButton();
    void setupCreateAccountButton();
    void setupHostYourOwnServerButton();


    Ui_WelcomePage _ui;
    OwncloudWizard *_ocWizard;
    WizardCommon::Pages _nextPage = WizardCommon::Page_ServerSetup;
};
}
