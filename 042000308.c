#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<time.h>
#define N 6//学生总人数
#define M 3//课程总数
typedef struct //学生基本信息的结构
{
	char xh[10];//学号,唯一标识
	char xm[20];//姓名，10个汉字以内
	char xb[3];//性别，只能保存一个汉字
	int nl;//年龄
}Student;
typedef struct//课程基本信息的结构
{
	char kh[10];//课程编号,唯一标识
	char km[25];//课程名称，12个汉字以内
	float xf;//课程学分
}Course;
typedef struct//选课信息的结构
{
	char xh[10];//学号
	char kh[10];//课程编号
	float cj;//成绩
}Select;
typedef struct
{
	char xh[10];//学号
	char xm[20];//姓名
	float cj[30];//各门课程成绩
	float zpj;//加权平均分
	float zxf;//总修课学分
}Score;

//函数原型声明
//菜单以及子菜单
int menu_select();
int disp(Student slist[],int scount,Course clist[],int ccount,Select sclist[],int sccount,Score cjlist[]);
int input(Student slist[],int *scount,Course clist[],int *ccount,Select sclist[],int *sccount,Score cjlist[]);
int del(Student slist[],int *scount,Course clist[],int *ccount,Select sclist[],int *sccount,Score cjlist[]);
int query(Student slist[],int scount,Course clist[],int ccount,Select sclist[],int sccount,Score cjlist[]);
//初始化数据：将学生基本信息导入slist,将课程基本信息导入clist,将选课信息导入sclist
void init(Student slist[],int *scount,Course clist[],int *ccount,Select sclist[],int *sccount);
//建立成绩单:依据学生基本信息表slist、课程基本信息表clist以及选课信息表sclist建立成绩单放在cjlist中。
int creat_cjlist(Select sclist[],int sccount,Course clist[],int ccount,Student slist[],int scount,Score cjlist[]);
int query_stud_index(Student slist[], int scount, char info[]);
int query_course_index(Course clist[], int ccount,char info[]);
int query_cj_index(Score cjlist[], int cjcount, char info[]);
int query_select_index(Select select[], int scount, char xh[], char kh[]);
int query_cjlist_stu_index(Score cjlist[],int cjcount,char xh[]);
//数据显示
void disp_stud(Student slist[],int scount);//显示学生基本信息
void disp_course(Course clist[],int ccount);//显示课程基本信息
void disp_cjlist(Score cjlist[],int cjcount);//显示成绩单信息
//排序
void sort_slist(Student slist[],int scount);
void sort_clist(Course clist[],int ccount);
void sort_cjlist(Score cjlist[],int cjcount);
//数据输入
int input_stud(Student slist[],int scount);
int input_course(Course clist[],int ccount);
int input_select(Student slist[],int scount,Course clist[],int ccount,Score sclist[],int sccount);
//删除记录
int delete_stud(Student slist[],int scount);
int delete_course(Course clist[],int ccount);
int delete_select(Select sclist[],int sccount);
//查询
void query_stud(Student slist[],int scount);
void query_course(Course cjlist[],int ccount);
void query_cjlist(Score cjlist[],int cjcount,Course clist[],int ccount,Student slist[],int scount);
// 查询该学号的学生的在成绩单的位置 
int query_cjlist_stu_index(Score cjlist[], int cjcount, char xh[]);
//批量输导出
void write_to_file1(Student slist[], int scount, Course clist[], int ccount, Select sclist[], int sccount);
void write_to_file2(Score cjlist[], int cjcount, Course clist[], int ccount, Student slist[], int scount);
struct tm *newtime;
    time_t tt;
