#include "user.h"

void usermenu(void)
{
	printf("\t\t*******************************************\t\t\n");
	printf("\t\t****	0.退 出		1.购买商品	***\t\t\n");
	printf("\t\t****	2.删除已购商品	3.查看已购商品	***\t\t\n");
	printf("\t\t****	4.修改已购商品	5.结算商品     	***\t\t\n");
	printf("\t\t*******************************************\t\t\n\n");
}

void user(struct Type* ps, struct UserType* pos)
{
	int temp;
	char q;
	//保存用户购买记录  购买成功再更改商品结构体
	int buf[ps->size];
	bzero(buf, sizeof buf);
	do
	{
		system("clear");
		goodsmenu(ps, buf);
		usermenu();
		printf("请输入对应的序号选择功能:>");
		scanf("%d", &temp);
		switch(temp)
		{
			case 0:
				break;
			case 1:
				SelectGoods(ps, buf);
				sleep(1);
				break;
			case 2:
				if(CheckGoods(ps, buf, 1, 0) == 0)
				{
					printf("您还没有选择商品,请先选择商品\n");
					sleep(1);
				}
				else
				{
					DeleteGoods(buf);
					sleep(1);
				}
				break;
			case 3:
				CheckGoods(ps, buf, 1, 0);
				sleep(3);
				printf("请输入任意字符后Enter退出:>\n");
				scanf("%c", &q);
				break;
			case 4:
				if(CheckGoods(ps, buf, 1, 0) == 0)
				{
					printf("您还没有选择商品,请先选择商品\n");
					sleep(1);
				}
				else
				{
					ChangeGoods(ps, buf);
					sleep(1);
				}
				break;
			case 5:
				//结算成功则保存现有货物信息和注册vip信息
				if(SettlementGoods(ps, pos, buf) == 1)
				{
					SaveGoods(ps, buf);
				}
				break;
			default:
				printf("序号输入正确？请重新输入\n");
				break;
		}
	}while(temp);
}
//选择商品
void SelectGoods(const struct Type* ps, int *str)
{
	int in_n, in_num;
	printf("请输入你要购买的商品编号:>");
	scanf("%d", &in_n);
	printf("请输入你要购买的商品数量:>");
	scanf("%d", &in_num);
	//判断购买数量是否过多
	if (in_num > ps->data[in_n-1].num)
	{
		printf("目前库存不足,请通知管理员补货\n");
	}
	else
	{
		//保存购买记录
		str[in_n-1] += in_num;
		printf("选择成功！\n");
	}
}
//删除已购商品
void DeleteGoods(int *str)
{
	int in_n, in_num;
	printf("请输入你要删除的商品编号:>");
	scanf("%d", &in_n);
	printf("请输入你要删除的商品数量:>");
	scanf("%d", &in_num);
	//判断是否删除过多
	if(in_num > str[in_n-1])
	{
		printf("您输入的删除数量过多,在下就直接帮你清零了吧\n");
		//删除过多直接清零
		str[in_n-1] = 0;
	}
	else
	{
		//只删除一部分的话就保存剩余商品数据
		str[in_n-1] -= in_num;
	}
	printf("删除成功！\n");
}
//查看已购商品
float CheckGoods(const struct Type* ps, const int *str, float n, int vip)
{
	int num = 0;
	float sum = 0;
	printf("\n您的商品清单有:\n");
	for (int i = 0; i < ps->size; ++i)
	{
		if (str[i] != 0)
		{
			num++;
			printf("%s\r\t\t%.2f元\r\t\t\t%d个\n", ps->data[i].name, ps->data[i].price * n, str[i]);
			sum += ps->data[i].price * n * str[i];
		}
	}
	/*
	vip == 0 普通购买或者会员购买
	vip == 1 注册会员购买
	*/
	if (vip == 0)
	{
		printf("总价\t\t%.2f元\n\n", sum);
	}
	if(vip == 1)
	{
		printf("%s\r\t\t%.2f元\r\t\t\t%d个\n", "注册会员", 100.00, 1);
		sum += 100;
		printf("总价\t\t%.2f元\n\n", sum);
	}
	return sum;
}
//修改已购商品
void ChangeGoods(const struct Type* ps, int *str)
{
	int in_n, in_num;
	printf("请输入你要修改的商品编号:>");
	scanf("%d", &in_n);
	printf("请输入你要修改的商品数量:>");
	scanf("%d", &in_num);
	//判断是否修改的商品数量过多
	if (in_num > ps->data[in_n-1].num)
	{
		printf("目前库存不足,请通知管理员补货\n");
	}
	else
	{
		//保存修改记录
		str[in_n-1] = in_num;
		printf("修改成功！\n");
	}
}
//结算商品  结算成功返回1,结算失败返回-1
int SettlementGoods(struct Type* ps, struct UserType* pos, int *str)
{
	//是否使用vip或者办理vip
	int n;
	//消费总价
	float s;
	//查看已购商品清单
	CheckGoods(ps, str, 1, 0);
	printf("请问是否有VIP账户(存在请输入1,不存在请输入0):>");
	scanf("%d", &n);
	if (n == 1)
	{
		//VIP支付
		if(LandVIP(pos) == 1)
		{
			//登陆成功
			//查看清单
			s = CheckGoods(ps, str, 0.8, 0);
			printf("请您扫码付款%.2f元:>\n", s);
			//扫码付款
			if (ScanCode())
			{
				//购买成功
				jdt();
				SaveGoods(ps, str);
				EmptyBuf(str);
				printf("支付成功！欢迎您的下次光临 \\ ^_^ /\n");
				sleep(6);
				return 1;
			}
			else
			{
				//购买失败
				printf("支付失败！\n");
				return -1;
			}
		}
	}
	else
	{
		//询问是否要办理VIP服务
		printf("请问是否需要办理VIP服务,现注册VIP可畅享购物商品八折优惠哦 ^_^ \n(办理VIP服务输入1,不办理VIP服务输入0)\n");
		scanf("%d", &n);
		if (n == 1)
		{
			//需要办理vip服务,进行vip付款
			RegisterVIP(pos);
			//登陆vip账号
			if(LandVIP(pos) == 1)
			{
				//登陆成功
				//查看清单
				s = CheckGoods(ps, str, 0.8, 1);
				printf("请您扫码付款%.2f元:>\n", s);
				//扫码付款
				if (ScanCode())
				{
					//购买成功
					jdt();
					SaveGoods(ps, str);
					EmptyBuf(str);
					printf("支付成功！欢迎您的下次光临 \\ ^_^ /\n");
					sleep(6);
					return 1;
				}
				else
				{
					//购买失败 清除注册会员记录
					bzero(pos->data[ps->size].account, sizeof pos->data[ps->size].account);
					bzero(pos->data[ps->size].passage, sizeof pos->data[ps->size].passage);
					ps->size--;
					printf("支付失败！\n");
					return -1;
				}
			}
		}
		else
		{
			//不办理vip服务,进行普通付款
			s = CheckGoods(ps, str, 1, 0);
			printf("请您扫码付款%.2f元:>\n", s);
			//扫码付款
			if (ScanCode())
			{
				//购买成功
				jdt();
				SaveGoods(ps, str);
				EmptyBuf(str);
				printf("支付成功！欢迎您的下次光临 \\ ^_^ /\n");
				sleep(6);
				return 1;
			}
			else
			{
				//购买失败
				printf("支付失败！\n");
				return -1;
			}
		}
	}
}
//登陆VIP  登陆成功返回1,登陆失败返回-1
int LandVIP(struct UserType* pos)
{
	char buf[MAX_NAME];
	int n1;
	int n2;
	int count = 0;
	while(1)
	{
		printf("请输入账号:>");
		scanf("%s", buf);
		n1 = FindByAccount(pos, buf);
		if (n1 == -1)
		{
			printf("未找到账户,请重新输入账户:>");
		}
		else
		{
			printf("账户已找到 ^_^\n");
			break;
		}
		count++;
		if (count == 3)
		{
			//登陆失败
			return -1;
		}
	}
	count = 3;
	while(1)
	{
		printf("请输入密码:>");
		scanf("%s", buf);
		n2 = FindByPassage(pos, n1, buf);
		if (n2 == -1)
		{
			printf("密码输入错误,请重新输入密码:>");
		}
		else
		{
			printf("密码输入正确 ^_^\n");
			return 1;
		}
		count--;
		if (count == 0)
		{
			//登陆失败
			return -1;
		}
	}
}

//注册VIP  注册成功返回1并且把注册数据保存到用户会员账号结构体中,注册失败返回-1
int RegisterVIP(struct UserType* pos)
{
	char account[MAX_NAME];
	char passage[MAX_NAME];
	int n;
	int count = 0;
	while(1)
	{
		printf("请输入新建账号:>");
		scanf("%s", account);
		printf("请输入账号密码:>");
		scanf("%s", passage);
		n = FindByAccount(pos, account);
		if (n == -1)
		{
			//没找到相同账户说明无重复账号,可以注册
			pos->size++;
			strcpy(pos->data[pos->size-1].account, account);
			strcpy(pos->data[pos->size-1].passage, passage);
			printf("注册成功！\n");
			break;
		}
		else
		{
			printf("有重复账号,请重新输入一个\n");
		}
	}
}

void SaveGoods(struct Type* ps, int *str)
{
	for (int i = 0; i < ps->size; ++i)
	{
		if (str[i] != 0)
		{
			ps->data[i].num -= str[i];
		}
	}
}

void EmptyBuf(int *str)
{
	memset(str, 0, sizeof(str));
}