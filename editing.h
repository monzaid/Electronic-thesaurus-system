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
	printf("PS���ǵ��޸ĺ�ʱ�����ļ�����Ȼ�ͻ�ǰ��������Ŷ\n");
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
					printf("����ɹ�\n");
				else
					printf("����ʧ��\n");
			}
			else
				printf("û���������ʿ⣡����\n");
			printf("�������������һ��\n");
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
		printf("û���������ʿ⣡����\n�������������һ��\n");
		getch();
		edit();
		return; 
	} 
	
	
	start_edits:
	
	if (type == ADD)
		printf("��������Ҫ�����ĵ��ʣ�");
	else if (type == DEL)
		printf("��������Ҫɾ���ĵ��ʣ�");
	else
		printf("��������Ҫ�޸ĵĵ��ʣ�");
	
	//scanf("%s", word);
	//getchar();
	gets(word);
	
	int item = finds(word);
	
	if (type == ADD){
		if (item == INF){
			printf("��������Ҫ�����ĵ��ʵ���˼��");
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
			printf("�����ɹ�\n�������������һ��\n");
			getch();
			edit();
		}
		else{
			printf("���ʿ��Ѿ�����������ʣ�����\n\n���ʣ�%s\n��˼��%s\n\n����ѡ����(0~3)��\n\t1����������һ�ε���\n\t2�����޸ĵ��ʵ���˼\n\t3����׷�ӵ��ʵ���˼\n\t0����������һ��\n", dictionary[item].word, dictionary[item].translate);
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
					printf("���ʣ�%s\n��˼��%s\n", dictionary[item].word, dictionary[item].translate);
					printf("�����뵥�ʵ�׷����˼��");
					//scanf("%s", translate);
					gets(translate);
					if (dictionary[item].language == EN)
						strcat(dictionary[item].translate, "; ");
					else
						strcat(dictionary[item].translate, "��");
					strcat(dictionary[item].translate, translate);
					printf("׷�ӳɹ�\n");
					printf("\n�޸ĺ󵥴ʣ�%s\n�޸ĺ���˼��%s\n", dictionary[item].word, dictionary[item].translate);
					printf("\n�������������һ��\n");
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
			printf("���ʿ�û��������ʣ�����\n�������������һ��\n");
					getch();
					edit();
		}
		else{
			printf("\n���ʣ�%s\n��˼��%s\n", dictionary[item].word, dictionary[item].translate);
			printf("\n�Ƿ�ɾ����\n��y\t��n\n");
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
					printf("ɾ���ɹ�\n");
					break;
				}
				else if (choice == 'n')
					break;
			}
			printf("�������������һ��\n");
				getch();
				edit();
		}
	}
	else if (type == MEND){
		if (item == INF){
			printf("���ʿ�û��������ʣ�����\n\n����ѡ����(0~1)��\n\t1���������޸ĵ���\n\t0����������һ��\n");
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
			printf("\n���ʣ�%s\n��˼��%s\n", dictionary[item].word, dictionary[item].translate);
			printf("\n����ѡ����(1~3)��\n\t1�����޸ĵ���\n\t2�����޸ĵ��ʵ���˼\n\t3����׷�ӵ��ʵ���˼\n");
			while (choice = getch()){
				if (choice == '1'){
					system("cls");
					printf("���ʣ�%s\n��˼��%s\n", dictionary[item].word, dictionary[item].translate);
					printf("�������޸ĺ�ĵ��ʣ�");
					//scanf("%s", dictionary[item].word);
					gets(dictionary[item].word);
					dictionary[item].hash = hash(dictionary[item].word);
					fallow_word = MESS;
					printf("�޸ĳɹ�\n");
					printf("\n�޸ĺ󵥴ʣ�%s\n�޸ĺ���˼��%s\n", dictionary[item].word, dictionary[item].translate);
					break;
				}
				else if (choice == '2'){
					mend_word_translate:
					system("cls");
					printf("���ʣ�%s\n��˼��%s\n", dictionary[item].word, dictionary[item].translate);
					printf("�������޸ĺ�ĵ��ʵ���˼��");
					//scanf("%s", dictionary[item].translate);
					gets(dictionary[item].translate);
					printf("�޸ĳɹ�\n");
					printf("\n�޸ĺ󵥴ʣ�%s\n�޸ĺ���˼��%s\n", dictionary[item].word, dictionary[item].translate);
					break; 
				}
				else if (choice == '3'){
					goto add_word_translate;
					break;
				}
			}
			printf("\n�������������һ��\n");
			getch();
			edit();
		}
	}
	return;
}
