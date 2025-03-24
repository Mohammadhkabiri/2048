#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define count 4      /*تعریف برای استفاده در تعداد بعد های ارایه*/
#define left 'L'     /*تعریف به عنوان حرکت به چپ*/
#define right 'R'    /*تعریف به عنوان حرکت به راست*/
#define up 'U'       /*تعریف به عنوان حرکت به بالا*/
#define down 'D'     /*تعریف به عنوان حرکت به پایین*/
#define quit 'Q'     /*تعریف به عنوان خروج از بازی*/
#define back 'B'     /*تعریف به عنوان یک مرحله برگشت به عقب*/
#define new_game 'N' /*تعریف به عنوان شروع دوباره */
#define star '*'     /*تعریف برای استفاده در صفحه پرینت بازی*/
#define dash '-'     /*تعریف برای استفاده در صفحه پرینت بازی و جداسازی مراحل*/
#define line '|'     /*تعریف برای استفاده در جداسازی اعداد در صفحه بازی*/

void print_Board(int table[count][count]);      /*تابع چاپ صفحه بازی*/
void add_Random(int table[count][count]);       /*تابع تولید عدد رندوم*/
void initialize_Board(int table[count][count]); /*تابع مقدار دهی اولیه بازی*/

int move_Left(int table[count][count]);  /*تابع حرکت اعداد به سمت چپ*/
int move_right(int table[count][count]); /*تابع حرکت به سمت راست*/
int move_down(int table[count][count]);  /*تابع حرکت به سمت پایین*/
int move_up(int table[count][count]);    /*تابع حرکت به سمت بالا*/
void Rotate(int table[count][count]);    /*تابع چرخش ۹۰ درجه ساعتگرد تابع*/
void Back(int table[count][count] , int copy_table[count][count]);/*تابع بازگشت*/

int calculate_Score(int table[count][count]); /*تابع محاسبه امتیاز*/
int check_win_Lose(int table[count][count]);

int main()
{
    int table[count][count];      /*آرایه دو بعدی بازی*/
    int copy_table[count][count]; /*آرایه برای نگهداری مقادیر آرایه قبل از تغییر */
    int status = 1;               /*متغیر بررسی شرایط ادامه بازی*/
    char Move = ' ';              /*متغیر حرکت*/

    srand(time(NULL)); /*استفاده از تابع برای استفاده در تولید عدد رندوم*/
    initialize_Board(table);
    print_Board(table);
    while (status)
    {

        scanf("\n%c", &Move); /*دریافت حرکت از کاربر*/
        if (Move == left || Move == right || Move == up || Move == down)
        {
            Back(copy_table, table);
        }
        switch (Move)
        {
        case left:
            if (move_Left(table)) /*شرط حرکت به چپ*/
            {
                add_Random(table);
                print_Board(table);
            }
            else
            {
                print_Board(table);
                printf("you can,t move left any more\n");
            }
            break;
        case right:
            if (move_right(table)) /*شرط حرکت به راست*/
            {
                add_Random(table);
                print_Board(table);
            }
            else
            {
                print_Board(table);
                printf("you cant,t move right any more\n");
            }
            break;
        case up:
            if (move_up(table)) /* شرط حرکت به بالا*/
            {
                add_Random(table);
                print_Board(table);
            }
            else
            {
                print_Board(table);
                printf("you can,t move up anymore\n");
            }
            break;
        case down:
            if (move_down(table)) /*شرط حرکت به پایین*/
            {
                add_Random(table);
                print_Board(table);
            }
            else
            {
                print_Board(table);
                printf("you can,t move down any more\n");
            }
            break;
        case quit:
            printf("bye\n");
            status = 0;
            break;
        case back:
            Back(table, copy_table);
            print_Board(table);
            break;
        case new_game:
            initialize_Board(table); /*مقدار دهی اولیه دوباره بازی*/
            print_Board(table);
            break;
        default:
            printf("invalid Move\n");
            break;
        }
        if (check_win_Lose(table) == 1) /*شرط برد بازی*/
        {
            printf("YOU WIN\n");
            status = 0; /* پایان بازی همراه با برد*/
        }
        else if (check_win_Lose(table) == -1) /*شرط باخت بازی*/
        {
            printf("Game Over\n");
            status = 0; /*پایان بازی*/
        }
    }
}

void print_Board(int table[count][count])
{
    for (int i = 0; i < 40; i++)
    {
        printf("%c", star);
    }
    printf("\n");

    printf("YOUR SCORE = %d\n", calculate_Score(table));
    for (int i = 0; i < 25; i++)
    {
        printf("%c", dash);
    }
    printf("\n");

    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            printf("%c", line);
            if (table[i][j] != 0) /* چاپ نکردن مقادیر برابر صفر*/
            {
                printf("%d", table[i][j]);
            }
            printf("\t");
        }
        printf("\n");
    }
    for (int i = 0; i < 25; i++)
    {
        printf("%c", dash);
    }
    printf("\n");
    printf("Move (L,R,U,D) or Quit ,Back ,New Start(Q , B , N) :\n");
}