int main()
{
	Student slist[50];
	Course clist[100];
	Select sclist[5000];
	Score cjlist[100];

    int n=0,scount=0,ccount=0,cjcount=0,sccount=0;
	char filename[50];
	for(;;)
	{
		switch(menu_select())
		{
		case 1:
			//从文件导入数据，进行初始化
			init(slist, &scount, clist, &ccount, sclist, &sccount);
			system("pause");  //暂停
			break;
		case 2:
			//创建成绩单
			creat_cjlist(sclist,sccount,clist,ccount,slist,scount,cjlist);
			system("pause");  //暂停
			break;
		case 3:
			//显示学生基本信息
			disp(slist,scount,clist,ccount,sclist,sccount,cjlist);
			system("pause");
			break;
		case 4:
			//输入记录
			input(slist,&scount,clist,&ccount,sclist,&sccount,cjlist);
			system("pause");
			break;
		case 5:
			//删除数据
			del(slist, &scount, clist, &ccount, sclist, &sccount, cjlist);
			system("pause");
			break;
		case 6:
			//查询
			query(slist, scount, clist, ccount, sclist, sccount, cjlist);
			system("pause");
			break;
		case 7:
			//批量导出数据
			write_to_file1(slist,scount,clist,ccount,sclist,sccount);
			write_to_file2(cjlist,cjcount,clist,ccount,slist,scount);
			system("pause");
			break;
		case 0:
			//退出
			printf("Goodbye!\n");
			exit(0);
		default:
			break;
		}
	}
}

//菜单函数menu_select
int menu_select()
{
	char c;
	do
	{
		system("cls");//清屏
		printf("1.导入初始数据\n");
		printf("2.建立成绩单\n");
		printf("3.显示信息\n");
		printf("4.输入记录\n");
		printf("5.删除记录\n");
		printf("6.查询记录\n");
		printf("7.批量导出数据\n");
		printf("0.退出\n");
		printf("请给出你的选择1-7,0:");
		c=getchar();
	}while(c<'0' || c>'7');
	return (c-'0');
}
int disp(Student slist[],int scount,Course clist[],int ccount,Select sclist[],int sccount,Score cjlist[]) {
	int op;
	int cjcount;
	do {
		printf("1.显示所有学生信息\n");
		printf("2.显示所有课程信息\n");
		printf("3.显示所有学生成绩单信息\n");
		scanf("%d", &op);
	} while (op<1 || op>3);
	
	
	switch(op) {
	case 1:
		sort_slist(slist, scount); 
		disp_stud(slist, scount);
		break;
	case 2:
		sort_clist(clist, ccount);
		disp_course(clist, ccount);
		break;
	case 3:
		cjcount = creat_cjlist(sclist, sccount, clist, ccount, slist, scount, cjlist);
		sort_cjlist(cjlist, cjcount);
		disp_cjlist(cjlist, cjcount, clist, ccount, slist, scount);
		break;
	}
	
	return op;
}

int input(Student slist[],int *scount,Course clist[],int *ccount,Select sclist[],int *sccount,Score cjlist[]) {
	int op;
	do {
		printf("1.添加学生信息\n");
		printf("2.添加课程信息\n");
		printf("3.添加选课信息\n");
		scanf("%d", &op);
	} while (op<1 || op>3);
	
	switch(op) {
	case 1:
		*scount = input_stud(slist, *scount);
		break;
	case 2:
		*ccount = input_course(clist, *ccount);
		break;
	case 3:
		*sccount = input_select(slist, *scount, clist, *ccount, sclist, *sccount);
		break;
	}
	return op;
}

int del(Student slist[],int *scount,Course clist[],int *ccount,Select sclist[],int *sccount,Score cjlist[]) {
	int op;
	do {
		printf("1.删除学生信息\n");
		printf("2.删除课程信息\n");
		printf("3.删除选课信息\n");
		scanf("%d", &op);
	} while (op<1 || op>3);
	
	switch(op) {
	case 1:
		*scount = delete_stud(slist, *scount);
		break;
	case 2:
		*ccount = delete_course(clist, *ccount);
		break;
	case 3:
		*sccount = delete_select(sclist, *sccount);
		break;
	}
	return op;
}

int query(Student slist[],int scount,Course clist[],int ccount,Select sclist[],int sccount,Score cjlist[])
{
	int op, cjcount;
	do {
		printf("1.查询学生信息\n");
		printf("2.查询课程信息\n");
		printf("3.查询选课及其成绩单信息\n");
		scanf("%d", &op);
	} while (op<1 || op>3);
	
	switch(op) {
	case 1:
		query_stud(slist, scount);
		break;
	case 2:
		query_course(clist, ccount);
		break;
	case 3:
		cjcount = creat_cjlist(sclist, sccount, clist, ccount, slist, scount, cjlist);
		query_cjlist(cjlist, cjcount, clist, ccount, slist, scount); 
		break;
	}
	return op;
}

