/*
** philosophe.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Mon Feb 23 23:18:06 2015 chapui_s
** Last update Sun Mar  1 13:06:46 2015 chapui_s
*/

#include "philosophe.h"

#ifndef DEBUG

static t_sdl	*init_pictures(t_sdl *struct_sdl)
{
  if ((SDL_Init(SDL_INIT_VIDEO)) < 0)
    return ((t_sdl*)0);
  if ((struct_sdl->ecran = SDL_SetVideoMode(159 * nb_philos, 196, 32,
					    SDL_HWSURFACE)) == (SDL_Surface*)0)
    return ((t_sdl*)0);
  SDL_WM_SetCaption("Le repas des Philosophes", NULL);
  if ((struct_sdl->image_fond = SDL_LoadBMP("ressources/background.bmp"))
      == (SDL_Surface*)0)
    return ((t_sdl*)0);
  if ((SDL_BlitSurface(struct_sdl->image_fond, NULL, struct_sdl->ecran,
		       &(struct_sdl->position_fond))) < 0)
    return ((t_sdl*)0);
  if ((struct_sdl->surface_thinking = SDL_LoadBMP("ressources/reflexion.bmp"))
      == (SDL_Surface*)0
      || (struct_sdl->surface_resting = SDL_LoadBMP("ressources/repos.bmp"))
      == (SDL_Surface*)0
      || (struct_sdl->surface_eating = SDL_LoadBMP("ressources/riz.bmp"))
      == (SDL_Surface*)0
      || (struct_sdl->surface_philo = SDL_LoadBMP("ressources/philosophe.bmp"))
      == (SDL_Surface*)0)
    return ((t_sdl*)0);
  return (struct_sdl);
}

static t_sdl	*alloc_sdl()
{
  t_sdl		*struct_sdl;

  if ((struct_sdl = (t_sdl*)malloc(sizeof(*struct_sdl))) == (t_sdl*)0
      || (struct_sdl->tab_philo
	  = (SDL_Surface**)malloc(sizeof(SDL_Surface*)
				  * nb_philos)) == (SDL_Surface**)0
      || (struct_sdl->tab_etat
	  = (SDL_Surface**)malloc(sizeof(SDL_Surface*)
				  * nb_philos)) == (SDL_Surface**)0
      || (struct_sdl->tab_pos_philo
	  = (SDL_Rect*)malloc(sizeof(SDL_Rect) * nb_philos)) == (SDL_Rect*)0
      || (struct_sdl->tab_pos_etat
	  = (SDL_Rect*)malloc(sizeof(SDL_Rect) * nb_philos)) == (SDL_Rect*)0)
    return ((t_sdl*)0);
  return (struct_sdl);
}

t_sdl		*init_SDL(void)
{
  t_sdl		*struct_sdl;
  int		i;

  if ((struct_sdl = alloc_sdl()) == (t_sdl*)0)
    return ((t_sdl*)0);
  struct_sdl->position_fond.x = 0;
  struct_sdl->position_fond.y = 0;
  struct_sdl->tab_pos_philo[0].x = 30;
  struct_sdl->tab_pos_philo[0].y = 30;
  struct_sdl->tab_pos_etat[0].x = 100;
  struct_sdl->tab_pos_etat[0].y = 120;
  i = 1;
  while (i < nb_philos)
  {
    struct_sdl->tab_pos_philo[i].y = 30;
    struct_sdl->tab_pos_philo[i].x = struct_sdl->tab_pos_philo[i - 1].x + 157;
    struct_sdl->tab_pos_etat[i].y = 120;
    struct_sdl->tab_pos_etat[i].x = struct_sdl->tab_pos_etat[i - 1].x + 157;
    i += 1;
  }
  return (init_pictures(struct_sdl));
}

void		update_picture(t_sdl *struct_sdl, t_state *states_tmp, int i)
{
  if (!struct_sdl)
    return ;
  struct_sdl->tab_philo[i] = struct_sdl->surface_philo;
  if (SDL_SetColorKey(struct_sdl->tab_philo[i], SDL_SRCCOLORKEY,
		      SDL_MapRGB(struct_sdl->tab_philo[i]->format, 0, 0, 255))
      < 0)
    return ;
  if ((SDL_BlitSurface(struct_sdl->tab_philo[i], NULL,
		       struct_sdl->ecran, &(struct_sdl->tab_pos_philo[i]))) < 0)
    return ;
  if (states_tmp[i] == THINKING)
    struct_sdl->tab_etat[i] = struct_sdl->surface_thinking;
  else if (states_tmp[i] == EATING)
    struct_sdl->tab_etat[i] = struct_sdl->surface_eating;
  else
    struct_sdl->tab_etat[i] = struct_sdl->surface_resting;
  if (SDL_SetColorKey(struct_sdl->tab_etat[i], SDL_SRCCOLORKEY,
		      SDL_MapRGB(struct_sdl->tab_etat[i]->format, 0, 0, 255))
      < 0)
    return ;
  SDL_BlitSurface(struct_sdl->tab_etat[i], NULL,
		  struct_sdl->ecran, &(struct_sdl->tab_pos_etat[i]));
}

#endif /* !DEBUG */
