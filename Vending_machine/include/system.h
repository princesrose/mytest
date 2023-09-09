#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#define MAX 100
#define MAX_NAME 40
#define PATH_GOODS "./txt/goods.txt"
#define PATH_USER "./txt/user.txt"
#define admin_ac "admin"
#define admin_pg "123456"
//商品信息
struct Goods
{
	int n;							//商品编号
	char name[MAX_NAME];			//商品名称
	float price;					//商品价格
	int num;						//商品个数						
};
//商品类型
struct Type
{
	struct Goods data[MAX];			//单个商品信息
	int size;						//已保存的商品个数
};

//用户信息
struct User
{
	char account[MAX_NAME];			//VIP用户账号
	char passage[MAX_NAME];			//VIP用户密码
};
//用户类型
struct UserType
{
	struct User data[MAX];			//单个VIP用户信息
	int size;						//已保存的VIP用户个数
};

//售货机界面UI
void menu(void);
//商品界面UI
void goodsmenu(const struct Type* ps, const int *str);
//售货机主界面
void System(void);
//初始化货物单和VIP用户信息
void Initsystem(struct Type* ps, struct UserType* pos);
//系统结束进度条
void System_jdt(void);
//用户结算和管理员保存数据的进度条
void jdt(void);
//找到账户名,找到了就返回下标,没找到就返回-1
int FindByAccount(const struct UserType* pos, const char *str);
//匹配对于账户的密码,输入正确返回1,输入错误返回-1
int FindByPassage(const struct UserType* pos, int i, const char *str);
//创建随机数
long rand_num(void);
//扫描条码  扫描成功返回1,扫描失败返回-1
int ScanCode(void);
//清空文件,并向文件导入VIP用户和货物单信息
void SaveSystem(struct Type* ps, struct UserType* pos);
//管理员登陆验证  验证成功返回1,验证失败返回-1
int CheckingAdmin(void);

#endif
