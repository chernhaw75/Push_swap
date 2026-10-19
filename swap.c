void sa(int *stack_a)
{
    int temp;

    temp = stack_a[0];
    stack_a[0] = stack_a[1];
    stack_a[1] = temp;
}

void sb(int *stack_b)
{
    int temp;

    temp = stack_b[0];
    stack_b[0] = stack_b[1];
    stack_b[1] = temp;
}

void ss(int *stack_a, int *stack_b)
{
    sa(stack_a);
    sb(stack_b);
}