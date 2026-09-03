#include "so_long.h"

t_img	load_xpm(t_game *game, char *path)
{
	t_img	img;

	img.img = mlx_xpm_file_to_image(game->mlx, path, &img.width, &img.height);
	if (!img.img)
		error_exit("Error: Failed to load XPM", game);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	return (img);
}

void	init_images(t_game *game)
{
	game->wall = load_xpm(game, "sprites/wall.xpm");
	game->floor = load_xpm(game, "sprites/floor.xpm");
	game->player = load_xpm(game, "sprites/player_down.xpm");
	game->player_up = load_xpm(game, "sprites/player_up.xpm");
	game->player_down = load_xpm(game, "sprites/player_down.xpm");
	game->player_left = load_xpm(game, "sprites/player_left.xpm");
	game->player_right = load_xpm(game, "sprites/player_right.xpm");
	game->collectible = load_xpm(game, "sprites/collectible.xpm");
	game->exit = load_xpm(game, "sprites/exit_closed.xpm");
	game->exit_open = load_xpm(game, "sprites/exit_open.xpm");
	game->enemy = load_xpm(game, "sprites/enemy.xpm");
}

void	render_tile(t_game *game, t_img *img, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, img->img,
		x * TILE_SIZE, y * TILE_SIZE);
}

void	render_map(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			render_tile(game, &game->floor, x, y);
			if (game->map.grid[y][x] == '1')
				render_tile(game, &game->wall, x, y);
			else if (game->map.grid[y][x] == 'C')
				render_tile(game, &game->collectible, x, y);
			else if (game->map.grid[y][x] == 'E')
			{
				if (game->collectibles_collected == game->map.collectibles)
					render_tile(game, &game->exit_open, x, y);
				else
					render_tile(game, &game->exit, x, y);
			}
			else if (game->map.grid[y][x] == 'P')
			{
				if (game->player_dir == 0)
					render_tile(game, &game->player_up, x, y);
				else if (game->player_dir == 1)
					render_tile(game, &game->player_down, x, y);
				else if (game->player_dir == 2)
					render_tile(game, &game->player_left, x, y);
				else
					render_tile(game, &game->player_right, x, y);
			}
			x++;
		}
		y++;
	}
	for (int i = 0; i < game->enemy_count; i++)
		render_tile(game, &game->enemy, game->enemy_x[i], game->enemy_y[i]);
	char moves_str[32];
	sprintf(moves_str, "Moves: %d", game->moves);
	mlx_string_put(game->mlx, game->win, 10, 20, 0xFFFFFF, moves_str);
}