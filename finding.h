#ifndef SOURCE_H
#define SOURCE_H
#include "source.h"
#endif


void find(){
	static char word[100]; 
	system("cls");
	if (total_word == 0){
		printf("生词库没有单词！！！\n请注意是否载入了文件或者载入的文件没有单词！！！\n按任意键返回主菜单\n");
		choice = getch();
		menu();
		return;
	}
	find_word:
	printf("请输入要查找的单词：");
	//scanf("%s", word);
	gets(word);
	int item = finds(word);
	if (item == INF)
		printf("生词库没有这个单词！！！\n\n输入选项编号(0~1)：\n\t1——重新查找单词\n\t0——返回主菜单\n");
	else
		printf("找到了！\n\n单词：%s\n意思：%s\n\n输入选项编号(0~1)：\n\t1——再查询一次单词\n\t0——返回主菜单\n", dictionary[item].word, dictionary[item].translate);
	while (choice = getch()){
		if (choice == '1'){
			system("cls");
			goto find_word;
			break;
		}
		else if (choice == '0'){
			menu();
			break; 
		}
	}
	return;
}

int finds(char temp[]){
	if (fallow_word != FALLOW_HASH)
		sorts(FALLOW_HASH, WORDS);
	ULL temp_hash = hash(temp);
	return bisearch(temp_hash, WORDS);
}
