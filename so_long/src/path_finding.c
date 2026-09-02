#include "so_long.h"

static void	flood_fill_recursive(char **grid, int x, int y, int *collectibles, int *exit_found, int width, int height)
{
	if (x < 0 || x >= width || y < 0 || y >= height)
		return ;
	if (grid[y][x] == '1' || grid[y][x] == 'F')
		return ;
	if (grid[y][x] == 'C')
		(*collectibles)++;
	if (grid[y][x] == 'E')
		*exit_found = 1;
	grid[y][x] = 'F';
	flood_fill_recursive(grid, x + 1, y, collectibles, exit_found, width, height);
	flood_fill_recursive(grid, x - 1, y, collectibles, exit_found, width, height);
	flood_fill_recursive(grid, x, y + 1, collectibles, exit_found, width, height);
	flood_fill_recursive(grid, x, y - 1, collectibles, exit_found, width, height);
}

void	validate_path(t_game *game)
{
	char	**grid_copy;
	int		collectibles;
	int		exit_found;
	int		i;

	grid_copy = malloc(sizeof(char *) * (game->map.height + 1));
	if (!grid_copy)
		error_exit("Error: Memory allocation failed", game);
	i = 0;
	while (i < game->map.height)
	{
		grid_copy[i] = ft_strdup(game->map.grid[i]);
		if (!grid_copy[i])
			error_exit("Error: Memory allocation failed", game);
		i++;
	}
	grid_copy[i] = NULL;
	collectibles = 0;
	exit_found = 0;
	flood_fill_recursive(grid_copy, game->map.player_x, game->map.player_y,
		&collectibles, &exit_found, game->map.width, game->map.height);
	if (collectibles != game->map.collectibles)
	{
		free_map_array(grid_copy);
		error_exit("Error: Not all collectibles are reachable", game);
	}
	if (!exit_found)
	{
		free_map_array(grid_copy);
		error_exit("Error: Exit is not reachable", game);
	}
	free_map_array(grid_copy);
}

void	free_map_array(char **grid)
{
	int	i;

	i = 0;
	while (grid[i])
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}