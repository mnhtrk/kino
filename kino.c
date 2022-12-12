#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
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

void printElem(int count, char elem)
{
    for (int i = 0; i < count; i++)
    {
        printf("%c", elem);
    }
}

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

struct film scanfFilm(FILE* films)
{
    struct film f;
    fgets(f.name, 100, films);
    f.name[strcspn(f.name, "\n")] = 0;
    fgets(f.year, 100, films);
    f.year[strcspn(f.year, "\n")] = 0;
    fgets(f.country, 100, films);
    f.country[strcspn(f.country, "\n")] = 0;
    fgets(f.genre, 100, films);
    f.genre[strcspn(f.genre, "\n")] = 0;
    fgets(f.rating, 100, films);
    f.rating[strcspn(f.rating, "\n")] = 0;
    return f;
}

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    FILE* films = fopen("C:\\Users\\Ilya\\Desktop\\ch\\proga\\kino\\films.txt", "r");
    struct film f1, f2;
    f1 = scanfFilm(films);
    f2 = scanfFilm(films);

    struct list library;
    library.head = (struct node*) malloc(sizeof(struct node));
    library.tail = (struct node*) malloc(sizeof(struct node));
    library.tail->next = library.head;
    library.tail->prev = library.head;
    library.head->prev = library.tail;
    library.head->next = library.tail;
    library.head->film = f1;
    library.tail->film = f2;
    int libraryCurr = 0;

    struct film f; 
    while(fgets(f.name, 100, films) != NULL)
    {
        f.name[strcspn(f.name, "\n")] = 0;
        fgets(f.year, 100, films);
        f.year[strcspn(f.year, "\n")] = 0;
        fgets(f.country, 100, films);
        f.country[strcspn(f.country, "\n")] = 0;
        fgets(f.genre, 100, films);
        f.genre[strcspn(f.genre, "\n")] = 0;
        fgets(f.rating, 100, films);
        f.rating[strcspn(f.rating, "\n")] = 0;
        push(&library, f);
    }
    fclose(films);

    int currWindow = 0;
    while(TRUE)
    {
        // Окно входа в систему
        if (currWindow == 0)
        {
            
        }

        // Окно регистрации
        if (currWindow == 1)
        {

        }

        // Каталог
        if (currWindow == 2)
        {
            if (GetAsyncKeyState(VK_RIGHT) != 0)
            {
                libraryCurr++;
                system("cls");
                Sleep(200);
                printCards(library, libraryCurr);
            }
            if (GetAsyncKeyState(VK_LEFT) != 0)
            {
                libraryCurr--;
                system("cls");
                Sleep(200);
                printCards(library, libraryCurr);
            }
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

        }

        // Добавление фильма в каталог
        if (currWindow == 6)
        {
            
        }
    }

    system("pause");
}