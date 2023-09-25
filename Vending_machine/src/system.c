#include "system.h"
#include "user.h"
#include "admin.h"
void menu(void)
{
	printf("\t\t**************************************************\t\t\n");
	printf("\t\t****************    1.购 物    *******************\t\t\n");
	printf("\t\t****************    2.管 理    *******************\t\t\n");
	printf("\t\t****************    0.退 出    *******************\t\t\n");
	printf("\t\t**************************************************\t\t\n");
}

void goodsmenu(const struct Type* ps, const int *str)
{
	printf("\t\t-------------------------------------------\t\t\n");
	printf("\t\t  商品                  价格           数量\n");
	for (int i = 0; i < ps->size; ++i)
	{
		//打印商品结构体里面的所有保存商品信息
		if (str[i] != 0)
		{
			printf("\t\t%d.%s\r\t\t\t\t\t%.2f\r\t\t\t\t\t\t\t%d\t\t\n", 
				ps->data[i].n, ps->data[i].name, ps->data[i].price, ps->data[i].num-str[i]);
		}
		else
		{
			printf("\t\t%d.%s\r\t\t\t\t\t%.2f\r\t\t\t\t\t\t\t%d\t\t\n", 
				ps->data[i].n, ps->data[i].name, ps->data[i].price, ps->data[i].num);
		}
	}
	printf("\t\t-------------------------------------------\t\t\n");
}

void System(void)
{
	int input = 0;
	//创建货物单
	struct Type ps;
	//创建VIP用户
	struct UserType pos;
	//设置随机种子
	srand((unsigned)time(NULL));
	//初始化货物单
	Initsystem(&ps, &pos);
	do
	{
		system("clear");
		menu();
		printf("请选择：>");
		scanf("%d", &input);
		switch(input)
		{
			case 0:
				printf("正在保存数据--->> ");
				//清空文件,并向文件导入VIP用户和货物单信息
				SaveSystem(&ps, &pos);
				System_jdt();
				printf("感谢您的陪伴,我们下个版本见! \\ ^_^ /\n");
				sleep(3);
				exit(0);
				break;
			case 1:
				//用户模式,进行购物
				user(&ps, &pos);
				break;
			case 2:
				//管理员模式,进行商品管理
				if (CheckingAdmin() == 1)
				{
					printf("验证成功！进入管理员模式\n");
					admin(&ps);
				}
				else
				{
					printf("验证失败,你是假的管理员! \\ # # /\n");
				}
				break;
			default:
				printf("有问题 @_@\n请重新输入\n");
				break;
		}
	}while(1);
}
//fp1-->fpGoods  fp2-->fpUser
void Initsystem(struct Type* ps, struct UserType* pos)
{
	//打开保存的数据文件
	FILE* fpUser;
	fpUser = fopen(PATH_USER, "at+");
	if (fpUser == NULL)
	{
		printf("%s\n", strerror(errno));
		return;
	}
	FILE* fpGoods;
	fpGoods = fopen(PATH_GOODS, "at+");
	if (fpGoods == NULL)
	{
		printf("%s\n", strerror(errno));
		return;
	}
	//memset(ps->data, 0, sizeof(ps->data));
	//memset(pos->data, 0, sizeof(pos->data));
	//存放读取数据
	int temp = 0;
	//读取文档中的货物信息到Type结构体中完成初始化
	while(temp = fscanf(fpGoods, "%d %s %f %d", &ps->data[ps->size].n, ps->data[ps->size].name, &ps->data[ps->size].price, &ps->data[ps->size].num) >= 4)
	{
		ps->size++;
	}
	//读取文档中的vip用户信息到UserType结构体中完成初始化
	while(temp = fscanf(fpUser, "%s %s", pos->data[pos->size].account, pos->data[pos->size].passage) >= 2)
	{
		pos->size++;
	}
	//关闭文件
	fclose(fpGoods);
	fclose(fpUser);
}

