#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<time.h>
#define N 6//ѧ��������
#define M 3//�γ�����
typedef struct //ѧ��������Ϣ�Ľṹ
{
	char xh[10];//ѧ��,Ψһ��ʶ
	char xm[20];//������10����������
	char xb[3];//�Ա�ֻ�ܱ���һ������
	int nl;//����
}Student;
typedef struct//�γ̻�����Ϣ�Ľṹ
{
	char kh[10];//�γ̱��,Ψһ��ʶ
	char km[25];//�γ����ƣ�12����������
	float xf;//�γ�ѧ��
}Course;
typedef struct//ѡ����Ϣ�Ľṹ
{
	char xh[10];//ѧ��
	char kh[10];//�γ̱��
	float cj;//�ɼ�
}Select;
typedef struct
{
	char xh[10];//ѧ��
	char xm[20];//����
	float cj[30];//���ſγ̳ɼ�
	float zpj;//��Ȩƽ����
	float zxf;//���޿�ѧ��
}Score;

//����ԭ������
//�˵��Լ��Ӳ˵�
int menu_select();
int disp(Student slist[],int scount,Course clist[],int ccount,Select sclist[],int sccount,Score cjlist[]);
int input(Student slist[],int *scount,Course clist[],int *ccount,Select sclist[],int *sccount,Score cjlist[]);
int del(Student slist[],int *scount,Course clist[],int *ccount,Select sclist[],int *sccount,Score cjlist[]);
int query(Student slist[],int scount,Course clist[],int ccount,Select sclist[],int sccount,Score cjlist[]);
//��ʼ�����ݣ���ѧ��������Ϣ����slist,���γ̻�����Ϣ����clist,��ѡ����Ϣ����sclist
void init(Student slist[],int *scount,Course clist[],int *ccount,Select sclist[],int *sccount);
//�����ɼ���:����ѧ��������Ϣ��slist���γ̻�����Ϣ��clist�Լ�ѡ����Ϣ��sclist�����ɼ�������cjlist�С�
int creat_cjlist(Select sclist[],int sccount,Course clist[],int ccount,Student slist[],int scount,Score cjlist[]);
int query_stud_index(Student slist[], int scount, char info[]);
int query_course_index(Course clist[], int ccount,char info[]);
int query_cj_index(Score cjlist[], int cjcount, char info[]);
int query_select_index(Select select[], int scount, char xh[], char kh[]);
int query_cjlist_stu_index(Score cjlist[],int cjcount,char xh[]);
//������ʾ
void disp_stud(Student slist[],int scount);//��ʾѧ��������Ϣ
void disp_course(Course clist[],int ccount);//��ʾ�γ̻�����Ϣ
void disp_cjlist(Score cjlist[],int cjcount);//��ʾ�ɼ�����Ϣ
//����
void sort_slist(Student slist[],int scount);
void sort_clist(Course clist[],int ccount);
void sort_cjlist(Score cjlist[],int cjcount);
//��������
int input_stud(Student slist[],int scount);
int input_course(Course clist[],int ccount);
int input_select(Student slist[],int scount,Course clist[],int ccount,Score sclist[],int sccount);
//ɾ����¼
int delete_stud(Student slist[],int scount);
int delete_course(Course clist[],int ccount);
int delete_select(Select sclist[],int sccount);
//��ѯ
void query_stud(Student slist[],int scount);
void query_course(Course cjlist[],int ccount);
void query_cjlist(Score cjlist[],int cjcount,Course clist[],int ccount,Student slist[],int scount);
// ��ѯ��ѧ�ŵ�ѧ�����ڳɼ�����λ�� 
int query_cjlist_stu_index(Score cjlist[], int cjcount, char xh[]);
//�����䵼��
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
			//���ļ��������ݣ����г�ʼ��
			init(slist, &scount, clist, &ccount, sclist, &sccount);
			system("pause");  //��ͣ
			break;
		case 2:
			//�����ɼ���
			creat_cjlist(sclist,sccount,clist,ccount,slist,scount,cjlist);
			system("pause");  //��ͣ
			break;
		case 3:
			//��ʾѧ��������Ϣ
			disp(slist,scount,clist,ccount,sclist,sccount,cjlist);
			system("pause");
			break;
		case 4:
			//�����¼
			input(slist,&scount,clist,&ccount,sclist,&sccount,cjlist);
			system("pause");
			break;
		case 5:
			//ɾ������
			del(slist, &scount, clist, &ccount, sclist, &sccount, cjlist);
			system("pause");
			break;
		case 6:
			//��ѯ
			query(slist, scount, clist, ccount, sclist, sccount, cjlist);
			system("pause");
			break;
		case 7:
			//������������
			write_to_file1(slist,scount,clist,ccount,sclist,sccount);
			write_to_file2(cjlist,cjcount,clist,ccount,slist,scount);
			system("pause");
			break;
		case 0:
			//�˳�
			printf("Goodbye!\n");
			exit(0);
		default:
			break;
		}
	}
}

