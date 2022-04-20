#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#define MAX_WORD_NUM 1000000
#define MAX_FILE_NAME 100
#define MAX_WORD_LONG 100
#define ULL unsigned long long
#define EXIT 0
#define MAIN 1
#define CREAT 2
#define SHOW 3
#define EDIT 4
#define GAME 5
#define EN '3'
#define CN '2'
#define X 13331
#define PRIME 233317
#define MESS 0
#define FALLOW_ASCII 1
#define FALLOW_HASH 2
#define INF -1
#define LOGIN '1'
#define REGISTER '2'
#define HAVE '3'
#define MAX_USER_NUM 1000000
#define M 24
#define WORDS 0
#define USERS 1

struct user_node{
	ULL name_hash;
	ULL password_hash;
	char question[MAX_WORD_LONG];
	ULL ans_hash;
}users[MAX_USER_NUM];

int total_user, now_user;

struct word_node{
	char word[MAX_WORD_LONG];
	char translate[MAX_WORD_LONG];
	int language;
	ULL hash;
};

FILE *fp = NULL;
char choice;
int total_word, total_cn, total_en;
struct word_node dictionary[MAX_WORD_NUM];
int fallow_word, fallow_user;
char file_name[MAX_FILE_NAME];

int cmphash0 (const void * a, const void * b){
	if ( (*(word_node *)a).hash > (*(word_node *)b).hash )
		return 1;
	else if ( (*(word_node *)a).hash < (*(word_node *)b).hash )
		return -1;
	return 0;
}
int cmphash1 (const void * a, const void * b){
	if ( (*(user_node *)a).name_hash > (*(user_node *)b).name_hash )
		return 1;
	else if ( (*(user_node *)a).name_hash < (*(user_node *)b).name_hash )
		return -1;
	return 0;
}
int cmpascii (const void * a, const void * b){
	if ( (*(word_node *)a).language == (*(word_node *)b).language )
		return ( strcmp((*(word_node *)a).word, (*(word_node *)b).word) );
	return ( (*(word_node *)a).language - (*(word_node *)b).language );
}

void gotoxy(int x, int y)//��λ���λ�õ�ָ������
{   
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { x,y };
    SetConsoleCursorPosition(hOut, pos);
}

void color(short x){//�Զ��庯���ݲ����ı���ɫ 
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}

