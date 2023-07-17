/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunert <skunert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 12:24:59 by skunert           #+#    #+#             */
/*   Updated: 2023/07/17 12:07:47 by skunert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**cpy_envp(char **envp)
{
	int		i;
	char	*str;
	char	**envp_cpy;

	i = 0;
	envp_cpy = ft_calloc(get_len_matrix(envp), sizeof(char *));
	while (envp[i] != NULL)
	{
		str = get_envp_name(envp[i]);
		envp_cpy[i] = getenv(str);
		str = ft_strjoin_free(str, "=");
		envp_cpy[i] = ft_strjoin_free(str, envp_cpy[i]);
		i++;
	}
	return (envp_cpy);
}

void	shell_loop(void)
{
	char	*str;

	str = readline("miniHell > ");
	while (str != NULL)
	{
		if (!(handle_build_in(str)))
			return ;
		free(str);
		str = readline("miniHell > ");
	}
	free(str);
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	char	**envp_cpy;

	envp_cpy = NULL;
	if (argc != 1 && argv == NULL)
	{
		printf("Wrong amount of arguments!\n");
		return (-1);
	}
	else
	{
		envp_cpy = cpy_envp(envp);
		shell_loop();
	}
	return (0);
}
