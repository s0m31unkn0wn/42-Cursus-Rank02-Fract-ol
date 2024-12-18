/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armirono <armirono@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 23:45:50 by armirono          #+#    #+#             */
/*   Updated: 2024/12/07 21:34:10 by armirono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	here_doc_action(char **av, int *pipe_fd)
{
	char	*rtrn;

	close(pipe_fd[0]);
	while (1)
	{
		rtrn = get_next_line(0);
		if (ft_strncmp(rtrn, av[2], ft_strlen(av[2])) == 0)
		{
			free(rtrn);
			close(pipe_fd[1]);
			exit(0);
		}
		ft_putstr_fd(rtrn, pipe_fd[1]);
		free(rtrn);
	}
}

void	here_doc(char **av)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;

	if (pipe(pipe_fd) == -1)
	{
		ft_putstr_fd("Error: Pipe failed in heredoc\n", 2);
		exit(0);
	}
	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Error: Fork failed in heredoc\n", 2);
		exit(0);
	}
	if (!pid)
		here_doc_action(av, pipe_fd);
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		waitpid(pid, &status, 0);
	}
}

void	do_pipe(char *cmmnd, char **environ)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
	{
		ft_putstr_fd("Error: Pipe in do_pipe failed\n", 2);
		exit(0);
	}
	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Error: Fork in do_pipe failed\n", 2);
		exit(0);
	}
	if (!pid)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], 1);
		execution(cmmnd, environ);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
	}
}

int	main(int argc, char **argv, char **enviro)
{
	int	i;
	int	fd_input;
	int	fd_output;

	if (argc < 5)
		exit_handler(1);
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		if (argc < 6)
			exit_handler(2);
		i = 3;
		fd_output = file_action(argv[argc - 1], 2);
		here_doc(argv);
	}
	else
	{
		i = 2;
		fd_input = file_action(argv[1], 0);
		fd_output = file_action(argv[argc - 1], 1);
		dup2(fd_input, 0);
	}
	while (i < argc - 2)
		do_pipe(argv[i++], enviro);
	dup2(fd_output, 1);
	execution(argv[argc - 2], enviro);
}
