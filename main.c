#include <stdio.h>
#include <stdbool.h>

#define MAZE_SIZE 10
#define STACK_SIZE 30

typedef struct
{
    int x, y;
} coordinate;

coordinate stack[STACK_SIZE];
int top = -1;

int maze[MAZE_SIZE][MAZE_SIZE] = {
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 1, 1, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 1, 0, 0},
    {0, 1, 1, 1, 1, 0, 0, 1, 1, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
    {0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0}};

int isempty()
{

    if (top == -1)
        return 1;
    else
        return 0;
}

int isfull()
{

    if (top == STACK_SIZE)
        return 1;
    else
        return 0;
}

coordinate peek()
{
    return stack[top];
}

coordinate pop()
{
    if (!isempty())
    {
        coordinate data = stack[top];
        top = top - 1;
        return data;
    }
    else
    {
        printf("Stack is empty.\n");
        coordinate data;
        data.x = -1;
        data.y = -1;
        return data;
    }
}

void push(coordinate data)
{
    if (!isfull())
    {
        top = top + 1;
        stack[top] = data;
    }
    else
    {
        printf("Could not insert data, Stack is full.\n");
    }
}

coordinate find_entrance(int v[], int n)
{
    int i;
    coordinate data;
    data.x = -1;
    data.y = 0;
    for (i = 0; i < n; i++)
    {
        if (v[i] == 1)
        {
            data.x = i;
            return data;
        }
    }
    printf("There is no entrance!");
    return data;
}

void navigate(coordinate pos){
    if(pos.y == 9) {
        return;
    }
    if(maze[pos.x][pos.y+1] == 1){
        pos.y++;
        push(pos);
        navigate(pos);
    }
    if (maze[pos.x-1][pos.y] == 1){
        pos.x--;
        push(pos);
        navigate(pos);
    }
    if (maze[pos.x+1][pos.y] == 1){
        pos.x++;
        push(pos);
        navigate(pos);
    }
    if(maze[pos.x][pos.y-1] == 1){
        pos.y++;
        push(pos);
        navigate(pos);
    }
    pop();
    return;
}

void solve_maze(){
    coordinate position = find_entrance(maze[0], MAZE_SIZE);
    navigate(position);

}

int main(void)
{
    solve_maze();
    int i;
    for(i = 0; i <= top; i++){
        printf("%d, %d", stack[i].x, stack[i].y);
    }



    return 0;
}
