#include "admin.h"

void adminmenu(void)
{
	printf("\t\t*******************************************\t\t\n");
	printf("\t\t****	0.退出		1.增加商品	***\t\t\n");
	printf("\t\t****	2.删除商品	3.修改商品	***\t\t\n");
	printf("\t\t*******************************************\t\t\n\n");
}

void admin(struct Type* ps)
{
	int temp;
	int buf[ps->size];
	bzero(buf, sizeof buf);
	do
	{
		system("clear");
		goodsmenu(ps, buf);
		adminmenu();
		printf("请输入对应的序号选择功能:>");
		scanf("%d", &temp);
		switch(temp)
		{
			case 0:
				break;
			case 1:
				AddAdmin(ps);
				break;
			case 2:
				DeleteAdmin(ps);
				break;
			case 3:
				ChangeAdmin(ps);
				break;
			default:
				printf("你输错了 \\ &-& / \n");
				break;
		}
	}while(temp);
}

void AddAdmin(struct Type* ps)
{
	ps->size++;
	printf("请输入商品名称:>");
	scanf("%s", ps->data[ps->size-1].name);
	printf("请输入商品价格:>");
	scanf("%f", &ps->data[ps->size-1].price);
	printf("请输入商品个数:>");
	scanf("%d", &ps->data[ps->size-1].num);
	printf("添加商品 %s 成功！", ps->data[ps->size-1].name);
	ps->data[ps->size-1].n = ps->data[ps->size-2].n + 1;
}

void DeleteAdmin(struct Type* ps)
{
	int n;
	printf("请输入要删除的商品编号:>");
	scanf("%d", &n);
	for (int i = n-1; i < ps->size-1; ++i)
	{
		ps->data[i].n = ps->data[i+1].n;
		strcpy(ps->data[i].name, ps->data[i+1].name);
		ps->data[i].price = ps->data[i+1].price;
		ps->data[i].num = ps->data[i+1].num;
	}
	ps->data[ps->size-1].n = 0;
	bzero(ps->data[ps->size-1].name, sizeof ps->data[ps->size-1].name);
	ps->data[ps->size-1].price = 0;
	ps->data[ps->size-1].num = 0;
	ps->size--;
}

void ChangeAdmin(struct Type* ps)
{
	int n;
	char buf[MAX_NAME] = {0};
	printf("请输入要修改的商品编号:>");
	scanf("%d", &n);
	printf("请输入商品名称:>");
	scanf("%s", buf);
	strcpy(ps->data[n-1].name, buf);
	printf("请输入商品价格:>");
	scanf("%f", &ps->data[n-1].price);
	printf("请输入商品个数:>");
	scanf("%d", &ps->data[n-1].num);
	printf("修改商品 %s 成功！", ps->data[n-1].name);
}