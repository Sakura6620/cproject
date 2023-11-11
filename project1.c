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

#define N 1										//录入学生个数 
struct student {
	int number; 								//1. 学号；
	char name[20];								//2. 姓名；
	int absent;									//3.考勤（旷课次数）
	float  homework;							//4.课后作业成绩（9次，并求9次平均分）
	float bighomework;							//5.大作业成绩（1次）；
	float exam;									//6.期末考核成绩（1次）；
	float grade;								//7.学生总评成绩（课后作业成绩*0.15+大作业成绩*0.15+期末考核成绩*0.7）；
};

void f1search(FILE* fp, int number);
void f0search(FILE* fp, char name[20]);
void search(FILE* fp);
void alter(FILE* fp);
void falter1(FILE* fp, int number);
void falter0(FILE* fp, char name[20]);
void print(FILE* fp);
int main() {
	struct student stu[N];
	struct student a[N];
	float eachhomework[9] = { 0 };
	float sum = 0;
	int  function;
	FILE* fp;
	int i;
	int j;

	printf("C语言程序设计课程成绩管理系统\n");
	printf("-----------------------------------\n");
	printf("\n请输入需要录入的学号和姓名:\n");
	for (i = 0; i < N; i++) {							//录入学生姓名和学号 
		scanf("%d%s", &stu[i].number, &stu[i].name);
	}
	printf("完成!\n");

	printf("请输入需要录入的学生信息\n\n");		//录入学生信息 
	for (i = 0; i < N; i++) {
		printf("请输入第%-2d个学生的考勤信息:\n", i + 1);
		scanf("%d", &stu[i].absent);

		printf("请输入第%-2d个学生的课后作业成绩:\n", i + 1);
		for (j = 0; j < 9; j++) {
			printf("第%d次:", j + 1);
			scanf("%f", &eachhomework[j]);
			sum = sum + eachhomework[j];	//录入每一次作业的成绩 
		}
		stu[i].homework = sum / 9.0;
		printf("平均课后作业成绩是:%.2f\n", stu[i].homework);
		sum = 0;

		printf("请输入第%-2d个学生的大作业成绩:\n", i + 1);
		scanf("%f", &stu[i].bighomework);

		printf("请输入第%-2d个学生的期末考核成绩:\n", i + 1);
		scanf("%f", &stu[i].exam);

		stu[i].grade = stu[i].homework * 0.15 + stu[i].bighomework * 0.15 + stu[i].exam * 0.7;//计算总评成绩 
		printf("该学生的总评成绩是:%.2f分\n", stu[i].grade);
		printf("-----------------------------------\n");
	}

	if ((fp = fopen("D://student.txt", "w")) == NULL) {		//创建一个文件 
		printf("error");
		exit(0);
	}
	for (i = 0; i < N; i++) {								//写入到文件中 
		fprintf(fp, "%d %s %d %.2f %.2f %.2f %.2f\n",
			stu[i].number, stu[i].name, stu[i].absent, stu[i].homework, stu[i].bighomework, stu[i].exam, stu[i].grade);
	}
	fclose(fp);

	while (1) {
		printf("\n请选择你想要的功能：\n");					//选择想要的功能 
		printf("1:查询\n2:修改\n3:退出程序\n");
		scanf("%d", &function);
		switch (function) {
		case 1:search(fp); break;						//调用搜索函数 
		case 2:alter(fp);	break;						//调用修改函数 
		case 3:goto loop;
		}
	}
		
	
	loop:

	printf("-----------------------------------\n");


	print(fp);

	return 0;

}

//搜索函数 
void search(FILE* fp) {
	int num;
	int i;
	char name[20];
	char way[10];
	int result = 1;

	printf("请输入你想如何查询(姓名还是学号):\n");
	scanf("%s", way);
	if (strcmp(way, "姓名") == 0) {								//询问输入的是学号还是姓名 
		result = 0;											//result==0说明要输入姓名 
	}													    //result==1说明要输入学号 
	if (result == 0) {
		printf("请输入名字:\n");
		scanf("%s", name);
	}
	else if (result == 1) {
		printf("请输入学号:\n");
		scanf("%d", &num);
	}
	if (result == 0) {
		f0search(fp, name);
	}
	if (result == 1) {
		f1search(fp, num);
	}

}


