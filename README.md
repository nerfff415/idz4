Безруков Михаил Александрович БПИ 214 Вариант 22

Задача об инвентаризации по рядам. После нового года в библиотеке университета обнаружилась пропажа каталога. После поиска и наказания виноватых, ректор дал указание восстановить каталог силами студентов. Фонд библиотека представляет собой прямоугольное помещение, в котором находится M рядов по N шка8 фов по K книг в каждом шкафу. Требуется создать приложение, составляющее каталог. В качестве отдельного процесса задается составление подкаталога одним студентом–процессом для одного ряда. После этого студент передает информацию процессу– библиотекарю, который сортирует ее учитывая подкаталоги, переданные другими студентами. Сервер формирует каталог, получая информацию от студентов — клиентов. Порождение студентов может быть вручную или с использованием скрипта. Примечание. Каталог — это список книг, упорядоченный по их инвентарному номеру или по алфавиту (на выбор разработчика). Каждая строка каталога содержит идентифицирующее значение (номер или название), номер ряда, номер шкафа, номер книги в шкафу.

Сценарий решаемой задачи:

Клиенты (студенты) запускаются на компьютерах, соответствующих рядам библиотеки.
Каждый клиент (студент) отвечает за составление подкаталога для одного ряда библиотеки. 
Он получает информацию о шкафах и книгах, и составляет подкаталог, упорядочивая его по алфавиту.
Клиент передает информацию процессу-библиотекарю (серверу) по UDP.
Клиент отправляет данные о составленном подкаталоге, включая идентифицирующее значение (номер или название), номер шкафа и номер книги в шкафу.
Сервер получает информацию от клиентов и сортирует ее, учитывая подкаталоги, переданные другими клиентами. 
Он формирует общий каталог, упорядочивая его по инвентарному номеру или по алфавиту.
Взаимодействие между клиентами и сервером происходит через обмен сообщениями по UDP. 
Клиенты отправляют свои подкаталоги серверу, а сервер принимает и сортирует эти данные.

Параметры IP адресов и портов будут задаваться в командной строке при запуске программы. Это позволит гибко настраивать приложение для работы в разных сетях.
Для обеспечения корректного взаимодействия сетевых приложений и процессов, мы можем использовать сокеты для установления соединения между клиентами и сервером, а также функции отправки и приема данных по UDP.
Разработанное приложение работает как на одном компьютере, так и в распределенном (сетевом) режиме на нескольких компьютерах. Клиенты и серверы могут быть разнесены по разным компьютерам, чтобы обеспечить масштабируемость и возможность параллельной обработки данных.
Завершение работы клиентов и серверов на данном этапе не оговаривается, но можно предположить, что они могут завершиться после успешного завершения составления подкаталогов и формирования общего каталога.

gcc server.c -o server

gcc client.c -o client

./server <IP-адрес сервера> <порт сервера> <количество рядов> (Пример: ./server 127.0.0.2 8080 2)

./client <IP-адрес сервера> <порт сервера> <номер ряда> (Пример: ./client 127.0.0.2 8080 1)

Тестирование: 

./client 127.0.0.2 8765 1
Введите информацию о книгах в ряде 1 (для окончания ввода введите END):

Идентификатор, Номер шкафа, Номер книги в шкафу: A, 3, 4

Идентификатор, Номер шкафа, Номер книги в шкафу: L, 2, 1

Идентификатор, Номер шкафа, Номер книги в шкафу: U, 6, 7

Идентификатор, Номер шкафа, Номер книги в шкафу: END


./client 127.0.0.2 8765 3
Введите информацию о книгах в ряде 3 (для окончания ввода введите END):

Идентификатор, Номер шкафа, Номер книги в шкафу: Z, 2, 3

Идентификатор, Номер шкафа, Номер книги в шкафу: L, 1, 3

Идентификатор, Номер шкафа, Номер книги в шкафу: END


./client 127.0.0.2 8765 2
Введите информацию о книгах в ряде 2 (для окончания ввода введите END):

Идентификатор, Номер шкафа, Номер книги в шкафу: F, 2, 6

Идентификатор, Номер шкафа, Номер книги в шкафу: P, 7, 1

Идентификатор, Номер шкафа, Номер книги в шкафу: END


./server 127.0.0.2 8765 3
Сервер запущен и готов принимать данные от клиентов...

Клиент на ряду 1 завершил передачу данных.

Клиент на ряду 2 завершил передачу данных.

Клиент на ряду 3 завершил передачу данных.

Каталог библиотеки:

Название книги: A, Номер ряда: 1, Номер шкафа: 3, Номер книги в шкафу: 4

Название книги: F, Номер ряда: 3, Номер шкафа: 2, Номер книги в шкафу: 6

Название книги: L, Номер ряда: 1, Номер шкафа: 2, Номер книги в шкафу: 1

Название книги: L, Номер ряда: 2, Номер шкафа: 1, Номер книги в шкафу: 3

Название книги: P, Номер ряда: 3, Номер шкафа: 7, Номер книги в шкафу: 1

Название книги: U, Номер ряда: 1, Номер шкафа: 6, Номер книги в шкафу: 7

Название книги: Z, Номер ряда: 2, Номер шкафа: 2, Номер книги в шкафу: 3


