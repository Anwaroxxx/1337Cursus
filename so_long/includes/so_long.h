#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include "../gnl/get_next_line.h"
# include "../ft_printf/ft_printf.h"

# define TILE_SIZE 64
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307

# define TILE_EMPTY '0'
# define TILE_WALL '1'
# define TILE_COLLECTIBLE 'C'
# define TILE_EXIT 'E'
# define TILE_PLAYER 'P'
# define TILE_ENEMY 'M'

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		collectibles;
	int		exit_count;
	int		player_count;
	int		player_x;
	int		player_y;
	int		exit_x;
	int		exit_y;
}	t_map;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_map	map;
	t_img	wall;
	t_img	floor;
	t_img	player;
	t_img	collectible;
	t_img	exit;
	t_img	exit_open;
	t_img	enemy;
	t_img	player_up;
	t_img	player_down;
	t_img	player_left;
	t_img	player_right;
	int		moves;
	int		collectibles_collected;
	int		game_over;
	int		player_dir;
	int		frame_count;
	int		enemy_count;
	int		enemy_x[10];
	int		enemy_y[10];
	int		enemy_dir[10];
}	t_game;

void	error_exit(char *msg, t_game *game);
void	parse_map(char *file, t_game *game);
void	validate_map(t_game *game);
void	validate_map_walls(t_game *game);
void	validate_map_chars(t_game *game);
void	validate_path(t_game *game);
void	flood_fill(char **grid, int x, int y, int *collectibles, int *exit_found);
int		find_path(char **grid, int width, int height, int start_x, int start_y);
void	init_game(t_game *game);
void	init_images(t_game *game);
void	render_map(t_game *game);
void	render_tile(t_game *game, t_img *img, int x, int y);
int		key_hook(int keycode, void *param);
int		close_window(void *param);
void	move_player(t_game *game, int new_x, int new_y);
void	free_game(t_game *game);
void	free_map(t_map *map);
void	free_map_array(char **grid);
t_img	load_xpm(t_game *game, char *path);

int		is_wall(t_map *map, int x, int y);
int		is_collectible(t_map *map, int x, int y);
int		is_exit(t_map *map, int x, int y);
void	collect_item(t_map *map, int x, int y);
void	set_player_pos(t_map *map, int x, int y);
void	init_enemies(t_game *game);
void	update_enemies(t_game *game);
int		check_enemy_collision(t_game *game);
int		game_loop(void);

#endif