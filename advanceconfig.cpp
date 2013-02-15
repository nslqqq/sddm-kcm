/*
    Copyright 2013 by Reza Fatahilah Shah <rshah0385@kireihana.com>
 
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.
   
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
   
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "advanceconfig.h"
#include "ui_advanceconfig.h"

#include "config.h"

AdvanceConfig::AdvanceConfig(QWidget *parent) :
    QWidget(parent)
{
    mConfig = KSharedConfig::openConfig(SDDM_CONFIG_FILE, KConfig::SimpleConfig);
    
    configUi = new Ui::AdvanceConfig();
    configUi->setupUi(this);
    
    connect(configUi->haltCommand, SIGNAL(textChanged(QString)), SIGNAL(changed()));
    connect(configUi->rebootCommand, SIGNAL(textChanged(QString)), SIGNAL(changed()));
    
    load();
}

AdvanceConfig::~AdvanceConfig()
{
    delete configUi;
}

void AdvanceConfig::load()
{
    configUi->haltCommand->setUrl(mConfig->group("General").readEntry("HaltCommand"));
    configUi->rebootCommand->setUrl(mConfig->group("General").readEntry("RebootCommand"));
}

QVariantMap AdvanceConfig::save()
{
    QVariantMap args;
    
    args["sddm.conf/General/HaltCommand"] = configUi->haltCommand->url().path();
    args["sddm.conf/General/RebootCommand"] = configUi->rebootCommand->url().path();
    
    return args;
}