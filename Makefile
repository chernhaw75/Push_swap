NAME		= push_swap

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -I.
RM			= rm -f

SRCS		= push_swap.c \
			  ft_parse.c \
			  ft_bench.c \
			  ft_put.c \
			  ft_push.c \
			  ft_rotate.c \
			  ft_rotate_both.c \
			  ft_swap.c \
			  ft_compute_disorder.c \
			  ft_rank.c \
			  ft_small_sort.c \
			  ft_simple_sort.c \
			  ft_medium_sort.c \
			  ft_medium_pull.c \
			  ft_complex_sort.c

OBJS		= $(SRCS:.c=.o)
HEADER		= push_swap.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
.PHONY: all clean fclean re
