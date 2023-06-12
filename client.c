#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define MAX_BUFFER_SIZE 1024

// Функция для отправки данных серверу
void send_data(int sockfd, struct sockaddr_in* server_addr, char* data) {
    // Отправка данных на сервер
    int bytes_sent = sendto(sockfd, data, strlen(data), 0, (struct sockaddr*)server_addr, sizeof(*server_addr));
    if (bytes_sent < 0) {
        perror("Ошибка при отправке данных на сервер");
        exit(1);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Использование: %s <IP-адрес сервера> <порт сервера> <номер ряда>\n", argv[0]);
        exit(1);
    }

    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[MAX_BUFFER_SIZE];
    int row_number = atoi(argv[3]); // Получение номера ряда из аргумента командной строки

    // Создание UDP сокета
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Ошибка при создании сокета");
        exit(1);
    }

    // Настройка адреса сервера
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2])); // Преобразование порта из аргумента командной строки
    if (inet_pton(AF_INET, argv[1], &(server_addr.sin_addr)) <= 0) {
        perror("Ошибка при преобразовании IP-адреса");
        exit(1);
    }

    printf("Введите информацию о книгах в ряде %d (для окончания ввода введите END):\n", row_number);

    while (1) {
        printf("Идентификатор, Номер полки, Номер книги в полке: ");
        fgets(buffer, MAX_BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = '\0'; // Удаление символа новой строки

        if (strcmp(buffer, "END") == 0) {
            // Отправка сигнала окончания передачи данных серверу
            send_data(sockfd, &server_addr, "END");
            break;
        }

        // Отправка данных серверу
        send_data(sockfd, &server_addr, buffer);
    }

    // Закрытие сокета
    close(sockfd);

    return 0;
}
