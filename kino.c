#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <locale.h>
#include <math.h>

struct film
{
    char name[100];
    char year[6];
    char country[100];
    char genre[100];
    char rating[5];
};

struct node
{
    struct film film;
    struct node* next;
    struct node* prev;
};

struct list
{
    struct node* head;
    struct node* tail;
};  

struct user
{
    char login[20];
    char pass[20];
    long long card;
    int favSize;
    int isAdmin;
};

// Добавление элемента
void push(struct list* l, struct film film)
{
    struct node* current = (struct node*) malloc(sizeof(struct node));
    current->film = film;
    current->next = l->head;
    current->prev = l->tail;
    l->head->prev = current;
    l->tail->next = current;
    l->head = current;
}

// Удаление элемента
void pop(struct list* l)
{
    struct node* current = l->head->next;
    current->prev = l->tail; 
    free(l->head);
    l->head = current;
}

void popBack(struct list* l)
{
    struct node* current = l->tail->prev;
    current->next = l->head; 
    free(l->tail);
    l->tail = current;
}

// Вывод нескольких одинаковых символов
void printElem(int count, char elem)
{
    for (int i = 0; i < count; i++)
    {
        printf("%c", elem);
    }
}

// Карусель
void printCards(struct list l, int index)
{
    struct node* current = l.head;
    if (index > 0)
    {
        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }
    }
    else
    {
        for (int i = 0; i > index; i--)
        {
            current = current->prev;
        }
    }

    printf("%s   |%s|   %s\n", current->prev->film.name, current->film.name, current->next->film.name);
}

