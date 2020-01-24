/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 16:38:33 by afonck            #+#    #+#             */
/*   Updated: 2020/01/24 18:19:19 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		copy_enemy_info(const t_enemy_info *src, t_enemy_info **dst, int num_enemies)
{
	int i;

	i = 0;
	if ((*dst = malloc(sizeof(t_enemy_info) * num_enemies)) == NULL)
		return (1);
	while (i < num_enemies)
	{
		(*dst)[i].enemy_spawn.x = src[i].enemy_spawn.x;
		(*dst)[i].enemy_spawn.y = src[i].enemy_spawn.y;
		(*dst)[i].which_enemy = src[i].which_enemy;
		i++;
	}
	return (0);
}

int		copy_map(const t_map *srcmap, t_map *dstmap)
{
	if (srcmap == NULL || dstmap == NULL)
		return (1);
	dstmap->num_sectors = srcmap->num_sectors;
	dstmap->num_enemies = srcmap->num_enemies;
	if (srcmap->num_enemies > 0 && srcmap->enemy_info != NULL)
	{
		if (copy_enemy_info(srcmap->enemy_info, &dstmap->enemy_info, srcmap->num_enemies) != 0)
			return (1);
	}
	if (srcmap->num_sectors > 0 && srcmap->sector_head != NULL)
	{
		if (copy_sector_list(srcmap->sector_head, &dstmap->sector_head) == -1)
			return (1);
	}
	return (0);
}