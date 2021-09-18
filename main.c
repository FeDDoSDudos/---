/*
 * Фролов Фёдор Александрович
 * ИВТ-Б-01-Д-2020-1
 */
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define GOODS_SIZE 64
#define CLIENT_SIZE 64
#define ORDER_SIZE 64

int Goods_quantity;   // Переменная для кол-ва товаров
int Clients_quantity; // Переменная для кол-ва пользователей
int Order_quantity;   // Переменная для кол-ва закозов

// Структура для товаров
struct Goods
{
	char *type;
	int price;
	char *comp;
	char *characteristics;
	int quantity;
	struct Goods *next;
};
// Структура для клиентов
struct Client
{
  char *FN;
  char *LN;
  char *PNum;
  char *Email;
  struct Order *o;
  int o_quantity;
  struct Client *next;
};
// Структура для времени
struct Date
{
  int day;
  int month;
  int year;
  int hour;
  int minute;
};
// Структура для заказов
struct Order
{
  struct Date *date;
  struct Client *c;
  struct Goods *g;
  int quantity;
  char *deliveryPlace;
  struct Date *deliveryDate;
  char *status;
  struct Order *next;
};

// Функции ∨∨∨∨∨∨∨

int checkDis();
int exitP(int exit);
void bubbleSort(struct Goods *g);

void goodsInfo(struct Goods *g);
void goodsAdd(struct Goods *g);
void clientsInfo(struct Client *c, struct Order *o, struct Goods *g);
void clientsAssDel(struct Client *c);
void clientsEdit(struct Client *c);
void orderMake(struct Order *o, struct Client *c, struct Goods *g);
void orderCheck(struct Order *o, struct Client *c, struct Goods *g);
void goodsSort(struct Goods *g);
void workFile(struct Goods *g);
// Функции ^^^^^^^^^

// Функция для выбора варианта
char option()
{
  char inquiry[2];
  printf("\nВаш запрос: ");
  scanf("%1s", inquiry);
  return inquiry[0];
}

