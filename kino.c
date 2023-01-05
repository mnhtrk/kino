#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <math.h>

#define USERS "bin/users.txt"
#define FILMS "bin/films.txt"
#define FAV_FOLDER "bin/favorites"
#define BUF 256

///////////////////////////////////////////////////////////////////////////////////
//структура фильма и список к нему
struct film
{
    char name[100];
    char year[6];
    char country[100];
    char genre[100];
    char rating[5];
};

struct film_node
{
    struct film film;
    struct film_node* next;
    struct film_node* prev;
};

struct film_list
{
    struct film_node* head;
    struct film_node* tail;
};  

// Добавление элемента
void push_film(struct film_list* l, struct film film)
{
    struct film_node* current = (struct film_node*) malloc(sizeof(struct film_node));
    current->film = film;
    current->next = l->head;
    current->prev = l->tail;
    l->head->prev = current;
    l->tail->next = current;
    l->head = current;
}

// Удаление элемента
void pop_film(struct film_list* l)
{
    struct film_node* current = l->head->next;
    current->prev = l->tail; 
    free(l->head);
    l->head = current;
}
///////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////
//структура юзера и лист к нему
struct user
{
    char login[20];
    char pass[20];
    long long card;
    int favSize;
    int isAdmin;
};

struct user_node
{
    struct user user;
    struct user_node* next;
    struct user_node* prev;
};

struct user_list
{
    struct user_node* head;
    struct user_node* tail;
};

// Добавление элемента
void push_user(struct user_list* l, struct user user)
{
    struct user_node* current = (struct user_node*) malloc(sizeof(struct user_node));
    current->user = user;
    current->next = NULL;
    current->prev = l->tail;
    // l->head->prev = current;
    l->tail->next = current;
    l->tail = current;
}

// Удаление элемента
void pop_user(struct user_list* l)
{
    struct user_node* current = l->head->next;
    current->prev = l->tail; 
    free(l->head);
    l->head = current;
}

int find_user(struct user_list user_list, char* login)
{
    struct user_node* current = user_list.head;
    int count=0;
    while(current->user.login!=login)
    {
        if(current->next==NULL)
        {
            return -1;
        }
        current=current->next;
        ++count;
    }
    return count;
}


///////////////////////////////////////////////////////////////////////////////////

