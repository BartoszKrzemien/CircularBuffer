#include <stdio.h>
#include "circular_buffer.h"

void clearBuffer(){
    if(getchar()!='\n') clearBuffer();
}

int main() {
    int size;
    printf("Podaj rozmiar bufora:");
    if(scanf(" %d", &size) != 1){
        printf("Incorrect input");
        return 1;
    }
    clearBuffer();
    if(size < 1){
        printf("Incorrect input data");
        return 2;
    }

    struct circular_buffer_t *circular_buffer;
    int result = circular_buffer_create_struct(&circular_buffer, size);
    if(result != 0){
        printf("Failed to allocate memory");
        return 8;
    }

    while (1){
        int menu_button;
        printf("Co chcesz zrobic? ");
        if(scanf(" %d", &menu_button) != 1){
            printf("Incorrect input");
            circular_buffer_destroy_struct(&circular_buffer);
            return 1;
        }
        clearBuffer();
        if(menu_button < 0 || menu_button > 6){
            printf("Incorrect input data\n");
        }
        int value;
        int error_code;
        int result_in_case;
        switch (menu_button) {
            case 0:
                circular_buffer_destroy_struct(&circular_buffer);
                return 0;
            case 1:
                printf("Podaj liczbe");
                if (scanf(" %d", &value) != 1) {
                    circular_buffer_destroy_struct(&circular_buffer);
                    printf("Incorrect input");
                    return 1;
                }
                clearBuffer();
                circular_buffer_push_back(circular_buffer, value);
                break;
            case 2:
                result_in_case = circular_buffer_pop_back(circular_buffer, &error_code);
                if (error_code) {
                    printf("Buffer is empty\n");
                } else {
                    printf("%d\n", result_in_case);
                }
                break;
            case 3:
                result_in_case = circular_buffer_pop_front(circular_buffer, &error_code);
                if (error_code) {
                    printf("Buffer is empty\n");
                } else {
                    printf("%d\n", result_in_case);
                }
                break;
            case 4:
                if(circular_buffer_empty(circular_buffer)) {
                    printf("Buffer is empty\n");
                }
                circular_buffer_display(circular_buffer);
                break;
            case 5:
                if (circular_buffer_empty(circular_buffer)) {
                    printf("1\n");
                } else {
                    printf("0\n");
                }
                break;
            case 6:
                if (circular_buffer_full(circular_buffer)) {
                    printf("1\n");
                } else {
                    printf("0\n");
                }
                break;
            default:
                break;
        }
    }
}
