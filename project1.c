//C���Գ�����ƿγ̳ɼ�����ϵͳ
//һ��	�ṹ���������
//ÿλѧ������������Ϣ��
//1. ѧ�ţ�
//2. ������
//3.���ڣ����δ�����
//4.�κ���ҵ�ɼ���9�Σ�����9��ƽ���֣�
//5.����ҵ�ɼ���1�Σ���
//6.��ĩ���˳ɼ���1�Σ���
//7.ѧ�������ɼ����κ���ҵ�ɼ�*0.15+����ҵ�ɼ�*0.15+��ĩ���˳ɼ�*0.7����
//��������ѧ��
//	¼��ѧ����Ϣ��ѧ�ţ���������
//����¼��ѧ����Ϣ
//   1.¼��ѧ����������������δ�����
//   2.¼��κ���ҵ�ɼ������ƽ���֣���0.0-100.0��
//   3.¼�����ҵ�ɼ�����0.0-100.0��
//   4.¼����ĩ���˳ɼ�����0.0-100.0��
//   5.���������ɼ����κ���ҵ�ɼ�*0.15+����ҵ�ɼ�*0.15+��ĩ���˳ɼ�*0.7����
//�ġ�����ѧ�ţ�����������ѯѧ����Ϣ
//�塢����ѧ�ţ����������޸�ѧ����Ϣ
//������ӡ����ѧ����Ϣ
//ע��¼��ѧ������Ϣ������һ���ļ��ڡ�
#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1										//¼��ѧ������ 
struct student {
	int number; 								//1. ѧ�ţ�
	char name[20];								//2. ������
	int absent;									//3.���ڣ����δ�����
	float  homework;							//4.�κ���ҵ�ɼ���9�Σ�����9��ƽ���֣�
	float bighomework;							//5.����ҵ�ɼ���1�Σ���
	float exam;									//6.��ĩ���˳ɼ���1�Σ���
	float grade;								//7.ѧ�������ɼ����κ���ҵ�ɼ�*0.15+����ҵ�ɼ�*0.15+��ĩ���˳ɼ�*0.7����
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

	printf("C���Գ�����ƿγ̳ɼ�����ϵͳ\n");
	printf("-----------------------------------\n");
	printf("\n��������Ҫ¼���ѧ�ź�����:\n");
	for (i = 0; i < N; i++) {							//¼��ѧ��������ѧ�� 
		scanf("%d%s", &stu[i].number, &stu[i].name);
	}
	printf("���!\n");

	printf("��������Ҫ¼���ѧ����Ϣ\n\n");		//¼��ѧ����Ϣ 
	for (i = 0; i < N; i++) {
		printf("�������%-2d��ѧ���Ŀ�����Ϣ:\n", i + 1);
		scanf("%d", &stu[i].absent);

		printf("�������%-2d��ѧ���Ŀκ���ҵ�ɼ�:\n", i + 1);
		for (j = 0; j < 9; j++) {
			printf("��%d��:", j + 1);
			scanf("%f", &eachhomework[j]);
			sum = sum + eachhomework[j];	//¼��ÿһ����ҵ�ĳɼ� 
		}
		stu[i].homework = sum / 9.0;
		printf("ƽ���κ���ҵ�ɼ���:%.2f\n", stu[i].homework);
		sum = 0;

		printf("�������%-2d��ѧ���Ĵ���ҵ�ɼ�:\n", i + 1);
		scanf("%f", &stu[i].bighomework);

		printf("�������%-2d��ѧ������ĩ���˳ɼ�:\n", i + 1);
		scanf("%f", &stu[i].exam);

		stu[i].grade = stu[i].homework * 0.15 + stu[i].bighomework * 0.15 + stu[i].exam * 0.7;//���������ɼ� 
		printf("��ѧ���������ɼ���:%.2f��\n", stu[i].grade);
		printf("-----------------------------------\n");
	}

	if ((fp = fopen("D://student.txt", "w")) == NULL) {		//����һ���ļ� 
		printf("error");
		exit(0);
	}
	for (i = 0; i < N; i++) {								//д�뵽�ļ��� 
		fprintf(fp, "%d %s %d %.2f %.2f %.2f %.2f\n",
			stu[i].number, stu[i].name, stu[i].absent, stu[i].homework, stu[i].bighomework, stu[i].exam, stu[i].grade);
	}
	fclose(fp);

	while (1) {
		printf("\n��ѡ������Ҫ�Ĺ��ܣ�\n");					//ѡ����Ҫ�Ĺ��� 
		printf("1:��ѯ\n2:�޸�\n3:�˳�����\n");
		scanf("%d", &function);
		switch (function) {
		case 1:search(fp); break;						//������������ 
		case 2:alter(fp);	break;						//�����޸ĺ��� 
		case 3:goto loop;
		}
	}
		
	
	loop:

	printf("-----------------------------------\n");


	print(fp);

	return 0;

}

