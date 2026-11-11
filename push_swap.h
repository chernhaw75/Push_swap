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

/* ft_push.c */
void	push(int *from, int *to, int *size_from, int *size_to);
void	pa(int *a, int *b, int *size_a, int *size_b);
void	pb(int *a, int *b, int *size_a, int *size_b);

/* ft_rotate.c */
void	rotate_a(int stack_a[], int size_a);
void	reverse_rotate_a(int stack_a[], int size_a);
void	rotate_b(int stack_b[], int size_b);
void	reverse_rotate_b(int stack_b[], int size_b);

/* ft_swap.c */
void	sa(int *stack);
void	sb(int *stack);
void	ss(int *stack_a, int *stack_b);

/* simple, medium and complex*/
void	ft_simple_sort(int *a, int *b, int size);
void	ft_medium_sort(int *a, int *b, int size);
void	ft_complex_sort(int *a, int *b, int size);

int		rank_values(int *a, int size);
float	ft_compute_disorder(int *stack, int size);

#endif
