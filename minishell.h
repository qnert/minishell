/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 13:35:14 by skunert           #+#    #+#             */
/*   Updated: 2023/08/02 14:15:27 by skunert          ###   ########.fr       */
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

typedef struct shell
{
	int				status;
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

//signals
void	set_signals(void);

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

//parsing2
void	get_outfile(t_shell *sh);
void	get_outfile_append(t_shell *sh);

//parsing3
void	expander(t_shell *sh);
t_lexer	*check_correct_file(t_lexer *lst);
void	check_and_write_here_doc(t_shell *sh, t_files *infiles);

//envp
char	*get_envp_name(char *str);
char	**cpy_envp(char **envp);
void	erase_env_var(t_shell *sh, int index);

//built in
bool	check_built_in_child(char *str);
bool	check_built_in_main(char *str);
void	handle_built_in(t_shell *sh, char *str);

//built_in_cmds
void	handle_echo(char *str);
void	handle_pwd(void);
void	handle_export(t_shell *sh, char *str);
void	handle_unset(t_shell *sh, char *str);
void	handle_cd(t_shell *sh, char *str);
void	check_exit(t_shell *sh);

// access
bool	check_path(t_shell *sh, char **path, char *cmd);
bool	access_check(t_shell *sh, char *arg);
bool	check_cmd(t_shell *sh);

//utils
t_shell	*shell_init(char **envp);
int		get_len_matrix(char **matrix);
void	free_arr(char **arr);
void	print_matrix(char **matrix);
void	terminate_struct(t_shell *sh);
bool	check_existence_env(t_shell *sh, char *str);

//utils2
int		ft_outfile_check(char *filepath);
int		ft_infile_check(char *filepath);
int		outfile_check_app(char *filepath);
void	get_expand(t_shell *sh, t_lexer *curr);
char	*change_str_to_env(t_shell *sh, char *str);

//utils3.c
int		list_len(t_files *files);
bool	check_word_token(int token);
t_files	*ft_lstlast_files(t_files *lst);
void	replace_split_char(char *str);
t_lexer	*get_right_start_point(t_shell *sh);

//utils4
char	*get_home_from_env(t_shell *sh);
bool	ft_check_flag(char *str, int *i, int *check);
char	*ft_charjoin_free(char *str, char c);
t_files	*get_right_file(t_shell *sh, t_files *file);

//utils5
char	*get_expand_here_doc(t_shell *sh, char *str);

//lst_utils
int		lst_add_new(t_lexer *lst, char *str, int token);
void	lst_add_new_infile(t_files *infiles, char *str, char *delim, int pipe);
void	lst_add_new_outfile(t_files *lst, char *str, int token, int pipe);
void	free_lst_lexer(t_lexer *lst);
void	free_lst_files(t_files *lst);

//execute
void	execute_main(t_shell *sh);
void	execute_no_pipes(t_shell *sh, t_files *infile, t_files *outfile);
void	which_dup(t_files *infile, t_files *outfile);
void	execute_cmd(t_shell *sh, t_files *infile);

//execute_pipes
void	which_dup_pipes(t_shell *sh, t_files *in, t_files *out, int *fd);
void	child_process_pipes(t_shell *sh, t_files *in);
void	redirect_for_other_pipe(int	*fd);
int		handle_child_pipes(t_shell *sh, t_files *in, t_files *out, int *fd);
void	execute_pipes(t_shell *sh, t_files *in, t_files *out);

void	print_list(t_files *lst);

#endif