//�������� 
void search(FILE* fp) {
	int num;
	int i;
	char name[20];
	char way[10];
	int result = 1;

	printf("������������β�ѯ(��������ѧ��):\n");
	scanf("%s", way);
	if (strcmp(way, "����") == 0) {								//ѯ���������ѧ�Ż������� 
		result = 0;											//result==0˵��Ҫ�������� 
	}													    //result==1˵��Ҫ����ѧ�� 
	if (result == 0) {
		printf("����������:\n");
		scanf("%s", name);
	}
	else if (result == 1) {
		printf("������ѧ��:\n");
		scanf("%d", &num);
	}
	if (result == 0) {
		f0search(fp, name);
	}
	if (result == 1) {
		f1search(fp, num);
	}

}


//������Ѱ�� 
void f0search(FILE* fp, char name[20]) {
	int i;
	int m;
	struct student a[N];
	if ((fp = fopen("D://student.txt", "r")) == NULL) {	//��ԭ�ļ� ��ȡ 
		printf("error");
		exit(0);
	}
	for (i = 0; i < N; i++) {								//�浽�ṹ��a�� 
		fscanf(fp, "%d %s %d %f %f %f %f\n",
			&a[i].number, a[i].name, &a[i].absent, &a[i].homework, &a[i].bighomework, &a[i].exam, &a[i].grade);

	}
	fclose(fp);
	for (i = 0; i < N; i++) {								//Ѱ����ͬ������ 
		if (strcmp(name, a[i].name) == 0) {
			m = i;
			break;
		}
	}
	if (i < N) {
		printf("��ѧ������Ϣ����:\nѧ��:%d ����:%s\n����:%d,�κ���ҵ�ɼ�:%.2f,����ҵ�ɼ�:%.2f,��ĩ���˳ɼ�:%.2f,�����ɼ�:%.2f\n",
			a[m].number, a[m].name, a[m].absent, a[m].homework, a[m].bighomework, a[m].exam, a[m].grade);

	}
	else {
		printf("û���ҵ���ѧ��!");
	}
	printf("���!\n");
	printf("-----------------------------------\n");
}
//��ѧ��Ѱ��	
void f1search(FILE* fp, int number) {
	int i;
	int m;
	struct student a[N];
	if ((fp = fopen("D://student.txt", "r")) == NULL) {	//��ԭ�ļ� ��ȡ 
		printf("error");
		exit(0);
	}
	for (i = 0; i < N; i++) {								//�浽�ṹ��a�� 
		fscanf(fp, "%d %s %d %f %f %f %f\n",
			&a[i].number, a[i].name, &a[i].absent, &a[i].homework, &a[i].bighomework, &a[i].exam, &a[i].grade);

	}
	fclose(fp);

	for (i = 0; i < N; i++) {								//Ѱ����ͬ������ 
		if (number == a[i].number) {
			m = i;
			break;
		}
	}
	if (i < N) {
		printf("��ѧ������Ϣ����:\nѧ��:%d ����:%s\n����:%d,�κ���ҵ�ɼ�:%.2f,����ҵ�ɼ�:%.2f,��ĩ���˳ɼ�:%.2f,�����ɼ�:%.2f\n",
			a[m].number, a[m].name, a[m].absent, a[m].homework, a[m].bighomework, a[m].exam, a[m].grade);
	}
	else {
		printf("û���ҵ���ѧ��!");
	}
	printf("���!\n");
	printf("-----------------------------------\n");
}

//�޸ĺ���
void alter(FILE* fp) {										//�ж��������ֻ���ѧ�� 
	int num;
	int i;
	char name[20];
	char way[10];
	int result = 1;

	printf("��������������޸�(��������ѧ��):\n");
	scanf("%s", way);
	if (strcmp(way, "����") == 0) {								//ѯ���������ѧ�Ż������� 
		result = 0;											//result==0˵��Ҫ�������� 
	}													    //result==1˵��Ҫ����ѧ�� 
	if (result == 0) {
		printf("����������:\n");
		scanf("%s", name);
	}
	else if (result == 1) {
		printf("������ѧ��:\n");
		scanf("%d", &num);
	}
	if (result == 0) {
		falter0(fp, name);
	}
	else if (result == 1) {
		falter1(fp, num);
	}
	printf("�޸ĳɹ�!\n");
	printf("-----------------------------------\n");
}

