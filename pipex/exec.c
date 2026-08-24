/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anwar <anwar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 10:00:00 by anwar             #+#    #+#             */
/*   Updated: 2026/08/24 10:00:00 by anwar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

static void	report_not_found(const char *name)
{
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	ft_putstr_fd((char *)name, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
}

static void	exec_fail(char **args, char *path)
{
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	perror(args[0]);
	free(path);
	free_split(args);
}

void	execute(char *cmd, char **envp)
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	if (!args || !args[0])
	{
		free_split(args);
		report_not_found(cmd);
		exit(127);
	}
	path = find_path(args[0], envp);
	if (!path)
	{
		report_not_found(args[0]);
		free_split(args);
		exit(127);
	}
	execve(path, args, envp);
	if (errno == ENOENT)
	{
		exec_fail(args, path);
		exit(127);
	}
	exec_fail(args, path);
	exit(126);
}