//初始化数据
void init(Student slist[],int *scount,Course  clist[],int *ccount,Select sclist[],int *sccount)
{
	int i,a=0,b=0,c=0;
	FILE *fp1=fopen("slist.txt","r");
	FILE *fp2=fopen("clist.txt","r");
	FILE *fp3=fopen("sclist.txt","r");//打开三个文件
	if(NULL==fp1)
	{
		printf("打开slist.txt失败");
	}
	if(NULL==fp2)
	{
		printf("打开clist.txt失败");
	}
	if(NULL==fp3)
	{
		printf("打开sclist.txt失败");
	}
	for(i=0;i<N;i++)//将三个文件中的数据导入数组
	{
		fscanf(fp1,"%s %s %s %d",&slist[i].xh,&slist[i].xm,&slist[i].xb,&slist[i].nl);
		a=a+1;//计数
	}
	for(i=0;i<M;i++)
	{
		fscanf(fp2,"%s %s %f",&clist[i].kh,&clist[i].km,&clist[i].xf);
		b=b+1;
	}
	for(i=0;i<(N*M);i++)
	{
		fscanf(fp3,"%s %s %f",&sclist[i].xh,&sclist[i].kh,&sclist[i].cj);
		c=c+1;
	}
	*scount = a;
	*ccount = b;
	*sccount = c;
	printf("初始化信息成功\n");
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);//关闭文件
}
//建立成绩单
int creat_cjlist(Select sclist[],int sccount,Course clist[],int ccount,Student slist[],int scount,Score cjlist[])
{
	int i=0,m,j,t;
	for(i=0;i<scount;i++)//遍历学生人数，将前三个数组中的数据按要求导入新的成绩单数组
	{
		m=0;
		cjlist[i].zxf=0;
		strcpy(cjlist[i].xh,slist[i].xh);
		strcpy(cjlist[i].xm,slist[i].xm);
		for(j=0;j<ccount;j++)
		{
			cjlist[i].zxf=cjlist[i].zxf+clist[j].xf;
			m=m+sclist[0+i*ccount+j].cj*clist[j].xf;
		}
		cjlist[i].zpj=m/cjlist[i].zxf;
		for(t=ccount*i;t<ccount+ccount*i;t++)
		{
			cjlist[i].cj[t%ccount]=sclist[t].cj;
		}
	}

}

int query_stud_index(Student slist[], int scount, int type, char info[]) {
	int i = 0;
	for (i = 0; i < scount; ++i) {
		if (type == 1) {  // 学号 
			if (strcmp(slist[i].xh, info) == 0)
				return i;
		}
		else if (type == 2) {  // 姓名 
			if (strcmp(slist[i].xm, info) == 0)
				return i;
		}
	}
	return -1;
}

