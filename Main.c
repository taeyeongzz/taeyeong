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
    system("title 타자 연습");
    char startmode;
    char correctSentence[350];
    char* userInput;
    double startTime, endTime;
    int length, speed;
    double accuracy;

    printf("            <   타   자       연  습   >\n\n");
    printf("    짧은 글 연습하기(s)  |  긴 글 연습하기(l)  |  나가기(q)\n\n");
    printf(" :  ");
    scanf(" %c", &startmode);
    getchar();  // 개행 문자 제거

    if (startmode == 'q') {
        return 0;
    }
    else if (startmode == 's') {
        printf("\n              <   짧은 글 연습   >\n\n");
        printf("----------------------------------------------------------------------------------------------------\n\n");
        load_ShortSentences(correctSentence);
    }
    else if (startmode == 'l') {
        printf("\n              <   긴 글 연습   >\n\n");
        printf("----------------------------------------------------------------------------------------------------\n\n");
        load_LongSentences(correctSentence);
    }
    else {
        printf("잘못된 입력입니다.\n");
        return 1;
    }

    userInput = (char*)malloc(500 * sizeof(char));  // 사용자 입력 메모리 할당
    if (userInput == NULL) {
        printf("Memory allocation problem!!");
        return 1;
    }

    printf("\n----------------------------------------------------------------------------------------------------\n\n");
    printf("입력 : \n");
    startTime = (double)clock() / CLOCKS_PER_SEC;
    gets(userInput);
    endTime = (double)clock() / CLOCKS_PER_SEC;

    printf("\n----------------------------------------------------------------------------------------------------\n");
    length = strlen(userInput);  // 타자 수
    double timeTaken = endTime - startTime;  // 소요 시간
    speed = typingSpeed(length, timeTaken);  // 타자 속도
    accuracy = typingAccuracy(userInput, correctSentence);  // 타자 정확도

    printf("글자 수 : %d자  |  빠르기 : %d타  |  정확도 : %.2f%%\n\n", length, speed, accuracy);
    free(userInput);
}

void load_ShortSentences(char* sentence) {
    FILE* fp = fopen("short_sentence_1.txt", "r"); // 글 파일 읽어오기
    if (fp == NULL) {
        printf("Unable to open a file!!\n");
        exit(1);
    }
    fgets(sentence, 100, fp);  // 파일 문자열 읽어와서 sentence배열에 저장
    fclose(fp);
    printf("%s\n", sentence);  // 출력
}

void load_LongSentences(char* sentence) {
    FILE* fp = fopen("long_sentence_1.txt", "r"); // 글 파일 읽어오기
    if (fp == NULL) {
        printf("Unable to open a file!!\n");
        exit(1);
    }
    fgets(sentence, 350, fp);  // 파일 문자열 읽어와서 sentence배열에 저장
    fclose(fp);
    printf("%s\n", sentence);  // 출력
}

int typingSpeed(int typingCount, double timeTaken) {
    return (int)(typingCount / (timeTaken / 60)); // typingCount는 main()의 length
}

double typingAccuracy(const char* userInput, const char* correctCh) {
    int correctCount = 0;  // 일치하는 문자 수
    int total = strlen(correctCh);  // 기준 문자열 길이
    int userLength = strlen(userInput);  // 사용자 입력 문자열 길이

    for (int i = 0; i < total && i < userLength; i++) {
        if (userInput[i] == correctCh[i]) {
            correctCount++;
        }
    }
    return (total > 0) ? (100.0 * correctCount / total) : 0.0;
}