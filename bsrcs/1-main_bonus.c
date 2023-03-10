/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-main_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhellou < mkhellou@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 11:23:10 by mkhellou          #+#    #+#             */
/*   Updated: 2023/01/11 12:29:10 by mkhellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	render_frame(t_all_data *data)
{
	static int	i;
	static void	*image_set[50];

	if (i % 1 == 0)
	{
		map_modifier(data, i);
		image_modifier(data->img, image_set);
		simple_map_printer(image_set, data);
	}
	i++;
	return (0);
}

int	exit_cross(t_all_data *data)
{
	finish_game(data, 4);
	return (0);
}

void	data_intialisation(t_all_data *data, t_key *keys, t_enemy *enemies,
		t_image_info *img)
{
	data->keys = keys;
	ft_bzero(keys, sizeof(t_key) * 5);
	data->text = (t_text_data){0, 0};
	ft_bzero(enemies, sizeof(t_enemy) * 20);
	data->enemy = enemies;
	ft_bzero(img, sizeof(t_image_info) * 10);
	data->img = img;
}

void	window_initialisation(t_all_data *data)
{
	data->mlx.mlx = mlx_init();
	if (data->mlx.mlx == NULL)
	{
		free (data->map.map);
		exit (EXIT_FAILURE);
	}
	if (data->mlx.mlx_win == NULL)
	{
		free (data->mlx.mlx);
		free (data->map.map);
		exit (EXIT_FAILURE);
	}
}

int	main(int av, char **ac)
{
	t_all_data		data;
	t_key			keys[5];
	t_enemy			enemies[20];
	t_image_info	img[10];

	data.map = map_checker(av, ac);
	data_intialisation(&data, keys, enemies, img);
	enemy_spawner(&data.map);
	enemy_collector(&data);
	window_initialisation(&data);
	data.mlx.mlx_win = mlx_new_window(data.mlx.mlx, data.map.resolution.x
			* SPRITE_X, (data.map.resolution.y + 1) * SPRITE_Y, "so_long");
	images_generator(&data);
	mlx_hook(data.mlx.mlx_win, 2, (1L << 0), key_press, &data);
	mlx_hook(data.mlx.mlx_win, 3, (1L << 1), key_release, &data);
	mlx_hook(data.mlx.mlx_win, 17, 0L, exit_cross, &data);
	mlx_loop_hook(data.mlx.mlx, render_frame, &data);
	mlx_loop(data.mlx.mlx);
	total_clean(&data);
	return (0);
}
