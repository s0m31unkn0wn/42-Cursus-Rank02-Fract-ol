/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armirono <armirono@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 21:53:52 by armirono          #+#    #+#             */
/*   Updated: 2024/10/23 20:41:56 by armirono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exit_handler(int exit_signal)
{
	if (exit_signal == 1)
		ft_putstr_fd("./pipex infile cmd1 cmd2 outfile\n", 2);
	exit(0);
}

int	file_action(char *file, int action)
{
	int	rtrn;

	rtrn = -1;
	if (action == 0)
		rtrn = open(file, O_RDONLY, 0777);
	else if (action == 1)
		rtrn = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (action == 2)
		rtrn = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (rtrn == -1)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(" failed to open\n", 2);
		exit_handler(0);
	}
	return (rtrn);
}

void	tab_freer(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*get_environment(char *varname, char **environment)
{
	size_t	i;
	size_t	varname_len;

	i = 0;
	varname_len = ft_strlen(varname);
	while (environment[i])
	{
		if ((ft_strncmp(environment[i], varname, varname_len) == 0)
			&& (environment[i][varname_len] == 61))
			return (environment[i] + varname_len + 1);
		i++;
	}
	return (NULL);
}

char	*obtain_path(char *command, char **environment)
{
	char	*exec_path;
	char	**all_path;
	char	**split_commmand;
	char	*path_part;
	size_t	i;

	i = -1;
	all_path = ft_split(get_environment("PATH", environment), ':');
	split_commmand = ft_split(command, ' ');
	while (all_path[++i])
	{
		path_part = ft_strjoin(all_path[i], "/");
		exec_path = ft_strjoin(path_part, split_commmand[0]);
		free(path_part);
		if (access(exec_path, F_OK | X_OK) == 0)
		{
			tab_freer(split_commmand);
			return (exec_path);
		}
		free(exec_path);
	}
	tab_freer(all_path);
	tab_freer(split_commmand);
	return (command);
}
