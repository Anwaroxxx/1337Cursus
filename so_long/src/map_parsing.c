#include "so_long.h"

static int	get_map_height(char *file)
{
	int		fd;
	char	*line;
	int		height;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	height = 0;
	line = get_next_line(fd);
	while (line)
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (height);
}

static void	read_map_lines(char *file, t_game *game)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_exit("Error: Could not open map file", game);
	game->map.grid = malloc(sizeof(char *) * (game->map.height + 1));
	if (!game->map.grid)
		error_exit("Error: Memory allocation failed", game);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		game->map.grid[i] = ft_strtrim(line, "\n");
		free(line);
		if (!game->map.grid[i])
			error_exit("Error: Memory allocation failed", game);
		if (i == 0)
			game->map.width = ft_strlen(game->map.grid[i]);
		i++;
		line = get_next_line(fd);
	}
	game->map.grid[i] = NULL;
	close(fd);
}

void	parse_map(char *file, t_game *game)
{
	game->map.height = get_map_height(file);
	if (game->map.height <= 0)
		error_exit("Error: Invalid map file", game);
	read_map_lines(file, game);
}