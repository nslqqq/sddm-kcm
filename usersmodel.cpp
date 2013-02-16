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

#include "usersmodel.h"

#include <KUser>
#include <KLocalizedString>

UsersModel::UsersModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

UsersModel::~UsersModel()
{
}

int UsersModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    
    return mUserList.size();
}

QVariant UsersModel::data(const QModelIndex &index, int role) const
{
    const KUser user = mUserList[index.row()];
    
    switch(role) {
        case Qt::DisplayRole:
            return (index.row() == 0 ) ? "<No Autologin>" : user.loginName();
    }
    
    return QVariant();
}

void UsersModel::add(const KUser &user)         
{
    beginInsertRows(QModelIndex(), mUserList.count(), mUserList.count());
    
    mUserList.append( KUser(user) );
    
    endInsertRows();
}

void UsersModel::populate(const int minimumUid) {
    KUser firstUser("No Autologin");
    
    QList< KUser > userList = KUser::allUsers();
    
    KUser user;
    add(firstUser);
    
    foreach( user, userList ) {
        if (user.uid() >= minimumUid) {
            add(user);
        }
        /*kDebug() << user.loginName() << ",uid" << user.uid();
        kDebug() << " home:" << user.homeDir();
        kDebug() << " isSuperUser:" << user.isSuperUser() << ",isValid:" << user.isValid();
        kDebug() << " faceIconPath:" << user.faceIconPath();*/
    }
}
    