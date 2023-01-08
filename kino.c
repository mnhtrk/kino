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
    l->tail->next = current; 
    free(l->head);
    l->head = current;
}

void popBack(struct list* l)
{
    struct node* current = l->tail->prev;
    current->next = l->head;
    l->head->prev = current; 
    free(l->tail);
    l->tail = current;
}

void popIndex(struct list* l, int index)
{
    struct node* temp = (struct node*) malloc (sizeof (struct node));
    struct node* temp2 = (struct node*) malloc (sizeof (struct node));
    struct node* current = l->head;
    index -= 1;
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
    temp = current->next->next;
    temp->prev = current;
    free(current->next);
    current->next = temp;
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
    int prevWindow = 0;
    char fname[34];
    struct user newUser;
    struct user currUser;
    struct list libraryFav;
    int isInFav;
    short showPass = 0;
    short showCard = 0;
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
    printf("-> Войти\n   Зарегистрироваться\n");
    while(TRUE)
    {
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
        struct node* currentFav = libraryFav.head;
        if (libraryCurr > 0)
        {
            for (int i = 0; i < libraryFavCurr; i++)
            {
                currentFav = currentFav->next;
            }
        }
        else
        {
            for (int i = 0; i > libraryFavCurr; i--)
            {
                currentFav = currentFav->prev;
            }
        }
        
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
                    char log[20];
                    for (int i = 0; i < strlen(currUser.login); i++)
                    {
                        log[i] = currUser.login[i];
                    }
                    strcpy(fname, "favourites_");
                    strncat(fname, currUser.login, 20);
                    strncat(fname, ".txt", 5);
                    system("cls");
                    printf("Добро пожаловать, %s ", currUser.login);
                    if (currUser.isAdmin == 1)
                    {
                        printf("(Администратор)");
                    }
                    printf("\n\n");
                    printCards(library, libraryCurr);
                    FILE* currUserFav = fopen(fname, "r");
                    char temp[100];
                    isInFav = 0;
                    for (int i = 0; i < currUser.favSize; i++)
                    {
                        fgets(temp, 100, currUserFav);
                        temp[strcspn(temp, "\n")] = 0;
                        if (strcmp(temp, current->film.name) == 0)
                        {
                            printf("\nУдалить из избранного (-)\n");
                            isInFav = 1;
                            break;
                        }
                        fgets(temp, 100, currUserFav);
                        fgets(temp, 100, currUserFav);
                        fgets(temp, 100, currUserFav);
                        fgets(temp, 100, currUserFav);
                    }
                    if (isInFav == 0)
                    {
                        printf("\nДобавить в избранное (+)\n");
                    }
                    if (currUser.isAdmin == 1)
                    {
                        printf("Удалить фильм (DEL)\n");
                        printf("Добавить фильм (LSHIFT)\n");
                    }
                    printf("Список избранного (SPACE)\n");
                    printf("Личный кабинет (TAB)");
                    fclose(currUserFav);
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
        }

        // Окно регистрации
        if (currWindow == 1 && GetAsyncKeyState(VK_ESCAPE) == 0)
        {
            FILE* users = fopen("users.txt", "aw");
            int isRightInput = 0;
            while (isRightInput == 0)
            {
                FILE* usersRead = fopen("users.txt", "r");
                printf("Придумайте логин: ");
                scanf("%s", &newUser.login);
                while (getchar() != '\n');
                int isWrongLog = 0;
                int isExistLog = 0;
                struct user temp;
                while(fgets(temp.login, 100, usersRead) != NULL)
                {
                    temp.login[strcspn(temp.login, "\n")] = '\0';
                    if (strcmp(newUser.login, temp.login) == 0)
                    {
                        fgets(temp.pass, 100, usersRead);
                        temp.pass[strcspn(temp.pass, "\n")] = '\0';
                        fscanf(usersRead, "%lld", &temp.card);
                        fscanf(usersRead, "%d", &temp.favSize);
                        fscanf(usersRead, "%d", &temp.isAdmin);
                        isExistLog = 1;
                        break;
                    }
                    fgets(temp.pass, 100, usersRead);
                    temp.pass[strcspn(temp.pass, "\n")] = '\0';
                    fscanf(usersRead, "%lld", &temp.card);
                    fscanf(usersRead, "%d", &temp.favSize);
                    fscanf(usersRead, "%d", &temp.isAdmin);
                    char tempSymb[2];
                    fgets(tempSymb, 100, usersRead);
                }
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
                else if (isExistLog == 1)
                {
                    system("cls");
                    printf("Логин уже существует\n");
                }
                else
                {
                    isRightInput = 1;
                }
                fclose(usersRead);
            }
            isRightInput = 0;
            while (isRightInput == 0)
            {
                int isHighReg = 0, isLowReg = 0, isNum = 0, isWrongPass = 0;
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
        if (currWindow == 2 && GetAsyncKeyState(VK_RETURN) == 0 && GetAsyncKeyState(VK_LSHIFT) == 0 && GetAsyncKeyState(VK_ESCAPE) == 0 && GetAsyncKeyState(VK_SPACE) == 0 && GetAsyncKeyState(VK_OEM_PLUS) == 0 && GetAsyncKeyState(VK_OEM_MINUS) == 0 && GetAsyncKeyState(VK_DELETE) == 0)
        {
            if (GetAsyncKeyState(VK_RIGHT) & 1)
            {
                libraryCurr++;
                current = current->next;
                system("cls");
                Sleep(200);
                printf("Добро пожаловать, %s ", currUser.login);
                if (currUser.isAdmin == 1)
                {
                    printf("(Администратор)");
                }
                printf("\n\n");
                printCards(library, libraryCurr);
                FILE* currUserFav = fopen(fname, "r");
                char temp[100];
                isInFav = 0;
                for (int i = 0; i < currUser.favSize; i++)
                {
                    fgets(temp, 100, currUserFav);
                    temp[strcspn(temp, "\n")] = 0;
                    if (strcmp(temp, current->film.name) == 0)
                    {
                        printf("\nУдалить из избранного (-)\n");
                        isInFav = 1;
                        break;
                    }
                    fgets(temp, 100, currUserFav);
                    fgets(temp, 100, currUserFav);
                    fgets(temp, 100, currUserFav);
                    fgets(temp, 100, currUserFav);
                }
                if (isInFav == 0)
                {
                    printf("\nДобавить в избранное (+)\n");
                }
                if (currUser.isAdmin == 1)
                {
                    printf("Удалить фильм (DEL)\n");
                    printf("Добавить фильм (LSHIFT)\n");
                }
                printf("Список избранного (SPACE)\n");
                printf("Личный кабинет (TAB)");
                current = current->prev;
            }
            if (GetAsyncKeyState(VK_LEFT) & 1)
            {
                libraryCurr--;
                current = current->prev;
                system("cls");
                Sleep(200);
                printf("Добро пожаловать, %s ", currUser.login);
                if (currUser.isAdmin == 1)
                {
                    printf("(Администратор)");
                }
                printf("\n\n");
                printCards(library, libraryCurr);
                FILE* currUserFav = fopen(fname, "r");
                char temp[100];
                isInFav = 0;
                for (int i = 0; i < currUser.favSize; i++)
                {
                    fgets(temp, 100, currUserFav);
                    temp[strcspn(temp, "\n")] = 0;
                    if (strcmp(temp, current->film.name) == 0)
                    {
                        printf("\nУдалить из избранного (-)\n");
                        isInFav = 1;
                        break;
                    }
                    fgets(temp, 100, currUserFav);
                    fgets(temp, 100, currUserFav);
                    fgets(temp, 100, currUserFav);
                    fgets(temp, 100, currUserFav);
                }
                if (isInFav == 0)
                {
                    printf("\nДобавить в избранное (+)\n");
                }
                if (currUser.isAdmin == 1)
                {
                    printf("Удалить фильм (DEL)\n");
                    printf("Добавить фильм (LSHIFT)\n");
                }
                printf("Список избранного (SPACE)\n");
                printf("Личный кабинет (TAB)");
                current = current->next;
            }
            if (GetAsyncKeyState(VK_RETURN) & 1)
            {
                system("cls");
                Sleep(200);
                printf("Название %s\n", current->film.name);
                printf("Год %s\n", current->film.year);
                printf("Страна %s\n", current->film.country);
                printf("Жанр %s\n", current->film.genre);
                printf("Рейтинг %s\n", current->film.rating);
                FILE* currUserFav = fopen(fname, "r");
                char temp[100];
                isInFav = 0;
                for (int i = 0; i < currUser.favSize; i++)
                {
                    fgets(temp, 100, currUserFav);
                    temp[strcspn(temp, "\n")] = 0;
                    if (strcmp(temp, current->film.name) == 0)
                    {
                        printf("\nУдалить из избранного (+)\n");
                        isInFav = 1;
                        break;
                    }
                    fgets(temp, 100, currUserFav);
                    fgets(temp, 100, currUserFav);
                    fgets(temp, 100, currUserFav);
                    fgets(temp, 100, currUserFav);
                }
                if (isInFav == 0)
                {
                    printf("\nДобавить в избранное (+)\n");
                }
                if (currUser.isAdmin == 1)
                {
                    printf("Удалить фильм (DEL)");
                }
                fclose(currUserFav);
                currWindow = 4;
                prevWindow = 0;
            }
            if (GetAsyncKeyState(VK_ESCAPE) & 1)
            {
                system("cls");
                Sleep(200);
                printf("-> Войти\n   Зарегистрироваться\n");
                currWindow = -1;
                libraryCurr = 0;
            }
            if (currUser.isAdmin == 1 && GetAsyncKeyState(VK_LSHIFT) & 1)
            {
                system("cls");
                Sleep(200);
                currWindow = 6;
            }
            if (GetAsyncKeyState(VK_SPACE) & 1 && currUser.favSize != 0)
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
                    }
                }
                popBack(&libraryFav);
                popBack(&libraryFav);
                printf("Избранное, %s ", currUser.login);
                if (currUser.isAdmin == 1)
                {
                    printf("(Администратор)");
                }
                printf("\n\n");
                printCards(libraryFav, libraryFavCurr);
                printf("\nУдалить из избранного (-)\n");
                if (currUser.isAdmin == 1)
                {
                    printf("Удалить фильм (DEL)\n");
                }
            }
            // Добавление в избранное
            if (GetAsyncKeyState(VK_OEM_PLUS) & 1 && isInFav == 0)
            {
                FILE* currUserFav = fopen(fname, "aw");
                if (currUser.favSize != 0)
                {
                    fprintf(currUserFav, "\n");
                }
                fprintf(currUserFav, "%s", current->film.name);
                fprintf(currUserFav, "\n%s", current->film.year);
                fprintf(currUserFav, "\n%s", current->film.country);
                fprintf(currUserFav, "\n%s", current->film.genre);
                fprintf(currUserFav, "\n%s", current->film.rating);
                currUser.favSize += 1;
                fclose(currUserFav);
                system("cls");
                Sleep(200);
                printf("Добро пожаловать, %s ", currUser.login);
                if (currUser.isAdmin == 1)
                {
                    printf("(Администратор)");
                }
                printf("\n\n");
                printCards(library, libraryCurr);
                printf("\nУдалить из избранного (-)\n");
                if (currUser.isAdmin == 1)
                {
                    printf("Удалить фильм (DEL)\n");
                    printf("Добавить фильм (LSHIFT)\n");
                }
                printf("Список избранного (SPACE)\n");
                printf("Личный кабинет (TAB)");
                isInFav = 1;

                FILE* users = fopen("users.txt", "r");
                FILE* ftemp = fopen("ftemp.txt", "w");
                struct user temp;
                int size = 0;
                while(fgets(temp.login, 100, users) != NULL)
                {
                    temp.login[strcspn(temp.login, "\n")] = '\0';
                    fgets(temp.pass, 100, users);
                    fscanf(users, "%lld", &temp.card);
                    fscanf(users, "%d", &temp.favSize);
                    fscanf(users, "%d", &temp.isAdmin);
                    char tempSymb[2];
                    fgets(tempSymb, 100, users);
                    size += 1;
                    fprintf(ftemp, "%s\n", temp.login);
                    fprintf(ftemp, "%s", temp.pass);
                    fprintf(ftemp, "%lld\n", temp.card);
                    if (strcmp(temp.login, currUser.login) != 0)
                    {
                        fprintf(ftemp, "%d\n", temp.favSize);
                    }
                    else
                    {
                        fprintf(ftemp, "%d\n", temp.favSize + 1);
                    }
                    fprintf(ftemp, "%d\n", temp.isAdmin);
                }
                fclose(users);
                fclose(ftemp);
                FILE* usersNew = fopen("users.txt", "w");
                FILE* ftempRead = fopen("ftemp.txt", "r");
                for (int i = 0; i < size; i++)
                {
                    struct user temp;
                    fgets(temp.login, 100, ftempRead);
                    fgets(temp.pass, 100, ftempRead);
                    fscanf(ftempRead, "%lld", &temp.card);
                    fscanf(ftempRead, "%d", &temp.favSize);
                    fscanf(ftempRead, "%d", &temp.isAdmin);
                    char tempSymb[2];
                    fgets(tempSymb, 100, ftempRead);
                    if (i > 0)
                    {
                        fprintf(usersNew, "\n");
                    }
                    fprintf(usersNew, "%s", temp.login);
                    fprintf(usersNew, "%s", temp.pass);
                    fprintf(usersNew, "%lld\n", temp.card);
                    fprintf(usersNew, "%d\n", temp.favSize);
                    fprintf(usersNew, "%d", temp.isAdmin);
                }
                fclose(usersNew);
                fclose(ftempRead);
            }
            // Удаление из избранного
            if (GetAsyncKeyState(VK_OEM_MINUS) & 1 && isInFav == 1)
            {
                FILE* currUserFav = fopen(fname, "r");
                FILE* ftemp = fopen("ftemp.txt", "w");
                for (int i = 0; i < currUser.favSize; i++)
                {
                    struct film temp;
                    fgets(temp.name, 100, currUserFav);
                    fgets(temp.year, 100, currUserFav);
                    fgets(temp.country, 100, currUserFav);
                    fgets(temp.genre, 100, currUserFav);
                    fgets(temp.rating, 100, currUserFav);
                    temp.name[strcspn(temp.name, "\n")] = '\0';
                    if (strcmp(temp.name, current->film.name) != 0)
                    {
                        fprintf(ftemp, "%s\n", temp.name);
                        fprintf(ftemp, "%s", temp.year);
                        fprintf(ftemp, "%s", temp.country);
                        fprintf(ftemp, "%s", temp.genre);
                        fprintf(ftemp, "%s", temp.rating);
                    }
                }
                fclose(currUserFav);
                fclose(ftemp);
                currUser.favSize -= 1;
                FILE* currUserFavNew = fopen(fname, "w");
                FILE* ftempRead = fopen("ftemp.txt", "r");
                for (int i = 0; i < currUser.favSize; i++)
                {
                    struct film temp;
                    fgets(temp.name, 100, ftempRead);
                    fgets(temp.year, 100, ftempRead);
                    fgets(temp.country, 100, ftempRead);
                    fgets(temp.genre, 100, ftempRead);
                    fgets(temp.rating, 100, ftempRead);
                    temp.rating[strcspn(temp.rating, "\n")] = '\0';
                    if (i > 0)
                    {
                        fprintf(currUserFavNew, "\n");
                    }
                    fprintf(currUserFavNew, "%s", temp.name);
                    fprintf(currUserFavNew, "%s", temp.year);
                    fprintf(currUserFavNew, "%s", temp.country);
                    fprintf(currUserFavNew, "%s", temp.genre);
                    fprintf(currUserFavNew, "%s", temp.rating);
                }
                fclose(ftempRead);
                fclose(currUserFavNew);
                system("cls");
                Sleep(200);
                printf("Добро пожаловать, %s ", currUser.login);
                if (currUser.isAdmin == 1)
                {
                    printf("(Администратор)");
                }
                printf("\n\n");
                printCards(library, libraryCurr);
                printf("\nДобавить в избранное (+)\n");
                if (currUser.isAdmin == 1)
                {
                    printf("Удалить фильм (DEL)\n");
                    printf("Добавить фильм (LSHIFT)\n");
                }
                printf("Список избранного (SPACE)\n");
                printf("Личный кабинет (TAB)");
                isInFav = 0;

                FILE* users = fopen("users.txt", "r");
                FILE* ftemp2 = fopen("ftemp.txt", "w");
                struct user temp;
                int size = 0;
                while(fgets(temp.login, 100, users) != NULL)
                {
                    temp.login[strcspn(temp.login, "\n")] = '\0';
                    fgets(temp.pass, 100, users);
                    fscanf(users, "%lld", &temp.card);
                    fscanf(users, "%d", &temp.favSize);
                    fscanf(users, "%d", &temp.isAdmin);
                    char tempSymb[2];
                    fgets(tempSymb, 100, users);
                    size += 1;
                    fprintf(ftemp2, "%s\n", temp.login);
                    fprintf(ftemp2, "%s", temp.pass);
                    fprintf(ftemp2, "%lld\n", temp.card);
                    if (strcmp(temp.login, currUser.login) != 0)
                    {
                        fprintf(ftemp2, "%d\n", temp.favSize);
                    }
                    else
                    {
                        fprintf(ftemp2, "%d\n", temp.favSize - 1);
                    }
                    fprintf(ftemp2, "%d\n", temp.isAdmin);
                }
                fclose(users);
                fclose(ftemp2);
                FILE* usersNew = fopen("users.txt", "w");
                FILE* ftempRead2 = fopen("ftemp.txt", "r");
                for (int i = 0; i < size; i++)
                {
                    struct user temp;
                    fgets(temp.login, 100, ftempRead2);
                    fgets(temp.pass, 100, ftempRead2);
                    fscanf(ftempRead2, "%lld", &temp.card);
                    fscanf(ftempRead2, "%d", &temp.favSize);
                    fscanf(ftempRead2, "%d", &temp.isAdmin);
                    char tempSymb[2];
                    fgets(tempSymb, 100, ftempRead2);
                    if (i > 0)
                    {
                        fprintf(usersNew, "\n");
                    }
                    fprintf(usersNew, "%s", temp.login);
                    fprintf(usersNew, "%s", temp.pass);
                    fprintf(usersNew, "%lld\n", temp.card);
                    fprintf(usersNew, "%d\n", temp.favSize);
                    fprintf(usersNew, "%d", temp.isAdmin);
                }
                fclose(usersNew);
                fclose(ftempRead2);
            }
            if (GetAsyncKeyState(VK_TAB) & 1)
            {
                system("cls");
                Sleep(200);
                currWindow = 5;
            }
            if (GetAsyncKeyState(VK_DELETE) & 1 && currUser.isAdmin == 1)
            {
                FILE* films = fopen("films.txt", "r");
                FILE* ftemp = fopen("ftemp.txt", "w");
                struct film temp;
                int size = 0;
                while(fgets(temp.name, 100, films) != NULL)
                {
                    fgets(temp.year, 100, films);
                    fgets(temp.country, 100, films);
                    fgets(temp.genre, 100, films);
                    fgets(temp.rating, 100, films);
                    temp.name[strcspn(temp.name, "\n")] = '\0';
                    if (strcmp(temp.name, current->film.name) != 0)
                    {
                        fprintf(ftemp, "%s\n", temp.name);
                        fprintf(ftemp, "%s", temp.year);
                        fprintf(ftemp, "%s", temp.country);
                        fprintf(ftemp, "%s", temp.genre);
                        fprintf(ftemp, "%s", temp.rating);
                        size += 1;
                    }
                }
                fclose(films);
                fclose(ftemp);

                FILE* filmsNew = fopen("films.txt", "w");
                FILE* ftempRead = fopen("ftemp.txt", "r");
                for (int i = 0; i < size; i++)
                {
                    struct film temp;
                    fgets(temp.name, 100, ftempRead);
                    fgets(temp.year, 100, ftempRead);
                    fgets(temp.country, 100, ftempRead);
                    fgets(temp.genre, 100, ftempRead);
                    fgets(temp.rating, 100, ftempRead);
                    temp.rating[strcspn(temp.rating, "\n")] = '\0';
                    if (i > 0)
                    {
                        fprintf(filmsNew, "\n");
                    }
                    fprintf(filmsNew, "%s", temp.name);
                    fprintf(filmsNew, "%s", temp.year);
                    fprintf(filmsNew, "%s", temp.country);
                    fprintf(filmsNew, "%s", temp.genre);
                    fprintf(filmsNew, "%s", temp.rating);
                }
                fclose(ftempRead);
                fclose(filmsNew);

                FILE* users = fopen("users.txt", "r");
                FILE* ftemp2 = fopen("ftemp.txt", "w");
                int userSize = 0;
                struct user tempUser;
                while(fgets(tempUser.login, 100, users) != NULL)
                {
                    tempUser.login[strcspn(tempUser.login, "\n")] = '\0';
                    fgets(tempUser.pass, 100, users);
                    fscanf(users, "%lld", &tempUser.card);
                    fscanf(users, "%d", &tempUser.favSize);
                    fscanf(users, "%d", &tempUser.isAdmin);
                    char tempSymb[2];
                    fgets(tempSymb, 100, users);
                    userSize += 1;
                    
                    strcpy(fname, "favourites_");
                    strncat(fname, tempUser.login, 20);
                    strncat(fname, ".txt", 5);

                    FILE* currUserFav = fopen(fname, "r");
                    FILE* ftemp3 = fopen("ftemp2.txt", "w");
                    int tempSize = 0;
                    for (int i = 0; i < tempUser.favSize; i++)
                    {
                        struct film temp;
                        fgets(temp.name, 100, currUserFav);
                        fgets(temp.year, 100, currUserFav);
                        fgets(temp.country, 100, currUserFav);
                        fgets(temp.genre, 100, currUserFav);
                        fgets(temp.rating, 100, currUserFav);
                        temp.name[strcspn(temp.name, "\n")] = '\0';
                        if (strcmp(temp.name, current->film.name) != 0)
                        {
                            fprintf(ftemp3, "%s\n", temp.name);
                            fprintf(ftemp3, "%s", temp.year);
                            fprintf(ftemp3, "%s", temp.country);
                            fprintf(ftemp3, "%s", temp.genre);
                            fprintf(ftemp3, "%s", temp.rating);
                            tempSize += 1;
                        }
                    }
                    fclose(currUserFav);
                    fclose(ftemp3);

                    FILE* currUserFavNew = fopen(fname, "w");
                    FILE* ftempRead2 = fopen("ftemp2.txt", "r");
                    for (int i = 0; i < tempSize; i++)
                    {
                        struct film temp;
                        fgets(temp.name, 100, ftempRead2);
                        fgets(temp.year, 100, ftempRead2);
                        fgets(temp.country, 100, ftempRead2);
                        fgets(temp.genre, 100, ftempRead2);
                        fgets(temp.rating, 100, ftempRead2);
                        temp.rating[strcspn(temp.rating, "\n")] = '\0';
                        if (i > 0)
                        {
                            fprintf(currUserFavNew, "\n");
                        }
                        fprintf(currUserFavNew, "%s", temp.name);
                        fprintf(currUserFavNew, "%s", temp.year);
                        fprintf(currUserFavNew, "%s", temp.country);
                        fprintf(currUserFavNew, "%s", temp.genre);
                        fprintf(currUserFavNew, "%s", temp.rating);
                    }
                    fclose(ftempRead2);
                    fclose(currUserFavNew);

                    fprintf(ftemp2, "%s\n", tempUser.login);
                    fprintf(ftemp2, "%s", tempUser.pass);
                    fprintf(ftemp2, "%lld\n", tempUser.card);
                    if (tempSize != tempUser.favSize)
                    {
                        fprintf(ftemp2, "%d\n", tempUser.favSize - 1);
                    }
                    else
                    {
                        fprintf(ftemp2, "%d\n", tempUser.favSize);
                    }
                    fprintf(ftemp2, "%d\n", tempUser.isAdmin);
                }
                fclose(users);
                fclose(ftemp2);

                strcpy(fname, "favourites_");
                strncat(fname, currUser.login, 20);
                strncat(fname, ".txt", 5);

                FILE* usersNew = fopen("users.txt", "w");
                FILE* ftempRead2 = fopen("ftemp.txt", "r");
                for (int i = 0; i < userSize; i++)
                {
                    struct user temp;
                    fgets(temp.login, 100, ftempRead2);
                    fgets(temp.pass, 100, ftempRead2);
                    fscanf(ftempRead2, "%lld", &temp.card);
                    fscanf(ftempRead2, "%d", &temp.favSize);
                    fscanf(ftempRead2, "%d", &temp.isAdmin);
                    char tempSymb[2];
                    fgets(tempSymb, 100, ftempRead2);
                    if (i > 0)
                    {
                        fprintf(usersNew, "\n");
                    }
                    fprintf(usersNew, "%s", temp.login);
                    fprintf(usersNew, "%s", temp.pass);
                    fprintf(usersNew, "%lld\n", temp.card);
                    fprintf(usersNew, "%d\n", temp.favSize);
                    fprintf(usersNew, "%d", temp.isAdmin);
                }
                fclose(usersNew);
                fclose(ftempRead2);

                if (libraryCurr == 0)
                {
                    pop(&library);
                }
                else
                {
                    popIndex(&library, libraryCurr);
                }
                currUser.favSize -= 1;

                system("cls");
                Sleep(200);
                printf("Добро пожаловать, %s ", currUser.login);
                if (currUser.isAdmin == 1)
                {
                    printf("(Администратор)");
                }
                printf("\n\n");
                printCards(library, libraryCurr);
                printf("\nДобавить в избранное (+)\n");
                if (currUser.isAdmin == 1)
                {
                    printf("Удалить фильм (DEL)\n");
                    printf("Добавить фильм (LSHIFT)\n");
                }
                printf("Список избранного (SPACE)\n");
                printf("Личный кабинет (TAB)");
            }
        }

        // Избранное
        if (currWindow == 3 && GetAsyncKeyState(VK_RETURN) == 0 && GetAsyncKeyState(VK_ESCAPE) == 0 && GetAsyncKeyState(VK_OEM_PLUS) == 0 && GetAsyncKeyState(VK_OEM_MINUS) == 0 && GetAsyncKeyState(VK_DELETE) == 0)
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
                printf("\nУдалить из избранного (-)\n");
                if (currUser.isAdmin == 1)
                {
                    printf("Удалить фильм (DEL)\n");
                }
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
                printf("\nУдалить из избранного (-)\n");
                if (currUser.isAdmin == 1)
                {
                    printf("Удалить фильм (DEL)\n");
                }
            }
            if (GetAsyncKeyState(VK_RETURN) & 1)
            {
                system("cls");
                Sleep(200);
                printf("Название %s\n", currentFav->film.name);
                printf("Год %s\n", currentFav->film.year);
                printf("Страна %s\n", currentFav->film.country);
                printf("Жанр %s\n", currentFav->film.genre);
                printf("Рейтинг %s\n", currentFav->film.rating);
                printf("\nУдалить из избранного (-)\n");
                if (currUser.isAdmin == 1)
                {
                    printf("Удалить фильм (DEL)");
                }
                isInFav = 1;
                prevWindow = 1;
                currWindow = 4;
            }
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
                FILE* currUserFav = fopen(fname, "r");
                char temp[100];
                isInFav = 0;
                for (int i = 0; i < currUser.favSize; i++)
                {
                    fgets(temp, 100, currUserFav);
                    temp[strcspn(temp, "\n")] = 0;
                    if (strcmp(temp, currentFav->film.name) == 0)
                    {
                        printf("\nУдалить из избранного (-)\n");
                        isInFav = 1;
                        break;
                    }
                    fgets(temp, 100, currUserFav);
                    fgets(temp, 100, currUserFav);
                    fgets(temp, 100, currUserFav);
                    fgets(temp, 100, currUserFav);
                }
                if (isInFav == 0)
                {
                    printf("\nДобавить в избранное (+)\n");
                }
                if (currUser.isAdmin == 1)
                {
                    printf("Удалить фильм (DEL)\n");
                    printf("Добавить фильм (LSHIFT)\n");
                }
                printf("Список избранного (SPACE)\n");
                printf("Личный кабинет (TAB)");
                fclose(currUserFav);
                currWindow = 2;
            }
            if (GetAsyncKeyState(VK_OEM_MINUS) & 1)
            {
                FILE* currUserFav = fopen(fname, "r");
                FILE* ftemp = fopen("ftemp.txt", "w");
                for (int i = 0; i < currUser.favSize; i++)
                {
                    struct film temp;
                    fgets(temp.name, 100, currUserFav);
                    fgets(temp.year, 100, currUserFav);
                    fgets(temp.country, 100, currUserFav);
                    fgets(temp.genre, 100, currUserFav);
                    fgets(temp.rating, 100, currUserFav);
                    temp.name[strcspn(temp.name, "\n")] = '\0';
                    if (strcmp(temp.name, currentFav->film.name) != 0)
                    {
                        fprintf(ftemp, "%s\n", temp.name);
                        fprintf(ftemp, "%s", temp.year);
                        fprintf(ftemp, "%s", temp.country);
                        fprintf(ftemp, "%s", temp.genre);
                        fprintf(ftemp, "%s", temp.rating);
                    }
                }
                fclose(currUserFav);
                fclose(ftemp);

                int tempSize = currUser.favSize - 1;
                FILE* currUserFavNew = fopen(fname, "w");
                FILE* ftempRead = fopen("ftemp.txt", "r");
                for (int i = 0; i < tempSize; i++)
                {
                    struct film temp;
                    fgets(temp.name, 100, ftempRead);
                    fgets(temp.year, 100, ftempRead);
                    fgets(temp.country, 100, ftempRead);
                    fgets(temp.genre, 100, ftempRead);
                    fgets(temp.rating, 100, ftempRead);
                    temp.rating[strcspn(temp.rating, "\n")] = '\0';
                    if (i > 0)
                    {
                        fprintf(currUserFavNew, "\n");
                    }
                    fprintf(currUserFavNew, "%s", temp.name);
                    fprintf(currUserFavNew, "%s", temp.year);
                    fprintf(currUserFavNew, "%s", temp.country);
                    fprintf(currUserFavNew, "%s", temp.genre);
                    fprintf(currUserFavNew, "%s", temp.rating);
                }
                fclose(ftempRead);
                fclose(currUserFavNew);
                FILE* users = fopen("users.txt", "r");
                FILE* ftemp2 = fopen("ftemp.txt", "w");
                struct user temp;
                int size = 0;
                while(fgets(temp.login, 100, users) != NULL)
                {
                    temp.login[strcspn(temp.login, "\n")] = '\0';
                    fgets(temp.pass, 100, users);
                    fscanf(users, "%lld", &temp.card);
                    fscanf(users, "%d", &temp.favSize);
                    fscanf(users, "%d", &temp.isAdmin);
                    char tempSymb[2];
                    fgets(tempSymb, 100, users);
                    size += 1;
                    fprintf(ftemp2, "%s\n", temp.login);
                    fprintf(ftemp2, "%s", temp.pass);
                    fprintf(ftemp2, "%lld\n", temp.card);
                    if (strcmp(temp.login, currUser.login) != 0)
                    {
                        fprintf(ftemp2, "%d\n", temp.favSize);
                    }
                    else
                    {
                        fprintf(ftemp2, "%d\n", temp.favSize - 1);
                    }
                    fprintf(ftemp2, "%d\n", temp.isAdmin);
                }
                fclose(users);
                fclose(ftemp2);
                FILE* usersNew = fopen("users.txt", "w");
                FILE* ftempRead2 = fopen("ftemp.txt", "r");
                for (int i = 0; i < size; i++)
                {
                    struct user temp;
                    fgets(temp.login, 100, ftempRead2);
                    fgets(temp.pass, 100, ftempRead2);
                    fscanf(ftempRead2, "%lld", &temp.card);
                    fscanf(ftempRead2, "%d", &temp.favSize);
                    fscanf(ftempRead2, "%d", &temp.isAdmin);
                    char tempSymb[2];
                    fgets(tempSymb, 100, ftempRead2);
                    if (i > 0)
                    {
                        fprintf(usersNew, "\n");
                    }
                    fprintf(usersNew, "%s", temp.login);
                    fprintf(usersNew, "%s", temp.pass);
                    fprintf(usersNew, "%lld\n", temp.card);
                    fprintf(usersNew, "%d\n", temp.favSize);
                    fprintf(usersNew, "%d", temp.isAdmin);
                }
                fclose(usersNew);
                fclose(ftempRead2);
                if (libraryFavCurr == 0)
                {
                    pop(&libraryFav);
                }
                else
                {
                    popIndex(&libraryFav, libraryFavCurr);
                }
                currUser.favSize -= 1;
                
                if (currUser.favSize == 0)
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
                    printf("\nДобавить в избранное (+)\n");
                    if (currUser.isAdmin == 1)
                    {
                        printf("Удалить фильм (DEL)\n");
                        printf("Добавить фильм (LSHIFT)\n");
                    }
                    printf("Список избранного (SPACE)\n");
                    printf("Личный кабинет (TAB)");
                    currWindow = 2;
                }
                else
                {
                    system("cls");
                    Sleep(200);
                    printf("Избранное, %s ", currUser.login);
                    if (currUser.isAdmin == 1)
                    {
                        printf("(Администратор)");
                    }
                    printf("\n\n");
                    printCards(libraryFav, libraryFavCurr);
                    printf("\nУдалить из избранного (-)\n");
                    if (currUser.isAdmin == 1)
                    {
                        printf("Удалить фильм (DEL)");
                    }
                }
            }
            if (GetAsyncKeyState(VK_DELETE) & 1 && currUser.isAdmin == 1)
            {
                FILE* films = fopen("films.txt", "r");
                FILE* ftemp = fopen("ftemp.txt", "w");
                struct film temp;
                int size = 0;
                while(fgets(temp.name, 100, films) != NULL)
                {
                    fgets(temp.year, 100, films);
                    fgets(temp.country, 100, films);
                    fgets(temp.genre, 100, films);
                    fgets(temp.rating, 100, films);
                    temp.name[strcspn(temp.name, "\n")] = '\0';
                    if (strcmp(temp.name, currentFav->film.name) != 0)
                    {
                        fprintf(ftemp, "%s\n", temp.name);
                        fprintf(ftemp, "%s", temp.year);
                        fprintf(ftemp, "%s", temp.country);
                        fprintf(ftemp, "%s", temp.genre);
                        fprintf(ftemp, "%s", temp.rating);
                        size += 1;
                    }
                }
                fclose(films);
                fclose(ftemp);

                FILE* filmsNew = fopen("films.txt", "w");
                FILE* ftempRead = fopen("ftemp.txt", "r");
                for (int i = 0; i < size; i++)
                {
                    struct film temp;
                    fgets(temp.name, 100, ftempRead);
                    fgets(temp.year, 100, ftempRead);
                    fgets(temp.country, 100, ftempRead);
                    fgets(temp.genre, 100, ftempRead);
                    fgets(temp.rating, 100, ftempRead);
                    temp.rating[strcspn(temp.rating, "\n")] = '\0';
                    if (i > 0)
                    {
                        fprintf(filmsNew, "\n");
                    }
                    fprintf(filmsNew, "%s", temp.name);
                    fprintf(filmsNew, "%s", temp.year);
                    fprintf(filmsNew, "%s", temp.country);
                    fprintf(filmsNew, "%s", temp.genre);
                    fprintf(filmsNew, "%s", temp.rating);
                }
                fclose(ftempRead);
                fclose(filmsNew);

                FILE* users = fopen("users.txt", "r");
                FILE* ftemp2 = fopen("ftemp.txt", "w");
                int userSize = 0;
                struct user tempUser;
                while(fgets(tempUser.login, 100, users) != NULL)
                {
                    tempUser.login[strcspn(tempUser.login, "\n")] = '\0';
                    fgets(tempUser.pass, 100, users);
                    fscanf(users, "%lld", &tempUser.card);
                    fscanf(users, "%d", &tempUser.favSize);
                    fscanf(users, "%d", &tempUser.isAdmin);
                    char tempSymb[2];
                    fgets(tempSymb, 100, users);
                    userSize += 1;
                    
                    strcpy(fname, "favourites_");
                    strncat(fname, tempUser.login, 20);
                    strncat(fname, ".txt", 5);

                    FILE* currUserFav = fopen(fname, "r");
                    FILE* ftemp3 = fopen("ftemp2.txt", "w");
                    int tempSize = 0;
                    for (int i = 0; i < tempUser.favSize; i++)
                    {
                        struct film temp;
                        fgets(temp.name, 100, currUserFav);
                        fgets(temp.year, 100, currUserFav);
                        fgets(temp.country, 100, currUserFav);
                        fgets(temp.genre, 100, currUserFav);
                        fgets(temp.rating, 100, currUserFav);
                        temp.name[strcspn(temp.name, "\n")] = '\0';
                        if (strcmp(temp.name, currentFav->film.name) != 0)
                        {
                            fprintf(ftemp3, "%s\n", temp.name);
                            fprintf(ftemp3, "%s", temp.year);
                            fprintf(ftemp3, "%s", temp.country);
                            fprintf(ftemp3, "%s", temp.genre);
                            fprintf(ftemp3, "%s", temp.rating);
                            tempSize += 1;
                        }
                    }
                    fclose(currUserFav);
                    fclose(ftemp3);

                    FILE* currUserFavNew = fopen(fname, "w");
                    FILE* ftempRead2 = fopen("ftemp2.txt", "r");
                    for (int i = 0; i < tempSize; i++)
                    {
                        struct film temp;
                        fgets(temp.name, 100, ftempRead2);
                        fgets(temp.year, 100, ftempRead2);
                        fgets(temp.country, 100, ftempRead2);
                        fgets(temp.genre, 100, ftempRead2);
                        fgets(temp.rating, 100, ftempRead2);
                        temp.rating[strcspn(temp.rating, "\n")] = '\0';
                        if (i > 0)
                        {
                            fprintf(currUserFavNew, "\n");
                        }
                        fprintf(currUserFavNew, "%s", temp.name);
                        fprintf(currUserFavNew, "%s", temp.year);
                        fprintf(currUserFavNew, "%s", temp.country);
                        fprintf(currUserFavNew, "%s", temp.genre);
                        fprintf(currUserFavNew, "%s", temp.rating);
                    }
                    fclose(ftempRead2);
                    fclose(currUserFavNew);

                    fprintf(ftemp2, "%s\n", tempUser.login);
                    fprintf(ftemp2, "%s", tempUser.pass);
                    fprintf(ftemp2, "%lld\n", tempUser.card);
                    if (tempSize != tempUser.favSize)
                    {
                        fprintf(ftemp2, "%d\n", tempUser.favSize - 1);
                    }
                    else
                    {
                        fprintf(ftemp2, "%d\n", tempUser.favSize);
                    }
                    fprintf(ftemp2, "%d\n", tempUser.isAdmin);
                }
                fclose(users);
                fclose(ftemp2);
            
                strcpy(fname, "favourites_");
                strncat(fname, currUser.login, 20);
                strncat(fname, ".txt", 5);

                FILE* usersNew = fopen("users.txt", "w");
                FILE* ftempRead2 = fopen("ftemp.txt", "r");
                for (int i = 0; i < userSize; i++)
                {
                    struct user temp;
                    fgets(temp.login, 100, ftempRead2);
                    fgets(temp.pass, 100, ftempRead2);
                    fscanf(ftempRead2, "%lld", &temp.card);
                    fscanf(ftempRead2, "%d", &temp.favSize);
                    fscanf(ftempRead2, "%d", &temp.isAdmin);
                    char tempSymb[2];
                    fgets(tempSymb, 100, ftempRead2);
                    if (i > 0)
                    {
                        fprintf(usersNew, "\n");
                    }
                    fprintf(usersNew, "%s", temp.login);
                    fprintf(usersNew, "%s", temp.pass);
                    fprintf(usersNew, "%lld\n", temp.card);
                    fprintf(usersNew, "%d\n", temp.favSize);
                    fprintf(usersNew, "%d", temp.isAdmin);
                }
                fclose(usersNew);
                fclose(ftempRead2);

                current = library.head;
                libraryCurr = 0;
                while (strcmp(current->film.name, currentFav->film.name) != 0)
                {
                    current = current->next;
                    libraryCurr += 1;
                }
                if (libraryCurr == 0)
                {
                    pop(&library);
                }
                else
                {
                    popIndex(&library, libraryCurr);
                }
                if (libraryFavCurr == 0)
                {
                    pop(&libraryFav);
                }
                else
                {
                    popIndex(&libraryFav, libraryFavCurr);
                }
                currUser.favSize -= 1;
                
                if (currUser.favSize == 0)
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
                    printf("\nДобавить в избранное (+)\n");
                    if (currUser.isAdmin == 1)
                    {
                        printf("Удалить фильм (DEL)\n");
                        printf("Добавить фильм (LSHIFT)\n");
                    }
                    printf("Список избранного (SPACE)\n");
                    printf("Личный кабинет (TAB)");
                    currWindow = 2;
                }
                else
                {
                    system("cls");
                    Sleep(200);
                    printf("Избранное, %s ", currUser.login);
                    if (currUser.isAdmin == 1)
                    {
                        printf("(Администратор)");
                    }
                    printf("\n\n");
                    printCards(libraryFav, libraryFavCurr);
                    printf("\nУдалить из избранного (-)\n");
                    if (currUser.isAdmin == 1)
                    {
                        printf("Удалить фильм (DEL)");
                    }
                }
            }
        }

        // Подробная информация о фильме
        if (currWindow == 4 && GetAsyncKeyState(VK_ESCAPE) == 0 && GetAsyncKeyState(VK_DELETE) == 0)
        {
            // Добавление в избранное
            if (GetAsyncKeyState(VK_OEM_PLUS) & 1 && isInFav == 0)
            {
                FILE* currUserFav = fopen(fname, "aw");
                if (currUser.favSize != 0)
                {
                    fprintf(currUserFav, "\n");
                }
                fprintf(currUserFav, "%s", current->film.name);
                fprintf(currUserFav, "\n%s", current->film.year);
                fprintf(currUserFav, "\n%s", current->film.country);
                fprintf(currUserFav, "\n%s", current->film.genre);
                fprintf(currUserFav, "\n%s", current->film.rating);
                currUser.favSize += 1;
                fclose(currUserFav);
                system("cls");
                Sleep(200);
                printf("Название %s\n", current->film.name);
                printf("Год %s\n", current->film.year);
                printf("Страна %s\n", current->film.country);
                printf("Жанр %s\n", current->film.genre);
                printf("Рейтинг %s\n", current->film.rating);
                printf("\nУдалить из избранного (-)\n");
                if (currUser.isAdmin == 1)
                {
                    printf("Удалить фильм (DEL)");
                }
                isInFav = 1;

                FILE* users = fopen("users.txt", "r");
                FILE* ftemp = fopen("ftemp.txt", "w");
                struct user temp;
                int size = 0;
                while(fgets(temp.login, 100, users) != NULL)
                {
                    temp.login[strcspn(temp.login, "\n")] = '\0';
                    fgets(temp.pass, 100, users);
                    fscanf(users, "%lld", &temp.card);
                    fscanf(users, "%d", &temp.favSize);
                    fscanf(users, "%d", &temp.isAdmin);
                    char tempSymb[2];
                    fgets(tempSymb, 100, users);
                    size += 1;
                    fprintf(ftemp, "%s\n", temp.login);
                    fprintf(ftemp, "%s", temp.pass);
                    fprintf(ftemp, "%lld\n", temp.card);
                    if (strcmp(temp.login, currUser.login) != 0)
                    {
                        fprintf(ftemp, "%d\n", temp.favSize);
                    }
                    else
                    {
                        fprintf(ftemp, "%d\n", temp.favSize + 1);
                    }
                    fprintf(ftemp, "%d\n", temp.isAdmin);
                }
                fclose(users);
                fclose(ftemp);
                FILE* usersNew = fopen("users.txt", "w");
                FILE* ftempRead = fopen("ftemp.txt", "r");
                for (int i = 0; i < size; i++)
                {
                    struct user temp;
                    fgets(temp.login, 100, ftempRead);
                    fgets(temp.pass, 100, ftempRead);
                    fscanf(ftempRead, "%lld", &temp.card);
                    fscanf(ftempRead, "%d", &temp.favSize);
                    fscanf(ftempRead, "%d", &temp.isAdmin);
                    char tempSymb[2];
                    fgets(tempSymb, 100, ftempRead);
                    if (i > 0)
                    {
                        fprintf(usersNew, "\n");
                    }
                    fprintf(usersNew, "%s", temp.login);
                    fprintf(usersNew, "%s", temp.pass);
                    fprintf(usersNew, "%lld\n", temp.card);
                    fprintf(usersNew, "%d\n", temp.favSize);
                    fprintf(usersNew, "%d", temp.isAdmin);
                }
                fclose(usersNew);
                fclose(ftempRead);
            }
            // Удаление из избранного
            if (GetAsyncKeyState(VK_OEM_MINUS) & 1 && isInFav == 1)
            {
                FILE* currUserFav = fopen(fname, "r");
                FILE* ftemp = fopen("ftemp.txt", "w");
                for (int i = 0; i < currUser.favSize; i++)
                {
                    struct film temp;
                    fgets(temp.name, 100, currUserFav);
                    fgets(temp.year, 100, currUserFav);
                    fgets(temp.country, 100, currUserFav);
                    fgets(temp.genre, 100, currUserFav);
                    fgets(temp.rating, 100, currUserFav);
                    temp.name[strcspn(temp.name, "\n")] = '\0';
                    if (strcmp(temp.name, current->film.name) != 0)
                    {
                        fprintf(ftemp, "%s\n", temp.name);
                        fprintf(ftemp, "%s", temp.year);
                        fprintf(ftemp, "%s", temp.country);
                        fprintf(ftemp, "%s", temp.genre);
                        fprintf(ftemp, "%s", temp.rating);
                    }
                }
                fclose(currUserFav);
                fclose(ftemp);
                currUser.favSize -= 1;
                FILE* currUserFavNew = fopen(fname, "w");
                FILE* ftempRead = fopen("ftemp.txt", "r");
                for (int i = 0; i < currUser.favSize; i++)
                {
                    struct film temp;
                    fgets(temp.name, 100, ftempRead);
                    fgets(temp.year, 100, ftempRead);
                    fgets(temp.country, 100, ftempRead);
                    fgets(temp.genre, 100, ftempRead);
                    fgets(temp.rating, 100, ftempRead);
                    temp.rating[strcspn(temp.rating, "\n")] = '\0';
                    if (i > 0)
                    {
                        fprintf(currUserFavNew, "\n");
                    }
                    fprintf(currUserFavNew, "%s", temp.name);
                    fprintf(currUserFavNew, "%s", temp.year);
                    fprintf(currUserFavNew, "%s", temp.country);
                    fprintf(currUserFavNew, "%s", temp.genre);
                    fprintf(currUserFavNew, "%s", temp.rating);
                }
                fclose(ftempRead);
                fclose(currUserFavNew);
                system("cls");
                Sleep(200);
                printf("Название %s\n", current->film.name);
                printf("Год %s\n", current->film.year);
                printf("Страна %s\n", current->film.country);
                printf("Жанр %s\n", current->film.genre);
                printf("Рейтинг %s\n", current->film.rating);
                printf("\nДобавить в избранное (+)\n");
                if (currUser.isAdmin == 1)
                {
                    printf("Удалить фильм (DEL)");
                }
                isInFav = 0;

                FILE* users = fopen("users.txt", "r");
                FILE* ftemp2 = fopen("ftemp.txt", "w");
                struct user temp;
                int size = 0;
                while(fgets(temp.login, 100, users) != NULL)
                {
                    temp.login[strcspn(temp.login, "\n")] = '\0';
                    fgets(temp.pass, 100, users);
                    fscanf(users, "%lld", &temp.card);
                    fscanf(users, "%d", &temp.favSize);
                    fscanf(users, "%d", &temp.isAdmin);
                    char tempSymb[2];
                    fgets(tempSymb, 100, users);
                    size += 1;
                    fprintf(ftemp2, "%s\n", temp.login);
                    fprintf(ftemp2, "%s", temp.pass);
                    fprintf(ftemp2, "%lld\n", temp.card);
                    if (strcmp(temp.login, currUser.login) != 0)
                    {
                        fprintf(ftemp2, "%d\n", temp.favSize);
                    }
                    else
                    {
                        fprintf(ftemp2, "%d\n", temp.favSize - 1);
                    }
                    fprintf(ftemp2, "%d\n", temp.isAdmin);
                }
                fclose(users);
                fclose(ftemp2);
                FILE* usersNew = fopen("users.txt", "w");
                FILE* ftempRead2 = fopen("ftemp.txt", "r");
                for (int i = 0; i < size; i++)
                {
                    struct user temp;
                    fgets(temp.login, 100, ftempRead2);
                    fgets(temp.pass, 100, ftempRead2);
                    fscanf(ftempRead2, "%lld", &temp.card);
                    fscanf(ftempRead2, "%d", &temp.favSize);
                    fscanf(ftempRead2, "%d", &temp.isAdmin);
                    char tempSymb[2];
                    fgets(tempSymb, 100, ftempRead2);
                    if (i > 0)
                    {
                        fprintf(usersNew, "\n");
                    }
                    fprintf(usersNew, "%s", temp.login);
                    fprintf(usersNew, "%s", temp.pass);
                    fprintf(usersNew, "%lld\n", temp.card);
                    fprintf(usersNew, "%d\n", temp.favSize);
                    fprintf(usersNew, "%d", temp.isAdmin);
                }
                fclose(usersNew);
                fclose(ftempRead2);
            }
            if (GetAsyncKeyState(VK_ESCAPE) & 1)
            {
                if (prevWindow == 0 || currUser.favSize == 0)
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
                    FILE* currUserFav = fopen(fname, "r");
                    char temp[100];
                    isInFav = 0;
                    for (int i = 0; i < currUser.favSize; i++)
                    {
                        fgets(temp, 100, currUserFav);
                        temp[strcspn(temp, "\n")] = 0;
                        if (strcmp(temp, current->film.name) == 0)
                        {
                            printf("\nУдалить из избранного (-)\n");
                            isInFav = 1;
                            break;
                        }
                        fgets(temp, 100, currUserFav);
                        fgets(temp, 100, currUserFav);
                        fgets(temp, 100, currUserFav);
                        fgets(temp, 100, currUserFav);
                    }
                    if (isInFav == 0)
                    {
                        printf("\nДобавить в избранное (+)\n");
                    }
                    if (currUser.isAdmin == 1)
                    {
                        printf("Удалить фильм (DEL)\n");
                        printf("Добавить фильм (LSHIFT)\n");
                    }
                    printf("Список избранного (SPACE)\n");
                    printf("Личный кабинет (TAB)");
                    fclose(currUserFav);
                    currWindow = 2;
                }
                else if (prevWindow == 1)
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
                        }
                    }
                    popBack(&libraryFav);
                    popBack(&libraryFav);
                    printf("Избранное, %s ", currUser.login);
                    if (currUser.isAdmin == 1)
                    {
                        printf("(Администратор)");
                    }
                    printf("\n\n");
                    printCards(libraryFav, libraryFavCurr);
                    printf("\nУдалить из избранного (-)\n");
                    if (currUser.isAdmin == 1)
                    {
                        printf("Удалить фильм (DEL)\n");
                    }
                }
                prevWindow = 0;
            }
            if (GetAsyncKeyState(VK_DELETE) & 1 && currUser.isAdmin == 1)
            {
                char tempName[100];
                if (prevWindow == 0)
                {
                    strcpy(tempName, current->film.name);
                }
                else
                {
                    strcpy(tempName, currentFav->film.name);
                }
                FILE* films = fopen("films.txt", "r");
                FILE* ftemp = fopen("ftemp.txt", "w");
                struct film temp;
                int size = 0;
                while(fgets(temp.name, 100, films) != NULL)
                {
                    fgets(temp.year, 100, films);
                    fgets(temp.country, 100, films);
                    fgets(temp.genre, 100, films);
                    fgets(temp.rating, 100, films);
                    temp.name[strcspn(temp.name, "\n")] = '\0';
                    if (strcmp(temp.name, tempName) != 0)
                    {
                        fprintf(ftemp, "%s\n", temp.name);
                        fprintf(ftemp, "%s", temp.year);
                        fprintf(ftemp, "%s", temp.country);
                        fprintf(ftemp, "%s", temp.genre);
                        fprintf(ftemp, "%s", temp.rating);
                        size += 1;
                    }
                }
                fclose(films);
                fclose(ftemp);

                FILE* filmsNew = fopen("films.txt", "w");
                FILE* ftempRead = fopen("ftemp.txt", "r");
                for (int i = 0; i < size; i++)
                {
                    struct film temp;
                    fgets(temp.name, 100, ftempRead);
                    fgets(temp.year, 100, ftempRead);
                    fgets(temp.country, 100, ftempRead);
                    fgets(temp.genre, 100, ftempRead);
                    fgets(temp.rating, 100, ftempRead);
                    temp.rating[strcspn(temp.rating, "\n")] = '\0';
                    if (i > 0)
                    {
                        fprintf(filmsNew, "\n");
                    }
                    fprintf(filmsNew, "%s", temp.name);
                    fprintf(filmsNew, "%s", temp.year);
                    fprintf(filmsNew, "%s", temp.country);
                    fprintf(filmsNew, "%s", temp.genre);
                    fprintf(filmsNew, "%s", temp.rating);
                }
                fclose(ftempRead);
                fclose(filmsNew);

                FILE* users = fopen("users.txt", "r");
                FILE* ftemp2 = fopen("ftemp.txt", "w");
                int userSize = 0;
                struct user tempUser;
                while(fgets(tempUser.login, 100, users) != NULL)
                {
                    tempUser.login[strcspn(tempUser.login, "\n")] = '\0';
                    fgets(tempUser.pass, 100, users);
                    fscanf(users, "%lld", &tempUser.card);
                    fscanf(users, "%d", &tempUser.favSize);
                    fscanf(users, "%d", &tempUser.isAdmin);
                    char tempSymb[2];
                    fgets(tempSymb, 100, users);
                    userSize += 1;
                    
                    strcpy(fname, "favourites_");
                    strncat(fname, tempUser.login, 20);
                    strncat(fname, ".txt", 5);

                    FILE* currUserFav = fopen(fname, "r");
                    FILE* ftemp3 = fopen("ftemp2.txt", "w");
                    int tempSize = 0;
                    for (int i = 0; i < tempUser.favSize; i++)
                    {
                        struct film temp;
                        fgets(temp.name, 100, currUserFav);
                        fgets(temp.year, 100, currUserFav);
                        fgets(temp.country, 100, currUserFav);
                        fgets(temp.genre, 100, currUserFav);
                        fgets(temp.rating, 100, currUserFav);
                        temp.name[strcspn(temp.name, "\n")] = '\0';
                        if (strcmp(temp.name, tempName) != 0)
                        {
                            fprintf(ftemp3, "%s\n", temp.name);
                            fprintf(ftemp3, "%s", temp.year);
                            fprintf(ftemp3, "%s", temp.country);
                            fprintf(ftemp3, "%s", temp.genre);
                            fprintf(ftemp3, "%s", temp.rating);
                            tempSize += 1;
                        }
                    }
                    fclose(currUserFav);
                    fclose(ftemp3);

                    FILE* currUserFavNew = fopen(fname, "w");
                    FILE* ftempRead2 = fopen("ftemp2.txt", "r");
                    for (int i = 0; i < tempSize; i++)
                    {
                        struct film temp;
                        fgets(temp.name, 100, ftempRead2);
                        fgets(temp.year, 100, ftempRead2);
                        fgets(temp.country, 100, ftempRead2);
                        fgets(temp.genre, 100, ftempRead2);
                        fgets(temp.rating, 100, ftempRead2);
                        temp.rating[strcspn(temp.rating, "\n")] = '\0';
                        if (i > 0)
                        {
                            fprintf(currUserFavNew, "\n");
                        }
                        fprintf(currUserFavNew, "%s", temp.name);
                        fprintf(currUserFavNew, "%s", temp.year);
                        fprintf(currUserFavNew, "%s", temp.country);
                        fprintf(currUserFavNew, "%s", temp.genre);
                        fprintf(currUserFavNew, "%s", temp.rating);
                    }
                    fclose(ftempRead2);
                    fclose(currUserFavNew);

                    fprintf(ftemp2, "%s\n", tempUser.login);
                    fprintf(ftemp2, "%s", tempUser.pass);
                    fprintf(ftemp2, "%lld\n", tempUser.card);
                    if (tempSize != tempUser.favSize)
                    {
                        fprintf(ftemp2, "%d\n", tempUser.favSize - 1);
                    }
                    else
                    {
                        fprintf(ftemp2, "%d\n", tempUser.favSize);
                    }
                    fprintf(ftemp2, "%d\n", tempUser.isAdmin);
                }
                fclose(users);
                fclose(ftemp2);

                strcpy(fname, "favourites_");
                strncat(fname, currUser.login, 20);
                strncat(fname, ".txt", 5);

                FILE* usersNew = fopen("users.txt", "w");
                FILE* ftempRead2 = fopen("ftemp.txt", "r");
                for (int i = 0; i < userSize; i++)
                {
                    struct user temp;
                    fgets(temp.login, 100, ftempRead2);
                    fgets(temp.pass, 100, ftempRead2);
                    fscanf(ftempRead2, "%lld", &temp.card);
                    fscanf(ftempRead2, "%d", &temp.favSize);
                    fscanf(ftempRead2, "%d", &temp.isAdmin);
                    char tempSymb[2];
                    fgets(tempSymb, 100, ftempRead2);
                    if (i > 0)
                    {
                        fprintf(usersNew, "\n");
                    }
                    fprintf(usersNew, "%s", temp.login);
                    fprintf(usersNew, "%s", temp.pass);
                    fprintf(usersNew, "%lld\n", temp.card);
                    fprintf(usersNew, "%d\n", temp.favSize);
                    fprintf(usersNew, "%d", temp.isAdmin);
                }
                fclose(usersNew);
                fclose(ftempRead2);

                if (prevWindow == 0)
                {
                    if (libraryCurr == 0)
                    {
                        pop(&library);
                    }
                    else
                    {
                        popIndex(&library, libraryCurr);
                    }
                }
                else
                {
                    current = library.head;
                    libraryCurr = 0;
                    while (strcmp(current->film.name, currentFav->film.name) != 0)
                    {
                        current = current->next;
                        libraryCurr += 1;
                    }
                    if (libraryCurr == 0)
                    {
                        pop(&library);
                    }
                    else
                    {
                        popIndex(&library, libraryCurr);
                    }
                    if (libraryFavCurr == 0)
                    {
                        pop(&libraryFav);
                    }
                    else
                    {
                        popIndex(&libraryFav, libraryFavCurr);
                    }
                }
                currUser.favSize -= 1;

                if (prevWindow == 0 || currUser.favSize == 0)
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
                    FILE* currUserFav = fopen(fname, "r");
                    char temp[100];
                    isInFav = 0;
                    for (int i = 0; i < currUser.favSize; i++)
                    {
                        fgets(temp, 100, currUserFav);
                        temp[strcspn(temp, "\n")] = 0;
                        if (strcmp(temp, current->film.name) == 0)
                        {
                            printf("\nУдалить из избранного (-)\n");
                            isInFav = 1;
                            break;
                        }
                        fgets(temp, 100, currUserFav);
                        fgets(temp, 100, currUserFav);
                        fgets(temp, 100, currUserFav);
                        fgets(temp, 100, currUserFav);
                    }
                    if (isInFav == 0)
                    {
                        printf("\nДобавить в избранное (+)\n");
                    }
                    if (currUser.isAdmin == 1)
                    {
                        printf("Удалить фильм (DEL)\n");
                        printf("Добавить фильм (LSHIFT)\n");
                    }
                    printf("Список избранного (SPACE)\n");
                    printf("Личный кабинет (TAB)");
                    fclose(currUserFav);
                    currWindow = 2;
                }
                else if (prevWindow == 1)
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
                        }
                    }
                    popBack(&libraryFav);
                    popBack(&libraryFav);
                    printf("Избранное, %s ", currUser.login);
                    if (currUser.isAdmin == 1)
                    {
                        printf("(Администратор)");
                    }
                    printf("\n\n");
                    printCards(libraryFav, libraryFavCurr);
                    printf("\nУдалить из избранного (-)\n");
                    if (currUser.isAdmin == 1)
                    {
                        printf("Удалить фильм (DEL)\n");
                    }
                }
                prevWindow = 0;
            }
        }

        // Личный кабинет
        if (currWindow == 5)
        {
            int choice;
            int err;
            FILE* users = fopen("users.txt", "r+");
            if (users == NULL) perror("Произошла ошибка: ");
            system("cls");
            printf("Ваш профиль\n\n");
            printf("Юзернейм: %s\n", currUser.login);
            printf("Пароль: ");
            if(showPass==0)
            {
                for(int i = 0; i<sizeof(currUser.pass);i++)
                {
                    if(currUser.pass[i]=='\0')
                    {
                        break;
                    }
                    printf("*");
                }
                printf("\n");
            }
            else
            {
                printf("%s\n",currUser.pass);
            }
            if(showCard==0)
            {
                printf("Номер карты: **** %lld\n\n",currUser.card%10000);
            }
            else
            {
                printf("Номер карты: %lld\n\n",currUser.card);
            }
            if(showPass==0)
            {
                printf("1) Показать пароль\n");
            }
            else
            {
                printf("1) Скрыть пароль\n");
            }
            if(showCard==0)
            {
                printf("2) Показать номер карты\n");
            }
            else
            {
                printf("2) Скрыть номер карты\n");
            }
            
            printf("3) Сменить номер карты\n");
            printf("4) Поменять имя\n");
            printf("5) Изменить пароль\n\n");
            printf("6) Выйти в каталог и сохранить данные\n\n");
            printf("Выбор: ");scanf("%d",&choice);
            
            char passhold[21];
            char passhold1[20];
            char namehold[21];
            
            switch (choice)
            {
            case 1:
            {
                if (showPass == 0)
                {
                    showPass = 1;
                }
                else
                {
                    showPass = 0;
                }
                break;
            }

            case 2:
            {
                if (showCard == 0)
                {
                    showCard = 1;
                }
                else
                {
                    showCard = 0;
                }
                break;
            }
            
            case 3: //смена карты
            {
                long long cardtemp; 
                system("cls");
                printf("Введите новый номер карты: ");
                scanf("%lld",&cardtemp);
                if(digits(cardtemp) != 16){
                    system("cls");
                    printf("Неверный номер карты, повторите попытку снова");
                    Sleep(3000);
                }
                else
                {
                    printf("Введите пароль: ");scanf("%s",passhold);
                    if(strcmp(passhold,currUser.pass) != 0)
                    {
                        system("cls");
                        printf("Неверный пароль, повторите попытку снова");
                        Sleep(3000);
                    }
                    else
                    {
                        currUser.card=cardtemp;
                        FILE* users = fopen("users.txt", "r");
                        FILE* ftemp = fopen("ftemp.txt", "w");
                        struct user temp;
                        int size = 0;
                        while(fgets(temp.login, 100, users) != NULL)
                        {
                            temp.login[strcspn(temp.login, "\n")] = '\0';
                            fgets(temp.pass, 100, users);
                            fscanf(users, "%lld", &temp.card);
                            fscanf(users, "%d", &temp.favSize);
                            fscanf(users, "%d", &temp.isAdmin);
                            char tempSymb[2];
                            fgets(tempSymb, 100, users);
                            size += 1;
                            fprintf(ftemp, "%s\n", temp.login);
                            fprintf(ftemp, "%s", temp.pass);
                            if (strcmp(temp.login, currUser.login) != 0)
                            {
                                fprintf(ftemp, "%lld\n", temp.card);
                            }
                            else
                            {
                                fprintf(ftemp, "%lld\n", cardtemp);
                            }
                            fprintf(ftemp, "%d\n", temp.favSize);
                            fprintf(ftemp, "%d\n", temp.isAdmin);
                        }
                        fclose(users);
                        fclose(ftemp);
                        FILE* usersNew = fopen("users.txt", "w");
                        FILE* ftempRead = fopen("ftemp.txt", "r");
                        for (int i = 0; i < size; i++)
                        {
                            struct user temp;
                            fgets(temp.login, 100, ftempRead);
                            fgets(temp.pass, 100, ftempRead);
                            fscanf(ftempRead, "%lld", &temp.card);
                            fscanf(ftempRead, "%d", &temp.favSize);
                            fscanf(ftempRead, "%d", &temp.isAdmin);
                            char tempSymb[2];
                            fgets(tempSymb, 100, ftempRead);
                            if (i > 0)
                            {
                                fprintf(usersNew, "\n");
                            }
                            fprintf(usersNew, "%s", temp.login);
                            fprintf(usersNew, "%s", temp.pass);
                            fprintf(usersNew, "%lld\n", temp.card);
                            fprintf(usersNew, "%d\n", temp.favSize);
                            fprintf(usersNew, "%d", temp.isAdmin);
                        }
                        fclose(usersNew);
                        fclose(ftempRead);

                        printf("\nУспешная смена карты!");
                        Sleep(3000);
                    }
                }
                break;
            }
            
            case 4: //смена имени
            {
                system("cls");
                char namehold[20];
                printf("Введите новое имя: ");scanf("%s",namehold);
                int isRightInput = 0;
                int isWrongLog = 0;
                int isExistLog = 0;
                FILE* usersRead = fopen("users.txt", "r");
                struct user temp;
                while(fgets(temp.login, 100, usersRead) != NULL)
                {
                    temp.login[strcspn(temp.login, "\n")] = '\0';
                    if (strcmp(namehold, temp.login) == 0)
                    {
                        fgets(temp.pass, 100, usersRead);
                        temp.pass[strcspn(temp.pass, "\n")] = '\0';
                        fscanf(usersRead, "%lld", &temp.card);
                        fscanf(usersRead, "%d", &temp.favSize);
                        fscanf(usersRead, "%d", &temp.isAdmin);
                        isExistLog = 1;
                        break;
                    }
                    fgets(temp.pass, 100, usersRead);
                    temp.pass[strcspn(temp.pass, "\n")] = '\0';
                    fscanf(usersRead, "%lld", &temp.card);
                    fscanf(usersRead, "%d", &temp.favSize);
                    fscanf(usersRead, "%d", &temp.isAdmin);
                    char tempSymb[2];
                    fgets(tempSymb, 100, usersRead);
                }
                for (int i = 0; i < strlen(namehold); i++)
                {
                    if ((namehold[i] < 48 || namehold[i] > 57) && (namehold[i] < 65 || namehold[i] > 90) && (namehold[i] < 97 || namehold[i] > 122))
                    {
                        isWrongLog = 1;
                        break;
                    }
                }
                if (strlen(namehold) < 3 || strlen(namehold) > 20 || isWrongLog == 1)
                {
                    system("cls");
                    printf("Логин должен быть от 3 до 20 символов и состоять только из букв латинского алфавита и цифр\n");
                    Sleep(3000);
                }
                else if (isExistLog == 1)
                {
                    system("cls");
                    printf("Логин уже существует\n");
                    Sleep(3000);
                }
                else
                {
                    isRightInput = 1;
                }
                
                if (isRightInput == 1)
                {
                    printf("Введите пароль: ");scanf("%s",passhold);
                    if(strcmp(passhold,currUser.pass) != 0)
                    {
                        system("cls");
                        printf("Неверный пароль, повторите попытку снова");
                        Sleep(3000);
                    }
                    else
                    {
                        FILE* users = fopen("users.txt", "r");
                        FILE* ftemp = fopen("ftemp.txt", "w");
                        struct user temp;
                        int size = 0;
                        while(fgets(temp.login, 100, users) != NULL)
                        {
                            temp.login[strcspn(temp.login, "\n")] = '\0';
                            fgets(temp.pass, 100, users);
                            fscanf(users, "%lld", &temp.card);
                            fscanf(users, "%d", &temp.favSize);
                            fscanf(users, "%d", &temp.isAdmin);
                            char tempSymb[2];
                            fgets(tempSymb, 100, users);
                            size += 1;
                            if (strcmp(temp.login, currUser.login) != 0)
                            {
                                fprintf(ftemp, "%s\n", temp.login);
                            }
                            else
                            {
                                fprintf(ftemp, "%s\n", namehold);
                            }
                            fprintf(ftemp, "%s", temp.pass);
                            fprintf(ftemp, "%lld\n", temp.card);
                            fprintf(ftemp, "%d\n", temp.favSize);
                            fprintf(ftemp, "%d\n", temp.isAdmin);
                        }
                        fclose(users);
                        fclose(ftemp);
                        FILE* usersNew = fopen("users.txt", "w");
                        FILE* ftempRead = fopen("ftemp.txt", "r");
                        for (int i = 0; i < size; i++)
                        {
                            struct user temp;
                            fgets(temp.login, 100, ftempRead);
                            fgets(temp.pass, 100, ftempRead);
                            fscanf(ftempRead, "%lld", &temp.card);
                            fscanf(ftempRead, "%d", &temp.favSize);
                            fscanf(ftempRead, "%d", &temp.isAdmin);
                            char tempSymb[2];
                            fgets(tempSymb, 100, ftempRead);
                            if (i > 0)
                            {
                                fprintf(usersNew, "\n");
                            }
                            fprintf(usersNew, "%s", temp.login);
                            fprintf(usersNew, "%s", temp.pass);
                            fprintf(usersNew, "%lld\n", temp.card);
                            fprintf(usersNew, "%d\n", temp.favSize);
                            fprintf(usersNew, "%d", temp.isAdmin);
                        }
                        fclose(usersNew);
                        fclose(ftempRead);
                        strcpy(currUser.login, namehold);

                        char fnameOld[34];
                        strcpy(fnameOld, fname);
                        strcpy(fname, "favourites_");
                        strncat(fname, currUser.login, 20);
                        strncat(fname, ".txt", 5);
                        rename(fnameOld, fname);
                        
                        printf("\nУспешная смена имени!");
                        Sleep(3000);
                    }
                }
                break;
            }

            case 5: //смена пароля
            {
                system("cls");
                printf("Введите старый пароль: ");scanf("%s",passhold);
                if(strcmp(passhold,currUser.pass) != 0)
                {
                    system("cls");
                    printf("Неверный старый пароль, повторите попытку снова");
                    Sleep(3000);
                }
                else
                {
                    printf("\nВведите новый пароль (не более 20 символов): ");
                    scanf("%s",passhold1);
                    int isHighReg = 0, isLowReg = 0, isNum = 0, isWrongPass = 0, isRightInput = 0;;
                    for (int i = 0; i < strlen(passhold1); i++)
                    {
                        if ((passhold1[i] < 48 || passhold1[i] > 57) && (passhold1[i] < 65 || passhold1[i] > 90) && (passhold1[i] < 97 || passhold1[i] > 122))
                        {
                            isWrongPass = 1;
                            break;
                        }
                        if (passhold1[i] < 58 && passhold1[i] > 47)
                        {
                            isNum += 1;
                        }
                        if (passhold1[i] < 91 && passhold1[i] > 64)
                        {
                            isHighReg += 1;
                        }
                        if (passhold1[i] < 123 && passhold1[i] > 96)
                        {
                            isLowReg += 1;
                        }
                        if (isNum > 0 && isLowReg > 0 && isHighReg > 0 && strlen(passhold1) >= 6 && strlen(passhold1) <= 20 && isWrongPass == 0)
                        {
                            isRightInput = 1;
                        }
                    }
                    if (isNum == 0 || isLowReg == 0 || isHighReg == 0 || strlen(passhold1) < 6 || strlen(passhold1) > 20 || isWrongPass == 1)
                    {
                        system("cls");
                        printf("Пароль должен содержать от 6 до 20 символов, хотя бы одну цифру и букву верхнего и нижнего регистра латинского алфавита\n");
                        Sleep(3000);
                    }
                    else
                    {
                        FILE* users = fopen("users.txt", "r");
                        FILE* ftemp = fopen("ftemp.txt", "w");
                        struct user temp;
                        int size = 0;
                        while(fgets(temp.login, 100, users) != NULL)
                        {
                            temp.login[strcspn(temp.login, "\n")] = '\0';
                            fgets(temp.pass, 100, users);
                            fscanf(users, "%lld", &temp.card);
                            fscanf(users, "%d", &temp.favSize);
                            fscanf(users, "%d", &temp.isAdmin);
                            char tempSymb[2];
                            fgets(tempSymb, 100, users);
                            size += 1;
                            fprintf(ftemp, "%s\n", temp.login);
                            if (strcmp(temp.login, currUser.login) != 0)
                            {
                                fprintf(ftemp, "%s", temp.pass);
                            }
                            else
                            {
                                fprintf(ftemp, "%s\n", passhold1);
                            }
                            fprintf(ftemp, "%lld\n", temp.card);
                            fprintf(ftemp, "%d\n", temp.favSize);
                            fprintf(ftemp, "%d\n", temp.isAdmin);
                        }
                        fclose(users);
                        fclose(ftemp);
                        FILE* usersNew = fopen("users.txt", "w");
                        FILE* ftempRead = fopen("ftemp.txt", "r");
                        for (int i = 0; i < size; i++)
                        {
                            struct user temp;
                            fgets(temp.login, 100, ftempRead);
                            fgets(temp.pass, 100, ftempRead);
                            fscanf(ftempRead, "%lld", &temp.card);
                            fscanf(ftempRead, "%d", &temp.favSize);
                            fscanf(ftempRead, "%d", &temp.isAdmin);
                            char tempSymb[2];
                            fgets(tempSymb, 100, ftempRead);
                            if (i > 0)
                            {
                                fprintf(usersNew, "\n");
                            }
                            fprintf(usersNew, "%s", temp.login);
                            fprintf(usersNew, "%s", temp.pass);
                            fprintf(usersNew, "%lld\n", temp.card);
                            fprintf(usersNew, "%d\n", temp.favSize);
                            fprintf(usersNew, "%d", temp.isAdmin);
                        }
                        fclose(usersNew);
                        fclose(ftempRead);
                        strcpy(currUser.pass, passhold1);

                        printf("\nУдачная смена пароля!");
                        Sleep(3000);
                    }
                }
                break;
            }
            case 6:
            {
                currWindow = 2;
                system("cls");
                printf("Добро пожаловать, %s ", currUser.login);
                if (currUser.isAdmin == 1)
                {
                    printf("(Администратор)");
                }
                printf("\n\n");
                printCards(library, libraryCurr);
                FILE* currUserFav = fopen(fname, "r");
                char temp[100];
                isInFav = 0;
                for (int i = 0; i < currUser.favSize; i++)
                {
                    fgets(temp, 100, currUserFav);
                    temp[strcspn(temp, "\n")] = 0;
                    if (strcmp(temp, current->film.name) == 0)
                    {
                        printf("\nУдалить из избранного (-)\n");
                        isInFav = 1;
                        break;
                    }
                    fgets(temp, 100, currUserFav);
                    fgets(temp, 100, currUserFav);
                    fgets(temp, 100, currUserFav);
                    fgets(temp, 100, currUserFav);
                }
                if (isInFav == 0)
                {
                    printf("\nДобавить в избранное (+)\n");
                }
                if (currUser.isAdmin == 1)
                {
                    printf("Удалить фильм (DEL)\n");
                    printf("Добавить фильм (LSHIFT)\n");
                }
                printf("Список избранного (SPACE)\n");
                printf("Личный кабинет (TAB)");
                fclose(currUserFav);
                break;
            }
            default:
            {
                system("cls");
                printf("Неверное значение!");
                Sleep(500);
                break;
            }
            }
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
            FILE* currUserFav = fopen(fname, "r");
            char temp[100];
            isInFav = 0;
            for (int i = 0; i < currUser.favSize; i++)
            {
                fgets(temp, 100, currUserFav);
                temp[strcspn(temp, "\n")] = 0;
                if (strcmp(temp, current->film.name) == 0)
                {
                    printf("\nУдалить из избранного (-)\n");
                    isInFav = 1;
                    break;
                }
                fgets(temp, 100, currUserFav);
                fgets(temp, 100, currUserFav);
                fgets(temp, 100, currUserFav);
                fgets(temp, 100, currUserFav);
            }
            if (isInFav == 0)
            {
                printf("\nДобавить в избранное (+)\n");
            }
            if (currUser.isAdmin == 1)
            {
                printf("Удалить фильм (DEL)\n");
                printf("Добавить фильм (LSHIFT)\n");
            }
            printf("Список избранного (SPACE)\n");
            printf("Личный кабинет (TAB)");
            fclose(currUserFav);
            currWindow = 2;
        }
    }

    system("pause");
}