#ifndef SOURCE_H
#define SOURCE_H
#include "source.h"
#endif


void find(){
	static char word[100]; 
	system("cls");
	if (total_word == 0){
		printf("���ʿ�û�е��ʣ�����\n��ע���Ƿ��������ļ�����������ļ�û�е��ʣ�����\n��������������˵�\n");
		choice = getch();
		menu();
		return;
	}
	find_word:
	printf("������Ҫ���ҵĵ��ʣ�");
	//scanf("%s", word);
	gets(word);
	int item = finds(word);
	if (item == INF)
		printf("���ʿ�û��������ʣ�����\n\n����ѡ����(0~1)��\n\t1�������²��ҵ���\n\t0�����������˵�\n");
	else
		printf("�ҵ��ˣ�\n\n���ʣ�%s\n��˼��%s\n\n����ѡ����(0~1)��\n\t1�����ٲ�ѯһ�ε���\n\t0�����������˵�\n", dictionary[item].word, dictionary[item].translate);
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
