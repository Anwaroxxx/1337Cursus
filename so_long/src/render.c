#include "so_long.h"

t_img	create_color_image(t_game *game, int color)
{
	t_img	img;

	img.img = mlx_new_image(game->mlx, TILE_SIZE, TILE_SIZE);
	if (!img.img)
		error_exit("Error: Failed to create image", game);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	img.width = TILE_SIZE;
	img.height = TILE_SIZE;
	(void)color;
	return (img);
}

static void	fill_image(t_img *img, int color)
{
	int	x;
	int	y;
	char	*dst;

	y = 0;
	while (y < TILE_SIZE)
	{
		x = 0;
		while (x < TILE_SIZE)
		{
			dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
			*(unsigned int *)dst = color;
			x++;
		}
		y++;
	}
}

void	init_images(t_game *game)
{
	game->wall = create_color_image(game, 0x000000);
	fill_image(&game->wall, 0x444444);
	game->floor = create_color_image(game, 0x000000);
	fill_image(&game->floor, 0x1A1A2E);
	game->player = create_color_image(game, 0x000000);
	fill_image(&game->player, 0x00FF00);
	game->collectible = create_color_image(game, 0x000000);
	fill_image(&game->collectible, 0xFFD700);
	game->exit = create_color_image(game, 0x000000);
	fill_image(&game->exit, 0xFF0000);
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
				render_tile(game, &game->exit, x, y);
			else if (game->map.grid[y][x] == 'P')
				render_tile(game, &game->player, x, y);
			x++;
		}
		y++;
	}
}