int query_course_index(Course clist[], int ccount, int type, char info[]) {
	int i = 0;
	for (i = 0; i < ccount; ++i) {
		if (type == 1) {  // 课号 
			if (strcmp(clist[i].kh, info) == 0)
				return i;
		}
		else if (type == 2) {  // 课名 
			if (strcmp(clist[i].km, info) == 0)
				return i;
		}
	}
	return -1;
}
int query_select_index(Select select[], int scount, char xh[], char kh[])
{
	int i = 0;
	for (i = 0; i < scount; ++i) {
		if (strcmp(select[i].xh, xh) == 0 && strcmp(select[i].kh, kh) == 0)
			return i;
	}
	return -1;
}
// 查询该学号的学生的在成绩单的位置 
int query_cjlist_stu_index(Score cjlist[], int cjcount, char xh[]) 
{
	int i = 0;
	for (i = 0; i < cjcount; ++i)
	{
		if (strcmp(cjlist[i].xh, xh) == 0)
			return i;
	}
	return -1;
}
//排序
void sort_slist(Student slist[],int scount)//按学号升序排序
{
	Student p[100];
	int x,y;
	for(x=0;x<N;++x)
	{
		for(y=x+1;y<N;++y)
		{
			if(strcmp(slist[x].xh,slist[y].xh)>0)
			{
				strcpy(p[x].xh,slist[x].xh);
				strcpy(p[x].xm,slist[x].xm);
				strcpy(p[x].xb,slist[x].xb);
				p[x].nl=slist[x].nl;
				strcpy(slist[x].xh,slist[y].xh);
				strcpy(slist[x].xm,slist[y].xm);
				strcpy(slist[x].xb,slist[y].xb);
				slist[x].nl=slist[y].nl;
				strcpy(slist[y].xh,p[x].xh);
				strcpy(slist[y].xm,p[x].xm);
				strcpy(slist[y].xb,p[x].xb);
				slist[y].nl=p[x].nl;
			}
		}
	}
}
void sort_clist(Course clist[], int ccount) 
{
	int i, j;
	Course temp;
	for (i = 0; i < ccount - 1; i++) 
	{
		for (j = 0; j < ccount - 1 - i; j++) 
		{
			if (strcmp(clist[j].kh, clist[j + 1].kh) > 0) 
			{
				memcpy(&temp, &clist[j], sizeof(Course));
				memcpy(&clist[j], &clist[j + 1], sizeof(Course));
				memcpy(&clist[j + 1], &temp, sizeof(Course));
			}
		}
	}
}
void sort_cjlist(Score cjlist[], int cjcount) 
{
	int i, j;
	Score temp;
	for (i = 0; i < cjcount - 1; i++) 
	{
		for (j = 0; j < cjcount - 1 - i; j++) 
		{
			if (cjlist[j].zpj < cjlist[j + 1].zpj) 
			{
				memcpy(&temp, &cjlist[j], sizeof(Score));
				memcpy(&cjlist[j], &cjlist[j + 1], sizeof(Score));
				memcpy(&cjlist[j + 1], &temp, sizeof(Score));
			}
		}
	}
}
//显示数据
void disp_stud(Student slist[],int scount)//显示学生基本信息
{
	int i;
	char str[32];
	scount=delete_stud(slist,scount);
	printf("序号\t学号\t姓名\t性别\t年龄\n");
	for (i = 0; i < scount; ++i) 
	{
		if (i % 10 == 0 && i != 0) {
			printf("输入任意字符显示下一屏\n");
			scanf("%s", str);
		}
		printf("%3d\t%5s\t%5s\t%3s\t%d\n", i + 1, slist[i].xh, slist[i].xm, slist[i].xb, slist[i].nl);
	}
}
void disp_course(Course clist[],int ccount)//显示课程基本信息
{
	int i;
	char str[32];
	ccount=delete_course(clist,ccount);
	printf("序号\t课号\t课名\t\t\t\t学分\n");
	for (i = 0; i < ccount; ++i) 
	{
		if (i % 10 == 0 && i != 0)    
		{
			printf("输入任意字符显示下一屏\n");
			scanf("%s", str);
		}
		   printf("%2.d\t%s\t%s\t\t\t%.1f\n", i + 1, clist[i].kh, clist[i].km, clist[i].xf);
	}
}
void disp_cjlist(Score cjlist[],int cjcount,Course clist[],int ccount,Student slist[],int scount)//显示学生成绩单
{
	char str[32];
	int i, j;
	for (i = 0; i < cjcount; ++i) 
	{
		if (i % 10 == 0 && i != 0) 
			{
				printf("输入任意字符显示下一屏\n");
				scanf("%s", str);
			}
		printf("名次: %d\n学号: %s\n姓名: %s\n加权平均分: %.3f\n总学分: %.3f\n", i + 1, cjlist[i].xh, cjlist[i].xm, cjlist[i].zpj, cjlist[i].zxf);
		printf("学生的选课信息以及成绩为: \n");
		for (j = 0; j < ccount; ++j) 
		    {
				if (cjlist[i].cj[j] == -2)
					continue;
				if (cjlist[i].cj[j] == -1) 
			{
				printf("课程号: %s  课程名: %s\t成绩未输入\n", clist[j].kh, clist[j].km);
			}
			else 
			{
				printf("课程号: %s  课程名: %s\t成绩: %.1f\n", clist[j].kh, clist[j].km, cjlist[i].cj[j]);
			}
		}
	}
		printf("---------------------------\n");
}

