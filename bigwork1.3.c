//C语言程序设计课程成绩管理系统
//一、	结构体变量定义
//每位学生包含以下信息：
//1. 学号；
//2. 姓名；
//3.考勤（旷课次数）
//4.课后作业成绩（9次，并求9次平均分）
//5.大作业成绩（1次）；
//6.期末考核成绩（1次）；
//7.学生总评成绩（课后作业成绩*0.15+大作业成绩*0.15+期末考核成绩*0.7）；
//二、增加学生
//	录入学生信息（学号，姓名）；
//三、录入学生信息
//   1.录入学生考勤情况；（旷课次数）
//   2.录入课后作业成绩并求出平均分；（0.0-100.0）
//   3.录入大作业成绩；（0.0-100.0）
//   4.录入期末考核成绩；（0.0-100.0）
//   5.计算总评成绩（课后作业成绩*0.15+大作业成绩*0.15+期末考核成绩*0.7）；
//四、按照学号（或姓名）查询学生信息
//五、按照学号（或姓名）修改学生信息
//六、打印所有学生信息
//注意录入学生的信息保存在一个文件内。
#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
	int number; 								//1. 学号；
	char name[20];								//2. 姓名；
	int absent;									//3.考勤（旷课次数）
	float  homework;							//4.课后作业成绩（9次，并求9次平均分）
	float bighomework;							//5.大作业成绩（1次）；
	float exam;									//6.期末考核成绩（1次）；
	float grade;								//7.学生总评成绩（课后作业成绩*0.15+大作业成绩*0.15+期末考核成绩*0.7）；
};

void scan(FILE* fp, struct student* ps, int n);
void f1search(FILE* fp, int number, int n);
void f0search(FILE* fp, char name[20], int n);
void search(FILE* fp, int n);
void alter(FILE* fp, int n);
void falter1(FILE* fp, int number, int n);
void falter0(FILE* fp, char name[20], int n);
void print(FILE* fp, int n);
int count();

int main() {
	struct student stu[100];
	FILE *fp=NULL;
	int  function;
	int n;

	printf("C语言程序设计课程成绩管理系统\n\n\n");
	
	while (1) {
		printf("\n请选择你想要的功能：\n");							//选择想要的功能 
		printf("-----------------------------------\n");
		printf("--  1:录入          --\n--  2:查询          --\n--  3:修改          --\n--  4:打印学生信息  --\n--  5:退出程序      --\n");
		printf("-----------------------------------\n");
		printf("请输入对应功能前的数字：");
		scanf("%d", &function);
		n = count();												//原来文件中有几个学生的信息；
		switch (function) {
		case 1:scan(fp, stu, n);   break;
		case 2:search(fp,n); break;									//调用搜索函数 
		case 3:alter(fp,n);break;									//调用修改函数 
		case 4:print(fp, n);break;
		case 5: goto loop;
		}
	}
loop:
	printf("退出成功！");
	

	return 0;

}
//计算函数
int count() {
	struct student a[100];
	int i = 0;
	FILE* fp;
	if ((fp = fopen("D://student.txt", "r")) == NULL) {			//以只读的方式打开文件
		printf("error");
		exit(0);
	}
	while ((fscanf(fp, "%d %s %d %f %f %f %f\n",
		&a[i].number, a[i].name, &a[i].absent, &a[i].homework, &a[i].bighomework, &a[i].exam, &a[i].grade))!=-1) {
		i++;
		if (i == 99) {
			printf("以达到储存学生信息上限！\n");
			break;
		}
	}

	return i;
}



