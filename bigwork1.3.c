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

struct student {
	int number; 								//1. ѧ�ţ�
	char name[20];								//2. ������
	int absent;									//3.���ڣ����δ�����
	float  homework;							//4.�κ���ҵ�ɼ���9�Σ�����9��ƽ���֣�
	float bighomework;							//5.����ҵ�ɼ���1�Σ���
	float exam;									//6.��ĩ���˳ɼ���1�Σ���
	float grade;								//7.ѧ�������ɼ����κ���ҵ�ɼ�*0.15+����ҵ�ɼ�*0.15+��ĩ���˳ɼ�*0.7����
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

	printf("C���Գ�����ƿγ̳ɼ�����ϵͳ\n\n\n");
	
	while (1) {
		printf("\n��ѡ������Ҫ�Ĺ��ܣ�\n");							//ѡ����Ҫ�Ĺ��� 
		printf("-----------------------------------\n");
		printf("--  1:¼��          --\n--  2:��ѯ          --\n--  3:�޸�          --\n--  4:��ӡѧ����Ϣ  --\n--  5:�˳�����      --\n");
		printf("-----------------------------------\n");
		printf("�������Ӧ����ǰ�����֣�");
		scanf("%d", &function);
		n = count();												//ԭ���ļ����м���ѧ������Ϣ��
		switch (function) {
		case 1:scan(fp, stu, n);   break;
		case 2:search(fp,n); break;									//������������ 
		case 3:alter(fp,n);break;									//�����޸ĺ��� 
		case 4:print(fp, n);break;
		case 5: goto loop;
		}
	}
loop:
	printf("�˳��ɹ���");
	

	return 0;

}
//���㺯��
int count() {
	struct student a[100];
	int i = 0;
	FILE* fp;
	if ((fp = fopen("D://student.txt", "r")) == NULL) {			//��ֻ���ķ�ʽ���ļ�
		printf("error");
		exit(0);
	}
	while ((fscanf(fp, "%d %s %d %f %f %f %f\n",
		&a[i].number, a[i].name, &a[i].absent, &a[i].homework, &a[i].bighomework, &a[i].exam, &a[i].grade))!=-1) {
		i++;
		if (i == 99) {
			printf("�Դﵽ����ѧ����Ϣ���ޣ�\n");
			break;
		}
	}

	return i;
}



//¼�뺯��
void scan(FILE* fp,struct student *ps,int n) {
	int m;
	int i, j;
	float eachhomework[9] = { 0 };
	float sum=0;

	printf("��������Ҫ¼���ѧ������:");
	scanf("%d", &m);										//��Ҫ¼���ѧ������
	printf("��������Ҫ¼���ѧ����ѧ�ź�����:\n");
	for (i = 0; i < m; i++) {								//¼��ѧ��������ѧ�� 
		scanf("%d%s", &(ps+i)->number, &(ps + i)->name);
	}
	printf("\n��������Ҫ¼���%d��ѧ����Ϣ:\n\n", m);		//¼��ѧ����Ϣ 
	for (i = 0; i < m; i++) {
		printf("�������%-2d��ѧ���Ŀ�����Ϣ:\n", i + 1);
		scanf("%d", &(ps + i)->absent);

		printf("�������%-2d��ѧ���Ŀκ���ҵ�ɼ�:\n", i + 1);
		for (j = 0; j < 9; j++) {
			printf("��%d��:", j + 1);
			scanf("%f", &eachhomework[j]);
			sum = sum + eachhomework[j];					//¼��ÿһ����ҵ�ĳɼ� 
		}
		(ps + i)->homework = sum / 9.0;
		printf("ƽ���κ���ҵ�ɼ���:%.2f\n", (ps + i)->homework);
		sum = 0;

		printf("�������%-2d��ѧ���Ĵ���ҵ�ɼ�:\n", i + 1);
		scanf("%f", &(ps + i)->bighomework);

		printf("�������%-2d��ѧ������ĩ���˳ɼ�:\n", i + 1);
		scanf("%f", &(ps + i)->exam);

		(ps + i)->grade = (ps + i)->homework * 0.15 + (ps + i)->bighomework * 0.15 + (ps + i)->exam * 0.7;//���������ɼ� 
		printf("��ѧ���������ɼ���:%.2f��\n", (ps + i)->grade);
		printf("-----------------------------------\n");
	}



	if ((fp = fopen("D://student.txt", "a")) == NULL) {		//����һ���ļ� 
		printf("error");
		exit(0);
	}
	for (i =0; i <m; i++) {								//д�뵽�ļ��� 
		fprintf(fp, "%d %s %d %.2f %.2f %.2f %.2f\n",
			(ps + i)->number, (ps + i)->name, (ps + i)->absent, (ps + i)->homework, (ps + i)->bighomework, (ps + i)->exam, (ps + i)->grade);
	}
	fclose(fp);

}

