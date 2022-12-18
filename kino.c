#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <math.h>

#define USERS "users.txt"
#define FILMS "films.txt"

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

    printf("Название %s\n", current->film.name);
    printf("Год %s\n", current->film.year);
    printf("Страна %s\n", current->film.country);
    printf("Жанр %s\n", current->film.genre);
    printf("Рейтинг %s\n", current->film.rating);
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

int find_user_point(FILE* file, char* string, long point_id)
{//ftell с поиском необходимой строки и возврата нужного указателя по пользователям
    char bufer[128];

    do
    {
        if(feof(file)!=0)
        {
            break;
        }
        for(int i = 0;i<strlen(bufer);i++)
        {
            bufer[i]=bufer[i];
        }

        for(int i = 0; i<4;i++)
        {
            fgets(bufer, 128, file);
        }
    }  while(strcspn(fgets(bufer, 128, file), string) || feof(file));

    fseek(file, strlen(bufer)*(-1), SEEK_END);
    
    point_id = ftell(file);

    return 0;

}

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    FILE* films = fopen(FILMS, "r");
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
    int currWindow = -1; //!!поменять обратно на -1, 5 поставлено для теста ЛК
    int logReg = 0;
    BYTE keyStatus[256];
    struct user newUser;
    struct user currUser;
    short showPass = 0;
    short showCard = 0;
    printf("-> Войти\n   Зарегистрироваться\n");
    while(TRUE)
    {
        // Стартовое окно
        if (currWindow == -1 && GetAsyncKeyState(VK_RETURN) == 0)
        {
            if (GetAsyncKeyState(VK_UP) != 0)
            {
                system("cls");
                Sleep(200);
                printf("-> Войти\n   Зарегистрироваться\n");
                logReg = 0;
            }
            if (GetAsyncKeyState(VK_DOWN) != 0)
            {
                system("cls");
                Sleep(200);
                printf("   Войти\n-> Зарегистрироваться\n");
                logReg = 1;
            }
            if (GetAsyncKeyState(VK_RETURN) != 0)
            {
                system("cls");
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
            }
            if (GetAsyncKeyState(VK_ESCAPE) != 0)
            {
                return 0;
            }
            SetKeyboardState(keyStatus);
        }

        // Окно входа в систему
        if (currWindow == 0)
        {
            char inputLog[20];
            char inputPass[20];
            printf("Логин:\n");
            scanf("%s", &inputLog);
            printf("Пароль:\n");
            scanf("%s", &inputPass);
            FILE* users = fopen(USERS, "r");
            while(fgets(currUser.login, 100, users) != NULL)
            {
                currUser.login[strcspn(currUser.login, "\n")] = 0;
                fgets(currUser.pass, 100, users);
                currUser.pass[strcspn(currUser.pass, "\n")] = 0;
                if (strcmp(inputLog, currUser.login) == 0 && strcmp(inputPass, currUser.pass) == 0)
                {
                    fscanf(users, "%d", &currUser.card);
                    fscanf(users, "%d", &currUser.favSize);
                    fscanf(users, "%d", &currUser.isAdmin);
                    currWindow = 2;
                    system("cls");
                    printf("Добро пожаловать, %s\n\n", currUser.login);
                    printCards(library, libraryCurr);
                    break;
                }
                fscanf(users, "%d", &currUser.card);
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
            SetKeyboardState(keyStatus);
        }

        // Окно регистрации
        if (currWindow == 1)
        {
            FILE* users = fopen(USERS, "aw");
            int isRightInput = 0;
            while (isRightInput == 0)
            {
                printf("Придумайте логин:\n");
                scanf("%s", &newUser.login);
                isRightInput = 1;
            }
            isRightInput = 0;
            while (isRightInput == 0)
            {
                printf("Придумайте пароль:\n");
                scanf("%s", &newUser.pass);
                isRightInput = 1;
            }
            isRightInput = 0;
            while(isRightInput == 0)
            {
                printf("Введите номер карты:\n");
                scanf("%lld", &newUser.card);
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
            printf("-> Войти:\n   Регистрация\n");
            currWindow = -1;
            SetKeyboardState(keyStatus);
        }

        // Каталог
        if (currWindow == 2)
        {
            if (GetAsyncKeyState(VK_RIGHT) != 0)
            {
                libraryCurr++;
                system("cls");
                Sleep(200);
                printf("Добро пожаловать, %s\n\n", currUser.login);
                printCards(library, libraryCurr);
            }
            if (GetAsyncKeyState(VK_LEFT) != 0)
            {
                libraryCurr--;
                system("cls");
                Sleep(200);
                printf("Добро пожаловать, %s\n\n", currUser.login);
                printCards(library, libraryCurr);
            }
            if (GetAsyncKeyState(VK_ESCAPE) != 0)
            {
                system("cls");
                Sleep(200);
                printf("-> login:\n   registration\n");
                currWindow = -1;
                libraryCurr = 0;
            }
            if (GetAsyncKeyState(VK_DOWN) != 0)
            {
                currWindow=5;
            }
            SetKeyboardState(keyStatus);
        }

        // Избранное
        if (currWindow == 3)
        {

        }

        // Подробная информация о фильме
        if (currWindow == 4)
        {

        }

        // Личный кабинет
        if (currWindow == 5)
        {
            int choice;
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
                if (showPass == 0)
                {
                    showPass = 1;
                }
                else
                {
                    showPass = 0;
                }
                break;
            
            case 2:
                if (showCard == 0)
                {
                    showCard = 1;
                }
                else
                {
                    showCard = 0;
                }
                break;
            
            case 3: //смена карты
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
                    short cond=1;
                    for(int i = 0; i<strlen(currUser.pass);i++)
                    {
                        if(passhold[i]!=currUser.pass[i])
                        {
                            cond=0;
                        }
                    }
                    if(cond==0)
                    {
                        system("cls");
                        printf("Неверный пароль, повторите попытку снова");
                        Sleep(3000);
                    }
                    currUser.card=cardtemp;
                    printf("\nУспешная смена карты!");
                    Sleep(3000);
                }
                break;
            
            case 4: //смена имени
                system("cls");
                char namehold[21];
                printf("Введите новое имя: ");scanf("%s",namehold);
                if(3<=strlen(namehold)<=20)
                {
                    printf("Введите пароль: ");scanf("%s",passhold);
                    short cond=1;
                    for(int i = 0; i<strlen(currUser.pass);i++)
                    {
                        if(passhold[i]!=currUser.pass[i])
                        {
                            cond=0;
                        }
                    }

                    if(cond==0)
                    {
                        system("cls");
                        printf("Неверный пароль, повторите попытку снова");
                        Sleep(3000);
                    }
                    else
                    {
                        for(int i = 0; i<strlen(namehold);i++)
                        {
                            currUser.pass[i]=namehold[i];
                            currUser.pass[i+1]='\0';
                        }
                        printf("\nУспешная смена имени!");
                        Sleep(3000);
                    }
                }
                else
                {
                    system("cls");
                    printf("Неверно введено имя, повторите попытку снова");
                    Sleep(3000);
                }
                break;

            case 5: //смена пароля
                system("cls");
                printf("Введите старый пароль: ");scanf("%s",passhold);
                short cond=1;
                for(int i = 0; i<strlen(currUser.pass);i++)
                {
                    if(passhold[i]!=currUser.pass[i])
                    {
                        cond=0;
                    }
                }
                if(cond==0)
                {
                    system("cls");
                    printf("Неверный старый пароль, повторите попытку снова");
                    Sleep(3000);
                }
                else
                {
                    printf("\nВведите новый пароль (не более 20 символов): ");
                    scanf("%s",passhold1);
                    if(strlen(passhold1)>20)
                    {
                        system("cls");
                        printf("Неверно набранная строка, повторите попытку снова");
                        Sleep(3000);
                    }
                    else
                    {
                        for(int i = 0; i<strlen(passhold1);i++)
                        {
                            currUser.pass[i]=passhold1[i];
                            currUser.pass[i+1]='\0';
                        }
                        printf("\nУдачная смена пароля!");
                        Sleep(3000);
                    }
                }
                break;

            case 6:
                currWindow = 2;
                break;

            default:
                break;
            }

            FILE* users = fopen(USERS, "r+");
            long point;
            int error_code = find_user_point(users,currUser.pass,point);
            
            if(error_code==0)
            {
                fseek(users,point,SEEK_SET);

                fprintf(users, "%s\n", currUser.login);
                fprintf(users, "%s\n", currUser.pass);
                fprintf(users, "%lld\n", currUser.card);
                fprintf(users, "%d\n", currUser.favSize);
                fprintf(users, "%d", currUser.isAdmin);
                fclose(users);
            }
            else
            {
                system("cls");
                printf("Ошибка записи данных. Код ошибки: %d", error_code);
                return 0;           
            }
        }

        // Добавление фильма в каталог
        if (currWindow == 6)
        {
            
        }
    }

    system("pause");
}