/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 13:57:03 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/11 11:54:23 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"
#include "libbmp.h"

void	null_doom_pointers(t_doom *doom)
{
	null_game_pointers(&doom->game);
	null_menu_pointers(&doom->menu);
	null_editor_pointers(&doom->editor);
	null_sdlmain_pointers(&doom->sdlmain);
	null_map_pointers(&doom->map);
	null_walltextures_pointers(doom->wall_textures);
}

int		check_doom_state(t_doom *doom)
{
	int	ret;

	ret = 0;
	if (init_doom(doom) == 1)
	{
		ret = 1;
		doom->state = QUIT_STATE;
	}
	while (doom->state != QUIT_STATE)
	{
		if (doom->state == GAME_STATE && (doom->map.sector_head == NULL \
			|| doom->game.player.sector == NULL))
			doom->state = EDITOR_STATE;
		if (doom->state == GAME_STATE)
			ret = game_loop(doom);
		else if (doom->state == MENU_STATE)
			ret = menu_loop(doom);
		else if (doom->state == EDITOR_STATE)
			ret = editor_loop(doom);
		if (ret == 1)
			doom->state = QUIT_STATE;
	}
	return (ret);
}

int		main_loop(void)
{
	t_doom	doom;
	int		ret;

	ret = 0;
	doom.state = GAME_STATE;
	doom.sdlmain.win_w = HD_W;
	doom.sdlmain.win_h = HD_H;
	null_doom_pointers(&doom);
	ret = check_doom_state(&doom);
	free_game(&doom.game, &doom.map);
	free_menu(&doom.menu);
	free_editor(&doom.editor);
	free_sdlmain(&doom.sdlmain);
	free_map(&doom.map);
	free_map(&doom.editor.edit_map);
	//free_sector_list(&doom.map.sector_head);
	free_wall_textures(doom.wall_textures);
	quit_sdl_and_ttf();
	if (ret == 1)
		return (error_return("Error during main loop\n", NULL));
	return (0);
}

int		verify_defines(void)
{
	if (SQRT2 != 1.4142135623730950488 || PLAYER_RADIUS != 0.3 || NB_WALL_TEXTURES != 9 \
	|| NB_SOUND_SOURCES != 3 || NB_SOUND_BUFFERS != 4 || QUIT_STATE != 0 || GAME_STATE != 1 \
	|| MENU_STATE != 2 || EDITOR_STATE != 3 || HD_W != 1280 || HD_H != 720 \
	|| FHD_W != 1920 || FHD_H != 1080 || QHD_W != 2560 || QHD_H != 1440 \
	|| OFFSET != 20 || NBPOINTS != 2501 || NBPOINTSROW != 50 || NBTEXTURES != 9 || NBOPTIONS != 8 \
	|| NBHOVEROPTIONS != 3 || NBINSTRUCTS != 10 || SIZEMAP != 4 || COLOR_HOVER != 0x6C1413 \
	|| COLOR_PRESSED != 0x00FF00 || COLOR_NORMAL != 0xff0000 || COLOR_NORMAL != 0xffff00 \
	|| ROT_MAP_SHOW != 1 || FIX_MAP_SHOW != 2 || TEXFLAG != 4 || HEALTH_STATUS != 8 \
	|| FIRST_OPTION_SELECT != 1 || SECOND_OPTION_SELECT != 2 || THIRD_OPTION_SELECT != 3 || FOURTH_OPTION_SELECT != 4)
		return (1);
	else
		return (0);
}

int		main(void/*int argc, char *argv[]*/)
{
	//if (WIN_W > 1920 || WIN_H > 1080 || WIN_W < 100 || WIN_H < 100)
	//	return (1);
	//if (verify_defines() != 0)
	//	return (error_return("Some defines should %{r}s be changed, \
	//							please\n", "NOT"));
	if (main_loop() == 1)
		return (error_return("The program %{r}s 😢\n", "FAILED"));
	return (EXIT_SUCCESS);
}
