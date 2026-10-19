float   compute_disorder(int *stack, int size)
{
    int mistakes;
    int total_pairs;
    int i;
    int j;

    mistakes = 0;
    i = 0;
    j = 0;
    while (i < size - 1)
    {
        j = i + 1;
        while (j < size)
        {
            if (stack[i] > stack[j])
                mistakes++;
            j++;
        }
        i++;
    }
    return (float)mistakes / (float)(size - 1);
}
