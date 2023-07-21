CC = cc
CFLAGS = -Wall -Wextra -Werror -I $(shell brew --prefix readline)/include
NAME = minishell

SRCS = ./src/main.c ./src/build_in.c ./src/utils.c ./src/envp.c \
		./src/access.c ./src/lexer.c ./src/build_in_cmd.c ./src/lst_utils.c \
		./src/lexer2.c ./src/parser.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C libs
	$(CC) -o $(NAME) $(OBJS) -lreadline -L $(shell brew --prefix readline)/lib ./libs/libs.a

clean:
	cd libs && make fclean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