// Карусель
void printCards(struct film_list l, int index)
{
    struct film_node* current = l.head;
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

//функция сравнивания строк
int streq(char* string1, char* string2)
{
    int cond=1;
    if(strlen(string1)!=strlen(string2))
    {
        cond = 0;
    }
    for(int i = 0; i<strlen(string1);i++)
    {
        if(string1[i]!=string2[i])
        {
            cond=0;
        }
        if(cond == 0)
        {
            break;
        }
    }

    return cond;
}

void save_user_base(struct user_list user_list, FILE* save_txt)
{
    struct user_node* current = (struct user_node*) malloc(sizeof(struct user_node));
     while (current!=NULL)
    {
        printf("%s\n%s\n%lld\n%%d\n%d\n", current->user.login, current->user.pass, 
        current->user.card, current->user.favSize, current->user.isAdmin);
        current=current->next;
    }
}

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    FILE* films = fopen(FILMS, "r");
    struct film f1, f2;
    fgets(f1.name, BUF, films);
    f1.name[strcspn(f1.name, "\n")] = '\0';
    fgets(f1.year, BUF, films);
    f1.year[strcspn(f1.year, "\n")] = '\0';
    fgets(f1.country, BUF, films);
    f1.country[strcspn(f1.country, "\n")] = '\0';
    fgets(f1.genre, BUF, films);
    f1.genre[strcspn(f1.genre, "\n")] = '\0';
    fgets(f1.rating, BUF, films);
    f1.rating[strcspn(f1.rating, "\n")] = '\0';
    fgets(f2.name, BUF, films);
    f2.name[strcspn(f2.name, "\n")] = '\0';
    fgets(f2.year, BUF, films);
    f2.year[strcspn(f2.year, "\n")] = '\0';
    fgets(f2.country, BUF, films);
    f2.country[strcspn(f2.country, "\n")] = '\0';
    fgets(f2.genre, BUF, films);
    f2.genre[strcspn(f2.genre, "\n")] = '\0';
    fgets(f2.rating, BUF, films);
    f2.rating[strcspn(f2.rating, "\n")] = '\0';

    struct film_list library;
    library.head = (struct film_node*) malloc(sizeof(struct film_node));
    library.tail = (struct film_node*) malloc(sizeof(struct film_node));
    library.tail->next = library.head;
    library.tail->prev = library.head;
    library.head->prev = library.tail;
    library.head->next = library.tail;
    library.head->film = f1;
    library.tail->film = f2;
    
    while(fgets(f1.name, BUF, films) != NULL)
    {
        f1.name[strcspn(f1.name, "\n")] = '\0';
        fgets(f1.year, BUF, films);
        f1.year[strcspn(f1.year, "\n")] = '\0';
        fgets(f1.country, BUF, films);
        f1.country[strcspn(f1.country, "\n")] = '\0';
        fgets(f1.genre, BUF, films);
        f1.genre[strcspn(f1.genre, "\n")] = '\0';
        fgets(f1.rating, BUF, films);
        f1.rating[strcspn(f1.rating, "\n")] = '\0';
        push_film(&library, f1);
    }
    fclose(films);

    FILE* users = fopen(USERS, "r");
    struct user u1, u2;
    fgets(u1.login, BUF, users);
    u1.login[strcspn(u1.login, "\n")] = '\0';
    fgets(u1.pass, BUF, users);
    u1.pass[strcspn(u1.pass, "\n")] = '\0';
    fscanf(users,"%lld%d%d\n",&u1.card,&u1.favSize,&u1.isAdmin);
    fgets(u2.login, BUF, users);
    u2.login[strcspn(u2.login, "\n")] = '\0';
    fgets(u2.pass, BUF, users);
    u2.pass[strcspn(u2.pass, "\n")] = '\0';
    fscanf(users,"%lld%d%d\n",&u2.card,&u2.favSize,&u2.isAdmin);

    struct user_list all_users;
    all_users.head = (struct user_node*) malloc(sizeof(struct user_node));
    all_users.tail = (struct user_node*) malloc(sizeof(struct user_node));
    all_users.tail->next = NULL;
    all_users.tail->prev = all_users.head;
    all_users.head->prev = NULL;
    all_users.head->next = all_users.tail;
    all_users.head->user = u1;
    all_users.tail->user = u2;
    
    while(fgets(u1.login, BUF, users) != NULL)
    {
        u1.login[strcspn(u1.login, "\n")] = '\0';
        fgets(u1.pass, BUF, users);
        u1.pass[strcspn(u1.pass, "\n")] = '\0';
        fscanf(users,"%lld%d%d\n",&u1.card,&u1.favSize,&u1.isAdmin);
        push_user(&all_users, u1);
    }
    fclose(users);


    int libraryCurr = 0;
    int currWindow = -1;
    int logReg = 0;
    BYTE keyStatus[BUF];
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
                /*system("cls");*/
                Sleep(200);
                printf("-> Войти\n   Зарегистрироваться\n");
                logReg = 0;
            }
            if (GetAsyncKeyState(VK_DOWN) != 0)
            {
                /*system("cls");*/
                Sleep(200);
                printf("   Войти\n-> Зарегистрироваться\n");
                logReg = 1;
            }
            if (GetAsyncKeyState(VK_RETURN) != 0)
            {
                /*system("cls");*/
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

        fflush(stdin);

        // Окно входа в систему
        if (currWindow == 0)
        {
            char inputLog[20];
            char inputPass[20];
            printf("Логин: "); scanf("%s", &inputLog);
            printf("Пароль: "); scanf("%s", &inputPass);
            FILE* users = fopen(USERS, "r");
            if (users == NULL) perror("Произошла ошибка: ");
            while(fgets(currUser.login, BUF, users) != NULL)
            {
                currUser.login[strcspn(currUser.login, "\n")] = 0;
                fgets(currUser.pass, BUF, users);
                currUser.pass[strcspn(currUser.pass, "\n")] = 0;
                if (strcmp(inputLog, currUser.login) == 0 && strcmp(inputPass, currUser.pass) == 0)
                {
                    fscanf(users, "%d", &currUser.card);
                    fscanf(users, "%d", &currUser.favSize);
                    fscanf(users, "%d", &currUser.isAdmin);
                    currWindow = 2;
                    /*system("cls");*/
                    printf("Добро пожаловать, %s\n\n", currUser.login);
                    printCards(library, libraryCurr);
                    break;
                }
                fscanf(users, "%d", &currUser.card);
                fscanf(users, "%d", &currUser.favSize);
                fscanf(users, "%d", &currUser.isAdmin);
                fgets(currUser.login, BUF, users);
            }
            fclose(users);
            if (currWindow != 2)
            {
                /*system("cls");*/
                printf("Неправильный логин или пароль\n");
            }
            SetKeyboardState(keyStatus);
        }

        // Окно регистрации
        if (currWindow == 1)
        {
            FILE* users = fopen(USERS, "aw");
            if (users == NULL) perror("Произошла ошибка: ");
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
                    /*system("cls");*/
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
            /*system("cls");*/
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
                /*system("cls");*/
                Sleep(200);
                printf("Добро пожаловать, %s\n\n", currUser.login);
                printCards(library, libraryCurr);
            }
            if (GetAsyncKeyState(VK_LEFT) != 0)
            {
                libraryCurr--;
                /*system("cls");*/
                Sleep(200);
                printf("Добро пожаловать, %s\n\n", currUser.login);
                printCards(library, libraryCurr);
            }
            if (GetAsyncKeyState(VK_ESCAPE) != 0)
            {
                /*system("cls");*/
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
            int err;
            FILE* users = fopen(USERS, "r+");
            if (users == NULL) perror("Произошла ошибка: ");
            /*system("cls");*/
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
                /*system("cls");*/
                printf("Введите новый номер карты: ");
                scanf("%lld",&cardtemp);
                if(digits(cardtemp) != 16){
                    /*system("cls");*/
                    printf("Неверный номер карты, повторите попытку снова");
                    Sleep(3000);
                }
                else
                {
                    printf("Введите пароль: ");scanf("%s",passhold);
                    short cond=streq(passhold,currUser.pass);
                    
                    if(cond==0)
                    {
                        /*system("cls");*/
                        printf("Неверный пароль, повторите попытку снова");
                        Sleep(3000);
                    }
                    else
                    {
                        
                        // if(err = find_user_point(users,currUser.login)!=0)
                        // {
                        //     /*system("cls");*/
                        //     printf("Ошибка записи данных. Код ошибки: %d", err);
                        //     Sleep(3000);
                        //     return err;           
                        // }
                        currUser.card=cardtemp;
                        save_user_base(all_users, users);
                        fclose(users);
                        
                        printf("\nУспешная смена карты!");
                        Sleep(3000);
                    }
                }
                break;
            
            case 4: //смена имени
                /*system("cls");*/
                char namehold[21];
                printf("Введите новое имя: ");scanf("%s",namehold);
                if(!(3<=strlen(namehold)<=20))
                {
                    /*system("cls");*/
                    printf("Неверно введено имя, повторите попытку снова");
                    Sleep(3000);
                }
                else
                {
                    printf("Введите пароль: ");scanf("%s",passhold);
                    int cond=streq(passhold,currUser.pass);

                    if(cond==0)
                    {
                        /*system("cls");*/
                        printf("Неверный пароль, повторите попытку снова");
                        Sleep(3000);
                    }
                    else
                    {
                        

                        // if(err = find_user_point(users,currUser.login)!=0)
                        // {
                        //     /*system("cls");*/
                        //     printf("Ошибка записи данных. Код ошибки: %d", err);
                        //     Sleep(3000);
                        //     return err;           
                        // }
                        for(int i = 0; i<strlen(namehold);i++)
                        {
                            currUser.login[i]=namehold[i];
                            currUser.login[i+1]='\0';
                        }
                        save_user_base(all_users, users);
                        fclose(users);
                        
                        printf("\nУспешная смена имени!");
                        Sleep(3000);
                    }
                }
                break;

            case 5: //смена пароля
                /*system("cls");*/
                printf("Введите старый пароль: ");scanf("%s",passhold);
                short cond=streq(passhold,currUser.pass);
                if(cond==0)
                {
                    /*system("cls");*/
                    printf("Неверный старый пароль, повторите попытку снова");
                    Sleep(3000);
                }
                else
                {
                    printf("\nВведите новый пароль (не более 20 символов): ");
                    scanf("%s",passhold1);
                    if(strlen(passhold1)>20)
                    {
                        /*system("cls");*/
                        printf("Неверно набранная строка, повторите попытку снова");
                        Sleep(3000);
                    }
                    else
                    {


                        // if(err = find_user_point(users,currUser.login)!=0)
                        // {
                        //     /*system("cls");*/
                        //     printf("Ошибка записи данных. Код ошибки: %d", err);
                        //     Sleep(3000);
                        //     return err;           
                        // }
                        for(int i = 0; i<strlen(passhold1);i++)
                        {
                            currUser.pass[i]=passhold1[i];
                            currUser.pass[i+1]='\0';
                        }
                        save_user_base(all_users, users);
                        fclose(users);
                        
                        printf("\nУдачная смена пароля!");
                        Sleep(3000);
                    }
                }
                break;

            case 6:
                currWindow = 2;
                break;

            default:
                /*system("cls");*/
                printf("Неверное значение!");
                Sleep(500);
                break;
            }
        }

        // Добавление фильма в каталог
        if (currWindow == 6)
        {
            
        }
    }

    system("pause");
}