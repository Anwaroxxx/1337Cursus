/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anwar <anwar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 10:00:00 by anwar             #+#    #+#             */
/*   Updated: 2026/08/24 10:00:00 by anwar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

static const char	*get_env_path(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

static char	*try_dirs(char **dirs, const char *cmd)
{
	char	*dir_slash;
	char	*full;
	int		i;

	i = 0;
	while (dirs[i])
	{
		dir_slash = ft_strjoin(dirs[i], "/");
		if (!dir_slash)
			return (NULL);
		full = ft_strjoin(dir_slash, cmd);
		free(dir_slash);
		if (!full)
			return (NULL);
		if (access(full, F_OK) == 0 && access(full, X_OK) == 0)
			return (full);
		free(full);
		i++;
	}
	return (NULL);
}

char	*find_path(const char *cmd, char **envp)
{
	const char	*env;
	char		**dirs;
	char		*path;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	env = get_env_path(envp);
	if (!env)
		return (NULL);
	dirs = ft_split(env, ':');
	if (!dirs)
		return (NULL);
	path = try_dirs(dirs, cmd);
	free_split(dirs);
	return (path);
}
