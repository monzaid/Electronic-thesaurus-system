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
	
	printf("��������������˵�\n");
	choice = getch();
	menu();
	
	return;
}



void creats(int type){
	
	system("cls");
	
	if (type == DEL_NEW){
		printf("�Ƿ��������ʿ⣿\n\n��y\t��n\n");
		while (choice = getch())
		if (choice == 'y'){
			total_word = total_cn = total_en = 0;
			fallow_word = MESS;
			file_name[0] = '\0';
			printf("\n���óɹ�\n");
			break;
		}
		else if (choice == 'n')
			break;
		printf("\n�������������һ��\n");
		getch();
		creat();
		return;
	}
	int front = 0;
	char bowlname[MAX_FILE_NAME];
	strcpy(bowlname, file_name);
	if (file_name[0] == '\0')
		front = 1;
	printf("ֻ֧��txt��docϵ���ļ�\n��");
	write_file_name:
	printf("�����ļ����ƣ���д��׺Ĭ��Ϊtxt�ļ�����");
	gets(file_name);
	
	//ûд��׺
	if (strstr (file_name, ".txt") == NULL && strstr (file_name, ".doc") == NULL)
		if (strchr (file_name, '.') != NULL){
			printf("��֧���������͵��ļ�\n������");
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
		printf("�ļ������ڣ�����\n\n");
		printf("����ѡ����(0~1)��\n\t1�������������ļ�����\n\t0����������һ��\n");
		while (choice = getch())
		if (choice == '1'){
			system("cls");
			printf("������");
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
			printf("����ʧ��\n");
		else
			printf("�����ɹ�\n");
	}
	else{
		//total_word = total_cn = total_en = 0;
		int smart = 0;
		
		printf("\n�Ƿ����ܵ��룿����ȡʱ���ظ��ĵ��ʲ���Ҫ�ֶ����������Ƕ�ȡ�ĵ�����ʱ�򲻹����룩\n\n��y\t��n\n");
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
							strcat(dictionary[item].translate, "��");
						strcat(dictionary[item].translate, dictionary[total_word].translate);
						total_word--;
					}
					continue;
				}
				system("cls");
				printf("����1��\t%s\n��˼��\t%s\n\n����2��\t%s\n��˼��\t%s\n\n����ѡ����(0~1)��\n\t1������������1\n\t2������������2\n\t3�����ϲ����ʵ���˼\n\t4�����ϲ����ʺ��޸���˼\n", dictionary[item].word, dictionary[item].translate, dictionary[total_word].word, dictionary[total_word].translate);
				while (choice = getch())
					if (choice == '1'){
						if (dictionary[total_word].language == EN)
							total_en--;
						else
							total_cn--;
						total_word--;
						printf("�����ɹ�\n");
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
						printf("�����ɹ�\n");
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
							strcat(dictionary[item].translate, "��");
						strcat(dictionary[item].translate, dictionary[total_word].translate);
						printf("�ϲ��ɹ�\n");
						total_word--;
						break;
					}
					else if (choice == '4'){
						if (dictionary[total_word].language == EN)
							total_en--;
						else
							total_cn--;
						printf("�������޸ĺ�ĵ��ʵ���˼��");
						//scanf("%s", dictionary[item].translate);
						gets(dictionary[item].translate);
						printf("�޸ĳɹ�\n");
						total_word--;
						break;
					}
			}
			
		}
		if (fclose(fp))
			printf("\n��ȡʧ��\n");
		else
			printf("\n��ȡ���\n");
		printf("\n�ܹ���ȡ���ʣ�%d\t�������ĵ��ʣ�%d\tӢ�ĵ��ʣ�%d\n", total_word, total_cn, total_en);
		
		if (front == 0)
			strcpy(file_name, bowlname);
	}
	
	
	return;
} 

