#include "so_long.h"

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		error_exit("Error: Failed to initialize MLX", game);
	game->win = mlx_new_window(game->mlx,
		game->map.width * TILE_SIZE,
		game->map.height * TILE_SIZE,
		"So Long");
	if (!game->win)
		error_exit("Error: Failed to create window", game);
	game->moves = 0;
	game->collectibles_collected = 0;
	game->game_over = 0;
}