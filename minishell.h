/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 13:35:14 by skunert           #+#    #+#             */
/*   Updated: 2023/07/18 19:55:17 by njantsch         ###   ########.fr       */
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
	int		index;
	int		fd_in;
	int		fd_out;
	char	*infile;
	char	*outfile;
	char	*sterr;
	char	**envp;
	char	**cmd_table;
	char	**path_to_file_table;
	int		pipes;
	int		ands;
	int		ors;
	int		*pipes_location;
	int		*ands_location;
	int		*ors_location;
}	t_shell;

//parsing
int		parser_main(char *str, t_shell *sh);
int		count_args(char *str);

//envp
char	**cpy_envp(char **envp);

//build in
bool	check_build_in(char *str);
void	handle_build_in(t_shell *sh, char *str);

//build_in_cmds
void	handle_echo(char *str);
void	handle_pwd(void);
void	handle_export(t_shell *sh, char *str);

// access
bool	check_path(t_shell *sh, char **path, char *cmd);
bool	access_check(t_shell *sh, char *arg);
bool	check_cmd(t_shell *sh);

// operand_check
char	**split_by_operators(char *str, char **new);
char	**split_commands(t_shell *sh, char *str);
void	get_operands_location(t_shell *sh, char *str);
char	**check_operands(t_shell *sh, char *str);

//execute
int		exec_cmd(t_shell *sh);

//utils
t_shell	*shell_init(char **envp);
char	*get_envp_name(char *str);
int		get_len_matrix(char **matrix);
void	free_arr(char **arr);
void	terminate_struct(t_shell *sh);
void	print_marix(char **matrix);
bool	check_existence_env(t_shell *sh, char *str);

#endif