//输入数据
int input_stud(Student slist[],int scount)//输入学生基本信息
{
	int index;
	int op;
	Student stu;
	printf("请依次输入学号 姓名 性别 年龄(用空格隔开)，每一条记录占一行\n");
	printf("输入0结束输入, 输入其他数字开始输入: ");
	scanf("%d", &op);
	while (1) 
	{
		scanf("%s%s%s%d", stu.xh, stu.xm, stu.xb, &stu.nl);
		index = query_stud_index(slist, scount, 1, stu.xh);
		if (index == -1)    // 说明记录不存在 
		{ 
			memcpy(&slist[scount], &stu, sizeof(Student));
			scount = scount + 1;
		}
		else 
		{
			do 
			{
				printf("记录已经存在，请问是否替换（输入1替换 0不替换）: ");
				scanf("%d", &op);
			} while (op != 0 && op != 1);
			if (op == 1)
				memcpy(&slist[index], &stu, sizeof(Student));
		}	
		printf("输入0结束输入, 输入其他数字继续输入: ");
		scanf("%d", &op);
		if (op == 0)
			return scount;
	}
	return scount;
}
int input_course(Course clist[],int ccount)//输入课程基本信息
{
	int index;
	int op;
	Course course;
	printf("请依次输入课程号 课程名 学分(用空格隔开)，每一条记录占一行\n");
	printf("输入0结束输入, 输入其他数字开始输入: ");
	scanf("%d", &op);
	if (op == 0)
		return ccount;
	while (1) 
	{
		scanf("%s%s%f", course.kh, course.km, &course.xf);
		index = query_course_index(clist, ccount, 1, course.kh);
		if (index == -1) // 说明记录不存在
		{   
			memcpy(&clist[ccount], &course, sizeof(Course));
			ccount = ccount + 1;
		}
		else 
		{
			do 
			{
				printf("记录已经存在，请问是否替换（输入1替换 0不替换）: ");
				scanf("%d", &op);
			} 
			while (op != 0 && op != 1);
			if (op == 1)
				memcpy(&clist[index], &course, sizeof(Course));
		}
		printf("输入1继续输入， 输入0结束输入: ");
		scanf("%d", &op);
		if (op == 0)
			return ccount;
	}
	return ccount;
}

