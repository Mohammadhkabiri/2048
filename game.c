#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define count 4
#define left 'L'
#define right 'R'
#define up 'U'
#define down 'D'
#define quit 'Q'
#define back 'B'
#define new_game 'N'
#define star '*'
#define dash '-'
#define line '|'

void print_Board(int table[count][count]);
void add_Random(int table[count][count]);
void initialize_Board(int table[count][count]);

int move_Left(int table[count][count]);
int move_right(int table[count][count]);
int move_down(int table[count][count]);
int move_up(int table[count][count]);
void Rotate(int table[count][count]);
void Back(int table[count][count], int copy_table[count][count]);

int calculate_Score(int table[count][count]);
int check_win_Lose(int table[count][count]);

int main()
{
    int table[count][count];
    int copy_table[count][count];
    int status = 1;
    char Move = ' ';

    srand(time(NULL));
    initialize_Board(table);
    print_Board(table);
    
    while (status)
    {
        scanf("\n%c", &Move);
        if (Move == left || Move == right || Move == up || Move == down)
        {
            Back(copy_table, table);
        }

        switch (Move)
        {
        case left:
            if (move_Left(table))
            {
                add_Random(table);
                print_Board(table);
            }
            else
            {
                print_Board(table);
                printf("you can't move left any more\n");
            }
            break;
        case right:
            if (move_right(table))
            {
                add_Random(table);
                print_Board(table);
            }
            else
            {
                print_Board(table);
                printf("you can't move right any more\n");
            }
            break;
        case up:
            if (move_up(table))
            {
                add_Random(table);
                print_Board(table);
            }
            else
            {
                print_Board(table);
                printf("you can't move up anymore\n");
            }
            break;
        case down:
            if (move_down(table))
            {
                add_Random(table);
                print_Board(table);
            }
            else
            {
                print_Board(table);
                printf("you can't move down any more\n");
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
            initialize_Board(table);
            print_Board(table);
            break;
        default:
            printf("invalid Move\n");
            break;
        }

        if (check_win_Lose(table) == 1)
        {
            printf("YOU WIN\n");
            status = 0;
        }
        else if (check_win_Lose(table) == -1)
        {
            printf("Game Over\n");
            status = 0;
        }
    }
    return 0;
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
            if (table[i][j] != 0)
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
    printf("Move (L,R,U,D) or Quit, Back, New Start (Q,B,N):\n");
}

void initialize_Board(int table[count][count])
{
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            table[i][j] = 0;
        }
    }
    add_Random(table);
    add_Random(table);
}

void add_Random(int table[count][count])
{
    int random_i, random_j;
    do
    {
        random_i = rand() % count;
        random_j = rand() % count;
    } while (table[random_i][random_j] != 0);
    
    int random_Num = (rand() % 2) > 0 ? 4 : 2;
    table[random_i][random_j] = random_Num;
}

int move_Left(int table[count][count])
{
    int result = 0;
    int copy_table[count][count];
    
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            copy_table[i][j] = table[i][j];
        }
    }

    for (int i = 0; i < count; i++)
    {
        int position = 0;
        for (int j = 0; j < count; j++)
        {
            if (table[i][j] != 0)
            {
                table[i][position] = table[i][j];
                position++;
            }
        }
        for (int j = position; j < count; j++)
        {
            table[i][j] = 0;
        }

        for (int j = 0; j < count - 1; j++)
        {
            if (table[i][j] == table[i][j + 1] && table[i][j] != 0)
            {
                table[i][j] += table[i][j + 1];
                table[i][j + 1] = 0;
            }
        }

        position = 0;
        for (int j = 0; j < count; j++)
        {
            if (table[i][j] != 0)
            {
                table[i][position] = table[i][j];
                position++;
            }
        }
        for (int j = position; j < count; j++)
        {
            table[i][j] = 0;
        }
    }

    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            if (table[i][j] != copy_table[i][j])
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
    int rotated[count][count];
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            rotated[j][count - i - 1] = table[i][j];
        }
    }

    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            table[i][j] = rotated[i][j];
        }
    }
}

void Back(int table[count][count], int copy_table[count][count])
{
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            table[i][j] = copy_table[i][j];
        }
    }
}

int calculate_Score(int table[count][count])
{
    int sum = 0;
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
    int copy[count][count];
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            copy[i][j] = table[i][j];
        }
    }

    if (move_down(copy) == 0 && move_Left(copy) == 0 && move_right(copy) == 0 && move_up(copy) == 0)
    {
        return -1;
    }

    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            if (table[i][j] == 2048)
            {
                return 1;
            }
        }
    }
    return 0;
}