void initialize_Board(int table[count][count])
{
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            table[i][j] = 0; /*مقدار دهی همه خانه های ارایه به صفر*/
        }
    }

    add_Random(table); /*قرار دادن مقدار رندوم بین ۲ و۴ در یکی از خانه های ارایه به صورت رندوم*/
    add_Random(table); /*قرار دادن مقدار رندوم بین ۲ و۴ در یکی از خانه های ارایه به صورت رندوم*/
}

void add_Random(int table[count][count])
{
    int random_i, random_j;
    do
    {
        random_i = rand() % count; /*به دست اوردن یک مقدار رندوم برای قرار دادن در ردیف های ارایه*/
        random_j = rand() % count; /*به دست اوردن یک مقدار رندوم برای قرار دادن در ستون های ارایه*/
    } while (table[random_i][random_j] != 0); /*ادامه به دست اوردن مقدار رندوم تا زمانی که به مقدار ۰ برای آن خانه برسد*/
    int random_Num = (rand() % 2) > 0 ? 4 : 2; /*تولید عدد رندوم بین ۲ و ۴*/
    table[random_i][random_j] = random_Num;    /*قرار دادن عدد رندوم تولید شده در یکی از خانه های ارایه*/
}

int move_Left(int table[count][count])
{
    int i, j;                     /*تعریف متغیر ها جهت استفاده در شمارنده حلقه ها*/
    int result = 0;               /*متغیر برای ذخیره خروجی تابع*/
    int copy_table[count][count]; /*تعریف ارایه برای ذخیره ارایه قبل از حرکت به چپ*/
    for (i = 0; i < count; i++)
    {
        for (j = 0; j < count; j++)
        {
            copy_table[i][j] = table[i][j];
        }
    }

    for (i = 0; i < count; i++)
    {
        int situation = 0; /*تعریف متغیر برای پیدا کردن مکان صحیح انتقال*/
        for (j = 0; j < count; j++)
        {
            if (table[i][j] != 0)
            {
                table[i][situation] = table[i][j]; /*مشخص کردن خانه صحیح برای انتقال عدد به سمت چپ*/
                situation++;
            }
        }
        for (j = situation; j < count; j++)
        {
            table[i][j] = 0; /*صفر کردن بقیه مقادیر قبلی بعد از انتقال به چپ*/
        }

        for (j = 0; j < count - 1; j++)
        {
            if (table[i][j] == table[i][j + 1] && table[i][j] != 0)
            {
                table[i][j] += table[i][j + 1]; /*جمع اعداد در صورت مساوی بودن*/
                table[i][j + 1] = 0;            /*صفر کردن عدد سمت راست بعد از محاسبه جمع*/
            }
        }

        situation = 0;
        for (j = 0; j < count; j++)
        {
            if (table[i][j] != 0)
            {
                table[i][situation] = table[i][j]; /*شیفت مجدد اعداد به جپ برای پر کردن فضا های خالی به وجود آمده بعد از جمع*/
                situation++;
            }
        }
        for (j = situation; j < count; j++)
        {
            table[i][j] = 0;
        }
    }

    for (i = 0; i < count; i++)
    {
        for (j = 0; j < count; j++)
        {
            if (table[i][j] != copy_table[i][j]) /*تغییر مقدار خروجی تابع در صورت برابر نبودن ارایه بعد از حرکت چپ و ارایه اولیه*/
            {
                result = 1;
            }
        }
    }
    return result;
}
int move_up(int table[count][count])
{

    int result = 0;
    Rotate(table);
    Rotate(table);
    Rotate(table);
    result = move_Left(table);
    Rotate(table);
    return result;
}
int move_down(int table[count][count])
{
    int result = 0;
    Rotate(table);
    result = move_Left(table);
    Rotate(table);
    Rotate(table);
    Rotate(table);
    return result;
}
int move_right(int table[count][count])
{
    int result = 0;
    Rotate(table);
    Rotate(table);
    result = move_Left(table);
    Rotate(table);
    Rotate(table);
    return result;
}
void Rotate(int table[count][count])
{
    int rotate_table[count][count]; /*تعریف ارایه جدید برای ذخیره تغییرات اعمال شده پس از چرخش ۹۰ درجه ساعتگرد*/
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            rotate_table[j][count - i - 1] = table[i][j];
        }
    }

    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            table[i][j] = rotate_table[i][j]; /*مساوی قرار دادن تابع بعد از چرخش با تابع اولیه*/
        }
    }
}

void Back(int copy_table[count][count], int table[count][count])
{
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            copy_table[i][j] = table[i][j];
        }
    }
}
int calculate_Score(int table[count][count])
{

    int sum = 0; /*متغیر برای به دست اوردن مجموع اعداد موجود در خانه ها*/
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            sum += table[i][j];
        }
    }
    return sum;
}

int check_win_Lose(int table[count][count])
{
    int copy_table[count][count]; /*تعریف ارایه جدید برای مساوی قرار داده شدن با ارایه اصلی و اعمال تغییرات*/
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            copy_table[i][j] = table[i][j];
        }
    }
    if (move_down(copy_table) == 0 && move_Left(copy_table) == 0 && move_right(copy_table) == 0 && move_up(copy_table) == 0) /*شرط باخت بازی*/
    {
        return -1;
    }
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            if (table[i][j] == 2048) /*شرط برد بازی*/
            {
                return 1;
            }
        }
    }
    return 0; /*خروجی تابع در صورت عدم برد یا باخت و ادامه بازی*/
}
