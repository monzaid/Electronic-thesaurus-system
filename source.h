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

void gotoxy(int x, int y)//定位光标位置到指定坐标
{   
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { x,y };
    SetConsoleCursorPosition(hOut, pos);
}

void color(short x){//自定义函根据参数改变颜色 
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}

void remain_color(){	//自定义函根据参数改变颜色 
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
		printf(".请输入选项编号(0~5)：.\n"
				".......................\n"
				". 1——创建生词库     .\n"
				". 2——显示词库       .\n"
				". 3——编辑词库       .\n"
				". 4——查找生词       .\n"
				". 5——创新功能       .\n");
	else if (type == CREAT)
		printf(".请输入选项编号(0~4)：.\n"
				".......................\n"
				". 1——创建生词库     .\n"
				". 2——导入生词库     .\n"
				". 3——重置生词库     .\n"
				". 4——返回           .\n"
				".                     .\n");
	else if (type == SHOW)
		printf(".请输入选项编号(0~4)：.\n"
				".......................\n"
				". 1——显示所有单词   .\n"
				". 2——显示中文单词   .\n"
				". 3——显示英文单词   .\n"
				". 4——返回           .\n"
				".                     .\n");
	else if (type == EDIT)
		printf(".请输入选项编号(0~5)：.\n"
				".......................\n"
				". 1——添加新词       .\n"
				". 2——删除旧词       .\n"
				". 3——修改旧词       .\n"
				". 4——返回           .\n"
				". 5——保存生词库     .\n");
	else if (type == GAME)
		printf(".请输入选项编号(0~4)：.\n"
				".......................\n"
				". 1——全拼练习       .\n"
				". 2——首字母填空     .\n"
				". 3——辨认单词       .\n"
				". 4——说文解字       .\n"
				". 5——返回           .\n");
	printf(". 0——退出系统       .\n"
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
				printf("感谢使用本软件！不能正常退出，按任意键结束。");
				exit(0);
			}
	
	if (strcmp(file_name, "") != 0){
		fp = fopen(file_name, "w+");
		
		sorts(FALLOW_HASH, WORDS);
		
		for (int i = 0; i < total_word; i++)
			fprintf(fp, "%s %s\n", dictionary[i].word, dictionary[i].translate);
		if (fclose(fp)){
			printf("感谢使用本软件！不能正常退出，按任意键结束。");
			exit(0);
		}
	}*/
	printf("感谢使用本软件！已正常退出，按任意键结束。");
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
		printf("程序异常！！！\n\n输入选项编号(0~1)：\n\t1——进入游客模式\n\t0——退出系统\n");
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
	printf("欢迎使用电子生词库系统\n\n\t1——已有账号\n\t2——注册账号\n\t3——游客模式\n\t0——退出系统\n\n截至今天，电子生词库系统已注册%d个账号\n", total_user);
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
	printf("请输入账号：");
	char temp[MAX_WORD_LONG];
	ULL temp_hash;
	gets(temp);
	temp_hash = hash(temp);
	sorts(FALLOW_HASH, USERS);
	ULL item = bisearch(temp_hash, USERS);
	if (choice == LOGIN){
		if (item == INF){
			printf("没有这个账号！！！\n\n输入选项编号(0~2)：\n\t1——重新输入账号\n\t2——注册账号\n\t0——退出系统\n");
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
			printf("用户名已注册！！！\n\n输入选项编号(0~2)：\n\t1——登录该账号\n\t2——重新输入账号\n\t0——退出系统\n");
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
	
	printf("请输入密码：");
	gets(temp);
	temp_hash = hash(temp);
	
	if (type == REGISTER){
		fp = fopen("use.txt", "a+");
		users[now_user].password_hash = temp_hash;
		fprintf(fp, "%llu ", users[now_user].password_hash);
		users[now_user].password_hash = temp_hash;
		printf("请输入密保：");
		gets(users[now_user].question);
		strcat(users[now_user].question, "   "); 
		printf("请输入答案：");
		gets(temp);
		temp_hash = hash(temp);
		fprintf(fp, "%llu ", temp_hash);
		for (int i = 0; users[now_user].question[i]; i++)
			fprintf(fp, "%c", users[now_user].question[i] ^ X);
		//fprintf(fp, "\n");
		printf("注册成功，按任意键登陆并进入主菜单\n");
		fclose(fp);
		getch();
		return;
	}
	
	if (temp_hash == users[now_user].password_hash)
		return;
	else if (type == HAVE){
		printf("输入的密码有误！！！\n\n按任意键返回上一层");
		getch();
		menu();
		return;
	}
	else{
		printf("\n输入的密码有误！！！\n\n输入选项编号(1~2)：\n\t1——重新输入密码\n\t2——忘记密码\n\t");
		if (type == LOGIN)
			printf("0——退出系统\n");
		else
			printf("0——返回上一层\n");
		while (~(choice = getch()) != NULL)
		if (choice == '1'){
			system("cls");
			goto input_password;
			break;
		}
		else if (choice == '2'){
			input_ans:
			system("cls");
			printf("密保：%s\n", users[now_user].question);
			printf("答案：");
			gets(temp);
			temp_hash = hash(temp);
			if (temp_hash == users[now_user].ans_hash){
				printf("请输入新的密码：");
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
				printf("输入的答案不匹配！！！\n\n输入选项编号(0~1)：\n\t1——重新输入答案\n\t");
				if (type == LOGIN)
					printf("0——退出系统\n");
				else
					printf("0——返回上一层\n");
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


