#ifndef _ADMIN_H_
#define _ADMIN_H_
#include "system.h"

//管理员界面UI
void adminmenu(void);
//管理员模式
void admin(struct Type* ps);
//增加商品
void AddAdmin(struct Type* ps);
//删除商品
void DeleteAdmin(struct Type* ps);
//修改商品
void ChangeAdmin(struct Type* ps);


#endif