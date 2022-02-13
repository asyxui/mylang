#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int MAXSIZE = 256;
int stack[256] = {0};
int top = -1;

int isempty()
{

    if (top == -1)
        return 1;
    else
        return 0;
}

int isfull()
{

    if (top == MAXSIZE)
        return 1;
    else
        return 0;
}

int peek()
{
    return stack[top];
}

int pop()
{
    int data;

    if (!isempty())
    {
        data = stack[top];
        top = top - 1;
        return data;
    }
    else
    {
        printf("Could not retrieve data, Stack is empty.\n");
        return -1;
    }
}

void push(int data)
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

int add(int a, int b)
{
    return a + b;
}

int subtract(int a, int b)
{
    return a - b;
}

int multiply(int a, int b)
{
    return a * b;
}

int divide(int a, int b)
{
    return a / b;
}

int contains_arithmetic_operator(char *command)
{
    if (strchr(command, '+') || strchr(command, '-') || strchr(command, '*') || strchr(command, '/'))
    {
        return 1;
    }
    return 0;
}

int getLeftDigits(char *command)
{
    int count = 1;
    while (*(command - count) == ' ')
    {
        count++;
    }
    while (*(command - count) >= '0' && *(command - count) <= '9')
    {
        count++;
    }
    return count - 1;
}

int getRightDigits(char *command)
{
    int count = 1;
    while (*(command + count) == ' ')
    {
        count++;
    }
    while (*(command + count) >= '0' && *(command + count) <= '9')
    {
        count++;
    }
    return count - 1;
}

void arithmetic_command(char *command)
{
    char *i;
    if ((i = strchr(command, '+')))
    {
        push(add(strtol(i - getLeftDigits(i), NULL, 10), strtol(i + getRightDigits(i), NULL, 10)));
    }
    if ((i = strchr(command, '-')))
    {
        push(subtract(strtol(i - getLeftDigits(i), NULL, 10), strtol(i + getRightDigits(i), NULL, 10)));
    }
    if ((i = strchr(command, '*')))
    {
        push(multiply(strtol(i - getLeftDigits(i), NULL, 10), strtol(i + getRightDigits(i), NULL, 10)));
    }
    if ((i = strchr(command, '/')))
    {
        push(divide(strtol(i - getLeftDigits(i), NULL, 10), strtol(i + getRightDigits(i), NULL, 10)));
    }
}

void interpret_command(char *command)
{
    if (contains_arithmetic_operator(command))
    {
        arithmetic_command(command);
    }
    if (strstr(command, "printd"))
    {
        printf("%d\n", pop());
    }
}

void read_file(char *file)
{
    FILE *f = fopen(file, "r");
    char *line = (char *)malloc(128 * sizeof(char));
    size_t size;
    ;
    if (f == NULL)
    {
        printf("%s no such file.\n", file);
        exit(1);
    }

    while (getline(&line, &size, f) != EOF)
    {
        interpret_command(line);
    }

    fclose(f);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("usage: %s <file>\n", argv[0]);
        exit(1);
    }
    read_file(argv[1]);

    return 0;
}