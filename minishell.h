/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njantsch <njantsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 13:35:14 by skunert           #+#    #+#             */
/*   Updated: 2023/07/18 13:24:10 by njantsch         ###   ########.fr       */
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
int		check_build_in(char *str);

// access
int		check_path(t_shell *sh, char **path, char *cmd);
int		access_check(t_shell *sh, char *arg);

//utils
t_shell	*shell_init(char **envp);
char	*get_envp_name(char *str);
int		get_len_matrix(char **matrix);
void	free_arr(char **arr);
#endif
