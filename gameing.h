#ifndef SOURCE_H
#define SOURCE_H
#include "source.h"
#endif
#define ALL_SPELL '1'
#define HEAD_SPELL '2'
#define KNOW_WORD '3'
#define EXPLAIN_WORD '4'
#define CN_EN '1'


void games(int type);

void game(){
	print_menu(GAME);
	while (choice = getch())
		if (choice == ALL_SPELL || choice == HEAD_SPELL || choice == KNOW_WORD || choice == EXPLAIN_WORD){
			games(choice);
			break;
		}
		else if (choice == '5'){
			menu();
			return;
		}
		else if (choice == '0'){
			end();
			return;
		}
	return;
}

void games(int type){
	static time_t t;
	static int book[MAX_WORD_NUM];
	int ac = 1, idx;
	char temp[MAX_WORD_LONG];
	char c;
	
	memset(book, 0, MAX_WORD_NUM * sizeof(int));
	
	game_begin:
	
	system("cls");
	
	if (strcmp(file_name, "") == 0){
		printf("没有载入生词库！！！\n按任意键返回上一层\n");
		getch();
		game();
		return; 
	} 
	
	printf("请输入单词类型：\n\n\t1——中英单词混合\n\t2——只有中文单词\n\t3——只有英文单词\n\t0——返回上一层\n");
	
	while (choice = getch())
		if (choice == CN_EN || choice == CN || choice == EN)
			break;
		else if (choice == '0'){
			menu();
			return;
		}
	
	if (choice == CN_EN && total_word == 0 || choice == CN && total_cn == 0 || choice == EN && total_en == 0){
		printf("生词库没有对应的单词！！！\n按任意键返回上一层\n");
			getch();
			goto game_begin;
		return;
	}
	
	srand((unsigned) time(&t));
	
	int lvl;
	sorts(FALLOW_ASCII, WORDS);
	
	word_num_set:
	
	printf("请输入单词数（最多不超过");
	if (choice == CN_EN)
		printf("%d", total_word);
	else if (choice == CN)
		printf("%d", total_cn);
	else if (choice == EN)
		printf("%d", total_en);
	printf("）：");
	
	scanf("%d", &lvl);
	getchar();
	if (!(choice == CN_EN && lvl <= total_word || choice == CN && lvl <= total_cn || choice == EN && lvl <= total_en)){
		printf("输入错误！！！\n"); 
		goto word_num_set;
	} 
	
	for (int level = 1; level <= lvl; level++){
		
		int bowlc = choice;
		do{
			if (choice == CN)
				idx = rand() % total_cn;
			else if (choice == EN)
				idx = rand() % total_en + total_cn;
			else
				idx = rand() % total_word;
		}while (book[idx] == 1);
		book[idx] = 1;
		if (bowlc == CN_EN)
			bowlc = dictionary[idx].language;
		
		system("cls");
		printf("输入0——退出");
		
		if (type == ALL_SPELL){
			int tips = 0;
			char cn_word[3];
			cn_word[2] = '\0';
			printf(" 输入1——提示\n");
			all_spell_begin:
			printf("\n意思：\t%s\n\n请输入单词：                                        ", dictionary[idx].translate);
			gotoxy(16, 4);
			while (1){
				for (int i = 0; 1; i++){
					temp[i] = getchar();
					if (temp[i] == '\n'){
						temp[i] = '\0';
						break;
					}
				}
				if (strcmp(temp, "0") == 0){
					game();
					return;
				} 
				else if (strcmp(temp, "1") == 0){
					if (dictionary[idx].language == CN && dictionary[idx].word[(tips*2)] != '\0'){
						if (tips == 0){
							gotoxy(0, 5);
							printf("tips: ");
						}
						gotoxy(tips+6, 5);
						cn_word[0] = dictionary[idx].word[(tips*2)];
						cn_word[1] = dictionary[idx].word[(tips*2)+1];
						printf("%s", cn_word);
						tips++;
					} 
					else if (dictionary[idx].language == EN && dictionary[idx].word[tips] != '\0'){
						if (tips == 0){
							gotoxy(0, 5);
							printf("tips: ");
						}
						gotoxy(tips+6, 5);
						printf("%c", dictionary[idx].word[tips]);
						tips++;
					}
					gotoxy(0, 1);
					goto all_spell_begin;
				}
				if (strcmp(temp, dictionary[idx].word) == 0){
					gotoxy(0, 7);
					color(2);
					printf("恭喜你，回答正确！！！\n按任意键进入下一关\n");
					remain_color();
					getch();
					break;
				}
				else{
					gotoxy(0, 7);
					color(4);
					printf("很遗憾，回答错误！！！\n");
					remain_color();
					gotoxy(0, 1);
					goto all_spell_begin;
				}
			}
		}
		else if (type == HEAD_SPELL){
			static char ans[100];
			memset(ans, '\0', 100 * sizeof(char));
			printf(" 输入1——提示\n");
			head_spell_begin:
			if (dictionary[idx].language == EN){
				printf("\n意思：\t%s\n\n请输入单词：\t___%s                                        ", dictionary[idx].translate, dictionary[idx].word + 1);
				ans[0] = dictionary[idx].word[0];
			}
			else{
				printf("\n意思：\t%s\n\n请输入单词：\t____%s                                        ", dictionary[idx].translate, dictionary[idx].word + 2);
				ans[0] = dictionary[idx].word[0];
				ans[1] = dictionary[idx].word[1];
			}
			gotoxy(17, 4);
			while (1){
				for (int i = 0; 1; i++){
					temp[i] = getchar();
					if (temp[i] == '\n'){
						temp[i] = '\0';
						break;
					}
				}
				if (strcmp(temp, "0") == 0){
					game();
					return;
				} 
				else if (strcmp(temp, "1") == 0){
					gotoxy(0, 5);
					printf("tips: %s", ans);
					gotoxy(0, 1);
					goto head_spell_begin;
				} 
				if (strcmp(temp, ans) == 0){
					gotoxy(0, 7);
					color(2);
					printf("恭喜你，回答正确！！！\n按任意键进入下一关\n");
					remain_color();
					getch();
					break;
				}
				else{
					gotoxy(0, 7);
					color(4);
					printf("很遗憾，回答错误！！！\n");
					remain_color();
					gotoxy(0, 1);
					goto head_spell_begin;
				}
			}
		}
		else if (type == KNOW_WORD){
			printf("\n\n单词：\t%s\n\n\n认识y\t不认识n\n", dictionary[idx].word);
			while (c = getch())
			if (c == 'y')
				break;
			else if (c == 'n'){
				gotoxy(0, 4);
				color(4);
				printf("意思：\t%s", dictionary[idx].translate);
				remain_color();
				gotoxy(0, 7);
			}
			else if (c == '0'){
				game();
				return;
			}
		}
		else{
			int choice_num = 4;
			if (bowlc == CN && total_cn < 4)
				choice_num = total_cn;
			else if (bowlc == EN && total_en < 4)
				choice_num = total_en;
			printf("\n\n单词：\t%s\n\n意思：\n\n", dictionary[idx].word);
			int pose = rand() % choice_num;
			static int pos[3], bowl[3];
			int posi = -1;
			for (int i = 0; i < choice_num; i++){
				printf("\t%d——", i + 1);
				if (i == pose)
					printf("%s\n", dictionary[idx].translate);
				else{
					posi++;
					do{
						if (bowlc == CN)
							pos[posi] = rand() % total_cn;
						else if (bowlc == EN)
							pos[posi] = rand() % total_en + total_cn;
					}while (pos[posi] == idx || book[pos[posi]] == -1);
					bowl[posi] = book[pos[posi]];
					book[pos[posi]] = -1;
					printf("%s\n", dictionary[pos[posi]].translate);
				}
			}
			for (int i = 0; i < choice_num - 1; i++)
				book[pos[i]] = bowl[i];
			while (c = getch())
				if (c - '0' == pose + 1){
					color(2);
					gotoxy(0, 6+pose);
					printf("\t%d——%s", pose + 1, dictionary[idx].translate);
					gotoxy(0, 11);
					printf("恭喜你，回答正确！！！\n按任意键进入下一关\n");
					remain_color();
					getch();
					break;
				}
				else if (c == '0'){
					game();
					return;
				}
				else{
					gotoxy(0, 11);
					color(4);
					printf("很遗憾，回答错误！！！\n");
					remain_color();
				}
		}
		
	}
	
	system("cls");
	color(2);
	printf("恭喜你，闯关成功！！！\n按任意键退出\n");
	remain_color();
	getch();
	game();
	return; 
}