//录入函数
void scan(FILE* fp,struct student *ps,int n) {
	int m;
	int i, j;
	float eachhomework[9] = { 0 };
	float sum=0;

	printf("请输入你要录入的学生个数:");
	scanf("%d", &m);										//需要录入的学生数量
	printf("请输入你要录入的学生的学号和姓名:\n");
	for (i = 0; i < m; i++) {								//录入学生姓名和学号 
		scanf("%d%s", &(ps+i)->number, &(ps + i)->name);
	}
	printf("\n请输入需要录入的%d个学生信息:\n\n", m);		//录入学生信息 
	for (i = 0; i < m; i++) {
		printf("请输入第%-2d个学生的考勤信息:\n", i + 1);
		scanf("%d", &(ps + i)->absent);

		printf("请输入第%-2d个学生的课后作业成绩:\n", i + 1);
		for (j = 0; j < 9; j++) {
			printf("第%d次:", j + 1);
			scanf("%f", &eachhomework[j]);
			sum = sum + eachhomework[j];					//录入每一次作业的成绩 
		}
		(ps + i)->homework = sum / 9.0;
		printf("平均课后作业成绩是:%.2f\n", (ps + i)->homework);
		sum = 0;

		printf("请输入第%-2d个学生的大作业成绩:\n", i + 1);
		scanf("%f", &(ps + i)->bighomework);

		printf("请输入第%-2d个学生的期末考核成绩:\n", i + 1);
		scanf("%f", &(ps + i)->exam);

		(ps + i)->grade = (ps + i)->homework * 0.15 + (ps + i)->bighomework * 0.15 + (ps + i)->exam * 0.7;//计算总评成绩 
		printf("该学生的总评成绩是:%.2f分\n", (ps + i)->grade);
		printf("-----------------------------------\n");
	}



	if ((fp = fopen("D://student.txt", "a")) == NULL) {		//创建一个文件 
		printf("error");
		exit(0);
	}
	for (i =0; i <m; i++) {								//写入到文件中 
		fprintf(fp, "%d %s %d %.2f %.2f %.2f %.2f\n",
			(ps + i)->number, (ps + i)->name, (ps + i)->absent, (ps + i)->homework, (ps + i)->bighomework, (ps + i)->exam, (ps + i)->grade);
	}
	fclose(fp);

}

//搜索函数 
void search(FILE* fp,int n) {
	int num;
	char name[20];
	char way[10];
	int result = 1;

	printf("请输入你想如何查询(姓名还是学号):\n");
	scanf("%s", way);
	if (strcmp(way, "姓名") == 0) {								//询问输入的是学号还是姓名 
		result = 0;												//result==0说明要输入姓名 
	}															//result==1说明要输入学号 
	if (result == 0) {
		printf("请输入名字:\n");
		scanf("%s", name);
	}
	else if (result == 1) {
		printf("请输入学号:\n");
		scanf("%d", &num);
	}
	if (result == 0) {
		f0search(fp, name,n);									//以名字搜索
	}
	if (result == 1) {											//以学号搜索
		f1search(fp, num,n);
	}

}
//以名字寻找 
void f0search(FILE* fp, char name[20],int n) {
	int i;
	int m;
	struct student a[100];
	if ((fp = fopen("D://student.txt", "r")) == NULL) {			//打开原文件 读取 
		printf("error");
		exit(0);
	}
	for (i = 0; i < n; i++) {									//存到结构体a中 
		fscanf(fp, "%d %s %d %f %f %f %f\n",
			&a[i].number, a[i].name, &a[i].absent, &a[i].homework, &a[i].bighomework, &a[i].exam, &a[i].grade);

	}
	fclose(fp);
	for (i = 0; i < n; i++) {									//寻找相同的名字 
		if (strcmp(name, a[i].name) == 0) {
			m = i;
			break;
		}
	}
	if (i < n) {
		printf("该学生的信息如下:\n学号:%d 姓名:%s\n考勤:%d,课后作业成绩:%.2f,大作业成绩:%.2f,期末考核成绩:%.2f,总评成绩:%.2f\n",
			a[m].number, a[m].name, a[m].absent, a[m].homework, a[m].bighomework, a[m].exam, a[m].grade);

	}
	else {
		printf("没有找到该学生!");
	}
	printf("完成!\n");
	printf("-----------------------------------\n");
}
//以学号寻找	
void f1search(FILE* fp, int number, int n) {
	int i;
	int m;
	struct student a[100];
	if ((fp = fopen("D://student.txt", "r")) == NULL) {			//打开原文件 读取 
		printf("error");
		exit(0);
	}
	for (i = 0; i < n; i++) {									//存到结构体a中 
		fscanf(fp, "%d %s %d %f %f %f %f\n",
			&a[i].number, a[i].name, &a[i].absent, &a[i].homework, &a[i].bighomework, &a[i].exam, &a[i].grade);

	}
	fclose(fp);

	for (i = 0; i < n; i++) {									//寻找相同的名字 
		if (number == a[i].number) {
			m = i;
			break;
		}
	}
	if (i < n) {
		printf("该学生的信息如下:\n学号:%d 姓名:%s\n考勤:%d,课后作业成绩:%.2f,大作业成绩:%.2f,期末考核成绩:%.2f,总评成绩:%.2f\n",
			a[m].number, a[m].name, a[m].absent, a[m].homework, a[m].bighomework, a[m].exam, a[m].grade);
	}
	else {
		printf("没有找到该学生!");
	}
	printf("完成!\n");
	printf("-----------------------------------\n");
}

