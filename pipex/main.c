#include "pipex.h"

static void	open_files(t_pipex *px, char **argv)
{
	px->infile = open(argv[1], O_RDONLY);
	if (px->infile == -1)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		perror(argv[1]);
	}
	px->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (px->outfile == -1)
		exit_error(argv[4]);
}

static pid_t	fork_check(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit_error("fork");
	return (pid);
}

static int	wait_children(pid_t pid1, pid_t pid2)
{
	int	status1;
	int	status2;

	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	if (WIFEXITED(status2))
		return (WEXITSTATUS(status2));
	return (EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	px;
	pid_t	pid1;
	pid_t	pid2;

	if (argc != 5)
	{
		ft_putstr_fd(USAGE, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	open_files(&px, argv);
	if (pipe(px.pipe_fd) == -1)
		exit_error("pipe");
	pid1 = fork_check();
	if (pid1 == 0)
		run_first_child(&px, argv, envp);
	pid2 = fork_check();
	if (pid2 == 0)
		run_second_child(&px, argv, envp);
	close(px.pipe_fd[0]);
	close(px.pipe_fd[1]);
	if (px.infile != -1)
		close(px.infile);
	close(px.outfile);
	return (wait_children(pid1, pid2));
}
