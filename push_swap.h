/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchern-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 10:18:54 by tchern-h          #+#    #+#             */
/*   Updated: 2026/11/09 10:19:20 by tchern-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

/* operation counters (defined in push_swap.c) */
typedef enum e_op
{
	SA,
	SB,
	SS,
	PA,
	PB,
	RA,
	RB,
	RR,
	RRA,
	RRB,
	RRR,
	OP_COUNT
}	t_op;

typedef enum e_strat
{
	ADAPTIVE,
	SIMPLE,
	MEDIUM,
	COMPLEX
}	t_strat;

typedef struct s_cfg
{
	t_strat	strat;
	int		bench;
}	t_cfg;

typedef struct s_st
{
	int	*a;
	int	*b;
	int	sa;
	int	sb;
}	t_st;

extern int	g_ops[OP_COUNT];

/* ft_push.c */
void	push(int *from, int *to, int *size_from, int *size_to);
void	pa(int *a, int *b, int *size_a, int *size_b);
void	pb(int *a, int *b, int *size_a, int *size_b);

/* ft_rotate.c */
void	rotate_a(int stack_a[], int size_a);
void	reverse_rotate_a(int stack_a[], int size_a);
void	rotate_b(int stack_b[], int size_b);
void	reverse_rotate_b(int stack_b[], int size_b);

/* ft_rotate_both.c */
void	rotate_both(int *a, int *b, int size_a, int size_b);

/* ft_swap.c */
void	sa(int *stack);
void	sb(int *stack);
void	ss(int *stack_a, int *stack_b);

/* simple, medium and complex*/
void	ft_simple_sort(int *a, int *b, int size);
void	ft_medium_sort(int *a, int *b, int size);
void	ft_complex_sort(int *a, int *b, int size);
void	ft_small_sort(int *a, int *b, int size);

int		rank_values(int *a, int size);
float	ft_compute_disorder(int *stack, int size);

/* ft_medium_pull.c */
int		ft_idx_of(int *b, int v);
int		ft_dist(int idx, int size);
void	ft_bring_to_top_b(t_st *s, int idx);
void	ft_pull_back(t_st *s);

/* ft_parse.c */
int		ft_is_sep(char c);
int		ft_load(char **argv, int count, int *a);

/* ft_args.c */
int		ft_parse_flag(const char *s, t_cfg *cfg);
int		ft_count(char **argv, int count);

/* ft_put.c / ft_bench.c (bench output goes to stderr) */
void	ft_putstr_err(const char *s);
void	ft_putnbr_err(int n);
void	ft_bench(t_strat used, t_cfg *cfg, double d);

#endif
