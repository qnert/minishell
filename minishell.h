/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 13:35:14 by skunert           #+#    #+#             */
/*   Updated: 2023/07/18 15:43:51 by skunert          ###   ########.fr       */
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
	int		fd_in;
	int		fd_out;
	char	*infile;
	char	*outfile;
	char	*sterr;
	char	**envp;
	char	**cmd_table;
	char	**path_to_file_table;
}	t_shell;

//parsing
int		parser_main(char *str, t_shell *sh);

//envp
char	**cpy_envp(char **envp);

//build in
bool	check_build_in(char *str);
void	handle_build_in(t_shell *sh, char *str);

//build_in_cmds
void	handle_echo(char *str);
void	handle_pwd(void);

// access
bool	check_path(t_shell *sh, char **path, char *cmd);
bool	access_check(t_shell *sh, char *arg);
bool	check_cmd(t_shell *sh);

//execute
int		exec_cmd(t_shell *sh);

//utils
t_shell	*shell_init(char **envp);
char	*get_envp_name(char *str);
int		get_len_matrix(char **matrix);
void	free_arr(char **arr);
void	print_marix(char **matrix);
#endif
