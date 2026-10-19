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

void	reverse_rotate_a(int stack_a[], int size_a)
{
	int	last;
	int	i;

	if (!stack_a || size_a < 2)
		return ;
	last = stack_a[size_a - 1];
	i = size_a - 1;
	while (i > 0)
	{
		stack_a[i] = stack_a[i - 1];
		i--;
	}
	stack_a[0] = last;
	write(1, "rra\n", 4);
}
