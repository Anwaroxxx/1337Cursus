/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anwar <anwar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 10:00:00 by anwar             #+#    #+#             */
/*   Updated: 2026/08/24 10:00:00 by anwar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

static void	dup2_check(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
		exit_error("dup2");
}

static void	redirect(int in, int out)
{
	dup2_check(in, STDIN_FILENO);
	dup2_check(out, STDOUT_FILENO);
}

void	run_first_child(t_pipex *px, char **argv, char **envp)
{
	if (px->infile == -1)
		exit(EXIT_FAILURE);
	redirect(px->infile, px->pipe_fd[1]);
	close(px->infile);
	close(px->pipe_fd[0]);
	close(px->pipe_fd[1]);
	execute(argv[2], envp);
}

void	run_second_child(t_pipex *px, char **argv, char **envp)
{
	redirect(px->pipe_fd[0], px->outfile);
	close(px->outfile);
	close(px->pipe_fd[0]);
	close(px->pipe_fd[1]);
	execute(argv[3], envp);
}