//以名字寻找 
void f0search(FILE* fp, char name[20]) {
	int i;
	int m;
	struct student a[N];
	if ((fp = fopen("D://student.txt", "r")) == NULL) {	//打开原文件 读取 
		printf("error");
		exit(0);
	}
	for (i = 0; i < N; i++) {								//存到结构体a中 
		fscanf(fp, "%d %s %d %f %f %f %f\n",
			&a[i].number, a[i].name, &a[i].absent, &a[i].homework, &a[i].bighomework, &a[i].exam, &a[i].grade);

	}
	fclose(fp);
	for (i = 0; i < N; i++) {								//寻找相同的名字 
		if (strcmp(name, a[i].name) == 0) {
			m = i;
			break;
		}
	}
	if (i < N) {
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
void f1search(FILE* fp, int number) {
	int i;
	int m;
	struct student a[N];
	if ((fp = fopen("D://student.txt", "r")) == NULL) {	//打开原文件 读取 
		printf("error");
		exit(0);
	}
	for (i = 0; i < N; i++) {								//存到结构体a中 
		fscanf(fp, "%d %s %d %f %f %f %f\n",
			&a[i].number, a[i].name, &a[i].absent, &a[i].homework, &a[i].bighomework, &a[i].exam, &a[i].grade);

	}
	fclose(fp);

	for (i = 0; i < N; i++) {								//寻找相同的名字 
		if (number == a[i].number) {
			m = i;
			break;
		}
	}
	if (i < N) {
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
void alter(FILE* fp) {										//判断输入名字还是学号 
	int num;
	int i;
	char name[20];
	char way[10];
	int result = 1;

	printf("请输入你想如何修改(姓名还是学号):\n");
	scanf("%s", way);
	if (strcmp(way, "姓名") == 0) {								//询问输入的是学号还是姓名 
		result = 0;											//result==0说明要输入姓名 
	}													    //result==1说明要输入学号 
	if (result == 0) {
		printf("请输入名字:\n");
		scanf("%s", name);
	}
	else if (result == 1) {
		printf("请输入学号:\n");
		scanf("%d", &num);
	}
	if (result == 0) {
		falter0(fp, name);
	}
	else if (result == 1) {
		falter1(fp, num);
	}
	printf("修改成功!\n");
	printf("-----------------------------------\n");
}

//以学号修改	
void falter1(FILE* fp, int number) {
	int i;
	int m;
	int want;											//储存要修改的内容的名字

	int w1;												//储存修改成的内容 学号,考勤 
	float w2;											//储存修改成的内容 成绩

	printf("选择你要修改的项目并输入前面的数字:\n");//输入要修改的内容的名字
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
	struct student a[N];
	if ((fp = fopen("D://student.txt", "r")) == NULL) {	//打开原文件 读取 
		printf("error");
		exit(0);
	}
	for (i = 0; i < N; i++) {								//存到结构体a中 
		fscanf(fp, "%d %s %d %f %f %f %f\n",
			&a[i].number, a[i].name, &a[i].absent, &a[i].homework, &a[i].bighomework, &a[i].exam, &a[i].grade);

	}
	fclose(fp);


	for (i = 0; i < N; i++) {								//寻找相同的学号 
		if (number == a[i].number) {
			m = i;
			break;
		}
	}
	if (i < N) {
		switch (want)
		{							//改变 
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
	if ((fp = fopen("D://student.txt", "w")) == NULL) {	//创建一个文件 
		printf("error");
		exit(0);
	}
	for (i = 0; i < N; i++) {								//写入到文件中 
		fprintf(fp, "%d %s %d %.2f %.2f %.2f %.2f\n",
			a[i].number, a[i].name, a[i].absent, a[i].homework, a[i].bighomework, a[i].exam, a[i].grade);
	}
	fclose(fp);
}

//以名字修改 
void falter0(FILE* fp, char name[20]) {
	int i;
	int m;
	int want;											//储存要修改的内容的名字

	int w1;												//储存修改成的内容 学号,考勤 
	float w2;											//储存修改成的内容 成绩

	printf("选择你要修改的项目并输入前面的数字:\n");//输入要修改的内容的名字
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
	struct student a[N];
	if ((fp = fopen("D://student.txt", "r")) == NULL) {	//打开原文件 读取 
		printf("error");
		exit(0);
	}
	for (i = 0; i < N; i++) {								//存到结构体a中 
		fscanf(fp, "%d %s %d %f %f %f %f\n",
			&a[i].number, a[i].name, &a[i].absent, &a[i].homework, &a[i].bighomework, &a[i].exam, &a[i].grade);

	}
	fclose(fp);


	for (i = 0; i < N; i++) {								//寻找相同的名字 
		if (strcmp(name, a[i].name) == 0) {
			m = i;
			break;
		}
	}
	if (i < N) {
		switch (want) {							//改变 
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
	if ((fp = fopen("D://student.txt", "w")) == NULL) {	//创建一个文件 
		printf("error");
		exit(0);
	}
	for (i = 0; i < N; i++) {								//写入到文件中 
		fprintf(fp, "%d %s %d %.2f %.2f %.2f %.2f\n",
			a[i].number, a[i].name, a[i].absent, a[i].homework, a[i].bighomework, a[i].exam, a[i].grade);
	}
	fclose(fp);

}
void print(FILE* fp) {

	struct student a[N];
	int i;

	if ((fp = fopen("D://student.txt", "r")) == NULL) {	//打开原文件 读取 
		printf("error");
		exit(0);
	}
	for (i = 0; i < N; i++) {								//存到结构体a中 
		fscanf(fp, "%d %s %d %f %f %f %f\n",
			&a[i].number, a[i].name, &a[i].absent, &a[i].homework, &a[i].bighomework, &a[i].exam, &a[i].grade);

	}
	fclose(fp);
	for (i = 0; i < N; i++) {
		printf("学生信息如下:\n");
		printf("学号:%d,姓名:%s\n,考勤:%d,课后作业成绩:%.2f,大作业成绩:%.2f,期末考核成绩:%.2f,学生总评成绩:%.2f\n",
			a[i].number, a[i].name, a[i].absent, a[i].homework, a[i].bighomework, a[i].exam, a[i].grade);
	}

}




