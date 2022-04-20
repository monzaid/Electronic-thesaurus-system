#ifndef SOURCE_H
#define SOURCE_H
#include "source.h"
#endif

void shows(int type);


void show(){
	print_menu(SHOW);
	printf("PS：如果中文出现乱码请把文件后缀改为txt，并且文件编码改成ANSI或其它\n");
	while (choice = getch())
		if (choice == '1' || choice == CN || choice == EN){
			shows(choice);
			break;
		}
		else if (choice == '4'){
			menu();
			break;
		}
		else if (choice == '0'){
			end();
			break;
		}
	return;
}

void shows(int type){
	static int front[MAX_WORD_NUM], book[MAX_WORD_NUM];
	static char c;
	
	memset(book, 0, MAX_WORD_NUM * sizeof(int));
	if (type == EN)
		sorts(FALLOW_ASCII, WORDS);
	
	system("cls");
	if (total_word == 0 || total_cn == 0 && type == CN || total_en == 0 && type == EN){
		printf("生词库没有这类的单词\n按任意键返回上一层\n");
		getch();
		show();
		return;
	}
	for (int i = 0, n = -1, bowl = 0, isfirst = 1; i < total_word; i++){
		if (type == dictionary[i].language || type == '1'){
			if (n % 10 == 9 || n == -1){
				color(8);
				printf("------------------------------------------------------------\n");
				remain_color();
			}
			printf("    %s\n    %s\n", dictionary[i].word, dictionary[i].translate);
			color(8);
			printf("------------------------------------------------------------\n");
			remain_color();
			n++;
			if (isfirst == 1 && book[bowl] == 0){
				book[bowl] = 1;
				front[bowl] = i;
				isfirst = 0;
			}
		}
		if (n % 10 == 9 || type == CN && n == total_cn - 1 || type == EN && n == total_en - 1 ||type == '1' && n == total_word - 1){
			gotoxy(0, 31);
			if (bowl == 0)//没有上一页 
				color(8);
			printf("<上一页 ");
			remain_color();
			printf("返回0 ");
			if (!(bowl < (total_word - 1) / 10 && type == '1' || bowl < (total_cn - 1) / 10 && type == CN || bowl < (total_en - 1) / 10 && type == EN))//没有下一页
				color(8);
			printf("下一页>    ");
			remain_color();
			if (type == CN)
				printf("中文单词总数：%d    ", total_cn);
			else if (type == EN)
				printf("英文单词总数：%d    ", total_en);
			else
				printf("所有的单词总数：%d    ", total_word);
			printf("第%d页\n", bowl + 1);
			while (choice = getch())
				if (choice == '<' && bowl != 0){
					i = front[--bowl] - 1;
					break;
				}
				else if (choice == '>' && (bowl < (total_word - 1) / 10 && type == '1' || bowl < (total_cn - 1) / 10 && type == CN || bowl < (total_en - 1) / 10 && type == EN)){
					bowl++;
					break;
				}
				else if (choice == '0'){
					show();
					return;
				}
			n = bowl * 10 - 1; 
			isfirst = 1;
			system("cls");
		}
	}
	return;
}