// Функция для проверки выхода
int exitP(int exit)
{ 
  printf("\nВы хотите выйти? [y/n] ");
  return checkDis(exit);
}
// Функция для проверки выбора выхода
int checkDis()
{ 
  switch(option())
  {
    case 'Y': case 'y':
      return 0;
      break;
    case 'N': case 'n':
      return 1;
      break;
    default:
      printf("\nНет такой команды.\n");
      return checkDis();
      break;
  }
}
// Функция для получение информации о товаре
void goodsInfo(struct Goods *g)
{
  int exit = 1;
  do
  {
    printf("\nCписок товаров:\n");
    if(g->type == NULL)
      printf("Пусто\n");
    else
      for(int i = 0; i < Goods_quantity; i++)
        printf("%d. %s.\n", i+1 , (g+i)->type);
    printf("\n1)Узнать подробнее\n0)Назад\n");
    switch(option())
    {
      case '1':
        printf("\nВыберете товар (укажите число по списку): ");
        int choice;
        scanf("%d", &choice);
        if(Goods_quantity == 0 || choice <= 0 || choice > Goods_quantity)
        {
          printf("Товаров нет или введено неправильное значение\n");
        }
        else
        {
          choice--;
          printf("Товар: %s\n", (g+choice)->type);
          printf("Цена: %d\n", (g+choice)->price);
          printf("Компания: %s\n", (g+choice)->comp);
          printf("Характеристики: %s\n", (g+choice)->characteristics);
          if((g+choice)->quantity == 0)
            printf("Нет в наличии\n");
          else
            printf("Количество: %d\n", (g+choice)->quantity);
        }
        break;
      case '0':
        exit = 0;
        break;
      default:
        exit = exitP(exit);
        break;
    }
  }while(exit);
}
// Функция для добавления и редактирования товаров
void goodsAdd(struct Goods *g)
{
  int exit = 1;
  do
  {
    printf("\n1)Добавить товар\n2)Редактировать товар\n0)Назад\n");
    switch (option())
    {
      case '1':
        printf("\nТовар: ");
        (g+Goods_quantity)->type = (char *)malloc(GOODS_SIZE * sizeof(char *));
        scanf(" %[^\n]s", (g+Goods_quantity)->type);
        do
        {
          printf("Цена: ");
          int buf;
          scanf("%d", &buf);
          if(buf < 0)
            printf("\nОшибка\n");
          else
          {
            (g+Goods_quantity)->price = buf;
            break;
          }
        }while(1);
        printf("Компания: ");
        (g+Goods_quantity)->comp = (char *)malloc(GOODS_SIZE * sizeof(char *));
        scanf(" %[^\n]s", (g+Goods_quantity)->comp);
        printf("Характеристики: ");
        (g+Goods_quantity)->characteristics = (char *)malloc(GOODS_SIZE * sizeof(char *));
        scanf(" %[^\n]s", (g+Goods_quantity)->characteristics);
        do
        {
          printf("Количество: ");
          int buf;
          scanf("%d", &buf);
          if(buf < 0)
            printf("\nОшибка\n");
          else
          {
            (g+Goods_quantity)->quantity = buf;
            break;
          }
        }while(1);
        Goods_quantity++;
        break;
      case '2':
        printf("\nCписок товаров:\n");
        if(g->type == NULL)
          printf("Пусто\n");
        else
        {
          for(int i = 0; i < (int) Goods_quantity; i++)
            printf("%d. %s.\n", i+1 , (g+i)->type);
          printf("\nВыберете товар, который хотите изменить (укажите число по списку): ");
          int choice;
          scanf("%d", &choice);
          if(Goods_quantity == 0 || choice <= 0 || choice > Goods_quantity)
          {
            printf("Товаров нет или введено неправильное значение\n");
          }
          else
          {
            choice--;
            printf("\nТовар: ");
            scanf(" %[^\n]s", (g+choice)->type);
            do
            {
              printf("Цена: ");
              int buf;
              scanf("%d", &buf);
              if(buf < 0)
                printf("\nОшибка\n");
              else
              {
                (g+Goods_quantity)->price = buf;
                break;
              }
            }while(1);
            printf("Компания: ");
            scanf(" %[^\n]s", (g+choice)->comp);
            printf("Характеристики: ");
            scanf(" %[^\n]s", (g+choice)->characteristics);
            do
            {
              printf("Количество: ");
              int buf;
              scanf("%d", &buf);
              if(buf < 0)
                printf("\nОшибка\n");
              else
              {
                (g+choice)->quantity = buf;
                break;
              }
            }while(1);
          }
        }
        break;
      case '0':
        exit = 0;
        break;
      default:
        exit = exitP(exit);
        break;
    }
  }while(exit);
}
// Функция для получения информации о пользователях
void clientsInfo(struct Client *c, struct Order *o, struct Goods *g)
{
  int exit = 1;
  do
  {
    printf("\nCписок пользователей:\n");
    if(c->FN == NULL || c->LN == NULL)
      printf("Пусто\n");
    else
      for(int i = 0; i < Clients_quantity; i++)
        printf("%d. %s %s.\n", i+1, (c+i)->FN, (c+i)->LN);
    printf("\n1)Узнать подробнее\n0)Назад\n");
    switch(option())
    {
      case '1':
        
        printf("\nВыберете пользователя (укажите число по списку): ");
        int choice;
        scanf("%d", &choice);
        if(Clients_quantity == 0 || choice <= 0 || choice > Clients_quantity)
        {
          printf("Пользователей нет или введено неправильное значение\n");
        }
        else
        {
          choice--;
          printf("Имя: %s\n", (c+choice)->FN);
          printf("Фамалия: %s\n", (c+choice)->LN);
          printf("Номер телефона: %s\n", (c+choice)->PNum);
          printf("E-mail: %s\n", (c+choice)->Email);
          printf("Заказы:\n");
          if((c+choice)->o_quantity == 0)
            printf("Нет заказов\n");
          else
            for(int i = 0; i < (c+choice)->o_quantity; i++)
            {
              printf("%d. %d/%d/%d %d:%d '%s'-%d (%s %s) %s %d/%d/%d %d:%d Статус: %s\n", i+1, (o+i)->date->day, (o+i)->date->month, (o+i)->date->year, (o+i)->date->hour, (o+i)->date->minute, (o+i)->g->type, (o+i)->quantity, (o+i)->c->FN, (o+i)->c->LN, (o+i)->deliveryPlace, (o+i)->deliveryDate->day, (o+i)->deliveryDate->month, (o+i)->deliveryDate->year, (o+i)->deliveryDate->hour, (o+i)->deliveryDate->minute, (o+i)->status);
            }
        }
        break;
      case '0':
        exit = 0;
        break;
      default:
        exit = exitP(exit);
        break;
    }
  }while(exit);
}
// Функция для добавления и удаления пользователя
void clientsAssDel(struct Client *c)
{
  int exit = 1;
  do
  {
    printf("\n1)Добавить пользователя\n2)Удалить пользователя\n0)Назад\n");
    switch(option())
    {
      case '1':
        printf("Имя: ");
        (c+Clients_quantity)->FN = (char *)malloc(CLIENT_SIZE * sizeof(char *));
        scanf(" %[^\n]s", (c+Clients_quantity)->FN);
        printf("Фамилия: ");
        (c+Clients_quantity)->LN = (char *)malloc(CLIENT_SIZE * sizeof(char *));
        scanf(" %[^\n]s", (c+Clients_quantity)->LN);
        printf("Номер телефона: ");
        (c+Clients_quantity)->PNum = (char *)malloc(CLIENT_SIZE * sizeof(char *));
        scanf(" %[^\n]s", (c+Clients_quantity)->PNum);
        printf("E-mail: ");
        (c+Clients_quantity)->Email = (char *)malloc(CLIENT_SIZE * sizeof(char *));
        scanf(" %[^\n]s", (c+Clients_quantity)->Email);
        Clients_quantity++;
        break;
      case '2':
        printf("\nCписок пользователей:\n");
        if(c->FN == NULL || c->LN == NULL)
          printf("Пусто\n");
        else
          for(int i = 0; i < Clients_quantity; i++)
            printf("%d. %s %s.\n", i+1, (c+i)->FN, (c+i)->LN);
        printf("\nВыберете пользователя (укажите число по списку): ");
        int choice;
        scanf("%d", &choice);
        if(Clients_quantity == 0 || choice <= 0 || choice > Clients_quantity)
        {
          printf("Пользователей нет или введено неправильное значение\n");
        }
        else
        {
          choice--;
          for(int i = choice; i < Clients_quantity-1; i++)
          {
            *(c+i) = *(c+(i+1));
          }
          Clients_quantity--;
        }
        break;
      case '0':
        exit = 0;
        break;
      default:
        exit = exitP(exit);
        break;
    }
  }while(exit);
}
// Функция для редактирования данных о пользователе
void clientsEdit(struct Client *c)
{
  int exit = 1;
  do
  {
    printf("\n1)Редактировать данные пользователя\n0)Назад\n");
    switch(option())
    {
      case '1':
        printf("\nCписок пользователей:\n");
        if(c->FN == NULL || c->LN == NULL)
          printf("Пусто\n");
        else
          for(int i = 0; i < Clients_quantity; i++)
            printf("%d. %s %s.\n", i+1, (c+i)->FN, (c+i)->LN);
        printf("\nВыберете пользователя (укажите число по списку): ");
        int choice;
        scanf("%d", &choice);
        if(Clients_quantity == 0 || choice <= 0 || choice > Clients_quantity)
        {
          printf("\nПользователей нет или введено неправильное значение\n");
        }
        else
        {
          choice--;
          printf("Имя: ");
          scanf(" %[^\n]s", (c+choice)->FN);
          printf("Фамилия: ");
          scanf(" %[^\n]s", (c+choice)->LN);
          printf("Номер телефона: ");
          scanf(" %[^\n]s", (c+choice)->PNum);
          printf("E-mail: ");
          scanf(" %[^\n]s", (c+choice)->Email);
        }
        break;
      case '0':
        exit = 0;
        break;
      default:
        exit = exitP(exit);
        break;
    }
  }while(exit);
}
// Функция для создания заказа
void orderMake(struct Order *o, struct Client *c, struct Goods *g)
{
  int exit = 1;
  do
  {
    printf("\n1)Сделать заказ\n0)Назад\n");
    switch(option())
    {
      case '1':
        printf("\nCписок пользователей:\n");
        if(c->FN == NULL || c->LN == NULL)
          printf("Пусто\n");
        else
          for(int i = 0; i < Clients_quantity; i++)
            printf("%d. %s %s.\n", i+1, (c+i)->FN, (c+i)->LN);
        printf("\nВыберете пользователя (укажите число по списку): ");
        int choice1;
        scanf("%d", &choice1);
        if(Clients_quantity == 0 || choice1 <= 0 || choice1 > Clients_quantity)
        {
          printf("\nПользователей нет или введено неправильное значение\n");
        }
        else
        {
          choice1--;
          (c+choice1)->o = o;
          (o+Order_quantity)->date = (struct Date *)malloc(ORDER_SIZE * sizeof(struct Date *));
          do
            {
              int dayBuf, monthBuf, yearBuf, hourBuf, minuteBuf;
              printf("\nДата заказа (день месяц год часы минтуы): ");
              scanf("%d", &dayBuf);
              scanf(" %d", &monthBuf);
              scanf(" %d", &yearBuf);
              scanf(" %d", &hourBuf);
              scanf(" %d", &minuteBuf);
              if(!(dayBuf > 0 && dayBuf < 30))
                printf("\nДень указан неправильно %d\n", dayBuf);
              else if(!(monthBuf > 0 && monthBuf < 12))
                printf("\nМесяц указан неправильно\n");
              else if(!(yearBuf > 1990))
                printf("\nГод указан неправильно\n");
              else if(!(hourBuf > 0 && hourBuf < 23))
                printf("\nЧасы указаны неправильно\n");
              else if(!(minuteBuf > 0 && minuteBuf < 59))
                printf("\nМинуты указаны неправильно\n");
              else
              {
                (o+Order_quantity)->date->day = dayBuf;
                (o+Order_quantity)->date->month = monthBuf;
                (o+Order_quantity)->date->year = yearBuf;
                (o+Order_quantity)->date->hour = hourBuf;
                (o+Order_quantity)->date->minute = minuteBuf;
                break;
              }
          }while(1);
          (o+Order_quantity)->c = (c+choice1);
          printf("\nСписок товаров:\n");
          if(g->type == NULL)
              printf("\nПусто\n");
            else
              for(int i = 0; i < Goods_quantity; i++)
                printf("%d. %s.\n", i+1 , (g+i)->type);
            
          printf("\nВыберете товар (укажите число по списку): ");
          int choice2;
          scanf("%d", &choice2);
          if(Goods_quantity == 0 || choice2 <= 0 || choice2 > Goods_quantity || (g+choice2-1)->quantity == 0)
          {
            printf("\nТоваров нет или введено неправильное значение\n");
            break;
          }
          else
          {
            choice2--;
            (o+Order_quantity)->g = (g+choice2);
            do
            {
              int buf;
              printf("\nКоличество: ");
              scanf("%d", &buf);
              if(buf <= 0 || (g+choice1)->quantity-buf < 0)
                printf("\nСтолько нет\n");
              else
              {
                (o+Order_quantity)->quantity = buf;
                (g+choice1)->quantity -= buf;
                break;
              }
            }while(1);
            printf("\nМесто доставки: ");
            (o+Order_quantity)->deliveryPlace = (char *)malloc(ORDER_SIZE * sizeof(char *));
            scanf(" %[^\n]s", (o+Order_quantity)->deliveryPlace);
            (o+Order_quantity)->deliveryDate = (struct Date *)malloc(ORDER_SIZE * sizeof(struct Date *));
            do
            {
              printf("\nДата доставки (день месяц год часы минтуы): ");
              int dayBuf, monthBuf, yearBuf, hourBuf, minuteBuf;
              scanf("%d", &dayBuf);
              scanf(" %d", &monthBuf);
              scanf(" %d", &yearBuf);
              scanf(" %d", &hourBuf);
              scanf(" %d", &minuteBuf);
              if(!(dayBuf > 0 && dayBuf < 30))
                printf("\nДень указан неправильно %d\n", dayBuf);
              else if(!(monthBuf > 0 && monthBuf < 12))
                printf("\nМесяц указан неправильно %d\n", monthBuf);
              else if(!(yearBuf > 1990))
                printf("\nГод указан неправильно %d\n", yearBuf);
              else if(!(hourBuf > 0 && hourBuf < 23))
                printf("\nЧасы указаны неправильно %d\n", hourBuf);
              else if(!(minuteBuf > 0 && minuteBuf < 59))
                printf("\nМинуты указаны неправильно %d\n", minuteBuf);
              else
              {
                (o+Order_quantity)->deliveryDate->day = dayBuf;
                (o+Order_quantity)->deliveryDate->month = monthBuf;
                (o+Order_quantity)->deliveryDate->year = yearBuf;
                (o+Order_quantity)->deliveryDate->hour = hourBuf;
                (o+Order_quantity)->deliveryDate->minute = minuteBuf;
                break;
              }
            }while(1);
            printf("\nСтатус заказа: ");
            (o+Order_quantity)->status = (char *)malloc(ORDER_SIZE * sizeof(char *));
            scanf(" %[^\n]s", (o+Order_quantity)->status);
            Order_quantity++;
            (c+choice1)->o_quantity++;
          }
        }
        break;
      case '0':
        exit = 0;
        break;
      default:
        exit = exitP(exit);
        break;
    }
  }while(exit);
}
// Функция для проверки заказов
void orderCheck(struct Order *o, struct Client *c, struct Goods *g)
{
  int exit = 1;
  do
  {
    printf("\n1)Посмотреть заказы\n0)Назад\n");
    switch(option())
    {
      case '1':
        for(int i = 0; i < Order_quantity; i++)
        {
          printf("%d. Дата зака-%d/%d/%d %d:%d Товар'%s'-%d Заказчик-%s %s Место доставки-%s Дата доставки-%d/%d/%d %d:%d Статус-%s\n", i+1, (o+i)->date->day, (o+i)->date->month, (o+i)->date->year, (o+i)->date->hour, (o+i)->date->minute, (o+i)->g->type, (o+i)->quantity, (o+i)->c->FN, (o+i)->c->LN, (o+i)->deliveryPlace, (o+i)->deliveryDate->day, (o+i)->deliveryDate->month, (o+i)->deliveryDate->year, (o+i)->deliveryDate->hour, (o+i)->deliveryDate->minute, (o+i)->status);
        }
        break;
      case '0':
        exit = 0;
        break;
      default:
        exit = exitP(exit);
        break;
    }
  }while(exit);
}
void bubbleSort(struct Goods *g)
{
  char *buf;
  int buf_i;
  for(int i = 0; i < Goods_quantity - 1; i++)
  {
    for(int j = i + 1; j < Goods_quantity; j++)
    {
      if(strcmp((g+i)->type, (g+j)->type) > 0)
      { 
        buf = (g+i)->type;
        (g+i)->type = (g+j)->type;
        (g+j)->type = buf;
        buf = (g+i)->comp;
        (g+i)->comp = (g+j)->comp;
        (g+j)->comp = buf;
        buf = (g+i)->characteristics;
        (g+i)->characteristics = (g+j)->characteristics;
        (g+j)->characteristics = buf;
        buf_i = (g+i)->price;
        (g+i)->price = (g+j)->price;
        (g+j)->price = buf_i;
        buf_i = (g+i)->quantity;
        (g+i)->quantity = (g+j)->quantity;
        (g+j)->quantity = buf_i;
      }
    }
  }
}

