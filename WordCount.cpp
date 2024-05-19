#include <stdio.h>  
#include <stdlib.h>  
#include <ctype.h>  
#include <string.h>  
  
// ��������  
int count_characters(FILE *file);  
int count_words(FILE *file);  
  
int main(int argc, char *argv[]) {  
    FILE *file;  
    char *filename;  
    char parameter;  
  
    // ��������в�������  
    if (argc != 3) {  
        fprintf(stderr, "Usage: %s [-c|-w] [input_file_name]\n", argv[0]);  
        return 1;  
    }  
  
    // ��ȡ�������ļ���  
    parameter = argv[1][1]; // ��ȡ-c��-w  
    filename = argv[2];  
  
    // ���ļ�  
    file = fopen(filename, "r");  
    if (file == NULL) {  
        perror("Error opening file");  
        return 1;  
    }  
  
    // ���ݲ���ͳ���ַ����򵥴���  
    int count;  
    switch (parameter) {  
        case 'c':  
            count = count_characters(file);  
            printf("�ַ�����%d\n", count);  
            break;  
        case 'w':  
            count = count_words(file);  
            printf("��������%d\n", count);  
            break;  
        default:  
            fprintf(stderr, "Invalid parameter: %c\n", parameter);  
            fclose(file);  
            return 1;  
    }  
  
    // �ر��ļ�  
    fclose(file);  
    return 0;  
}  
  
// ͳ���ַ���  
int count_characters(FILE *file) {  
    int count = 0;  
    char ch;  
    while ((ch = fgetc(file)) != EOF) {  
        count++;  
    }  
    // �����ļ�ָ�뵽�ļ���ʼ���Ա������������Զ�ȡ  
    rewind(file);  
    return count;  
}  
  
// ͳ�Ƶ�����  
int count_words(FILE *file) {  
    int count = 0;  
    int in_word = 0;  
    char ch;  
  
    while ((ch = fgetc(file)) != EOF) {  
        // ���Կհ��ַ����������ǳ����ڵ���֮��  
        if (isspace(ch) && in_word) {  
            in_word = 0;  
            count++;  
        } else if (!isspace(ch) && !ispunct(ch)) { // ���Ա�����  
            in_word = 1;  
        }  
    }  
    // ����ļ��Ե��ʽ�������Ҫ�������  
    if (in_word) {  
        count++;  
    }  
    // �����ļ�ָ�뵽�ļ���ʼ���Ա������������Զ�ȡ�������Ҫ��  
    rewind(file);  
    return count;  
}
