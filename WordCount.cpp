#include <stdio.h>  
#include <stdlib.h>  
#include <ctype.h>  
#include <string.h>  
  
// 函数声明  
int count_characters(FILE *file);  
int count_words(FILE *file);  
  
int main(int argc, char *argv[]) {  
    FILE *file;  
    char *filename;  
    char parameter;  
  
    // 检查命令行参数数量  
    if (argc != 3) {  
        fprintf(stderr, "Usage: %s [-c|-w] [input_file_name]\n", argv[0]);  
        return 1;  
    }  
  
    // 提取参数和文件名  
    parameter = argv[1][1]; // 提取-c或-w  
    filename = argv[2];  
  
    // 打开文件  
    file = fopen(filename, "r");  
    if (file == NULL) {  
        perror("Error opening file");  
        return 1;  
    }  
  
    // 根据参数统计字符数或单词数  
    int count;  
    switch (parameter) {  
        case 'c':  
            count = count_characters(file);  
            printf("字符数：%d\n", count);  
            break;  
        case 'w':  
            count = count_words(file);  
            printf("单词数：%d\n", count);  
            break;  
        default:  
            fprintf(stderr, "Invalid parameter: %c\n", parameter);  
            fclose(file);  
            return 1;  
    }  
  
    // 关闭文件  
    fclose(file);  
    return 0;  
}  
  
// 统计字符数  
int count_characters(FILE *file) {  
    int count = 0;  
    char ch;  
    while ((ch = fgetc(file)) != EOF) {  
        count++;  
    }  
    // 重置文件指针到文件开始，以便其他函数可以读取  
    rewind(file);  
    return count;  
}  
  
// 统计单词数  
int count_words(FILE *file) {  
    int count = 0;  
    int in_word = 0;  
    char ch;  
  
    while ((ch = fgetc(file)) != EOF) {  
        // 忽略空白字符，除非它们出现在单词之间  
        if (isspace(ch) && in_word) {  
            in_word = 0;  
            count++;  
        } else if (!isspace(ch) && !ispunct(ch)) { // 忽略标点符号  
            in_word = 1;  
        }  
    }  
    // 如果文件以单词结束，需要额外计数  
    if (in_word) {  
        count++;  
    }  
    // 重置文件指针到文件开始，以便其他函数可以读取（如果需要）  
    rewind(file);  
    return count;  
}