void remain_color(){	//�Զ��庯���ݲ����ı���ɫ 
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void user();
void print_menu(int type);
void menu();
void creat();
void show(); 
void edit();
void find();
int finds(char temp[]);
void game();
void end();
ULL hash(char temp[]);
int bisearch(ULL key, int type);
void sorts(int type, int kind);
void password(int type);

void print_menu(int type){
	system("cls");
	printf(".......................\n");
	if (type == MAIN)
		printf(".������ѡ����(0~5)��.\n"
				".......................\n"
				". 1�����������ʿ�     .\n"
				". 2������ʾ�ʿ�       .\n"
				". 3�����༭�ʿ�       .\n"
				". 4������������       .\n"
				". 5�������¹���       .\n");
	else if (type == CREAT)
		printf(".������ѡ����(0~4)��.\n"
				".......................\n"
				". 1�����������ʿ�     .\n"
				". 2�����������ʿ�     .\n"
				". 3�����������ʿ�     .\n"
				". 4��������           .\n"
				".                     .\n");
	else if (type == SHOW)
		printf(".������ѡ����(0~4)��.\n"
				".......................\n"
				". 1������ʾ���е���   .\n"
				". 2������ʾ���ĵ���   .\n"
				". 3������ʾӢ�ĵ���   .\n"
				". 4��������           .\n"
				".                     .\n");
	else if (type == EDIT)
		printf(".������ѡ����(0~5)��.\n"
				".......................\n"
				". 1��������´�       .\n"
				". 2����ɾ���ɴ�       .\n"
				". 3�����޸ľɴ�       .\n"
				". 4��������           .\n"
				". 5�����������ʿ�     .\n");
	else if (type == GAME)
		printf(".������ѡ����(0~4)��.\n"
				".......................\n"
				". 1����ȫƴ��ϰ       .\n"
				". 2��������ĸ���     .\n"
				". 3�������ϵ���       .\n"
				". 4����˵�Ľ���       .\n"
				". 5��������           .\n");
	printf(". 0�����˳�ϵͳ       .\n"
			".......................\n");
}

void menu(){
	print_menu(MAIN);
	while (~(choice = getch()) != NULL)
		if (choice == '1'){
			creat();
			break;
		}
		else if (choice == '2'){
			show();
			break;
		}
		else if (choice == '3'){
			if (now_user != total_user){
				system("cls");
				password(choice);
			}
			edit();
			break;
		}
		else if (choice == '4'){
			find();
			break;
		}
		else if (choice == '5'){
			game();
			break;
		}
		else if (choice == '0'){
			end();
			break;
		}
}

void end(){
	system("cls");/*
	if (fp != NULL)
		if (fclose(fp)){
				printf("��лʹ�ñ���������������˳����������������");
				exit(0);
			}
	
	if (strcmp(file_name, "") != 0){
		fp = fopen(file_name, "w+");
		
		sorts(FALLOW_HASH, WORDS);
		
		for (int i = 0; i < total_word; i++)
			fprintf(fp, "%s %s\n", dictionary[i].word, dictionary[i].translate);
		if (fclose(fp)){
			printf("��лʹ�ñ���������������˳����������������");
			exit(0);
		}
	}*/
	printf("��лʹ�ñ�������������˳����������������");
	exit(0);
	return;
}

ULL hash(char temp[]){
	ULL bowl = 0;
	for (int i = 0; temp[i]; i++)
		bowl = (bowl * X + temp[i]) + PRIME;
	return bowl;
}

void sorts(int type, int kind){
	if (kind == WORDS){
		if (type == FALLOW_HASH){
			if (fallow_word == type)
				return;
			qsort(dictionary, total_word, sizeof(dictionary[0]), cmphash0);
			fallow_word = FALLOW_HASH;
		}
		else{
			if (fallow_word == type)
				return;
			qsort(dictionary, total_word, sizeof(dictionary[0]), cmpascii);
			fallow_word = FALLOW_ASCII;
		}
	}
	else{
		if (type == FALLOW_HASH){
			if (fallow_user == type)
				return;
			qsort(users, total_user, sizeof(users[0]), cmphash1);
			fallow_user = FALLOW_HASH;
		}
	}
}


int bisearch(ULL key, int type){
	int start = 0, end, middle;
	if (type == WORDS){
		end = total_word - 1;
		do{
			middle = (start + end) / 2;
			if (key == dictionary[middle].hash)
				return middle;
			else if (key < dictionary[middle].hash)
				end = middle - 1;
			else
				start = middle + 1;
		}while (start <= end);
	}
	else{
		end = total_user - 1;
		do{
			middle = (start + end) / 2;
			if (key == users[middle].name_hash)
				return middle;
			else if (key < users[middle].name_hash)
				end = middle - 1;
			else
				start = middle + 1;
		}while (start <= end);
	}
	return INF;
}

void user(){
	
	if ((fp = fopen("use.txt", "a+")) == NULL){
		printf("�����쳣������\n\n����ѡ����(0~1)��\n\t1���������ο�ģʽ\n\t0�����˳�ϵͳ\n");
		while (~(choice = getch()) != NULL)
			if (choice == '1'){
				now_user = total_user;
				menu(); 
				return;
			}
			else if (choice == '0'){
				end();
				break;
			}
	}
	
	fseek(fp, 0L, 2);
	int tail = ftell(fp);
	fseek(fp, 0L, 0);
	for (total_user = 0; tail != ftell(fp); total_user++){
		fscanf(fp, "%llu%llu%llu", &users[total_user].name_hash, &users[total_user].password_hash, &users[total_user].ans_hash);
		fgetc(fp);
		fgets(users[total_user].question, MAX_WORD_LONG+5, fp);
		for (int i = 0; users[total_user].question[i]; i++)
			users[total_user].question[i] ^= X;
		if (users[total_user].question[strlen(users[total_user].question)-1] == '\n' ^ X)
			users[total_user].question[strlen(users[total_user].question)-1] = '\0';
	}
	
	system("cls");
	printf("��ӭʹ�õ������ʿ�ϵͳ\n\n\t1���������˺�\n\t2����ע���˺�\n\t3�����ο�ģʽ\n\t0�����˳�ϵͳ\n\n�������죬�������ʿ�ϵͳ��ע��%d���˺�\n", total_user);
	while (~(choice = getch()) != NULL)
		if (choice == LOGIN || choice == REGISTER)
			break;
		else if (choice == '3'){
			now_user = total_user;
			menu();
			return;
		}
		else if (choice == '0'){
			end();
			break;
		}
	write_name:
	system("cls");
	printf("�������˺ţ�");
	char temp[MAX_WORD_LONG];
	ULL temp_hash;
	gets(temp);
	temp_hash = hash(temp);
	sorts(FALLOW_HASH, USERS);
	ULL item = bisearch(temp_hash, USERS);
	if (choice == LOGIN){
		if (item == INF){
			printf("û������˺ţ�����\n\n����ѡ����(0~2)��\n\t1�������������˺�\n\t2����ע���˺�\n\t0�����˳�ϵͳ\n");
			while (~(choice = getch()) != NULL)
				if (choice == LOGIN || choice == REGISTER)
					goto write_name;
				else if (choice == '0'){
					end();
					break;
				}
		}
		else
			now_user = item;
	} 
	else{
		if (item == INF){
		now_user = total_user++;
		users[now_user].name_hash = temp_hash;
		fprintf(fp, "\n%llu ", users[now_user].name_hash);
		fallow_user = MESS;
		}
		else{
			printf("�û�����ע�ᣡ����\n\n����ѡ����(0~2)��\n\t1������¼���˺�\n\t2�������������˺�\n\t0�����˳�ϵͳ\n");
			while (~(choice = getch()) != NULL)
				if (choice == LOGIN){
					now_user = item;
					break;
				}
				else if (choice == REGISTER)
					goto write_name;
				else if (choice == '0'){
					end();
					break;
				}
		} 
	}
	fclose(fp);
	
	password(choice);
	
	menu();
} 

void password(int type){
	static char temp[MAX_WORD_LONG];
	static ULL temp_hash;
	
	input_password:
	
	printf("���������룺");
	gets(temp);
	temp_hash = hash(temp);
	
	if (type == REGISTER){
		fp = fopen("use.txt", "a+");
		users[now_user].password_hash = temp_hash;
		fprintf(fp, "%llu ", users[now_user].password_hash);
		users[now_user].password_hash = temp_hash;
		printf("�������ܱ���");
		gets(users[now_user].question);
		strcat(users[now_user].question, "   "); 
		printf("������𰸣�");
		gets(temp);
		temp_hash = hash(temp);
		fprintf(fp, "%llu ", temp_hash);
		for (int i = 0; users[now_user].question[i]; i++)
			fprintf(fp, "%c", users[now_user].question[i] ^ X);
		//fprintf(fp, "\n");
		printf("ע��ɹ������������½���������˵�\n");
		fclose(fp);
		getch();
		return;
	}
	
	if (temp_hash == users[now_user].password_hash)
		return;
	else if (type == HAVE){
		printf("������������󣡣���\n\n�������������һ��");
		getch();
		menu();
		return;
	}
	else{
		printf("\n������������󣡣���\n\n����ѡ����(1~2)��\n\t1����������������\n\t2������������\n\t");
		if (type == LOGIN)
			printf("0�����˳�ϵͳ\n");
		else
			printf("0����������һ��\n");
		while (~(choice = getch()) != NULL)
		if (choice == '1'){
			system("cls");
			goto input_password;
			break;
		}
		else if (choice == '2'){
			input_ans:
			system("cls");
			printf("�ܱ���%s\n", users[now_user].question);
			printf("�𰸣�");
			gets(temp);
			temp_hash = hash(temp);
			if (temp_hash == users[now_user].ans_hash){
				printf("�������µ����룺");
				gets(temp);
				users[now_user].password_hash = hash(temp);
				FILE *fpp = fopen("use.txt", "w+");
				for (int i = 0; i < total_user; i++){
					fprintf(fpp, "\n%llu %llu %llu ", users[i].name_hash, users[i].password_hash, users[i].ans_hash);
					for (int j = 0; users[i].question[j]; j++)
						fprintf(fpp, "%c", users[i].question[j] ^ X);
				}
				fclose(fpp);
				break;
			}
			else{
				printf("����Ĵ𰸲�ƥ�䣡����\n\n����ѡ����(0~1)��\n\t1�������������\n\t");
				if (type == LOGIN)
					printf("0�����˳�ϵͳ\n");
				else
					printf("0����������һ��\n");
				while (~(choice = getch()) != NULL)
					if (choice == '1'){
						goto input_ans;
						break;
					}
					else if (choice == '0'){
						if (type == HAVE)
							menu();
						else
							end();
						return;
					}
			}
		}
		else if (choice == '0'){
			if (type == LOGIN)
				menu();
			else
				end();
			return;
		}
	}
}


