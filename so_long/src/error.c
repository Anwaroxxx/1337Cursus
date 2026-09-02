#include "so_long.h"

void	error_exit(char *msg, t_game *game)
{
	if (game)
	{
		if (game->map.grid)
			free_map(&game->map);
		if (game->mlx)
		{
			if (game->win)
				mlx_destroy_window(game->mlx, game->win);
			mlx_destroy_display(game->mlx);
			free(game->mlx);
		}
	}
	ft_printf("Error\n%s\n", msg);
	exit(1);
}