//�������� 
void search(FILE* fp,int n) {
	int num;
	char name[20];
	char way[10];
	int result = 1;

	printf("������������β�ѯ(��������ѧ��):\n");
	scanf("%s", way);
	if (strcmp(way, "����") == 0) {								//ѯ���������ѧ�Ż������� 
		result = 0;												//result==0˵��Ҫ�������� 
	}															//result==1˵��Ҫ����ѧ�� 
	if (result == 0) {
		printf("����������:\n");
		scanf("%s", name);
	}
	else if (result == 1) {
		printf("������ѧ��:\n");
		scanf("%d", &num);
	}
	if (result == 0) {
		f0search(fp, name,n);									//����������
	}
	if (result == 1) {											//��ѧ������
		f1search(fp, num,n);
	}

}
//������Ѱ�� 
void f0search(FILE* fp, char name[20],int n) {
	int i;
	int m;
	struct student a[100];
	if ((fp = fopen("D://student.txt", "r")) == NULL) {			//��ԭ�ļ� ��ȡ 
		printf("error");
		exit(0);
	}
	for (i = 0; i < n; i++) {									//�浽�ṹ��a�� 
		fscanf(fp, "%d %s %d %f %f %f %f\n",
			&a[i].number, a[i].name, &a[i].absent, &a[i].homework, &a[i].bighomework, &a[i].exam, &a[i].grade);

	}
	fclose(fp);
	for (i = 0; i < n; i++) {									//Ѱ����ͬ������ 
		if (strcmp(name, a[i].name) == 0) {
			m = i;
			break;
		}
	}
	if (i < n) {
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
void f1search(FILE* fp, int number, int n) {
	int i;
	int m;
	struct student a[100];
	if ((fp = fopen("D://student.txt", "r")) == NULL) {			//��ԭ�ļ� ��ȡ 
		printf("error");
		exit(0);
	}
	for (i = 0; i < n; i++) {									//�浽�ṹ��a�� 
		fscanf(fp, "%d %s %d %f %f %f %f\n",
			&a[i].number, a[i].name, &a[i].absent, &a[i].homework, &a[i].bighomework, &a[i].exam, &a[i].grade);

	}
	fclose(fp);

	for (i = 0; i < n; i++) {									//Ѱ����ͬ������ 
		if (number == a[i].number) {
			m = i;
			break;
		}
	}
	if (i < n) {
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
void alter(FILE* fp, int n) {									//�ж��������ֻ���ѧ�� 
	int num;
	char name[20];
	char way[10];
	int result = 1;

	printf("��������������޸�(��������ѧ��):\n");
	scanf("%s", way);
	if (strcmp(way, "����") == 0) {								//ѯ���������ѧ�Ż������� 
		result = 0;												//result==0˵��Ҫ�������� 
	}															//result==1˵��Ҫ����ѧ�� 
	if (result == 0) {
		printf("����������:\n");
		scanf("%s", name);
	}
	else if (result == 1) {
		printf("������ѧ��:\n");
		scanf("%d", &num);
	}
	if (result == 0) {
		falter0(fp, name,n);
	}
	else if (result == 1) {
		falter1(fp, num, n);
	}
	printf("�޸ĳɹ�!\n");
	printf("-----------------------------------\n");
}

//��ѧ���޸�	
void falter1(FILE* fp, int number, int n) {
	int i;
	int m;
	int want;												//����Ҫ�޸ĵ����ݵ�����

	int w1;													//�����޸ĳɵ����� ѧ��,���� 
	float w2;												//�����޸ĳɵ����� �ɼ�

	printf("ѡ����Ҫ�޸ĵ���Ŀ������ǰ�������:\n");		//����Ҫ�޸ĵ����ݵ�����
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
	struct student a[100];
	if ((fp = fopen("D://student.txt", "r")) == NULL) {			//��ԭ�ļ� ��ȡ 
		printf("error");
		exit(0);
	}
	for (i = 0; i < n; i++) {									//�浽�ṹ��a�� 
		fscanf(fp, "%d %s %d %f %f %f %f\n",
			&a[i].number, a[i].name, &a[i].absent, &a[i].homework, &a[i].bighomework, &a[i].exam, &a[i].grade);

	}
	fclose(fp);


	for (i = 0; i < n; i++) {									//Ѱ����ͬ��ѧ�� 
		if (number == a[i].number) {
			m = i;
			break;
		}
	}
	if (i < n) {
		switch (want)
		{																	//�ı� 
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
	if ((fp = fopen("D://student.txt", "w")) == NULL) {					//����һ���ļ� 
		printf("error");
		exit(0);
	}
	for (i = 0; i < n; i++) {											//д�뵽�ļ��� 
		fprintf(fp, "%d %s %d %.2f %.2f %.2f %.2f\n",
			a[i].number, a[i].name, a[i].absent, a[i].homework, a[i].bighomework, a[i].exam, a[i].grade);
	}
	fclose(fp);
}

//�������޸� 
void falter0(FILE* fp, char name[20], int n) {
	int i;
	int m;
	int want;											//����Ҫ�޸ĵ����ݵ�����

	int w1;												//�����޸ĳɵ����� ѧ��,���� 
	float w2;											//�����޸ĳɵ����� �ɼ�

	printf("ѡ����Ҫ�޸ĵ���Ŀ������ǰ�������:\n");	//����Ҫ�޸ĵ����ݵ�����
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
	struct student a[100];
	if ((fp = fopen("D://student.txt", "r")) == NULL) {						//��ԭ�ļ� ��ȡ 
		printf("error");
		exit(0);
	}
	for (i = 0; i < n; i++) {												//�浽�ṹ��a�� 
		fscanf(fp, "%d %s %d %f %f %f %f\n",
			&a[i].number, a[i].name, &a[i].absent, &a[i].homework, &a[i].bighomework, &a[i].exam, &a[i].grade);

	}
	fclose(fp);


	for (i = 0; i < n; i++) {												//Ѱ����ͬ������ 
		if (strcmp(name, a[i].name) == 0) {
			m = i;
			break;
		}
	}
	if (i < n) {
		switch (want) {														//�ı� 
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
	if ((fp = fopen("D://student.txt", "w")) == NULL) {						//����һ���ļ� 
		printf("error");
		exit(0);
	}
	for (i = 0; i < n; i++) {												//д�뵽�ļ��� 
		fprintf(fp, "%d %s %d %.2f %.2f %.2f %.2f\n",
			a[i].number, a[i].name, a[i].absent, a[i].homework, a[i].bighomework, a[i].exam, a[i].grade);
	}
	fclose(fp);

}
//��ӡ����
void print(FILE* fp, int n) {

	struct student a[100];
	int i;

	if ((fp = fopen("D://student.txt", "r")) == NULL) {					//��ԭ�ļ� ��ȡ 
		printf("error");
		exit(0);
	}
	for (i = 0; i < n; i++) {											//�浽�ṹ��a�� 
		fscanf(fp, "%d %s %d %f %f %f %f\n",
			&a[i].number, a[i].name, &a[i].absent, &a[i].homework, &a[i].bighomework, &a[i].exam, &a[i].grade);

	}
	fclose(fp);
	for (i = 0; i < n; i++) {
		printf("ѧ����Ϣ����:\n");
		printf("ѧ��:%d,����:%s\n,����:%d,�κ���ҵ�ɼ�:%.2f,����ҵ�ɼ�:%.2f,��ĩ���˳ɼ�:%.2f,ѧ�������ɼ�:%.2f\n",
			a[i].number, a[i].name, a[i].absent, a[i].homework, a[i].bighomework, a[i].exam, a[i].grade);
	}

}




