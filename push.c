void push(int *stack_from, int *stack_to, int *size_from, int *size_to)
{
    if (*size_from > 0)
    {
        for (int i = *size_to; i > 0; i--)
            stack_to[i] = stack_to[i - 1];
        stack_to[0] = stack_from[0];
        for (int i = 0; i < *size_from - 1; i++)
            stack_from[i] = stack_from[i + 1];
        (*size_from)--;
        (*size_to)++;
    }
}