int input_select(Student slist[],int scount,Course clist[],int ccount,Select sclist[],int sccount)//输入选课信息
{
	int index, index_stu, index_course;
	int op;
	Select select;
	printf("请依次输入学号 课程号 成绩(用空格隔开，如果成绩不存在则填写-1.0)，每一条记录占一行\n");
	printf("输入0结束输入, 输入其他数字开始输入: ");
	scanf("%d", &op);
	if (op == 0)
		return sccount;
	while (1) 
	{
		scanf("%s%s%f", select.xh, select.kh, &select.cj);

		if ((select.cj < 0 && select.cj != -1) || select.cj > 120.0) {
			printf("成绩范围不合法,请重新输入");
			continue;
		}

		index_stu = query_stud_index(slist, scount, 1, select.xh);
		if (index_stu == -1) 
		{
			printf("输入学号的学生不存在,请重新输入");
			continue;
		}

		index_course = query_course_index(clist, ccount, 1, select.kh);
		if (index_course == -1) 
			{
			printf("输入课程号的课程不存在,请重新输入");
			continue;
		}

		index = query_select_index(sclist, sccount, select.xh, select.kh);
		if (index == -1) // 说明记录不存在 
		{  
			memcpy(&sclist[sccount], &select, sizeof(Select));
			sccount = sccount + 1;
		}
		else 
		{
			do 
			{
				printf("记录已经存在，请问是否替换（输入1替换 0不替换）: ");
				scanf("%d", &op);
			} while (op != 0 && op != 1);
			if (op == 1)
				memcpy(&sclist[index], &select, sizeof(Select));
		}
		printf("输入1继续输入， 输入0结束输入: ");
		scanf("%d", &op);
		if (op == 0)
			return sccount;
	}
	return sccount;
}
//删除数据
int delete_stud(Student slist[],int scount)
{
	char str[10];
	int i,g,j,q,len;
	printf("请输入删除的学生人数,如果不需要删除请按0\n");
	scanf("%d",&len);
	for(q=0;q<len;q++)
	{
		printf("请输入删除数据的学号：\n");
		scanf("%s",str);
		for(i=0;i<scount;i++)
		{
			if(0==strcmp(slist[i].xh,str))
			{
				g=1;
				for(j=i;j<scount-1;j++)
				{
					slist[j]=slist[j+1];
				}
			}
		}
	}
	return(scount-len);
}
int delete_course(Course clist[],int ccount)
{
	char str[10];
	int i,g,j,q,len;
	printf("请输入删除的课程数，如果不需要删除，请按0\n");
	scanf("%d",&len);
	for(q=0;q<len;q++)
	{
		printf("请输入删除课程的课程号：\n");
		scanf("%s",str);
		for(i=0;i<ccount;i++)
		{
			if(0==strcmp(clist[i].kh,str))
			{
				g=1;
				for(j=i;j<ccount-1;j++)
				{
					clist[j]=clist[j+1];
				}
			}
		}
	}
	return(ccount-len);
}
int delete_select(Select sclist[],int sccount)
{
	char str[10];
	int i,g,j,q,len;
	printf("请输入删除的选课信息数，如果不需要删除，请按0\n");
	scanf("%d",&len);
	for(q=0;q<len;q++)
	{
		printf("请输入删除选课信息的学生学号：\n");
		scanf("%s",str);
		for(i=0;i<sccount;i++)
		{
			if(0==strcmp(sclist[i].xh,str))
			{
				g=1;
				for(j=i;j<sccount-1;j++)
				{
					sclist[j]=sclist[j+1];
				}
			}
		}
	}
	return(sccount-len);
}

