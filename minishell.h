/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 13:35:14 by skunert           #+#    #+#             */
/*   Updated: 2023/07/21 14:33:03 by njantsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libs/libs.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <stdbool.h>
# include <fcntl.h>

typedef struct shell
{
	int				index;
	int				fd_in;
	int				fd_out;
	char			*infile;
	char			*outfile;
	char			*sterr;
	char			**envp;
	char			**cmd_table;
	char			**path_to_file_table;
	struct lexer	*token_list;
}	t_shell;

typedef struct lexer
{
	char				*str;
	int					token;
	struct lexer		*next;
}	t_lexer;

typedef enum tokens
{
	PIPE = 1,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
	SINGLE,
	DOUBLE,
}	t_tokens;

//lexer
bool	lexer(t_shell *sh, char *str);

//lexer2
int		check_words(t_shell *sh, char *str, int i);
bool	is_whitespace(char c);
int		check_single_quotes(t_shell *sh, char *str, int i);
int		check_double_quotes(t_shell *sh, char *str, int i);

//parsing
bool	parser_main(t_shell *sh);
bool	check_list(t_shell *sh);

//envp
char	*get_envp_name(char *str);
char	**cpy_envp(char **envp);
void	erase_env_var(t_shell *sh, int index);

//build in
bool	check_build_in(char *str);
void	handle_build_in(t_shell *sh, char *str);

//build_in_cmds
void	handle_echo(char *str);
void	handle_pwd(void);
void	handle_export(t_shell *sh, char *str);
void	handle_unset(t_shell *sh, char *str);

// access
bool	check_path(t_shell *sh, char **path, char *cmd);
bool	access_check(t_shell *sh, char *arg);
bool	check_cmd(t_shell *sh);

//utils
t_shell	*shell_init(char **envp);
int		get_len_matrix(char **matrix);
void	free_arr(char **arr);
void	print_marix(char **matrix);
void	terminate_struct(t_shell *sh);
bool	check_existence_env(t_shell *sh, char *str);

//lst_utils
int		lst_add_new(t_lexer *lst, char *str, int token);
void	free_lst(t_lexer *lst);

#endif