void System_jdt(void)
{
	//系统结束进度条
	int i = 0;
	char buf[102] = "#";
	char sym[] = "/|-\\";
	for (i = 1; i <= 50; ++i)
	{
		buf[i] = '#';
		printf("%s[%d%%][%c]\r", buf, i*2, sym[i % 4]);
		fflush(stdout);
		usleep(80000);
	}
	printf("\n");
}

void jdt(void)
{
	//用户结算和管理员保存数据的进度条
	int i = 0;
	char buf[102] = "#";
	char sym[] = "/|-\\";
	for (i = 1; i <= 50; ++i)
	{
		buf[i] = '#';
		printf("%s[%c]\r", buf, sym[i % 4]);
		fflush(stdout);
		usleep(80000);
	}
	printf("\n");
}

int FindByAccount(const struct UserType* pos, const char *str)
{
	//找到账户名,找到了就返回下标,没找到就返回-1
	int i = 0;
	for (i = 0; i < pos->size; ++i)
	{
		if(strcmp(pos->data[i].account, str) == 0)
		{
			//printf("账户已找到 ^_^\n");
			return i;
		}
	}
	//printf("未找到账户,请重新输入账户:>");
	return -1;
}

int FindByPassage(const struct UserType* pos, int i, const char *str)
{
	//匹配对于账户的密码,输入正确返回1,输入错误三次后返回-1
	if (strcmp(pos->data[i].passage, str) == 0)
	{
		//printf("密码输入正确 ^_^\n");
		return 1;
	}
	//printf("密码输入错误,请重新输入密码:>");
	return -1;
}

//fp1-->fpGoods  fp2-->fpUser
void SaveSystem(struct Type* ps, struct UserType* pos)
{
	//删除原有的数据文件
	remove(PATH_GOODS);
	remove(PATH_USER);
	//新建数据文件保存新的信息
	FILE* fpUser;
	fpUser = fopen(PATH_USER, "wt+");
	if (fpUser == NULL)
	{
		printf("%s\n", strerror(errno));
		return;
	}
	FILE* fpGoods;
	fpGoods = fopen(PATH_GOODS, "wt+");
	if (fpGoods == NULL)
	{
		printf("%s\n", strerror(errno));
		return;
	}
	//保存货物信息
	for (int i = 0; i < ps->size; ++i)
	{
		fprintf(fpGoods, "%d %s %f %d\n", 
			ps->data[i].n, ps->data[i].name,
			ps->data[i].price, ps->data[i].num);
	}
	//保存会员用户信息
	for (int i = 0; i < pos->size; ++i)
	{
		fprintf(fpUser, "%s %s\n", 
			pos->data[i].account, pos->data[i].passage);
	}
	//关闭文件
	fclose(fpGoods);
	fclose(fpUser);
}

//管理员登陆验证  验证成功返回1,验证失败返回-1
int CheckingAdmin(void)
{
	char account[MAX_NAME];
	char passage[MAX_NAME];
	printf("请输入管理员账号:>");
	scanf("%s", account);
	printf("请输入管理员密码:>");
	scanf("%s", passage);
	if ((strcmp(admin_ac, account) == 0) && (strcmp(admin_pg, passage) == 0))
	{
		return 1;
	}
	return -1;
}

long rand_num(void)
{
	long rand_num_rand = 1;
	while(rand_num_rand < 100000000)
	{
		rand_num_rand *= rand()%99;
	}
	return rand_num_rand;
}

//扫描条码  扫描成功返回1,扫描失败返回-1
int ScanCode(void)
{
	char buf[MAX_NAME];
	//验证数
	long n1 = rand_num();
	long n2;
	printf("您的付款码是:>%ld\n", n1);
	printf("请扫码:>");
	scanf("%s", buf);
	n2 = atoi(buf);
	if (n1 == n2)
	{
		printf("扫码成功！\n");
		return 1;
	}
	else
	{
		printf("扫码失败！\n");
		return -1;
	}
}