//修改函数
void alter(FILE* fp, int n) {									//判断输入名字还是学号 
	int num;
	char name[20];
	char way[10];
	int result = 1;

	printf("请输入你想如何修改(姓名还是学号):\n");
	scanf("%s", way);
	if (strcmp(way, "姓名") == 0) {								//询问输入的是学号还是姓名 
		result = 0;												//result==0说明要输入姓名 
	}															//result==1说明要输入学号 
	if (result == 0) {
		printf("请输入名字:\n");
		scanf("%s", name);
	}
	else if (result == 1) {
		printf("请输入学号:\n");
		scanf("%d", &num);
	}
	if (result == 0) {
		falter0(fp, name,n);
	}
	else if (result == 1) {
		falter1(fp, num, n);
	}
	printf("修改成功!\n");
	printf("-----------------------------------\n");
}

//以学号修改	
void falter1(FILE* fp, int number, int n) {
	int i;
	int m;
	int want;												//储存要修改的内容的名字

	int w1;													//储存修改成的内容 学号,考勤 
	float w2;												//储存修改成的内容 成绩

	printf("选择你要修改的项目并输入前面的数字:\n");		//输入要修改的内容的名字
	printf("1.学号\n");
	printf("2.考勤\n");
	printf("3.课后作业成绩\n");
	printf("4.大作业成绩\n");
	printf("5.期末考试成绩\n");
	printf("6.总评成绩\n");

	scanf("%d", &want);
	printf("请输入修改后的内容:\n");
	switch (want) {
	case 1:
	case 2:scanf("%d", &w1); break;
	case 3:
	case 4:
	case 5:
	case 6:scanf("%f", &w2); break;
	}
	struct student a[100];
	if ((fp = fopen("D://student.txt", "r")) == NULL) {			//打开原文件 读取 
		printf("error");
		exit(0);
	}
	for (i = 0; i < n; i++) {									//存到结构体a中 
		fscanf(fp, "%d %s %d %f %f %f %f\n",
			&a[i].number, a[i].name, &a[i].absent, &a[i].homework, &a[i].bighomework, &a[i].exam, &a[i].grade);

	}
	fclose(fp);


	for (i = 0; i < n; i++) {									//寻找相同的学号 
		if (number == a[i].number) {
			m = i;
			break;
		}
	}
	if (i < n) {
		switch (want)
		{																	//改变 
		case 1: a[m].number = w1; break;
		case 2: a[m].absent = w1; break;
		case 3: a[m].homework = w2; break;
		case 4: a[m].bighomework = w2; break;
		case 5: a[m].exam = w2; break;
		case 6: a[m].grade = w2; break;
		}

	}
	else {
		printf("没有找到该学生!");
	}
	if ((fp = fopen("D://student.txt", "w")) == NULL) {					//创建一个文件 
		printf("error");
		exit(0);
	}
	for (i = 0; i < n; i++) {											//写入到文件中 
		fprintf(fp, "%d %s %d %.2f %.2f %.2f %.2f\n",
			a[i].number, a[i].name, a[i].absent, a[i].homework, a[i].bighomework, a[i].exam, a[i].grade);
	}
	fclose(fp);
}