//�˵�����menu_select
int menu_select()
{
	char c;
	do
	{
		system("cls");//����
		printf("1.�����ʼ����\n");
		printf("2.�����ɼ���\n");
		printf("3.��ʾ��Ϣ\n");
		printf("4.�����¼\n");
		printf("5.ɾ����¼\n");
		printf("6.��ѯ��¼\n");
		printf("7.������������\n");
		printf("0.�˳�\n");
		printf("��������ѡ��1-7,0:");
		c=getchar();
	}while(c<'0' || c>'7');
	return (c-'0');
}
int disp(Student slist[],int scount,Course clist[],int ccount,Select sclist[],int sccount,Score cjlist[]) {
	int op;
	int cjcount;
	do {
		printf("1.��ʾ����ѧ����Ϣ\n");
		printf("2.��ʾ���пγ���Ϣ\n");
		printf("3.��ʾ����ѧ���ɼ�����Ϣ\n");
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
		printf("1.���ѧ����Ϣ\n");
		printf("2.��ӿγ���Ϣ\n");
		printf("3.���ѡ����Ϣ\n");
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
		printf("1.ɾ��ѧ����Ϣ\n");
		printf("2.ɾ���γ���Ϣ\n");
		printf("3.ɾ��ѡ����Ϣ\n");
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
		printf("1.��ѯѧ����Ϣ\n");
		printf("2.��ѯ�γ���Ϣ\n");
		printf("3.��ѯѡ�μ���ɼ�����Ϣ\n");
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

//��ʼ������
void init(Student slist[],int *scount,Course  clist[],int *ccount,Select sclist[],int *sccount)
{
	int i,a=0,b=0,c=0;
	FILE *fp1=fopen("slist.txt","r");
	FILE *fp2=fopen("clist.txt","r");
	FILE *fp3=fopen("sclist.txt","r");//�������ļ�
	if(NULL==fp1)
	{
		printf("��slist.txtʧ��");
	}
	if(NULL==fp2)
	{
		printf("��clist.txtʧ��");
	}
	if(NULL==fp3)
	{
		printf("��sclist.txtʧ��");
	}
	for(i=0;i<N;i++)//�������ļ��е����ݵ�������
	{
		fscanf(fp1,"%s %s %s %d",&slist[i].xh,&slist[i].xm,&slist[i].xb,&slist[i].nl);
		a=a+1;//����
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
	printf("��ʼ����Ϣ�ɹ�\n");
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);//�ر��ļ�
}
//�����ɼ���
int creat_cjlist(Select sclist[],int sccount,Course clist[],int ccount,Student slist[],int scount,Score cjlist[])
{
	int i=0,m,j,t;
	for(i=0;i<scount;i++)//����ѧ����������ǰ���������е����ݰ�Ҫ�����µĳɼ�������
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
		if (type == 1) {  // ѧ�� 
			if (strcmp(slist[i].xh, info) == 0)
				return i;
		}
		else if (type == 2) {  // ���� 
			if (strcmp(slist[i].xm, info) == 0)
				return i;
		}
	}
	return -1;
}

int query_course_index(Course clist[], int ccount, int type, char info[]) {
	int i = 0;
	for (i = 0; i < ccount; ++i) {
		if (type == 1) {  // �κ� 
			if (strcmp(clist[i].kh, info) == 0)
				return i;
		}
		else if (type == 2) {  // ���� 
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
// ��ѯ��ѧ�ŵ�ѧ�����ڳɼ�����λ�� 
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
//����
void sort_slist(Student slist[],int scount)//��ѧ����������
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
//��ʾ����
void disp_stud(Student slist[],int scount)//��ʾѧ��������Ϣ
{
	int i;
	char str[32];
	scount=delete_stud(slist,scount);
	printf("���\tѧ��\t����\t�Ա�\t����\n");
	for (i = 0; i < scount; ++i) 
	{
		if (i % 10 == 0 && i != 0) {
			printf("���������ַ���ʾ��һ��\n");
			scanf("%s", str);
		}
		printf("%3d\t%5s\t%5s\t%3s\t%d\n", i + 1, slist[i].xh, slist[i].xm, slist[i].xb, slist[i].nl);
	}
}
void disp_course(Course clist[],int ccount)//��ʾ�γ̻�����Ϣ
{
	int i;
	char str[32];
	ccount=delete_course(clist,ccount);
	printf("���\t�κ�\t����\t\t\t\tѧ��\n");
	for (i = 0; i < ccount; ++i) 
	{
		if (i % 10 == 0 && i != 0)    
		{
			printf("���������ַ���ʾ��һ��\n");
			scanf("%s", str);
		}
		   printf("%2.d\t%s\t%s\t\t\t%.1f\n", i + 1, clist[i].kh, clist[i].km, clist[i].xf);
	}
}
void disp_cjlist(Score cjlist[],int cjcount,Course clist[],int ccount,Student slist[],int scount)//��ʾѧ���ɼ���
{
	char str[32];
	int i, j;
	for (i = 0; i < cjcount; ++i) 
	{
		if (i % 10 == 0 && i != 0) 
			{
				printf("���������ַ���ʾ��һ��\n");
				scanf("%s", str);
			}
		printf("����: %d\nѧ��: %s\n����: %s\n��Ȩƽ����: %.3f\n��ѧ��: %.3f\n", i + 1, cjlist[i].xh, cjlist[i].xm, cjlist[i].zpj, cjlist[i].zxf);
		printf("ѧ����ѡ����Ϣ�Լ��ɼ�Ϊ: \n");
		for (j = 0; j < ccount; ++j) 
		    {
				if (cjlist[i].cj[j] == -2)
					continue;
				if (cjlist[i].cj[j] == -1) 
			{
				printf("�γ̺�: %s  �γ���: %s\t�ɼ�δ����\n", clist[j].kh, clist[j].km);
			}
			else 
			{
				printf("�γ̺�: %s  �γ���: %s\t�ɼ�: %.1f\n", clist[j].kh, clist[j].km, cjlist[i].cj[j]);
			}
		}
	}
		printf("---------------------------\n");
}

//��������
int input_stud(Student slist[],int scount)//����ѧ��������Ϣ
{
	int index;
	int op;
	Student stu;
	printf("����������ѧ�� ���� �Ա� ����(�ÿո����)��ÿһ����¼ռһ��\n");
	printf("����0��������, �����������ֿ�ʼ����: ");
	scanf("%d", &op);
	while (1) 
	{
		scanf("%s%s%s%d", stu.xh, stu.xm, stu.xb, &stu.nl);
		index = query_stud_index(slist, scount, 1, stu.xh);
		if (index == -1)    // ˵����¼������ 
		{ 
			memcpy(&slist[scount], &stu, sizeof(Student));
			scount = scount + 1;
		}
		else 
		{
			do 
			{
				printf("��¼�Ѿ����ڣ������Ƿ��滻������1�滻 0���滻��: ");
				scanf("%d", &op);
			} while (op != 0 && op != 1);
			if (op == 1)
				memcpy(&slist[index], &stu, sizeof(Student));
		}	
		printf("����0��������, �����������ּ�������: ");
		scanf("%d", &op);
		if (op == 0)
			return scount;
	}
	return scount;
}
int input_course(Course clist[],int ccount)//����γ̻�����Ϣ
{
	int index;
	int op;
	Course course;
	printf("����������γ̺� �γ��� ѧ��(�ÿո����)��ÿһ����¼ռһ��\n");
	printf("����0��������, �����������ֿ�ʼ����: ");
	scanf("%d", &op);
	if (op == 0)
		return ccount;
	while (1) 
	{
		scanf("%s%s%f", course.kh, course.km, &course.xf);
		index = query_course_index(clist, ccount, 1, course.kh);
		if (index == -1) // ˵����¼������
		{   
			memcpy(&clist[ccount], &course, sizeof(Course));
			ccount = ccount + 1;
		}
		else 
		{
			do 
			{
				printf("��¼�Ѿ����ڣ������Ƿ��滻������1�滻 0���滻��: ");
				scanf("%d", &op);
			} 
			while (op != 0 && op != 1);
			if (op == 1)
				memcpy(&clist[index], &course, sizeof(Course));
		}
		printf("����1�������룬 ����0��������: ");
		scanf("%d", &op);
		if (op == 0)
			return ccount;
	}
	return ccount;
}

int input_select(Student slist[],int scount,Course clist[],int ccount,Select sclist[],int sccount)//����ѡ����Ϣ
{
	int index, index_stu, index_course;
	int op;
	Select select;
	printf("����������ѧ�� �γ̺� �ɼ�(�ÿո����������ɼ�����������д-1.0)��ÿһ����¼ռһ��\n");
	printf("����0��������, �����������ֿ�ʼ����: ");
	scanf("%d", &op);
	if (op == 0)
		return sccount;
	while (1) 
	{
		scanf("%s%s%f", select.xh, select.kh, &select.cj);

		if ((select.cj < 0 && select.cj != -1) || select.cj > 120.0) {
			printf("�ɼ���Χ���Ϸ�,����������");
			continue;
		}

		index_stu = query_stud_index(slist, scount, 1, select.xh);
		if (index_stu == -1) 
		{
			printf("����ѧ�ŵ�ѧ��������,����������");
			continue;
		}

		index_course = query_course_index(clist, ccount, 1, select.kh);
		if (index_course == -1) 
			{
			printf("����γ̺ŵĿγ̲�����,����������");
			continue;
		}

		index = query_select_index(sclist, sccount, select.xh, select.kh);
		if (index == -1) // ˵����¼������ 
		{  
			memcpy(&sclist[sccount], &select, sizeof(Select));
			sccount = sccount + 1;
		}
		else 
		{
			do 
			{
				printf("��¼�Ѿ����ڣ������Ƿ��滻������1�滻 0���滻��: ");
				scanf("%d", &op);
			} while (op != 0 && op != 1);
			if (op == 1)
				memcpy(&sclist[index], &select, sizeof(Select));
		}
		printf("����1�������룬 ����0��������: ");
		scanf("%d", &op);
		if (op == 0)
			return sccount;
	}
	return sccount;
}
//ɾ������
int delete_stud(Student slist[],int scount)
{
	char str[10];
	int i,g,j,q,len;
	printf("������ɾ����ѧ������,�������Ҫɾ���밴0\n");
	scanf("%d",&len);
	for(q=0;q<len;q++)
	{
		printf("������ɾ�����ݵ�ѧ�ţ�\n");
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
	printf("������ɾ���Ŀγ������������Ҫɾ�����밴0\n");
	scanf("%d",&len);
	for(q=0;q<len;q++)
	{
		printf("������ɾ���γ̵Ŀγ̺ţ�\n");
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
	printf("������ɾ����ѡ����Ϣ�����������Ҫɾ�����밴0\n");
	scanf("%d",&len);
	for(q=0;q<len;q++)
	{
		printf("������ɾ��ѡ����Ϣ��ѧ��ѧ�ţ�\n");
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

//��ѯ
void query_stud(Student slist[],int scount)
{
	int i,g,len=0;
	char str1[10];
	printf("������Ҫ��ѯ������");
	scanf("%d",&len);
	for(g=0;g<len;g++)
	{
		printf("��������Ҫ��ѯ���ݵ�ѧ�ţ�\n");
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
	printf("��������Ҫ��ѯ�Ŀγ���:\n");
	scanf("%d",&len);
	for(g=0;g<len;g++)
	{
		printf("��������Ҫ��ѯ���ݵĿκ�:\n");
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
	printf("��������Ҫ��ѯ�Ĵ���:\n");
	scanf("%d",&len);
	
	for(g=0;g<len;g++)
	{
		printf("��������Ҫ��ѯ��ѧ����ѧ��\n");
		scanf("%s",str1);
		for(i=0;i<N;i++)
		{
			if(strcmp(cjlist[i].xh,str1)==0)
			{
				a=query_cjlist_stu_index(cjlist,cjcount,str1);
				printf("ѧ��%s ����%s ��ѧ��%f ��Ȩƽ����%f\n����:%d\n",cjlist[i].xh,cjlist[i].xm,cjlist[i].zxf,cjlist[i].zpj,a);
				for(t=0;t<ccount;t++)
				{
					printf("%s %f\n",clist[t].km,cjlist[i].cj[t]);
				}
			}
		}
	}
}
//����ÿ��ѧ����ѧ����Ϣ��ÿ�ſγ̵Ŀγ���Ϣ��ÿλѧ����ѡ����Ϣ
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
		printf("�� %s �ļ�ʧ�ܣ�����Ȩ�޲���\n", path);
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
		printf("�� %s �ļ�ʧ�ܣ�����Ȩ�޲���\n", path);
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
		printf("�� %s �ļ�ʧ�ܣ�����Ȩ�޲���\n", path);
		return;
	}
	for (i = 0; i < sccount; ++i)
		fprintf(fout, "%s\t%s\t%.1f\n", sclist[i].xh, sclist[i].kh, sclist[i].cj);
	fclose(fout);

	printf("��������1�ɹ�\n");
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
		printf("�� %s �ļ�ʧ�ܣ�����Ȩ�޲���\n", path);
		return;
	}
	fprintf(fout, "�γ�����Ϊ: \n");
	for (i = 0; i < ccount; ++i)
		fprintf(fout, "��%d���γ̺�Ϊ%s����Ϊ%s��ѧ��Ϊ%.1f\n", i + 1, clist[i].kh, clist[i].km, clist[i].xf);
	for (i = 0; i < cjcount; ++i) 
	{   index=query_stud_index(slist,scount,1,cjlist[i].xh);
		fprintf(fout, "����: %d\nѧ��: %s\n����: %s\n�Ա�: %s\n��Ȩƽ����: %.3f\n��ѧ��: %.1f\n", i + 1, cjlist[i].xh, cjlist[i].xm, slist[index].xb,cjlist[i].zpj, cjlist[i].zxf);
		fprintf(fout, "ÿ�ſγɼ�Ϊ: ");
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
	printf("��������2�ɹ�\n");
}
