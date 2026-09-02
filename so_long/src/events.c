#include "so_long.h"

static void	try_move(t_game *game, int new_x, int new_y)
{
	if (is_wall(&game->map, new_x, new_y))
		return ;
	if (is_collectible(&game->map, new_x, new_y))
	{
		game->collectibles_collected++;
		collect_item(&game->map, new_x, new_y);
	}
	if (is_exit(&game->map, new_x, new_y))
	{
		if (game->collectibles_collected == game->map.collectibles)
		{
			game->moves++;
			ft_printf("Moves: %d\n", game->moves);
			ft_printf("You win! Total moves: %d\n", game->moves);
			close_window(game);
		}
		return ;
	}
	move_player(game, new_x, new_y);
}

int	key_hook(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode == KEY_ESC)
		close_window(game);
	else if (keycode == KEY_W)
		try_move(game, game->map.player_x, game->map.player_y - 1);
	else if (keycode == KEY_S)
		try_move(game, game->map.player_x, game->map.player_y + 1);
	else if (keycode == KEY_A)
		try_move(game, game->map.player_x - 1, game->map.player_y);
	else if (keycode == KEY_D)
		try_move(game, game->map.player_x + 1, game->map.player_y);
	return (0);
}

int	close_window(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	free_game(game);
	exit(0);
	return (0);
}

void	move_player(t_game *game, int new_x, int new_y)
{
	game->map.grid[game->map.player_y][game->map.player_x] = '0';
	game->map.grid[new_y][new_x] = 'P';
	game->map.player_x = new_x;
	game->map.player_y = new_y;
	game->moves++;
	ft_printf("Moves: %d\n", game->moves);
	render_map(game);
}