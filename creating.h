#ifndef SOURCE_H
#define SOURCE_H
#include "source.h"
#endif
#define CREAT_NEW '1'
#define READ_NEW '2'
#define DEL_NEW '3' 


void creats(int type);



void creat(){
	print_menu(CREAT);
	while (choice = getch())
		if (choice >= CREAT_NEW && choice <= DEL_NEW){
			creats(choice);
			break;
		}
		else if (choice == '4'){
			menu();
			return;
		}
		else if (choice == '0'){
			end();
			return;
		}
	
	printf("按任意键返回主菜单\n");
	choice = getch();
	menu();
	
	return;
}



void creats(int type){
	
	system("cls");
	
	if (type == DEL_NEW){
		printf("是否重置生词库？\n\n是y\t否n\n");
		while (choice = getch())
		if (choice == 'y'){
			total_word = total_cn = total_en = 0;
			fallow_word = MESS;
			file_name[0] = '\0';
			printf("\n重置成功\n");
			break;
		}
		else if (choice == 'n')
			break;
		printf("\n按任意键返回上一层\n");
		getch();
		creat();
		return;
	}
	int front = 0;
	char bowlname[MAX_FILE_NAME];
	strcpy(bowlname, file_name);
	if (file_name[0] == '\0')
		front = 1;
	printf("只支持txt，doc系列文件\n请");
	write_file_name:
	printf("输入文件名称（不写后缀默认为txt文件）：");
	gets(file_name);
	
	//没写后缀
	if (strstr (file_name, ".txt") == NULL && strstr (file_name, ".doc") == NULL)
		if (strchr (file_name, '.') != NULL){
			printf("不支持这种类型的文件\n请重新");
			goto write_file_name; 
		}
		else
			strcat (file_name, ".txt");
	
	if (type == CREAT_NEW){
		fp = fopen (file_name, "w+");
		total_word = total_cn = total_en = 0;
	}
	else
		fp = fopen (file_name, "r+");
	
	if (fp == NULL){
		system("cls");
		printf("文件不存在！！！\n\n");
		printf("输入选项编号(0~1)：\n\t1——重新输入文件名称\n\t0——返回上一层\n");
		while (choice = getch())
		if (choice == '1'){
			system("cls");
			printf("请重新");
			goto write_file_name; 
			break;
		}
		else if (choice == '0'){
			creat();
			break;
		}
	}
	
	if (type == CREAT_NEW){
		if (fclose(fp))
			printf("创建失败\n");
		else
			printf("创建成功\n");
	}
	else{
		//total_word = total_cn = total_en = 0;
		int smart = 0;
		
		printf("\n是否智能导入？（读取时有重复的单词不需要手动操作，但是读取的单词有时候不够理想）\n\n是y\t否n\n");
		while (choice = getch()){
			if (choice == 'y'){
				smart = 1;
				break;
			}
			else if (choice == 'n'){
				smart = 0;
				break;
			}
		}
		fseek(fp, 0L, 2);
		int tail = ftell(fp);
		fseek(fp, 0L, 0);
		for ( ; tail != ftell(fp); total_word++){
			//fscanf(fp, "%s", dictionary[total_word].word);
			for (int i = 0; 1; i++){
				dictionary[total_word].word[i] = fgetc(fp);
				if (dictionary[total_word].word[i] == '\n' || dictionary[total_word].word[i] == ' '){
					dictionary[total_word].word[i] = '\0';
					break;
				}
				else if (dictionary[total_word].word[i] == '_')
					dictionary[total_word].word[i] = ' ';
			}
			if (dictionary[total_word].word[0] == '\0'){
				total_word--;
				continue;
			}
			//fgetc(fp);
			fgets(dictionary[total_word].translate, MAX_WORD_LONG+5, fp);
			if (dictionary[total_word].translate[strlen(dictionary[total_word].translate)-1] == '\n')
				dictionary[total_word].translate[strlen(dictionary[total_word].translate)-1] = '\0';
			//fscanf(fp, "%s", dictionary[total_word].translate);
			dictionary[total_word].hash = hash(dictionary[total_word].word);
			
			if (dictionary[total_word].word[0] >= 'a' && dictionary[total_word].word[0] <= 'z' || dictionary[total_word].word[0] >= 'A' && dictionary[total_word].word[0] <= 'Z'){
				total_en++;
				dictionary[total_word].language = EN;
			}
			else{
				total_cn++;
				dictionary[total_word].language = CN;
			}
			
			fallow_word = MESS;
			int item = finds(dictionary[total_word].word);
			
			if (item != INF && item < total_word){
				if (smart == 1){
					if (dictionary[total_word].language == EN)
						total_en--;
					else
						total_cn--;
					if (strcmp(dictionary[total_word].translate, dictionary[item].translate) == 0)
						total_word--;
					else{
						if (dictionary[item].language == EN)
							strcat(dictionary[item].translate, "; ");
						else
							strcat(dictionary[item].translate, "；");
						strcat(dictionary[item].translate, dictionary[total_word].translate);
						total_word--;
					}
					continue;
				}
				system("cls");
				printf("单词1：\t%s\n意思：\t%s\n\n单词2：\t%s\n意思：\t%s\n\n输入选项编号(0~1)：\n\t1——保留单词1\n\t2——保留单词2\n\t3——合并单词的意思\n\t4——合并单词后修改意思\n", dictionary[item].word, dictionary[item].translate, dictionary[total_word].word, dictionary[total_word].translate);
				while (choice = getch())
					if (choice == '1'){
						if (dictionary[total_word].language == EN)
							total_en--;
						else
							total_cn--;
						total_word--;
						printf("保留成功\n");
						break;
					}
					else if (choice == '2'){
						if (dictionary[item].language == EN)
							total_en--;
						else
							total_cn--;
						strcpy(dictionary[item].word, dictionary[total_word].word);
						strcpy(dictionary[item].translate, dictionary[total_word].translate);
						dictionary[item].language = dictionary[total_word].language;
						total_word--;
						printf("保留成功\n");
						break;
					}
					else if (choice == '3'){
						if (dictionary[total_word].language == EN)
							total_en--;
						else
							total_cn--;
						if (dictionary[item].language == EN)
							strcat(dictionary[item].translate, "; ");
						else
							strcat(dictionary[item].translate, "；");
						strcat(dictionary[item].translate, dictionary[total_word].translate);
						printf("合并成功\n");
						total_word--;
						break;
					}
					else if (choice == '4'){
						if (dictionary[total_word].language == EN)
							total_en--;
						else
							total_cn--;
						printf("请输入修改后的单词的意思：");
						//scanf("%s", dictionary[item].translate);
						gets(dictionary[item].translate);
						printf("修改成功\n");
						total_word--;
						break;
					}
			}
			
		}
		if (fclose(fp))
			printf("\n读取失败\n");
		else
			printf("\n读取完成\n");
		printf("\n总共读取单词：%d\t其中中文单词：%d\t英文单词：%d\n", total_word, total_cn, total_en);
		
		if (front == 0)
			strcpy(file_name, bowlname);
	}
	
	
	return;
} 

