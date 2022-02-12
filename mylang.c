#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
    if (i = strchr(command, '+'))
    {
        *i = '\0';
        // TODO: Instead of printing, replace the command with the result.
        printf("%d\n", add(*(i - getLeftDigits(i)) - '0', *(i + getRightDigits(i)) - '0'));

        if (contains_arithmetic_operator(i + 1))
            arithmetic_command(i + 1);
    }
    if (i = strchr(command, '-'))
    {
        *i = '\0';
        printf("%d\n", subtract(*(i - getLeftDigits(i)) - '0', *(i + getRightDigits(i)) - '0'));
        if (contains_arithmetic_operator(i + 1))
            arithmetic_command(i + 1);
    }
    if (i = strchr(command, '*'))
    {
        *i = '\0';
        printf("%d\n", multiply(*(i - getLeftDigits(i)) - '0', *(i + getRightDigits(i)) - '0'));
        if (contains_arithmetic_operator(i + 1))
            arithmetic_command(i + 1);
    }
    if (i = strchr(command, '/'))
    {
        *i = '\0';
        printf("%d\n", divide(*(i - getLeftDigits(i)) - '0', *(i + getRightDigits(i)) - '0'));
        if (contains_arithmetic_operator(i + 1))
            arithmetic_command(i + 1);
    }
}

void interpret_command(char *command)
{
    if (contains_arithmetic_operator(command))
    {
        arithmetic_command(command);
    }
}

void read_file(char *file)
{
    FILE *f = fopen(file, "r");
    char *line;
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