// Функция для сортирвки данных
void goodsSort(struct Goods *g)
{
  int exit = 1;
  do
  {
    printf("\nCписок товаров:\n");
      if(g->type == NULL)
        printf("Пусто\n");  
      else
        for(int i = 0; i < Goods_quantity; i++)
          printf("%d. %s.\n", i+1 , (g+i)->type);
    printf("\n1)Отсортировать\n0)Назад\n");
    switch(option())
    {
      case '1':
        bubbleSort(g);
        break;
      case '0':
        exit = 0;
        break;
      default:
        exit = exitP(exit);
        break;
    }
  }while(exit);
}
// Функция для работы с файлами
void workFile(struct Goods *g)
{
  int exit = 1;
  do
  {
    bubbleSort(g);
    printf("\n1)Файл с данными  по одному элементу списка\n2)Добавления информации из созданного файла\n3)Вывод дополненного списка в файл\n0)Назад\n");
    switch(option())
    {
      case '1':
        if(g->type == NULL)
          printf("Товаров нет\n");  
        else
        {
          int choice = 0;
          printf("\nСписок курсов: \n");
          if(g->type == NULL)
            printf("Пусто\n");  
          else
            for(int i = 0; i < Goods_quantity; i++)
              printf("%d. %s.\n", i+1 , (g+i)->type);
          printf("\nВведите номер: ");
          scanf(" %d", &choice);
          if(Goods_quantity == 0 || choice <= 0 || choice > Goods_quantity)
          {
            printf("Товаров нет или введено неправильное значение\n");
          }
          else
          {
            choice--;
            char a[32];
            printf("\nВведите название файла: ");
            scanf(" %s", a);
            FILE * file1 = fopen(a, "w+");
            if (file1 == NULL)
            {
              printf("Ошибка при открытия файла\n");
              break;
            }
            printf("Товар: %s\n", (g+choice)->type);
            fprintf(file1, "Товар: %s\n", (g+choice)->type);
            printf("Цена: %d\n", (g+choice)->price);
            fprintf(file1, "Цена: %d\n", (g+choice)->price);
            printf("Компания: %s\n", (g+choice)->comp);
            fprintf(file1, "Компания: %s\n", (g+choice)->comp);
            printf("Характеристики: %s\n", (g+choice)->characteristics);
            fprintf(file1, "Характеристики: %s\n", (g+choice)->characteristics);
            printf("Количество: %d\n", (g+choice)->quantity);
            fprintf(file1, "Количество: %d\n", (g+choice)->quantity);
            fclose(file1);
          }
        }
        bubbleSort(g);
        break;
      case '2':
        if(1)
        {
          int i = 0, j = 0;
          char a[32];
          char *name = (char *)malloc(GOODS_SIZE * sizeof(char *));
          char *price1 = (char *)malloc(GOODS_SIZE * sizeof(char *));
          char *comp = (char *)malloc(GOODS_SIZE * sizeof(char *));
          char *ch = (char *)malloc(GOODS_SIZE * sizeof(char *));
          char *quant1 = (char *)malloc(GOODS_SIZE * sizeof(char *));
          char *buf = (char *)malloc(4 * GOODS_SIZE * sizeof(char *));
          int price2 = 0;
          int quant2 = 0;
          printf("\nВведите название файла: ");
          scanf("%s", a);
          FILE * file1 = fopen(a, "r");
          if (file1 == NULL)
          {
            printf("Ошибка при открытия файла\n");
            break;
          }
          while(!feof(file1))
          {
            fscanf(file1, "%c", &buf[i]);
            i++;
          }
          i = 0;
          while(buf[i] != '/')
          {
            name[j] = buf[i];
            i++;
            j++;
          }
          i++;
          j = 0;
          while(buf[i] != '/')
          {
            price1[j] = buf[i];
            i++;
            j++;
          }
          price2 = atoi(price1);
          i++;
          j = 0;
          while(buf[i] != '/')
          {
            comp[j] = buf[i];
            i++;
            j++;
          }
          i++;
          j = 0;
          while(buf[i] != '/')
          {
            ch[j] = buf[i];
            i++;
            j++;
          }
          i++;
          j = 0;
          while(buf[i] != '\n')
          {
            quant1[j] = buf[i];
            i++;
            j++;
          }
          quant2 = atoi(quant1);
          (g+Goods_quantity)->type = (char *)malloc(GOODS_SIZE * sizeof(char *));
          (g+Goods_quantity)->type = name;
          (g+Goods_quantity)->price = price2;
          (g+Goods_quantity)->comp = (char *)malloc(GOODS_SIZE * sizeof(char *));
          (g+Goods_quantity)->comp = comp;
          (g+Goods_quantity)->characteristics = (char *)malloc(GOODS_SIZE * sizeof(char *));
          (g+Goods_quantity)->characteristics = ch;
          (g+Goods_quantity)->quantity = quant2 ;
          Goods_quantity++;
          bubbleSort(g);
        }
        break;
      case '3':
        if(g->type == NULL)
          printf("Товаров нет\n");  
        else
        {
          printf("\nСписок курсов: \n");
          if(g->type == NULL)
            printf("Пусто\n");  
          else
            for(int i = 0; i < Goods_quantity; i++)
              printf("%d. %s.\n", i+1 , (g+i)->type);
          char a[32];
          printf("\nВведите название файла: ");
          scanf(" %s", a);
          FILE * file1 = fopen(a, "w+");
          if (file1 == NULL)
          {
            printf("Ошибка при открытия файла\n");
            break;
          }
          for(int choice = 0; choice  < Goods_quantity; choice++)
          {
            fprintf(file1, "Товар: %s\t", (g+choice)->type);
            fprintf(file1, "Цена: %d\t", (g+choice)->price);
            fprintf(file1, "Компания: %s\t", (g+choice)->comp);
            fprintf(file1, "Характеристики: %s\t", (g+choice)->characteristics);
            fprintf(file1, "Количество: %d\n", (g+choice)->quantity);
          } 
          fclose(file1);
        }
        bubbleSort(g);
        break;
      case '0':
        exit = 0;
        break;
      default:
        exit = exitP(exit);
        break;
    }
  }while(exit);
}
int main()
{
  int exit = 1;
  Goods_quantity = 0;
  Clients_quantity = 0;
  Order_quantity = 0;
  struct Goods *g = (struct Goods *)malloc(GOODS_SIZE * sizeof(struct Goods));
  struct Client *c = (struct Client *)malloc(CLIENT_SIZE * sizeof(struct Client));
  struct Order *o = (struct Order *)malloc(ORDER_SIZE * sizeof(struct Order));
  printf("\nFrolov Fyodor Alexandrovich\n");
  printf("\nЗдравствуйте! Что хотите сделать?\n");
  do
  {
    printf("\n1)Узнать о товаре\n2)Добавить/редактировать информацию о товаре\n3)Просмотреть данные о пользователе\n4)Добавить/удалить пользователя\n5)Редактировать данные пользователя\n6)Сделать заказ\n7)Проверить статус заказа\n8)Отсортировать товары\n9)Работа с файлами\n0)Выйти\n");
    switch(option())
    {
      case '1':
        goodsInfo(g);
        break;
      case '2':
        goodsAdd(g);
        break;
      case '3':
        clientsInfo(c, o, g);
        break;
      case '4':
        clientsAssDel(c);
        break;
      case '5':
        clientsEdit(c);
        break;
      case '6':
        orderMake(o, c, g);
        break;
      case '7':
        orderCheck(o, c, g);
        break;
      case '8':
        goodsSort(g);
        break;
      case '9':
        workFile(g);
        break;
      case '0':
        exit = exitP(exit);
        break;
      default:
        printf("Нет такой команды.\n");
        exit = exitP(exit);
        break;
    }
  }while(exit);
  return 0;
}
