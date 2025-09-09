#include "string_functions.h"


// prints strings character by character until the NULL character is encountered
// str - передаваемая строка
int my_puts(const char* str)
    {

    if (str == NULL)
        {
        return EOF;
        }

    // пока не 0
    for ( ; *str != '\0' ; str++ )
        {
        if (putchar(*str) == EOF)
            {
            return EOF;
            }
        }

    // error -> EOF
    return (putchar('\n') == EOF) ? EOF : 0;

    }


// find the first occurrence of a character
// str - передаваемая строка
// ch  - элемент, который мы ищем в строке (int преобразуется внутри системы, чтобы юзать символы)
char *my_strchr(const char *str, int ch)
    {

    if (str == NULL)
        {
        return NULL;
        }

    // int -> char
    char target = (char)ch;

    for ( ; *str != '\0' ; str++ )
        {
        if (*str == target)
            {
            return (char *)str;
            }
        }

    return (target == '\0') ? (char *)str : NULL;

    }


// length of the string
// str - передаваемая строка
int my_strlen(const char *str)
    {

    // для подсчёта chars в str
    int counter = 0;

    for ( ; *str != '\0' ; str++ )
        {
        counter++;
        }

    return counter;

    }


// copy one string into another (with 0?)
// dest - строка куда копируем
// src  - строка которую копируем
char *my_strcpy(char *dest, const char *src)
    {

    // ptr - running pointer
    // без ptr возвращался бы указатель на начало, т.к. dest бы менялся
    // а так ptr бежит по dest
    char *ptr = dest;

    while (*src != '\0')
        {
        // двигаем ptr по dest
        *ptr++ = *src++;
        }

    // терминатор в конец, чтобы в конце dest не было мусора
    *ptr = '\0';
    return dest;

    }


// copy a specified number of characters from one string to another
// dest - строка куда копируем
// src  - строка которую копируем
// n    - кол-во копируемых символов
char *my_strncpy(char *dest, const char *src, size_t n)
    {

    char *ptr = dest;

    // копируем символы
    for (size_t i = 0; i < n && src[i] != '\0'; i++)
        {
        *ptr++ = src[i];
        }

    for (size_t i = ptr - dest; i < n; i++)
        {
        *ptr++ = '\0';
        }

    return dest;

    }


// append a copy in the destination string (with 0)
// dest - строка куда добавляем
// src  - строка которую добавляем
char *my_strcat(char *dest, const char *src)
    {

    char *ptr = dest;

    while (*ptr != '\0')
        {
        ptr++;
        }

    while (*src != '\0')
        {
        *ptr++ = *src++;
        }

    *ptr = '\0';
    return dest;

    }


// append not more than n characters (with 0)
// dest - строка куда добавляем
// src  - строка которую добавляем
// n    - кол-во доп символов
char *my_strncat(char *dest, const char *src, size_t n)
    {

    char *ptr = dest;
    size_t i = 0;

    while (*ptr != '\0')
        {
        ptr++;
        }

    while (i < n && src[i] != '\0')
        {
        *ptr++ = src[i++];
        }

    *ptr = '\0';
    return dest;

    }


// converts the numbers in string form to their integer value
// accepts a string as a parameter and yields an integer value in return
// strg - преобразуемая строка
int my_atoi(const char *strg)
    {

    int result = 0;
    int sign = 1;

    // пропуск пробелов
    while (*strg == ' ')
        {
        strg++;
        }

    // обработка знака
    if (*strg == '-')
        {
        sign = -1;
        strg++;
        }
    else if (*strg == '+')
        {
        strg++;
        }

    // преобразование
    while (*strg >= '0' && *strg <= '9')
        {
        result = result * 10 + (*strg - '0');
        strg++;
        }

    return sign * result;

    }


// reads the given number of characters of a line
// from the input stream and stores it into the specified string
// buff   - строковый буфер с входными данными
// n      - кол-во символов
// stream - входной поток
char *my_fgets(char *buff, int n, FILE *stream)
    {

    int ch;
    char *ptr = buff;

    if (n <= 0) return NULL;

    // чтение до n-1 символов или новой строки/EOF
    for (int i = 0; i < n - 1; i++)
        {
        ch = fgetc(stream);

        if (ch == EOF)
            {
            if (ptr == buff) return NULL; // ничего не прочитали
            break;
            }

        *ptr++ = (char)ch;

        if (ch == '\n')
            {
            break;
            }
        }

    *ptr = '\0';
    return buff;

    }


// returns a pointer to the duplicated string s
// сама функция не должна освобождать память, это должен делать вызывающий код
// s - копируемая строка
char *my_strdup(const char *s)
    {

    if (s == NULL) return NULL;

    size_t len = strlen(s) + 1;
    char *new_str = (char *)malloc(len);

    if (new_str == NULL) return NULL;

    return (char *)memcpy(new_str, s, len);

    }


// get a string from a file
// lineptr - указатель на указатель буфера
// n       - размер буфера
// stream  - файл

// pos - позиция в буфере
// ch  - прочитанный символ
ssize_t my_getline(char **lineptr, size_t *n, FILE *stream)
    {

    // проверка входных параметров
    if (lineptr == NULL || n == NULL || stream == NULL)
        {
        return -1;
        }

    size_t pos = 0;
    int ch = 0;

    // выделение памяти, если не выделена
    if (*lineptr == NULL || *n == 0)
        {
        *n = 128;
        *lineptr = (char *)malloc(*n);
        if (*lineptr == NULL) return -1;
        }

    while ((ch = fgetc(stream)) != EOF)
        {
        // увеличиваем буфер при необходимости
        if (pos + 1 >= *n)
            {
            size_t new_size = *n * 2;
            char *new_ptr = (char *)realloc(*lineptr, new_size);
            if (new_ptr == NULL) return -1;
            *lineptr = new_ptr;
            *n = new_size;
            }

        (*lineptr)[pos++] = (char)ch;

        if (ch == '\n')
            {
            break;
            }
        }

    if (pos == 0 && ch == EOF)
        {
        return -1; // конец файла
        }

    (*lineptr)[pos] = '\0';
    return (ssize_t)pos;

    }