// Функция для вычисления количества цифр в числе
int digits(long long n)
{
    int count = 0;
    while(n > 0)
    {
        n = n / 10;
        count++;
    }
    return count;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    FILE* films = fopen("films.txt", "r");
    struct film f1, f2;
    fgets(f1.name, 100, films);
    f1.name[strcspn(f1.name, "\n")] = '\0';
    fgets(f1.year, 100, films);
    f1.year[strcspn(f1.year, "\n")] = '\0';
    fgets(f1.country, 100, films);
    f1.country[strcspn(f1.country, "\n")] = '\0';
    fgets(f1.genre, 100, films);
    f1.genre[strcspn(f1.genre, "\n")] = '\0';
    fgets(f1.rating, 100, films);
    f1.rating[strcspn(f1.rating, "\n")] = '\0';
    fgets(f2.name, 100, films);
    f2.name[strcspn(f2.name, "\n")] = '\0';
    fgets(f2.year, 100, films);
    f2.year[strcspn(f2.year, "\n")] = '\0';
    fgets(f2.country, 100, films);
    f2.country[strcspn(f2.country, "\n")] = '\0';
    fgets(f2.genre, 100, films);
    f2.genre[strcspn(f2.genre, "\n")] = '\0';
    fgets(f2.rating, 100, films);
    f2.rating[strcspn(f2.rating, "\n")] = '\0';

    struct list library;
    library.head = (struct node*) malloc(sizeof(struct node));
    library.tail = (struct node*) malloc(sizeof(struct node));
    library.tail->next = library.head;
    library.tail->prev = library.head;
    library.head->prev = library.tail;
    library.head->next = library.tail;
    library.head->film = f1;
    library.tail->film = f2;

    
    
    while(fgets(f1.name, 100, films) != NULL)
    {
        f1.name[strcspn(f1.name, "\n")] = '\0';
        fgets(f1.year, 100, films);
        f1.year[strcspn(f1.year, "\n")] = '\0';
        fgets(f1.country, 100, films);
        f1.country[strcspn(f1.country, "\n")] = '\0';
        fgets(f1.genre, 100, films);
        f1.genre[strcspn(f1.genre, "\n")] = '\0';
        fgets(f1.rating, 100, films);
        f1.rating[strcspn(f1.rating, "\n")] = '\0';
        push(&library, f1);
    }
    fclose(films);

    int libraryCurr = 0;
    int libraryFavCurr = 0;
    int currWindow = -1;
    int logReg = 0, addDel = 0;
    char fname[34] = "favourites_";
    struct user newUser;
    struct user currUser;
    struct list libraryFav;
    printf("-> Войти\n   Зарегистрироваться\n");
    while(TRUE)
    {
        // Стартовое окно
        if (currWindow == -1 && GetAsyncKeyState(VK_RETURN) == 0 && GetAsyncKeyState(VK_ESCAPE) == 0)
        {
            if (GetAsyncKeyState(VK_UP) & 1)
            {
                system("cls");
                Sleep(200);
                printf("-> Войти\n   Зарегистрироваться\n");
                logReg = 0;
            }
            if (GetAsyncKeyState(VK_DOWN) & 1)
            {
                system("cls");
                Sleep(200);
                printf("   Войти\n-> Зарегистрироваться\n");
                logReg = 1;
            }
            if (GetAsyncKeyState(VK_RETURN) & 1)
            {
                Sleep(200);
                if (logReg == 0)
                {
                    currWindow = 0;
                }
                else if (logReg == 1)
                {
                    currWindow = 1;
                    logReg = 0;
                }
                while (getchar() != '\n');
                system("cls");
            }
            if (GetAsyncKeyState(VK_ESCAPE) & 1)
            {
                return 0;
            }
        }

        // Окно входа в систему
        if (currWindow == 0)
        {
            char inputLog[20];
            char inputPass[20];
            printf("Логин: ");
            scanf("%s", &inputLog);
            while (getchar() != '\n');
            printf("Пароль: ");
            scanf("%s", &inputPass);
            while (getchar() != '\n');
            FILE* users = fopen("users.txt", "r");
            while(fgets(currUser.login, 100, users) != NULL)
            {
                currUser.login[strcspn(currUser.login, "\n")] = 0;
                fgets(currUser.pass, 100, users);
                currUser.pass[strcspn(currUser.pass, "\n")] = 0;
                if (strcmp(inputLog, currUser.login) == 0 && strcmp(inputPass, currUser.pass) == 0)
                {
                    fscanf(users, "%lld", &currUser.card);
                    fscanf(users, "%d", &currUser.favSize);
                    fscanf(users, "%d", &currUser.isAdmin);
                    currWindow = 2;
                    system("cls");
                    printf("Добро пожаловать, %s ", currUser.login);
                    if (currUser.isAdmin == 1)
                    {
                        printf("(Администратор)");
                    }
                    printf("\n\n");
                    printCards(library, libraryCurr);
                    break;
                }
                fscanf(users, "%lld", &currUser.card);
                fscanf(users, "%d", &currUser.favSize);
                fscanf(users, "%d", &currUser.isAdmin);
                fgets(currUser.login, 100, users);
            }
            fclose(users);
            if (currWindow != 2)
            {
                system("cls");
                printf("Неправильный логин или пароль\n");
            }
            char log[20];
            for (int i = 0; i < strlen(currUser.login); i++)
            {
                log[i] = currUser.login[i];
            }
            strncat(fname, currUser.login, 20);
            strncat(fname, ".txt", 5);
        }

        // Окно регистрации
        if (currWindow == 1 && GetAsyncKeyState(VK_ESCAPE) == 0)
        {
            FILE* users = fopen("users.txt", "aw");
            int isRightInput = 0;
            while (isRightInput == 0)
            {
                printf("Придумайте логин: ");
                scanf("%s", &newUser.login);
                while (getchar() != '\n');
                int isWrongLog = 0;
                for (int i = 0; i < strlen(newUser.login); i++)
                {
                    if ((newUser.login[i] < 48 || newUser.login[i] > 57) && (newUser.login[i] < 65 || newUser.login[i] > 90) && (newUser.login[i] < 97 || newUser.login[i] > 122))
                    {
                        isWrongLog = 1;
                        break;
                    }
                }
                if (strlen(newUser.login) < 3 || strlen(newUser.login) > 20 || isWrongLog == 1)
                {
                    system("cls");
                    printf("Логин должен быть от 3 до 20 символов и состоять только из букв латинского алфавита и цифр\n");
                }
                else
                {
                    isRightInput = 1;
                }
            }
            isRightInput = 0;
            while (isRightInput == 0)
            {
                int isHighReg = 0, isLowReg = 0, isNum = 0, isWrongPass = 0;;
                printf("Придумайте пароль: ");
                scanf("%s", &newUser.pass);
                while (getchar() != '\n');
                for (int i = 0; i < strlen(newUser.pass); i++)
                {
                    if ((newUser.pass[i] < 48 || newUser.pass[i] > 57) && (newUser.pass[i] < 65 || newUser.pass[i] > 90) && (newUser.pass[i] < 97 || newUser.pass[i] > 122))
                    {
                        isWrongPass = 1;
                        break;
                    }
                    if (newUser.pass[i] < 58 && newUser.pass[i] > 47)
                    {
                        isNum += 1;
                    }
                    if (newUser.pass[i] < 91 && newUser.pass[i] > 64)
                    {
                        isHighReg += 1;
                    }
                    if (newUser.pass[i] < 123 && newUser.pass[i] > 96)
                    {
                        isLowReg += 1;
                    }
                    if (isNum > 0 && isLowReg > 0 && isHighReg > 0 && strlen(newUser.pass) >= 6 && strlen(newUser.pass) <= 20 && isWrongPass == 0)
                    {
                        isRightInput = 1;
                    }
                }
                if (isNum == 0 || isLowReg == 0 || isHighReg == 0 || strlen(newUser.pass) < 6 || strlen(newUser.pass) > 20 || isWrongPass == 1)
                {
                    system("cls");
                    printf("Пароль должен содержать от 6 до 20 символов, хотя бы одну цифру и букву верхнего и нижнего регистра латинского алфавита\n");
                }
            }
            isRightInput = 0;
            while(isRightInput == 0)
            {
                printf("Введите номер карты: ");
                scanf("%lld", &newUser.card);
                while (getchar() != '\n');
                if (digits(newUser.card) != 16)
                {
                    system("cls");
                    printf("Номер карты состоит из 16 цифр\n");
                }
                else
                {
                    isRightInput = 1;
                }
            }
            newUser.isAdmin = 0;
            newUser.favSize = 0;
            fprintf(users, "\n%s\n", newUser.login);
            fprintf(users, "%s\n", newUser.pass);
            fprintf(users, "%lld\n", newUser.card);
            fprintf(users, "%d\n", newUser.favSize);
            fprintf(users, "%d", newUser.isAdmin);
            printf("Регистрация прошла успешно\n");
            fclose(users);
            while (GetAsyncKeyState(VK_ESCAPE) == 0)
            {
            }
            system("cls");
            Sleep(200);
            printf("-> Войти\n   Зарегистрироваться\n");
            currWindow = -1;
        }

        // Каталог
        if (currWindow == 2 && GetAsyncKeyState(VK_RETURN) == 0 && GetAsyncKeyState(VK_DOWN) == 0 && GetAsyncKeyState(VK_ESCAPE) == 0)
        {
            if (GetAsyncKeyState(VK_RIGHT) & 1)
            {
                libraryCurr++;
                system("cls");
                Sleep(200);
                printf("Добро пожаловать, %s ", currUser.login);
                if (currUser.isAdmin == 1)
                {
                    printf("(Администратор)");
                }
                printf("\n\n");
                printCards(library, libraryCurr);
            }
            if (GetAsyncKeyState(VK_LEFT) & 1)
            {
                libraryCurr--;
                system("cls");
                Sleep(200);
                printf("Добро пожаловать, %s ", currUser.login);
                if (currUser.isAdmin == 1)
                {
                    printf("(Администратор)");
                }
                printf("\n\n");
                printCards(library, libraryCurr);
            }
            if (GetAsyncKeyState(VK_RETURN) & 1)
            {
                system("cls");
                Sleep(200);
                struct node* current = library.head;
                if (libraryCurr > 0)
                {
                    for (int i = 0; i < libraryCurr; i++)
                    {
                        current = current->next;
                    }
                }
                else
                {
                    for (int i = 0; i > libraryCurr; i--)
                    {
                        current = current->prev;
                    }
                }
                printf("Название %s\n", current->film.name);
                printf("Год %s\n", current->film.year);
                printf("Страна %s\n", current->film.country);
                printf("Жанр %s\n", current->film.genre);
                printf("Рейтинг %s\n", current->film.rating);
                currWindow = 4;
            }
            if (GetAsyncKeyState(VK_ESCAPE) & 1)
            {
                system("cls");
                Sleep(200);
                printf("-> Войти\n   Зарегистрироваться\n");
                currWindow = -1;
                libraryCurr = 0;
            }
            if (currUser.isAdmin == 1 && GetAsyncKeyState(VK_DOWN) & 1)
            {
                system("cls");
                Sleep(200);
                currWindow = 6;
            }
            if (currUser.isAdmin == 1 && GetAsyncKeyState(VK_UP) & 1)
            {
                system("cls");
                Sleep(200);
                currWindow = 3;
                FILE* currUserFav = fopen(fname, "a+");
                libraryFav.head = (struct node*) malloc(sizeof(struct node));
                libraryFav.tail = (struct node*) malloc(sizeof(struct node));
                libraryFav.tail->next = libraryFav.head;
                libraryFav.tail->prev = libraryFav.head;
                libraryFav.head->prev = libraryFav.tail;
                libraryFav.head->next = libraryFav.tail;
                libraryFav.head->film = f1;
                libraryFav.head->film = f2;
                if (currUser.favSize != 0)
                {
                    for (int i = 0; i < currUser.favSize; i++)
                    {
                        fgets(f1.name, 100, currUserFav);
                        f1.name[strcspn(f1.name, "\n")] = '\0';
                        fgets(f1.year, 100, currUserFav);
                        f1.year[strcspn(f1.year, "\n")] = '\0';
                        fgets(f1.country, 100, currUserFav);
                        f1.country[strcspn(f1.country, "\n")] = '\0';
                        fgets(f1.genre, 100, currUserFav);
                        f1.genre[strcspn(f1.genre, "\n")] = '\0';
                        fgets(f1.rating, 100, currUserFav);
                        f1.rating[strcspn(f1.rating, "\n")] = '\0';
                        push(&libraryFav, f1);
                        if (i <= 1)
                        {
                            popBack(&libraryFav);
                        }
                    }
                }
                printf("Избранное, %s ", currUser.login);
                if (currUser.isAdmin == 1)
                {
                    printf("(Администратор)");
                }
                printf("\n\n");
                printCards(libraryFav, libraryFavCurr);
            }
        }

        // Избранное
        if (currWindow == 3)
        {
            if (GetAsyncKeyState(VK_RIGHT) & 1)
            {
                libraryFavCurr++;
                system("cls");
                Sleep(200);
                printf("Избранное, %s ", currUser.login);
                if (currUser.isAdmin == 1)
                {
                    printf("(Администратор)");
                }
                printf("\n\n");
                printCards(libraryFav, libraryFavCurr);
            }
            if (GetAsyncKeyState(VK_LEFT) & 1)
            {
                libraryFavCurr--;
                system("cls");
                Sleep(200);
                printf("Избранное, %s ", currUser.login);
                if (currUser.isAdmin == 1)
                {
                    printf("(Администратор)");
                }
                printf("\n\n");
                printCards(libraryFav, libraryFavCurr);
            }
            if (GetAsyncKeyState(VK_RETURN) & 1)
            {
                system("cls");
                Sleep(200);
                struct node* current = libraryFav.head;
                if (libraryCurr > 0)
                {
                    for (int i = 0; i < libraryFavCurr; i++)
                    {
                        current = current->next;
                    }
                }
                else
                {
                    for (int i = 0; i > libraryFavCurr; i--)
                    {
                        current = current->prev;
                    }
                }
                printf("Название %s\n", current->film.name);
                printf("Год %s\n", current->film.year);
                printf("Страна %s\n", current->film.country);
                printf("Жанр %s\n", current->film.genre);
                printf("Рейтинг %s\n", current->film.rating);
                currWindow = 4;
            }
        }

        // Подробная информация о фильме
        if (currWindow == 4 && GetAsyncKeyState(VK_ESCAPE) == 0)
        {
            if (GetAsyncKeyState(VK_ESCAPE) & 1)
            {
                system("cls");
                Sleep(200);
                printf("Добро пожаловать, %s ", currUser.login);
                if (currUser.isAdmin == 1)
                {
                    printf("(Администратор)");
                }
                printf("\n\n");
                printCards(library, libraryCurr);
                currWindow = 2;
            }
        }

        // Личный кабинет
        if (currWindow == 5)
        {

        }

        // Добавление фильма в каталог
        if (currWindow == 6 && GetAsyncKeyState(VK_ESCAPE) == 0)
        {
            FILE* films = fopen("films.txt", "aw");
            printf("Добавление фильма в каталог\n\n");
            struct film newFilm;
            int isRightInput = 0;
            printf("Название: ");
            fgets(newFilm.name, 100, stdin);
            newFilm.name[strcspn(newFilm.name, "\n")] = '\0';
            printf("Год: ");
            while(isRightInput == 0)
            {   
                fgets(newFilm.year, 100, stdin);
                newFilm.year[strcspn(newFilm.year, "\n")] = '\0';
                int isNum = 1;
                for (int i = 0; i < strlen(newFilm.year); i++)
                {
                    if (newFilm.year[i] < 48 || newFilm.year[i] > 57)
                    {
                        isNum = 0;
                        break;
                    }
                }
                if (isNum == 0)
                {
                    system("cls");
                    printf("Введите число\n");
                }
                else
                {
                    isRightInput = 1;
                }
            }
            isRightInput = 0;
            printf("Страна: ");
            fgets(newFilm.country, 100, stdin);
            newFilm.country[strcspn(newFilm.country, "\n")] = '\0';
            printf("Жанр: ");
            fgets(newFilm.genre, 100, stdin);
            newFilm.genre[strcspn(newFilm.genre, "\n")] = '\0';
            printf("Рейтинг: ");
            while(isRightInput == 0)
            {   
                fgets(newFilm.rating, 100, stdin);
                newFilm.rating[strcspn(newFilm.rating, "\n")] = '\0';
                int isNum = 1;
                for (int i = 0; i < strlen(newFilm.rating); i++)
                {
                    if ((newFilm.rating[i] < 48 || newFilm.rating[i] > 57) && newFilm.rating[i] != '.')
                    {
                        isNum = 0;
                        break;
                    }
                }
                if (isNum == 0)
                {
                    system("cls");
                    printf("Введите число\n");
                }
                else
                {
                    isRightInput = 1;
                }
            }
            fprintf(films, "\n%s", newFilm.name);
            fprintf(films, "\n%s", newFilm.year);
            fprintf(films, "\n%s", newFilm.country);
            fprintf(films, "\n%s", newFilm.genre);
            fprintf(films, "\n%s", newFilm.rating);
            fclose(films);
            push(&library, newFilm);
            printf("Фильм добавлен в каталог\n");
            while (GetAsyncKeyState(VK_ESCAPE) == 0)
            {
            }
            system("cls");
            Sleep(200);
            printf("Добро пожаловать, %s ", currUser.login);
            if (currUser.isAdmin == 1)
            {
                printf("(Администратор)");
            }
            printf("\n\n");
            printCards(library, libraryCurr);
            currWindow = 2;
        }
    }

    system("pause");
}