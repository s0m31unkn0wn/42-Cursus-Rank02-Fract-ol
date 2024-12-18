/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armirono <armirono@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 23:45:16 by armirono          #+#    #+#             */
/*   Updated: 2024/10/22 23:15:38 by armirono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include "libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <stdlib.h>

void	exit_handler(int exit_signal);
int		file_action(char *file, int action);
void	tab_freer(char **tab);
char	*get_environment(char *varname, char **environment);
char	*obtain_path(char *command, char **environment);

#endif
