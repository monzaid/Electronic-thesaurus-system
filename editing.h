#ifndef SOURCE_H
#define SOURCE_H
#include "source.h"
#endif
#define ADD '1'
#define DEL '2'
#define MEND '3'

void edits(int type);


void edit(){
	print_menu(EDIT);
	printf("PS：记得修改后及时保存文件，不然就会前功尽弃的哦\n");
	while (choice = getch())
		if (choice == ADD || choice == DEL || choice == MEND){
			edits(choice);
			break;
		}
		else if (choice == '4'){
			menu();
			break;
		}
		else if (choice == '5'){
			system("cls");
			if (strcmp(file_name, "") != 0){
				fp = fopen(file_name, "w+");
				
				//sorts(FALLOW_ASCII, WORDS);
				
				for (int i = 0; i < total_word; i++){
					//fprintf(fp, "%s %s\n", dictionary[i].word, dictionary[i].translate);
					for (int j = 0; dictionary[i].word[j]; j++)
						if (dictionary[i].word[j] == ' ')
							fprintf(fp, "_");
						else
							fprintf(fp, "%c", dictionary[i].word[j]);
					fprintf(fp, " ");
					fprintf(fp, "%s\n", dictionary[i].translate);
				}
				if (!fclose(fp))
					printf("保存成功\n");
				else
					printf("保存失败\n");
			}
			else
				printf("没有载入生词库！！！\n");
			printf("按任意键返回上一层\n");
			getch();
			edit();
			break;
		} 
		else if (choice == '0'){
			end();
			break;
		}
	return;
}




void edits(int type){
	static char word[100]; 
	static char translate[100];
	
	system("cls");
	
	if (strcmp(file_name, "") == 0){
		printf("没有载入生词库！！！\n按任意键返回上一层\n");
		getch();
		edit();
		return; 
	} 
	
	
	start_edits:
	
	if (type == ADD)
		printf("请输入你要新增的单词：");
	else if (type == DEL)
		printf("请输入你要删除的单词：");
	else
		printf("请输入你要修改的单词：");
	
	//scanf("%s", word);
	//getchar();
	gets(word);
	
	int item = finds(word);
	
	if (type == ADD){
		if (item == INF){
			printf("请输入你要新增的单词的意思：");
			//scanf("%s", dictionary[total_word].translate);
			gets(dictionary[total_word].translate);
			strcpy(dictionary[total_word].word, word);
			dictionary[total_word].hash = hash(dictionary[total_word].word);
			if (dictionary[total_word].word[0] >= 'a' && dictionary[total_word].word[0] <= 'z' || dictionary[total_word].word[0] >= 'A' && dictionary[total_word].word[0] <= 'Z'){
				total_en++;
				dictionary[total_word].language = EN;
			}
			else{
				total_cn++;
				dictionary[total_word].language = CN;
			}
			total_word++;
			fallow_word = MESS;
			printf("新增成功\n按任意键返回上一层\n");
			getch();
			edit();
		}
		else{
			printf("生词库已经存在这个单词！！！\n\n单词：%s\n意思：%s\n\n输入选项编号(0~3)：\n\t1——再新增一次单词\n\t2——修改单词的意思\n\t3——追加单词的意思\n\t0——返回上一层\n", dictionary[item].word, dictionary[item].translate);
			while (choice = getch()){
				if (choice == ADD){
					system("cls");
					goto start_edits;
					break;
				}
				else if (choice == '2'){
					goto mend_word_translate;
					break;
				}
				else if (choice == '3'){
					add_word_translate:
					system("cls");
					printf("单词：%s\n意思：%s\n", dictionary[item].word, dictionary[item].translate);
					printf("请输入单词的追加意思：");
					//scanf("%s", translate);
					gets(translate);
					if (dictionary[item].language == EN)
						strcat(dictionary[item].translate, "; ");
					else
						strcat(dictionary[item].translate, "；");
					strcat(dictionary[item].translate, translate);
					printf("追加成功\n");
					printf("\n修改后单词：%s\n修改后意思：%s\n", dictionary[item].word, dictionary[item].translate);
					printf("\n按任意键返回上一层\n");
					getch();
					edit();
					break;
				}
				else if (choice == '0'){
					edit();
					break;
				}
			} 
		}
	}
	else if (type == DEL){
		if (item == INF){
			printf("生词库没有这个单词！！！\n按任意键返回上一层\n");
					getch();
					edit();
		}
		else{
			printf("\n单词：%s\n意思：%s\n", dictionary[item].word, dictionary[item].translate);
			printf("\n是否删除？\n是y\t否n\n");
			while (choice = getch()){
				if (choice == 'y'){
					if (dictionary[item].language == EN)
						total_en--;
					else
						total_cn--;
					total_word--;
					struct word_node temp = dictionary[item];
					dictionary[item] = dictionary[total_word];
					dictionary[total_word] = temp;
					printf("删除成功\n");
					break;
				}
				else if (choice == 'n')
					break;
			}
			printf("按任意键返回上一层\n");
				getch();
				edit();
		}
	}
	else if (type == MEND){
		if (item == INF){
			printf("生词库没有这个单词！！！\n\n输入选项编号(0~1)：\n\t1——重新修改单词\n\t0——返回上一层\n");
			while (choice = getch()){
				if (choice == '1'){
					system("cls");
					goto start_edits;
					break;
				}
				else if (choice == '0'){
					edit();
					break; 
				}
			}
		}
		else{
			printf("\n单词：%s\n意思：%s\n", dictionary[item].word, dictionary[item].translate);
			printf("\n输入选项编号(1~3)：\n\t1——修改单词\n\t2——修改单词的意思\n\t3——追加单词的意思\n");
			while (choice = getch()){
				if (choice == '1'){
					system("cls");
					printf("单词：%s\n意思：%s\n", dictionary[item].word, dictionary[item].translate);
					printf("请输入修改后的单词：");
					//scanf("%s", dictionary[item].word);
					gets(dictionary[item].word);
					dictionary[item].hash = hash(dictionary[item].word);
					fallow_word = MESS;
					printf("修改成功\n");
					printf("\n修改后单词：%s\n修改后意思：%s\n", dictionary[item].word, dictionary[item].translate);
					break;
				}
				else if (choice == '2'){
					mend_word_translate:
					system("cls");
					printf("单词：%s\n意思：%s\n", dictionary[item].word, dictionary[item].translate);
					printf("请输入修改后的单词的意思：");
					//scanf("%s", dictionary[item].translate);
					gets(dictionary[item].translate);
					printf("修改成功\n");
					printf("\n修改后单词：%s\n修改后意思：%s\n", dictionary[item].word, dictionary[item].translate);
					break; 
				}
				else if (choice == '3'){
					goto add_word_translate;
					break;
				}
			}
			printf("\n按任意键返回上一层\n");
			getch();
			edit();
		}
	}
	return;
}
