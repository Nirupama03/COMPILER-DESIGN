#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct exp
{
    int pos;
    char op;
    int precedence;
} k[15];

int i = 1, j = 0, no = 0, tmpch = 90;
char str[100], left[15], right[15];

void findopr();
void explore();
void fleft(int);
void fright(int);

int main()
{
    printf("\t\tINTERMEDIATE CODE GENERATION\n\n");
    printf("Enter the Expression :");
    scanf("%s", str);
    printf("The intermediate code:\t\tExpression\n");
    findopr();
    explore();
    return 0;
}

void findopr()
{
    for (i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == ':')
        {
            k[j].pos = i;
            k[j].op = ':';
            k[j].precedence = 1;
            j++;
        }
        else if (str[i] == '/')
        {
            k[j].pos = i;
            k[j].op = '/';
            k[j].precedence = 2;
            j++;
        }
        else if (str[i] == '*')
        {
            k[j].pos = i;
            k[j].op = '*';
            k[j].precedence = 2;
            j++;
        }
        else if (str[i] == '+')
        {
            k[j].pos = i;
            k[j].op = '+';
            k[j].precedence = 3;
            j++;
        }
        else if (str[i] == '-')
        {
            k[j].pos = i;
            k[j].op = '-';
            k[j].precedence = 3;
            j++;
        }
        // Add more operators with their precedences as needed
    }
}

void explore()
{
    // Sort operators based on precedence (higher precedence first)
    for (i = 0; k[i].op != '\0'; i++)
    {
        for (j = i + 1; k[j].op != '\0'; j++)
        {
            if (k[i].precedence < k[j].precedence)
            {
                struct exp temp = k[i];
                k[i] = k[j];
                k[j] = temp;
            }
        }
    }

    i = 0;
    while (k[i].op != '\0')
    {
        fleft(k[i].pos);
        fright(k[i].pos);
        str[k[i].pos] = tmpch--;
        printf("\t%c := %s%c%s\t\t", str[k[i].pos], left, k[i].op, right);
        for (j = 0; j < strlen(str); j++)
            if (str[j] != '$')
                printf("%c", str[j]);
        printf("\n");
        i++;
    }

    fright(-1);
    if (no == 0)
    {
        fleft(strlen(str));
        printf("\t%s := %s", right, left);
        exit(0);
    }
    printf("\t%s :=  %c", right, str[k[--i].pos]);
    exit(0);
}

void fleft(int x)
{
    int w = 0, flag = 0;
    x--;
    while (x != -1 && str[x] != '+' && str[x] != '*' && str[x] != '=' && str[x] != '\0' && str[x] != '-' && str[x] != '/' && str[x] != ':')
    {
        if (str[x] != '$' && flag == 0)
        {
            left[w++] = str[x];
            left[w] = '\0';
            str[x] = '$';
            flag = 1;
        }
        x--;
    }
}

void fright(int x)
{
    int w = 0, flag = 0;
    x++;
    while (x != -1 && str[x] != '+' && str[x] != '*' && str[x] != '\0' && str[x] != '=' && str[x] != ':' && str[x] != '-' && str[x] != '/')
    {
        if (str[x] != '$' && flag == 0)
        {
            right[w++] = str[x];
            right[w] = '\0';
            str[x] = '$';
            flag = 1;
        }
        x++;
    }
}

