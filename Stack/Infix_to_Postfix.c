/******************************************************************************************
 * Many well written wrong programs for infix to postfix are available on net. Sources:   *
 * http://www.codextream.com/write-a-c-program-to-convert-infix-to-postfix-expression/    *
 * http://geeksquiz.com/stack-set-2-infix-to-postfix/                                     *
 ******************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

struct Stack{
    int TOP;
    int StackSize;
    char S[];
};

void Push(struct Stack *, char );
char Pop(struct Stack *);
void InfixToPostfix(struct Stack *, char *);
int InStack_Priority(char );
int InComing_Priority(char );
char ReadSymbol(void);
void Print_post_exp(char *exp);
bool CheckParen(struct Stack*);
bool IsOperator(char );
bool IsOperand(char );
bool CheckOperator(char, char);
void HandleError(struct Stack *, char *);

int main(void)
{
    int n, op;
    printf("Enter the size of stack: ");
    scanf("%d", &n);

    struct Stack *stack = malloc(sizeof(struct Stack) + n);

    if(stack == NULL)
        return 0;

    stack->StackSize = n;
    stack->TOP = -1;

    char post_exp[n*10];

    while(1)
    {
        printf("\n__________________________________________________________________\n");
        printf("Select an operation:\n");
		printf("\t1. Convert Infix expression to postfix expression\n");
		printf("\t2. Print postfix expression\n");
		printf("\t3. To exit\n");
        printf("__________________________________________________________________\n\n");
		scanf("%d", &op);

		switch(op)
		{
		    case 1: InfixToPostfix(stack, post_exp);
                    break;
            case 2: Print_post_exp(post_exp);
                    break;
            case 3: exit(0);
            default: printf("Wrong Choice!\n\n");
		}
    }
}

char ReadSymbol(void)
{
    char c;
    scanf(" %c", &c);
    return c;
}

void Push(struct Stack *stack, char ch)
{
    if(stack->TOP >= stack->StackSize)
    {
        printf("Stack is overflow\n");
        return;
    }

    stack->S[++(stack->TOP)] = ch;
}

char Pop(struct Stack *stack)
{
    return stack->S[(stack->TOP)--];
}

int InStack_Priority(char x)
{
    if(x == '+' || x == '-')
        return 2;
    if(x == '*' || x == '/' || x == '%')
        return 4;
    if(x == '^')
        return 5;
    if(x == '(')
        return 0;
    if(isalnum(x))
        return 8;
    return -1;
}

int InComing_Priority(char x)
{
    if(x == '+' || x == '-')
        return 1;
    if(x == '*' || x == '/' || x == '%')
        return 3;
    if(x == '^')
        return 6;
    if(x == '(')
        return 9;
    if(x == ')')
        return 0;
    if(isalnum(x))
        return 7;
    return -1;
}


void Print_post_exp(char *exp)
{
    printf("The postfix expression is: ");
    if(exp[0] == '\0')
            printf("Empty!\n");
    while(*exp)
        printf("%c ", *exp++);
    printf("\n\n");
}

bool CheckParen(struct Stack *stack)
{
    int temp;
    if((temp = getchar()) != '\n' && stack->TOP == -1)
    {
        //HandleError();
        return 0;
    }
    else
    {
        ungetc(temp, stdin);
        return 1;
    }
}

bool IsOperator(char c)
{
    switch(c)
    {
        case '+': case '-': case '*': case '/': case '%': case '^': return 1;
        default: return 0;
    }
}

bool CheckOperator(char previous, char current)
{
    if((IsOperator(previous) && IsOperator(current)) || (current == ')' && IsOperator(previous)))
    {
        //HandleError();
        return 0;
    }
    return 1;
}

bool IsOperand(char c)
{
    return (bool)isalnum(c);
}

void HandleError(struct Stack *stack, char *exp)
{
    while(getchar() != '\n');
    memset(exp, '\0', stack->StackSize * 10);
    stack->TOP = -1;
    printf("Wrong expression! Either:\n 1. Too many arithmetic operators are there or\n");
    printf(" 2.Too many operands are there or\n");
    printf(" 3. Unmatched parenthesis are there or\n");
    printf(" 4. Some unexpected symbol are there.\n");
}


void InfixToPostfix(struct Stack *stack, char *exp)
{
    memset(exp, '\0', stack->StackSize * 10);
    Push(stack, '(');
    printf("Enter an infix expression delimited at the end by the ')' parenthesis:\n");

    int i = 0;
    char x, item, prev_item = '#';

    while(stack->TOP >= 0)
    {
        item = ReadSymbol();
        x = Pop(stack);
       // printf("%c\n", x);

        if(IsOperand(item))
        {
            if(IsOperand(prev_item))
            {
                HandleError(stack, exp);
                return;
            }
            Push(stack, x);
            exp[i++] = item;
        }
        else if(item == ')')
        {
            while(x != '(')
            {
                exp[i++] = x;
                x = Pop(stack);
            }
            if(!CheckParen(stack))
            {
                HandleError(stack, exp);
                return;
            }

        }
        /************************************************************************************
         * A symbol will be pushed onto the stack if its InComing _Priority is greater than *
         * that of InStack_Priority value.                                                  *
         ************************************************************************************/
        else if(InStack_Priority(x) >= InComing_Priority(item))
        {
            if(InComing_Priority(item) == -1)
            {
                HandleError(stack, exp);
                return;
            }
            while(InStack_Priority(x) >= InComing_Priority(item))
            {
                exp[i++] = x;
                x = Pop(stack);
            }
            Push(stack, x);
            Push(stack, item);
        }
        /************************************************************************************
         * A symbol will be poped from the stack if its InComing _Priority is less than     *
         * that of InStack_Priority value.                                                  *
         ************************************************************************************/
        else if(InStack_Priority(x) < InComing_Priority(item))
        {
            Push(stack, x);
            Push(stack, item);
        }
        else
        {
            printf("Invalid Expression\n");
            return;
        }
        if(!CheckOperator(prev_item, item))
        {
            HandleError(stack, exp);
            return;
        }
        prev_item = item;
    }
    Print_post_exp(exp);
}
