void sa(int *stack)
{
    int temp;

    temp = stack[0];
    stack[0] = stack[1];
    stack[1] = temp;
}

void ss(int *stack_a, int *stack_b)
{
    sa(stack_a);
    sb(stack_b);
}