#include <locale.h>
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX 50

typedef struct
{
    char title[100];
    char date[20];
    int hour;
    int minute;
    int duration;
    char genre[50];
    double budget;
} CinemaSession;

void inputSessions(CinemaSession sessions[], int n);
void printSessions(const CinemaSession sessions[], int n);
int writefile(const char *fname, const CinemaSession sessions[], int n);

int main(void)
{
    setlocale(LC_ALL, "Russian");
    CinemaSession sessions[MAX];
    int n;
    printf("Программа учета киносеансов\n\n");

    printf("Введите количество киносеансов: ");
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX)
    {
        printf("Ошибка ввода количества\n");
        return 1;
    }

    inputSessions(sessions, n);

    printSessions(sessions, n);

    if (writefile("sessions.txt", sessions, n))
    {
        printf("\nДанные записаны в файл sessions.txt\n");
    }
    else
    {
        printf("\nОшибка записи файла\n");
    }
    return 0;
}

void inputSessions(CinemaSession sessions[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("\nКиносеанс %d\n", i + 1);
        printf("Название фильма: ");
        scanf(" %99[^\n]", sessions[i].title);
        printf("Дата (ДД.ММ.ГГГГ): ");
        scanf("%19s", sessions[i].date);
        printf("Время (ЧЧ:ММ): ");
        scanf("%d:%d", &sessions[i].hour, &sessions[i].minute);
        printf("Продолжительность в минутах: ");
        scanf("%d", &sessions[i].duration);
        printf("Жанр: ");
        scanf(" %49[^\n]", sessions[i].genre);
        printf("Бюджет: ");
        scanf("%lf", &sessions[i].budget);
    }
}

void printSessions(const CinemaSession sessions[], int n)
{
    int found = 0;
    printf("\nПодходящие киносеансы:\n");
    for (int i = 0; i < n; i++)
    {
        if ((sessions[i].hour > 18 ||
            (sessions[i].hour == 18 && sessions[i].minute > 0)) &&
            sessions[i].duration > 100)
        {
            printf("\nНазвание: %s\n", sessions[i].title);
            printf("Дата: %s\n", sessions[i].date);
            printf("Время: %02d:%02d\n", sessions[i].hour, sessions[i].minute);
            printf("Продолжительность: %d минут\n", sessions[i].duration);
            printf("Жанр: %s\n", sessions[i].genre);
            printf("Бюджет: %.2f\n", sessions[i].budget);
            found++;
        }
    }

    if (found == 0)
    {
        printf("Подходящие фильмы не найдены\n");
    }
}

int writefile(const char *fname, const CinemaSession sessions[], int n)
{
    FILE *file = fopen(fname, "w");
    if (file == NULL)
    {
        return 0;
    }
    for (int i = 0; i < n; i++)
    {
        fprintf(file, "%s %s %02d:%02d %d %s %.2f\n",
            sessions[i].title,
            sessions[i].date,
            sessions[i].hour,
            sessions[i].minute,
            sessions[i].duration,
            sessions[i].genre,
            sessions[i].budget);
    }
    if (fclose(file) != 0)
    {
        return 0;
    }
    return 1;
}
