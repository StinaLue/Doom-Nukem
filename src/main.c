/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 13:57:03 by sluetzen          #+#    #+#             */
/*   Updated: 2020/01/27 12:45:23 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"
#include "libbmp.h"

void null_doom_pointers(t_doom *doom)
{
	null_game_pointers(&doom->game);
	null_menu_pointers(&doom->menu);
	null_editor_pointers(&doom->editor);
	null_sdlmain_pointers(&doom->sdlmain);
	null_map_pointers(&doom->map);
	/* doom->game.surfs.fixed_mmap = NULL;
	doom->game.surfs.rot_mmap = NULL;
	doom->game.surfs.perspective_view = NULL;
	doom->game.surfs.weapons = NULL;
	doom->menu.background = NULL;
	doom->menu.menu_title = NULL;
	doom->menu.options[0] = NULL;
	doom->menu.options[1] = NULL;
	doom->menu.options[2] = NULL;
	doom->menu.options[3] = NULL;
	doom->menu.font = NULL;*/
}

int	main_loop()
{
	t_doom	doom;
	int		ret;

	ret = 0;
	doom.state = GAME_STATE;
	doom.sdlmain.win_w = HD_W;
	doom.sdlmain.win_h = HD_H;
	null_doom_pointers(&doom);
	if (init_doom(&doom) == 1)
	{
		ret = 1;
		doom.state = QUIT_STATE;
	}
	while (doom.state != QUIT_STATE)
	{
		if (doom.state == GAME_STATE)
			ret = game_loop(&doom);
		else if (doom.state == MENU_STATE)
			ret = menu_loop(&doom);
		else if (doom.state == EDITOR_STATE)
			ret = editor_loop(&doom);
		if (ret == 1)
			doom.state = QUIT_STATE;
	}
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

int main(/*int argc, char *argv[]*/)
{
	//if (WIN_W > 1920 || WIN_H > 1080 || WIN_W < 100 || WIN_H < 100)
	//	return (1);
	if (main_loop() == 1)
		return (error_return("The program %{r}s 😢\n", "FAILED"));
	return (EXIT_SUCCESS);
}