//��ѧ���޸�	
void falter1(FILE* fp, int number) {
	int i;
	int m;
	int want;											//����Ҫ�޸ĵ����ݵ�����

	int w1;												//�����޸ĳɵ����� ѧ��,���� 
	float w2;											//�����޸ĳɵ����� �ɼ�

	printf("ѡ����Ҫ�޸ĵ���Ŀ������ǰ�������:\n");//����Ҫ�޸ĵ����ݵ�����
	printf("1.ѧ��\n");
	printf("2.����\n");
	printf("3.�κ���ҵ�ɼ�\n");
	printf("4.����ҵ�ɼ�\n");
	printf("5.��ĩ���Գɼ�\n");
	printf("6.�����ɼ�\n");

	scanf("%d", &want);
	printf("�������޸ĺ������:\n");
	switch (want) {
	case 1:
	case 2:scanf("%d", &w1); break;
	case 3:
	case 4:
	case 5:
	case 6:scanf("%f", &w2); break;
	}
	struct student a[N];
	if ((fp = fopen("D://student.txt", "r")) == NULL) {	//��ԭ�ļ� ��ȡ 
		printf("error");
		exit(0);
	}
	for (i = 0; i < N; i++) {								//�浽�ṹ��a�� 
		fscanf(fp, "%d %s %d %f %f %f %f\n",
			&a[i].number, a[i].name, &a[i].absent, &a[i].homework, &a[i].bighomework, &a[i].exam, &a[i].grade);

	}
	fclose(fp);


	for (i = 0; i < N; i++) {								//Ѱ����ͬ��ѧ�� 
		if (number == a[i].number) {
			m = i;
			break;
		}
	}
	if (i < N) {
		switch (want)
		{							//�ı� 
		case 1: a[m].number = w1; break;
		case 2: a[m].absent = w1; break;
		case 3: a[m].homework = w2; break;
		case 4: a[m].bighomework = w2; break;
		case 5: a[m].exam = w2; break;
		case 6: a[m].grade = w2; break;
		}

	}
	else {
		printf("û���ҵ���ѧ��!");
	}
	if ((fp = fopen("D://student.txt", "w")) == NULL) {	//����һ���ļ� 
		printf("error");
		exit(0);
	}
	for (i = 0; i < N; i++) {								//д�뵽�ļ��� 
		fprintf(fp, "%d %s %d %.2f %.2f %.2f %.2f\n",
			a[i].number, a[i].name, a[i].absent, a[i].homework, a[i].bighomework, a[i].exam, a[i].grade);
	}
	fclose(fp);
}

//�������޸� 
void falter0(FILE* fp, char name[20]) {
	int i;
	int m;
	int want;											//����Ҫ�޸ĵ����ݵ�����

	int w1;												//�����޸ĳɵ����� ѧ��,���� 
	float w2;											//�����޸ĳɵ����� �ɼ�

	printf("ѡ����Ҫ�޸ĵ���Ŀ������ǰ�������:\n");//����Ҫ�޸ĵ����ݵ�����
	printf("1.ѧ��\n");
	printf("2.����\n");
	printf("3.�κ���ҵ�ɼ�\n");
	printf("4.����ҵ�ɼ�\n");
	printf("5.��ĩ���Գɼ�\n");
	printf("6.�����ɼ�\n");

	scanf("%d", &want);
	printf("�޸ĺ������:\n");
	switch (want) {
	case 1:
	case 2:scanf("%d", &w1); break;
	case 3:
	case 4:
	case 5:
	case 6:scanf("%f", &w2); break;
	}
	struct student a[N];
	if ((fp = fopen("D://student.txt", "r")) == NULL) {	//��ԭ�ļ� ��ȡ 
		printf("error");
		exit(0);
	}
	for (i = 0; i < N; i++) {								//�浽�ṹ��a�� 
		fscanf(fp, "%d %s %d %f %f %f %f\n",
			&a[i].number, a[i].name, &a[i].absent, &a[i].homework, &a[i].bighomework, &a[i].exam, &a[i].grade);

	}
	fclose(fp);


	for (i = 0; i < N; i++) {								//Ѱ����ͬ������ 
		if (strcmp(name, a[i].name) == 0) {
			m = i;
			break;
		}
	}
	if (i < N) {
		switch (want) {							//�ı� 
		case 1: a[m].number = w1; break;
		case 2: a[m].absent = w1; break;
		case 3: a[m].homework = w2; break;
		case 4: a[m].bighomework = w2; break;
		case 5: a[m].exam = w2; break;
		case 6: a[m].grade = w2; break;
		}

	}
	else {
		printf("û���ҵ���ѧ��!");
	}
	if ((fp = fopen("D://student.txt", "w")) == NULL) {	//����һ���ļ� 
		printf("error");
		exit(0);
	}
	for (i = 0; i < N; i++) {								//д�뵽�ļ��� 
		fprintf(fp, "%d %s %d %.2f %.2f %.2f %.2f\n",
			a[i].number, a[i].name, a[i].absent, a[i].homework, a[i].bighomework, a[i].exam, a[i].grade);
	}
	fclose(fp);

}
void print(FILE* fp) {

	struct student a[N];
	int i;

	if ((fp = fopen("D://student.txt", "r")) == NULL) {	//��ԭ�ļ� ��ȡ 
		printf("error");
		exit(0);
	}
	for (i = 0; i < N; i++) {								//�浽�ṹ��a�� 
		fscanf(fp, "%d %s %d %f %f %f %f\n",
			&a[i].number, a[i].name, &a[i].absent, &a[i].homework, &a[i].bighomework, &a[i].exam, &a[i].grade);

	}
	fclose(fp);
	for (i = 0; i < N; i++) {
		printf("ѧ����Ϣ����:\n");
		printf("ѧ��:%d,����:%s\n,����:%d,�κ���ҵ�ɼ�:%.2f,����ҵ�ɼ�:%.2f,��ĩ���˳ɼ�:%.2f,ѧ�������ɼ�:%.2f\n",
			a[i].number, a[i].name, a[i].absent, a[i].homework, a[i].bighomework, a[i].exam, a[i].grade);
	}

}




