#include "so_long.h"

static void	count_map_elements(t_game *game)
{
	int	y;
	int	x;

	game->map.collectibles = 0;
	game->map.exit_count = 0;
	game->map.player_count = 0;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.grid[y][x] == TILE_COLLECTIBLE)
				game->map.collectibles++;
			else if (game->map.grid[y][x] == TILE_EXIT)
			{
				game->map.exit_count++;
				game->map.exit_x = x;
				game->map.exit_y = y;
			}
			else if (game->map.grid[y][x] == TILE_PLAYER)
			{
				game->map.player_count++;
				game->map.player_x = x;
				game->map.player_y = y;
			}
			x++;
		}
		y++;
	}
}

static void	check_rectangular(t_game *game)
{
	int	y;
	int	len;

	y = 1;
	while (y < game->map.height)
	{
		len = ft_strlen(game->map.grid[y]);
		if (len != game->map.width)
			error_exit("Error: Map is not rectangular", game);
		y++;
	}
}

static void	check_valid_chars(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.grid[y][x] != TILE_EMPTY
				&& game->map.grid[y][x] != TILE_WALL
				&& game->map.grid[y][x] != TILE_COLLECTIBLE
				&& game->map.grid[y][x] != TILE_EXIT
				&& game->map.grid[y][x] != TILE_PLAYER)
				error_exit("Error: Invalid character in map", game);
			x++;
		}
		y++;
	}
}

static void	check_walls(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < game->map.width)
	{
		if (game->map.grid[0][x] != TILE_WALL
			|| game->map.grid[game->map.height - 1][x] != TILE_WALL)
			error_exit("Error: Map not closed by walls", game);
		x++;
	}
	y = 0;
	while (y < game->map.height)
	{
		if (game->map.grid[y][0] != TILE_WALL
			|| game->map.grid[y][game->map.width - 1] != TILE_WALL)
			error_exit("Error: Map not closed by walls", game);
		y++;
	}
}

static void	check_counts(t_game *game)
{
	if (game->map.collectibles < 1)
		error_exit("Error: Map must have at least 1 collectible", game);
	if (game->map.exit_count != 1)
		error_exit("Error: Map must have exactly 1 exit", game);
	if (game->map.player_count != 1)
		error_exit("Error: Map must have exactly 1 player start position", game);
}

void	validate_map(t_game *game)
{
	count_map_elements(game);
	check_rectangular(game);
	check_valid_chars(game);
	check_walls(game);
	check_counts(game);
	validate_path(game);
}