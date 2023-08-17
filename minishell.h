/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 13:35:14 by skunert           #+#    #+#             */
/*   Updated: 2023/08/17 19:26:39 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libs/libs.h"
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <stdbool.h>
# include <fcntl.h>
# include <dirent.h>

typedef struct shell
{
	int				status;
	int				exit_code;
	int				check;
	int				index;
	int				pipes;
	int				old_stdin;
	int				old_stdout;
	char			*sterr;
	char			**envp;
	char			**cmd_table;
	char			**path_to_file_table;
	struct lexer	*token_list;
	struct files	*infiles;
	struct files	*outfiles;
}	t_shell;

typedef struct lexer
{
	char				*str;
	int					token;
	int					f_space;
	int					b_space;
	struct lexer		*next;
}	t_lexer;

typedef struct files
{
	char			*file_name;
	char			*delim;
	int				fd;
	int				pos;
	struct files	*next;
}	t_files;

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

// directory builtin
// built_in_cmd.c
void	handle_echo(char *str);
void	handle_pwd(t_shell *sh);
void	handle_export(t_shell *sh, char *str);
void	handle_unset(t_shell *sh, char *str);
void	handle_cd(t_shell *sh, char *str);

// built_in.c
bool	check_built_in_child(char *str);
bool	check_built_in_main(char *str);
void	check_exit(t_shell *sh);
void	handle_built_in(t_shell *sh, char *str);

// directory checks
// access.c
bool	check_path(t_shell *sh, char **path, char *cmd);
bool	access_check(t_shell *sh, char *arg);
bool	check_cmd(t_shell *sh);
//checks.c
bool	check_word_token(int token);
bool	ft_check_flag(char *str, int *i, int *check);

// file_check.c
int		ft_outfile_check(char *filepath);
int		outfile_check_app(char *filepath);
int		ft_infile_check(char *filepath);
t_lexer	*check_correct_file(t_lexer *lst);
bool	check_file_token(int token);

// directory envp
// envp.c
char	*get_envp_name(char *str);
char	**cpy_envp(char **envp);
void	change_env_vars(t_shell *sh, int index);
void	erase_env_var(t_shell *sh, int index);
char	*change_str_to_env(t_shell *sh, char *str);

// envp2.c
bool	check_existence_env(t_shell *sh, char *str);
char	*get_home_from_env(t_shell *sh);
char	**cpy_envp_add(char **envp, char *tmp);

// directory execution
// execute_pipes.c
void	which_dup_pipes(t_shell *sh, t_files *in, t_files *out, int *fd);
void	child_process_pipes(t_shell *sh, t_files *in, t_files *out);
void	redirect_for_other_pipe(int	*fd);
int		handle_child_pipes(t_shell *sh, t_files *in, t_files *out, int *fd);
void	execute_pipes(t_shell *sh, t_files *in, t_files *out);

//execute.c
void	which_dup(t_files *infile, t_files *outfile);
void	execute_cmd(t_shell *sh, t_files *in, t_files *out);
void	execute_no_pipes(t_shell *sh, t_files *infile, t_files *outfile);
void	execute_main(t_shell *sh);

//directory exit
// exit.c
void	check_failing_exit(t_shell *sh, int i, int j);
int		get_exit_code(t_shell *sh);
void	right_exit_builtin(t_shell *sh, int i, int j);
void	exit_error(t_shell *sh, char **tmp, DIR *dir, int i);
void	exit_status(t_shell *sh, char **tmp, int status);

// exit2.c
char	*get_exit_code_string(t_shell *sh, char *str);
void	exit_status_helper(t_shell *sh, char **tmp, DIR *dir, int i);

// directory lexing
// lexer.c
bool	check_null(char *str, int i);
void	check_pipe(t_shell *sh, char *str, int i);
void	check_redirect_plus(t_shell *sh, char *str, int i);
void	check_redirect(t_shell *sh, char *str, int i);
bool	lexer(t_shell *sh, char *str);

// lexer2.c
int		check_words(t_shell *sh, char *str, int i);
int		check_single_quotes(t_shell *sh, char *str, int i);
int		check_double_quotes(t_shell *sh, char *str, int i);
bool	is_whitespace(char c);

// directory parsing
// expander.c
int		count_spaces(char *str);
void	expander(t_shell *sh);
void	get_expand(t_shell *sh, t_lexer *curr);
char	*get_expand_here_doc(t_shell *sh, char *str);

// parser.c
void	table_init(t_shell *sh);
bool	check_list(t_shell *sh);
void	get_infile(t_shell *sh);
void	get_here_doc(t_shell *sh);
bool	parser_main(t_shell *sh);

// parser2.c
void	set_outfile_vars(t_shell *sh, int pipes);
void	get_outfile(t_shell *sh);
void	get_outfile_append(t_shell *sh);

// parser3.c
void	read_till_limiter(t_shell *sh, t_files *curr);
void	check_and_write_here_doc(t_shell *sh, t_files *infiles);
t_lexer	*get_right_start_point(t_shell *sh);
void	concat_right(t_shell *sh, t_lexer *curr, int *i);

// directory utils
// builtin_utils.c
void	go_to_home(t_shell *sh);
void	change_pwd(t_shell *sh);
int		count_until_space(char *str);
void	unset_helper(t_shell *sh, int i, int new, char *str);
bool	check_special_char(char *str);

// lexer_utils.c
void	check_redirect_plus_helper(t_shell *sh, char *str, int i);
void	check_redirect_helper(t_shell *sh, char *str, int i);

// lst_utils.c
int		lst_add_new(t_lexer *lst, char *str, int token);
void	lst_add_new_infile(t_files *lst, char *str, char *delim, int pipe);
void	lst_add_new_outfile(t_files *lst, char *str, int token, int pipe);
void	free_lst_lexer(t_lexer *lst);
void	free_lst_files(t_files *lst);

// lst_utils2.c
int		list_len(t_lexer *files);
t_files	*ft_lstlast_files(t_files *lst);
t_files	*get_right_file(t_shell *sh, t_files *file);

// parser_utils.c
void	expander_helper(t_shell *sh, t_lexer *curr);
void	get_expand_helper(char *first_str, t_lexer *curr, int i);
void	table_init_helper(t_shell *sh, t_lexer *curr, int *i);
char	*right_here_doc_name(t_files *lst, char *str);
void	get_here_doc_helper(t_shell *sh, t_lexer *curr, int pipe);

// utils.c
t_shell	*shell_init(char **envp);
int		get_len_matrix(char **matrix);
void	print_matrix(char **matrix);
void	terminate_struct(t_shell *sh);
void	free_arr(char **arr);

//utils2.c
void	replace_split_char(char *str);
char	*ft_charjoin_free(char *str, char c);
void	change_f_b_spaces(t_lexer *lst, char *str, int i, int start);
void	replace_space_char(char *str, int tmp);

// no own directory
// main.c
void	print_list(t_lexer *lst);
int		check_spaces(char *str);
int		shell_loop(t_shell *sh);
int		main(int argc, char **argv, char **envp);

// signals.c
void	sig_handler(int signal);
void	set_signals(void);

#endif
