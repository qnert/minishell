CC = cc
CFLAGS = -Wall -Wextra -Werror -I $(shell brew --prefix readline)/include -Wno-gnu-include-next
NAME = minishell

SRCS = ./src/main.c ./src/builtin/built_in.c ./src/utils/utils.c ./src/envp/envp.c \
		./src/checks/access.c ./src/lexing/lexer.c ./src/builtin/built_in_cmd.c ./src/utils/lst_utils.c ./src/utils/lexer_utils.c ./src/utils/parser_utils.c\
		./src/lexing/lexer2.c ./src/parsing/parser.c ./src/parsing/parser2.c \
		./src/execution/execute.c ./src/parsing/parser3.c ./src/utils/utils2.c ./src/utils/utils3.c ./src/execution/execute_pipes.c \
		./src/signals.c ./src/utils/builtin_utils.c ./src/utils/lst_utils2.c ./src/checks/file_check.c \
		./src/parsing/expander.c ./src/exit/exit.c ./src/exit/exit2.c ./src/envp/envp2.c ./src/checks/checks.c ./src/utils/parser_utils2.c

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

test:
	@cd tests && bash tester.sh m
