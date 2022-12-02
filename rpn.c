#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct Stack
{
    int *array;
    int cap;
    int size;

} Stack;

Stack *createStack(int cap)
{
    if (cap <= 0)
    {
        return NULL;
    }
    Stack *stack = malloc(sizeof(Stack));
    if (stack == NULL)
    {
        return NULL;
    }

    stack->array = malloc(sizeof(int) * cap);
    if (stack->array == NULL)
    {
        printf("\nFailed to create stack\n");
        free(stack);
        return NULL;
    }

    stack->cap = cap;
    stack->size = 0;

    return stack;
}

void freeStack(Stack *stack)
{
    free(stack->array);
    free(stack);
}

int isFull(Stack *stack)
{
    if (stack->size >= stack->cap)
    {
        // full
        return 1;
    }
    return 0;
}

int isEmpty(Stack *stack)
{
    if (stack->size == 0)
    {
        // printf("bs error");
        return 1;
    }
    return 0;
}

void push(Stack *stack, int value)
{
    if (isFull(stack) == 1)
    {
        printf("\nstack is full, cannot add any more items\n");
        return;
    }
    stack->array[stack->size] = value;
    stack->size++;

    // printf("\n pushed a value of : %d", value);
}

int pop(Stack *stack)
{
    if (isEmpty(stack) == 1)
    {
        // printf("stacks empty.");
        return -1;
    }
    stack->size--;

    // printf("\n popped a value of : %d", stack->array[stack->size]);
    return stack->array[stack->size];
}

int isNumber(char *input)
{
    if (input == NULL)
    {
        return 0;
    }

    int length = strlen(input);
    for (int i = 0; i < length; i++)
    {
        if (!isdigit(input[i]))
        {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char *argv[])
{
    if (argv[1] == NULL)
    {
        return -1;
    }

    char *line = argv[1];

    char newString[100];

    int temp = 0;

    for (int i = 0, j = 0; i < strlen(line); i++)
    {
        if ((line[i] == '+') || (line[i] == '-') || (line[i] == 'x') || (line[i] == '/'))
        {
            newString[j++] = ',';
            newString[j++] = line[i];
            newString[j++] = ',';
        }
        else
        {
            newString[j++] = line[i];
        }

        temp = j;
    }

    for (int i = temp; i < strlen(newString); i++)
    {
        newString[i] = ',';
    }

    Stack *stack = createStack(100);

    const char s[2] = ",";
    char *token;

    token = strtok(newString, s);

    while ((token != NULL) && strcmp(token, "\0") != 0)
    {
        // printf(" \n%s is a number? = %d\n", token, isNumber(token));

        if (isNumber(token) == 1)
        {
            push(stack, atoi(token));
        }
        else
        {
            if (isEmpty(stack) == 1)
            {
                return EXIT_FAILURE;
            }
            int pop1 = pop(stack);
            if (isEmpty(stack) == 1)
            {
                return EXIT_FAILURE;
            }
            int pop2 = pop(stack);

            switch ((char)*token)
            {
            case '+':
                // printf("\n addition \n");
                // for (int i = 0; i < stack->size; i++)
                // {
                //     printf("%d ", stack->array[i]);
                // }

                push(stack, pop1 + pop2);
                break;
            case '-':
                // printf("\n subtraction \n");

                push(stack, pop2 - pop1);
                break;
            case 'x':
                // printf("\n multiplication \n");

                push(stack, pop1 * pop2);
                break;
            case '/':
                // printf("\n division \n");

                push(stack, pop2 / pop1);
                break;
            default:
                break;
                // do nothing
            }
        }

        token = strtok(NULL, s);
    }

    // for (int i = 0; i < stack->size; i++)
    // {
    if (stack->size == 1){
        printf("%d\n", stack->array[0]);
        freeStack(stack);
        return EXIT_SUCCESS;
    }

    freeStack(stack);
    return EXIT_FAILURE;
}


