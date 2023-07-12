CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = minishell

SRCS = ./src/main.c ./src/build_in.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	cd libs && make
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lreadline ./libs/libs.a

clean:
	cd libs && make fclean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
