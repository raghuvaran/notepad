//
// Created by rchowda on 11/18/2016.
//

#ifndef PP4_REGULARUSER_H
#define PP4_REGULARUSER_H


#include "User/User.h"

class regularUser : public User {
protected:
    std::string type = "regular";
    User parent;
    int failedLogins, maxFailuresAllowed;
public:
    regularUser(int userId, const std::string &userName, const std::string &password, const std::string &lastLogin, const User &parent);

    virtual std::string getUserType() override;

    virtual void loginFailed();

    virtual void clearFailedLogins() override;

    virtual bool isLocked() override;

    virtual int getMaxFailuresAllowed() const;

    virtual void setMaxFailuresAllowed(int maxFailuresAllowed);

};


#endif //PP4_REGULARUSER_H