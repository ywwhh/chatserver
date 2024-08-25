#ifndef USERMODEL_H
#define USERMODEL_H

#include "user.hpp"

//User表的数据操作类
class UserModel
{
public:
    // User表的增加方法
    bool insert(User &user);

    // 根据用户号码查询用户信息
    User query(int id);

    // 更新用户的状态信息
    bool updateState(User user);

    // 重置用户的状态信息
    void resetState();
    

};


#endif /* C547C8FD_ED60_4745_A1C2_22A266986B8A */
