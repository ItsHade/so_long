SRCS = 	src/ft_put.c \
		src/check_map.c \
		src/check_map2.c \
		src/path_finding.c \
		src/main.c

OBJS = $(SRCS:.c=.o)

NAME = so_long

CC = gcc

FLAGS = -Wall -Wextra

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -lbsd -Lminilibx-linux -lmlx_Linux -lXext -lX11 -lm -o $(NAME)
	# $(NAME): $(OBJS)
# 	$(CC) $(FLAGS) $(OBJS) -lbsd -lmlx -lXext -lX11 -o $(NAME)

clean:
		$(RM) $(OBJS)

fclean:	clean
		$(RM) $(NAME)

re:		fclean all

.PHONY: all clean fclean re