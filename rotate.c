#include <unistd.h>

void	rotate_a(int stack_a[], int size_a)
{
	int	first;
	int	i;

	if (!stack_a || size_a < 2)
		return ;
	first = stack_a[0];
	i = 0;
	while (i < size_a - 1)
	{
		stack_a[i] = stack_a[i + 1];
		i++;
	}
	stack_a[size_a - 1] = first;
	write(1, "ra\n", 3);
}