//查询
void query_stud(Student slist[],int scount)
{
	int i,g,len=0;
	char str1[10];
	printf("请输入要查询的人数");
	scanf("%d",&len);
	for(g=0;g<len;g++)
	{
		printf("请输入你要查询数据的学号：\n");
		scanf("%s",str1);
		for(i=0;i<scount;i++)
		{
			if(strcmp(slist[i].xh,str1)==0)
			{
				printf("%s %s %s %d\n",slist[i].xh,slist[i].xm,slist[i].xb,slist[i].nl);
			}
		}
	}
}
void query_course(Course clist[],int ccount)
{
	int i,g,len=0;
	char str1[10];
	printf("请输入你要查询的课程数:\n");
	scanf("%d",&len);
	for(g=0;g<len;g++)
	{
		printf("请输入你要查询数据的课号:\n");
		scanf("%s",str1);
		for(i=0;i<ccount;i++)
		{
			if(strcmp(clist[i].kh,str1)==0)
			{
				printf("%s %s %f\n",clist[i].kh,clist[i].km,clist[i].xf);
			}
		}
	}
}
void query_cjlist(Score cjlist[],int cjcount,Course clist[],int ccount,Student slist[],int scount)
{
	int i,t=0,g,a,len=0;
	char str1[10];
	printf("请输入你要查询的次数:\n");
	scanf("%d",&len);
	
	for(g=0;g<len;g++)
	{
		printf("请输入你要查询的学生的学号\n");
		scanf("%s",str1);
		for(i=0;i<N;i++)
		{
			if(strcmp(cjlist[i].xh,str1)==0)
			{
				a=query_cjlist_stu_index(cjlist,cjcount,str1);
				printf("学号%s 姓名%s 总学分%f 加权平均分%f\n名次:%d\n",cjlist[i].xh,cjlist[i].xm,cjlist[i].zxf,cjlist[i].zpj,a);
				for(t=0;t<ccount;t++)
				{
					printf("%s %f\n",clist[t].km,cjlist[i].cj[t]);
				}
			}
		}
	}
}
//导出每个学生的学生信息，每门课程的课程信息，每位学生的选课信息
void write_to_file1(Student slist[],int scount,Course clist[],int ccount,Select sclist[],int sccount)
{
	int i;
	char path[64];
	FILE* fout;
    time(&tt);
    newtime=localtime(&tt);
    sprintf(path,"%s%d%d%d%d%d%d%s","student", newtime->tm_year+1900,newtime->tm_mon+1,newtime->tm_mday,newtime->tm_hour,newtime->tm_min,newtime->tm_sec,".txt");
	fout = fopen(path, "w");
	if (fout == NULL) 
	{
		printf("打开 %s 文件失败，可能权限不足\n", path);
		return;
	}
	for (i = 0; i < scount; ++i)
		fprintf(fout, "%s\t%s\t%s\t%d\n", slist[i].xh, slist[i].xm, slist[i].xb, slist[i].nl);
	fclose(fout);

    time(&tt);
    newtime=localtime(&tt);
    sprintf(path,"%s%d%d%d%d%d%d%s","course", newtime->tm_year+1900,newtime->tm_mon+1,newtime->tm_mday,newtime->tm_hour,newtime->tm_min,newtime->tm_sec,".txt");
	
	//sprintf(path, "course%lld.txt", t);
	fout = fopen(path, "w");
	if (fout == NULL) 
	{
		printf("打开 %s 文件失败，可能权限不足\n", path);
		return;
	}
	for (i = 0; i < ccount; ++i)
		fprintf(fout, "%s\t%s\t%.1f\n", clist[i].kh, clist[i].km, clist[i].xf);
	fclose(fout);

    time(&tt);
    newtime=localtime(&tt);
    sprintf(path,"%s%d%d%d%d%d%d%s","select", newtime->tm_year+1900,newtime->tm_mon+1,newtime->tm_mday,newtime->tm_hour,newtime->tm_min,newtime->tm_sec,".txt");
	fout = fopen(path, "w");
	if (fout == NULL) 
	{
		printf("打开 %s 文件失败，可能权限不足\n", path);
		return;
	}
	for (i = 0; i < sccount; ++i)
		fprintf(fout, "%s\t%s\t%.1f\n", sclist[i].xh, sclist[i].kh, sclist[i].cj);
	fclose(fout);

	printf("导出数据1成功\n");
}
void write_to_file2(Score cjlist[],int cjcount,Course clist[],int ccount,Student slist[],int scount)
{
	int i, j,index;
	char path[64];
	FILE* fout;
    time(&tt);
    newtime=localtime(&tt);
    sprintf(path,"%s%d%d%d%d%d%d%s","score", newtime->tm_year+1900,newtime->tm_mon+1,newtime->tm_mday,newtime->tm_hour,newtime->tm_min,newtime->tm_sec,".txt");
	fout = fopen(path, "w");
	if (fout == NULL) 
	{
		printf("打开 %s 文件失败，可能权限不足\n", path);
		return;
	}
	fprintf(fout, "课程依次为: \n");
	for (i = 0; i < ccount; ++i)
		fprintf(fout, "第%d个课程号为%s，名为%s，学分为%.1f\n", i + 1, clist[i].kh, clist[i].km, clist[i].xf);
	for (i = 0; i < cjcount; ++i) 
	{   index=query_stud_index(slist,scount,1,cjlist[i].xh);
		fprintf(fout, "名次: %d\n学号: %s\n姓名: %s\n性别: %s\n加权平均分: %.3f\n总学分: %.1f\n", i + 1, cjlist[i].xh, cjlist[i].xm, slist[index].xb,cjlist[i].zpj, cjlist[i].zxf);
		fprintf(fout, "每门课成绩为: ");
		for (j = 0; j < ccount; ++j) 
		{
			if (cjlist[i].cj[j] == -1.0||cjlist[i].cj[j] == -2.0)  //
			{
				fprintf(fout, "no ");
			}
			else 
			{
				fprintf(fout, "%.2f ", cjlist[i].cj[j]);
			}
		}
		fprintf(fout, "\n---------------------------\n");
	}
	fclose(fout);
	printf("导出数据2成功\n");
}
