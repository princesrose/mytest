#ifndef _USER_H_
#define _USER_H_
#include "system.h"

//用户界面UI
void usermenu(void);
//用户购买商品模式
void user(struct Type* ps, struct UserType* pos);
//选择商品
void SelectGoods(const struct Type* ps, int *str);
//删除已购商品
void DeleteGoods(int *str);
//查看已购商品  参数n代表打折数  vip判断会员购买 普通购买 注册会员购买的情况
float CheckGoods(const struct Type* ps, const int *str, float n, int vip);
//修改已购商品
void ChangeGoods(const struct Type* ps, int *str);
//结算商品  结算成功返回1,结算失败返回-1
int SettlementGoods(struct Type* ps, struct UserType* pos, int *str);
//登陆VIP  登陆成功返回1,登陆失败返回-1
int LandVIP(struct UserType* pos);
//注册VIP  注册成功返回1,注册失败返回-1
int RegisterVIP(struct UserType* pos);
//保存用户购买信息 修改货物数据
void SaveGoods(struct Type* ps, int *str);
//清空数据缓存区
void EmptyBuf(int *str);



#endif