//以名字修改 
void falter0(FILE* fp, char name[20], int n) {
	int i;
	int m;
	int want;											//储存要修改的内容的名字

	int w1;												//储存修改成的内容 学号,考勤 
	float w2;											//储存修改成的内容 成绩

	printf("选择你要修改的项目并输入前面的数字:\n");	//输入要修改的内容的名字
	printf("1.学号\n");
	printf("2.考勤\n");
	printf("3.课后作业成绩\n");
	printf("4.大作业成绩\n");
	printf("5.期末考试成绩\n");
	printf("6.总评成绩\n");

	scanf("%d", &want);
	printf("修改后的内容:\n");
	switch (want) {
	case 1:
	case 2:scanf("%d", &w1); break;
	case 3:
	case 4:
	case 5:
	case 6:scanf("%f", &w2); break;
	}
	struct student a[100];
	if ((fp = fopen("D://student.txt", "r")) == NULL) {						//打开原文件 读取 
		printf("error");
		exit(0);
	}
	for (i = 0; i < n; i++) {												//存到结构体a中 
		fscanf(fp, "%d %s %d %f %f %f %f\n",
			&a[i].number, a[i].name, &a[i].absent, &a[i].homework, &a[i].bighomework, &a[i].exam, &a[i].grade);

	}
	fclose(fp);


	for (i = 0; i < n; i++) {												//寻找相同的名字 
		if (strcmp(name, a[i].name) == 0) {
			m = i;
			break;
		}
	}
	if (i < n) {
		switch (want) {														//改变 
		case 1: a[m].number = w1; break;
		case 2: a[m].absent = w1; break;
		case 3: a[m].homework = w2; break;
		case 4: a[m].bighomework = w2; break;
		case 5: a[m].exam = w2; break;
		case 6: a[m].grade = w2; break;
		}

	}
	else {
		printf("没有找到该学生!");
	}
	if ((fp = fopen("D://student.txt", "w")) == NULL) {						//创建一个文件 
		printf("error");
		exit(0);
	}
	for (i = 0; i < n; i++) {												//写入到文件中 
		fprintf(fp, "%d %s %d %.2f %.2f %.2f %.2f\n",
			a[i].number, a[i].name, a[i].absent, a[i].homework, a[i].bighomework, a[i].exam, a[i].grade);
	}
	fclose(fp);

}
//打印函数
void print(FILE* fp, int n) {

	struct student a[100];
	int i;

	if ((fp = fopen("D://student.txt", "r")) == NULL) {					//打开原文件 读取 
		printf("error");
		exit(0);
	}
	for (i = 0; i < n; i++) {											//存到结构体a中 
		fscanf(fp, "%d %s %d %f %f %f %f\n",
			&a[i].number, a[i].name, &a[i].absent, &a[i].homework, &a[i].bighomework, &a[i].exam, &a[i].grade);

	}
	fclose(fp);
	for (i = 0; i < n; i++) {
		printf("学生信息如下:\n");
		printf("学号:%d,姓名:%s\n,考勤:%d,课后作业成绩:%.2f,大作业成绩:%.2f,期末考核成绩:%.2f,学生总评成绩:%.2f\n",
			a[i].number, a[i].name, a[i].absent, a[i].homework, a[i].bighomework, a[i].exam, a[i].grade);
	}

}




