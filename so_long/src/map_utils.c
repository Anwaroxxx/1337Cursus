#include "so_long.h"

void	free_map(t_map *map)
{
	int	i;

	if (!map->grid)
		return ;
	i = 0;
	while (map->grid[i])
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
	map->grid = NULL;
}

int	is_wall(t_map *map, int x, int y)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (1);
	return (map->grid[y][x] == '1');
}

int	is_collectible(t_map *map, int x, int y)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (0);
	return (map->grid[y][x] == 'C');
}

int	is_exit(t_map *map, int x, int y)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (0);
	return (map->grid[y][x] == 'E');
}

void	collect_item(t_map *map, int x, int y)
{
	if (is_collectible(map, x, y))
		map->grid[y][x] = '0';
}

void	set_player_pos(t_map *map, int x, int y)
{
	map->player_x = x;
	map->player_y = y;
}