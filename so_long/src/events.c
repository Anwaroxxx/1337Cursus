#include "so_long.h"
#include <time.h>

extern t_game	*g_game;

static void	try_move(t_game *game, int new_x, int new_y, int dir)
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
	game->player_dir = dir;
	move_player(game, new_x, new_y);
}

int	key_hook(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode == KEY_ESC)
		close_window(game);
	else if (keycode == KEY_W)
		try_move(game, game->map.player_x, game->map.player_y - 1, 0);
	else if (keycode == KEY_S)
		try_move(game, game->map.player_x, game->map.player_y + 1, 1);
	else if (keycode == KEY_A)
		try_move(game, game->map.player_x - 1, game->map.player_y, 2);
	else if (keycode == KEY_D)
		try_move(game, game->map.player_x + 1, game->map.player_y, 3);
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
	if (check_enemy_collision(game))
	{
		ft_printf("Game Over! Enemy caught you!\n");
		close_window(game);
	}
}

void	init_enemies(t_game *game)
{
	game->enemy_count = 0;
	for (int y = 0; y < game->map.height; y++)
	{
		for (int x = 0; x < game->map.width; x++)
		{
			if (game->map.grid[y][x] == 'M')
			{
				if (game->enemy_count < 10)
				{
					game->enemy_x[game->enemy_count] = x;
					game->enemy_y[game->enemy_count] = y;
					game->enemy_dir[game->enemy_count] = rand() % 4;
					game->enemy_count++;
				}
			}
		}
	}
}

int	get_random_dir(int exclude)
{
	int dir = rand() % 4;
	while (dir == exclude)
		dir = rand() % 4;
	return (dir);
}

void	update_enemies(t_game *game)
{
	if (game->frame_count % 30 != 0)
		return ;
	for (int i = 0; i < game->enemy_count; i++)
	{
		int x = game->enemy_x[i];
		int y = game->enemy_y[i];
		int dir = game->enemy_dir[i];
		int new_x = x;
		int new_y = y;

		if (dir == 0)
			new_y--;
		else if (dir == 1)
			new_y++;
		else if (dir == 2)
			new_x--;
		else
			new_x++;

		if (is_wall(&game->map, new_x, new_y) || is_exit(&game->map, new_x, new_y))
		{
			game->enemy_dir[i] = get_random_dir(dir);
			continue ;
		}
		game->enemy_x[i] = new_x;
		game->enemy_y[i] = new_y;
	}
	if (check_enemy_collision(game))
	{
		ft_printf("Game Over! Enemy caught you!\n");
		close_window(game);
	}
}

int	check_enemy_collision(t_game *game)
{
	for (int i = 0; i < game->enemy_count; i++)
	{
		if (game->enemy_x[i] == game->map.player_x
			&& game->enemy_y[i] == game->map.player_y)
			return (1);
	}
	return (0);
}

int	game_loop(void)
{
	t_game	*game;

	game = g_game;
	game->frame_count++;
	update_enemies(game);
	render_map(game);
	return (0);
}