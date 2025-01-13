#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

void load_ShortSentences(char* sentence);
void load_LongSentences(char* sentence);
int typingSpeed(int typingCount, double timeTaken);
double typingAccuracy(const char* userInput, const char* correctCh);

int main()
{
    system("title Ÿ�� ����");
    char startmode;
    char correctSentence[350];
    char* userInput;
    double startTime, endTime;
    int length, speed;
    double accuracy;

    printf("            <   Ÿ   ��       ��  ��   >\n\n");
    printf("    ª�� �� �����ϱ�(s)  |  �� �� �����ϱ�(l)  |  ������(q)\n\n");
    printf(" :  ");
    scanf(" %c", &startmode);
    getchar();  // ���� ���� ����

    if (startmode == 'q') {
        return 0;
    }
    else if (startmode == 's') {
        printf("\n              <   ª�� �� ����   >\n\n");
        printf("----------------------------------------------------------------------------------------------------\n\n");
        load_ShortSentences(correctSentence);
    }
    else if (startmode == 'l') {
        printf("\n              <   �� �� ����   >\n\n");
        printf("----------------------------------------------------------------------------------------------------\n\n");
        load_LongSentences(correctSentence);
    }
    else {
        printf("�߸��� �Է��Դϴ�.\n");
        return 1;
    }

    userInput = (char*)malloc(500 * sizeof(char));  // ����� �Է� �޸� �Ҵ�
    if (userInput == NULL) {
        printf("Memory allocation problem!!");
        return 1;
    }

    printf("\n----------------------------------------------------------------------------------------------------\n\n");
    printf("�Է� : \n");
    startTime = (double)clock() / CLOCKS_PER_SEC;
    gets(userInput);
    endTime = (double)clock() / CLOCKS_PER_SEC;

    printf("\n----------------------------------------------------------------------------------------------------\n");
    length = strlen(userInput);  // Ÿ�� ��
    double timeTaken = endTime - startTime;  // �ҿ� �ð�
    speed = typingSpeed(length, timeTaken);  // Ÿ�� �ӵ�
    accuracy = typingAccuracy(userInput, correctSentence);  // Ÿ�� ��Ȯ��

    printf("���� �� : %d��  |  ������ : %dŸ  |  ��Ȯ�� : %.2f%%\n\n", length, speed, accuracy);
    free(userInput);
}

void load_ShortSentences(char* sentence) {
    FILE* fp = fopen("short_sentence_1.txt", "r"); // �� ���� �о����
    if (fp == NULL) {
        printf("Unable to open a file!!\n");
        exit(1);
    }
    fgets(sentence, 100, fp);  // ���� ���ڿ� �о�ͼ� sentence�迭�� ����
    fclose(fp);
    printf("%s\n", sentence);  // ���
}

void load_LongSentences(char* sentence) {
    FILE* fp = fopen("long_sentence_1.txt", "r"); // �� ���� �о����
    if (fp == NULL) {
        printf("Unable to open a file!!\n");
        exit(1);
    }
    fgets(sentence, 350, fp);  // ���� ���ڿ� �о�ͼ� sentence�迭�� ����
    fclose(fp);
    printf("%s\n", sentence);  // ���
}

int typingSpeed(int typingCount, double timeTaken) {
    return (int)(typingCount / (timeTaken / 60)); // typingCount�� main()�� length
}

double typingAccuracy(const char* userInput, const char* correctCh) {
    int correctCount = 0;  // ��ġ�ϴ� ���� ��
    int total = strlen(correctCh);  // ���� ���ڿ� ����
    int userLength = strlen(userInput);  // ����� �Է� ���ڿ� ����

    for (int i = 0; i < total && i < userLength; i++) {
        if (userInput[i] == correctCh[i]) {
            correctCount++;
        }
    }
    return (total > 0) ? (100.0 * correctCount / total) : 0.0;
}