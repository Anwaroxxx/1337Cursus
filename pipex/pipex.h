
#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# include "libft.h"

# define USAGE "Usage: ./pipex file1 cmd1 cmd2 file2\n"

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		pipe_fd[2];
}	t_pipex;

/* main.c */
int		main(int argc, char **argv, char **envp);

/* process.c */
void	run_first_child(t_pipex *px, char **argv, char **envp);
void	run_second_child(t_pipex *px, char **argv, char **envp);

/* exec.c */
void	execute(char *cmd, char **envp);

/* path.c */
char	*find_path(const char *cmd, char **envp);

/* error.c */
void	exit_error(const char *msg);
void	free_split(char **arr);

#endif
