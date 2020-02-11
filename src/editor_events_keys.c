/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_events_keys.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 14:33:21 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/11 11:50:55 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"

void	copy_enemy_info_loop(t_map *map, t_vec delspawn, \
						t_enemy_info *new_enemy_info)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (j < map->num_enemies + 1)
	{
		if (delspawn.x == map->enemy_info[j].enemy_spawn.x \
			&& delspawn.y == map->enemy_info[j].enemy_spawn.y)
			j++;
		else
		{
			new_enemy_info[i] = map->enemy_info[j];
			i++;
			j++;
		}
	}
}

int		delete_enemy_info(t_map *map, t_vec delspawn)
{
	int				i;
	int				j;
	t_enemy_info	*new_enemy_info;

	i = 0;
	j = 0;
	if (map->num_enemies == 1)
	{
		ft_memdel((void **)&map->enemy_info);
		map->num_enemies--;
		return (0);
	}
	map->num_enemies--;
	if (map->enemy_info == NULL)
		return (1);
	if ((new_enemy_info = malloc(sizeof(t_enemy_info) \
			* map->num_enemies)) == NULL)
	{
		ft_memdel((void **)&map->enemy_info);
		return (1);
	}
	copy_enemy_info_loop(map, delspawn, new_enemy_info);
	ft_memdel((void **)&map->enemy_info);
	map->enemy_info = new_enemy_info;
	return (0);
}

int		add_enemy_info(t_map *map, t_vec newspawn, int new_which_enem)
{
	int				i;
	t_enemy_info	*new_enemy_info;

	i = 0;
	if (map->num_enemies <= 0)
		return (0);
	if (map->enemy_info == NULL)
		return (1);
	if ((new_enemy_info = malloc(sizeof(t_enemy_info) * map->num_enemies)) \
			== NULL)
	{
		ft_memdel((void **)&map->enemy_info);
		return (1);
	}
	while (i < (map->num_enemies - 1))
	{
		new_enemy_info[i] = map->enemy_info[i];
		i++;
	}
	new_enemy_info[i].enemy_spawn = newspawn;
	new_enemy_info[i].which_enemy = new_which_enem;
	ft_memdel((void **)&map->enemy_info);
	map->enemy_info = new_enemy_info;
	return (0);
}

int		is_sector_occupied(t_sector_node *sector, t_map *map)
{
	int		i;
	t_vec	center;

	i = 0;
	center = vecdb_to_vec(sector->sector_center);
	if (map->num_enemies >= 1)
	{
		while (i < map->num_enemies)
		{
			if (center.x == map->enemy_info[i].enemy_spawn.x \
				&& center.y == map->enemy_info[i].enemy_spawn.y)
				return (1);
			i++;
		}
	}
	if (center.x == map->player_spawn.x && center.y == map->player_spawn.y)
		return (1);
	return (0);
}

void	event_keydown(t_editor *editor, t_doom *doom, t_sdlmain *sdlmain)
{
	SDL_Keycode key;

	key = sdlmain->event.key.keysym.sym;
	check_menu(&doom->sdlmain.event, &doom->state, \
				&doom->menu.previous_state, EDITOR_STATE);
	event_keydown_a_to_l(doom, editor, key);
	event_keydown_m_to_q(doom, editor, key);
	event_keydown_r_to_u(doom, editor, key, sdlmain->event.key.repeat);
}
