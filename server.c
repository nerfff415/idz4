#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define MAX_BUFFER_SIZE 1024

// Структура для хранения информации о книге
typedef struct {
    char identifier[50];
    int row;
    int shelf;
    int book_number;
} BookInfo;

int compare_books(const void* a, const void* b) {
    BookInfo* book1 = (BookInfo*)a;
    BookInfo* book2 = (BookInfo*)b;
    return strcmp(book1->identifier, book2->identifier);
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Использование: %s <IP-адрес сервера> <порт сервера> <количество рядов>\n", argv[0]);
        exit(1);
    }

    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[MAX_BUFFER_SIZE];
    BookInfo catalog[MAX_BUFFER_SIZE];
    int num_books = 0;
    int num_rows = atoi(argv[3]); // Получение количества рядов из аргумента командной строки

    // Создание UDP сокета
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Ошибка при создании сокета");
        exit(1);
    }

    // Настройка адреса сервера
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(atoi(argv[2])); // Преобразование порта из аргумента командной строки

    // Привязка сокета к адресу сервера
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Ошибка при привязке сокета к адресу");
        exit(1);
    }

    printf("Сервер запущен и готов принимать данные от клиентов...\n");

    int num_clients = 0; // Счетчик количества клиентов

    while (num_clients < num_rows) {
        socklen_t client_len = sizeof(client_addr);
        // Получение данных от клиента
        int bytes_received = recvfrom(sockfd, buffer, MAX_BUFFER_SIZE, 0, (struct sockaddr*)&client_addr, &client_len);
        if (bytes_received < 0) {
            perror("Ошибка при приеме данных от клиента");
            exit(1);
        }

        buffer[bytes_received] = '\0';

        if (strcmp(buffer, "END") == 0) {
            // Если получен сигнал окончания передачи данных от клиента
            printf("Клиент на ряду %d завершил передачу данных.\n", num_clients + 1);
            num_clients++;
            continue;
        }

        // Разбор полученных данных
        char* token = strtok(buffer, ",");
        strcpy(catalog[num_books].identifier, token);
        token = strtok(NULL, ",");
        catalog[num_books].row = num_clients + 1;
        catalog[num_books].shelf = atoi(token);
        token = strtok(NULL, ",");
        catalog[num_books].book_number = atoi(token);

        num_books++;
    }

    // Сортировка каталога
    qsort(catalog, num_books, sizeof(BookInfo), compare_books);

    // Вывод отсортированного каталога
    printf("Каталог библиотеки:\n");
    for (int i = 0; i < num_books; i++) {
        printf("Название книги: %s, Номер ряда: %d, Номер шкафа: %d, Номер книги в шкафу: %d\n", catalog[i].identifier, catalog[i].row, catalog[i].shelf, catalog[i].book_number);
    }

    // Закрытие сокета
    close(sockfd);

    return 0;
}
