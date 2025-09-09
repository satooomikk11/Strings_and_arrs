#include <stdio.h>

#include "string_functions.h"


// fmemopen() - функция для работы с областью памяти как с файлом, но без файла
// которая у меня не поддерживается

int main() {

    char test[] = "HuaweyDed";


    printf("1. my_strlen: %c\n", my_strlen(test));


    printf("2. my_puts: ");
    my_puts(test);


    printf("3. my_strchr('a'): ");
    printf("Character '%c' found at position: %ld\n",
            'a', my_strchr(test, 'a') - test);


    char dest1[20] = "";
    my_strcpy(dest1, test);
    printf("4. my_strcpy: %s\n", dest1);


    char dest2[10] = "";
    my_strncpy(dest2, test, 5);
    dest2[5] = '\0';
    printf("5. my_strncpy (5 symbols): %s\n", dest2);


    char dest3[20] = "Hello_";
    my_strcat(dest3, test);
    printf("6. my_strcat: %s\n", dest3);


    char dest4[20] = "Test_";
    my_strncat(dest4, test, 3);
    printf("7. my_strncat (3 symbols): %s\n", dest4);


    char numbers[] = "32";
    int result = my_atoi(numbers);
    printf("8. my_atoi: '%s' -> %d\n", numbers, result);


    printf("9. my_strdup: %s\n", my_strdup(test));
    free(my_strdup(test));

    return 0;
}

