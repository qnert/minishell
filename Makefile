CC = cc
CFLAGS = -Wall -Wextra -Werror -I $(shell brew --prefix readline)/include
NAME = minishell

SRCS = ./src/main.c ./src/built_in.c ./src/utils.c ./src/envp.c \
		./src/access.c ./src/lexer.c ./src/built_in_cmd.c ./src/lst_utils.c \
		./src/lexer2.c ./src/parser.c ./src/utils2.c ./src/parser2.c \
		./src/execute.c ./src/parser3.c ./src/utils3.c ./src/utils4.c ./src/execute_pipes.c \
		./src/signals.c ./src/utils5.c ./src/utils6.c

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
