#include "so_long.h"
#include <time.h>

t_game	*g_game = NULL;

static int	close_window_wrapper(void)
{
	return (close_window(g_game));
}

int	main(int argc, char **argv)
{
	t_game	game;

	srand(time(NULL));
	ft_bzero(&game, sizeof(t_game));
	if (argc != 2)
		error_exit("Usage: ./so_long <map.ber>", &game);
	if (ft_strnstr(argv[1], ".ber", ft_strlen(argv[1])) == NULL)
		error_exit("Error: Map file must have .ber extension", &game);
	parse_map(argv[1], &game);
	validate_map(&game);
	init_game(&game);
	init_images(&game);
	init_enemies(&game);
	render_map(&game);
	g_game = &game;
	mlx_key_hook(game.win, key_hook, &game);
	mlx_hook(game.win, 17, 0, close_window_wrapper, &game);
	mlx_loop_hook(game.mlx, game_loop, NULL);
	mlx_loop(game.mlx);
	return (0);
}