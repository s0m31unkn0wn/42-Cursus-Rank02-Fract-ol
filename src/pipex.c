/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armirono <armirono@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 00:05:16 by armirono          #+#    #+#             */
/*   Updated: 2024/12/07 21:33:52 by armirono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execution(char *command, char **environment)
{
	char	**split_command;
	char	*path;

	if (*command == '\0')
	{
		ft_putstr_fd("Error: empty command\n", 2);
		exit(0);
	}
	split_command = ft_split(command, ' ');
	path = obtain_path(split_command[0], environment);
	if (execve(path, split_command, environment) == -1)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(split_command[0], 2);
		ft_putstr_fd(" not found\n", 2);
		tab_freer(split_command);
		exit(0);
	}
}

void	child_process(char **av, int *pipe_fd, char **environmen)
{
	int	fd;

	fd = file_action(av[1], 0);
	dup2(fd, 0);
	dup2(pipe_fd[1], 1);
	close(pipe_fd[0]);
	execution(av[2], environmen);
}

void	parent_process(char **av, int *pipe_fd, char **environme)
{
	int	fd;

	fd = file_action(av[4], 1);
	dup2(fd, 1);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[1]);
	execution(av[3], environme);
}

int	main(int ac, char **av, char **environm)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (ac != 5)
	{
		ft_putstr_fd("Error: invalid number of arguments\n", 2);
		exit_handler(1);
	}
	if (pipe(pipe_fd) == -1)
	{
		ft_putstr_fd("Error: pipe failed\n", 2);
		exit(-1);
	}
	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Error: fork failed\n", 2);
		exit(-1);
	}
	if (!pid)
		child_process(av, pipe_fd, environm);
	parent_process(av, pipe_fd, environm);
	return (0);
}
