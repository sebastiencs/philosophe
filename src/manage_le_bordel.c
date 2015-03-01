/*
** manage_le_bordel.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Mar  1 13:03:32 2015 chapui_s
** Last update Sun Mar  1 13:03:33 2015 chapui_s
*/

#include "philosophe.h"

void			init_le_bordel(pthread_mutex_t *unused,
				       t_state *states_tmp,
				       t_sdl *struct_sdl)
{
  struct timespec	time_to_wait;
  struct timeval	now;

#ifdef DEBUG
  (void)struct_sdl;
#endif /* !DEBUG */
  if (!gettimeofday(&now, (struct timezone*)0))
  {
    time_to_wait.tv_sec = now.tv_sec + time_refresh;
    time_to_wait.tv_nsec = now.tv_usec * 1000;
    pthread_cond_timedwait(&(cond_disp), unused, &time_to_wait);
  }
  else
    pthread_cond_wait(&(cond_disp), unused);
  get_states(states_tmp);
  print_msg("%s\n", "--------");
#ifndef DEBUG
  if (struct_sdl)
    if ((SDL_BlitSurface(struct_sdl->image_fond, NULL, struct_sdl->ecran,
			 &(struct_sdl->position_fond))) < 0)
      return ;
#endif /* !DEBUG */
}

void			destroy_le_bordel(t_sdl *struct_sdl)
{
#ifdef DEBUG
  (void)struct_sdl;
#else /* !DEBUG */
  if (struct_sdl)
  {
    SDL_FreeSurface(struct_sdl->ecran);
    SDL_FreeSurface(struct_sdl->image_fond);
    SDL_FreeSurface(struct_sdl->surface_resting);
    SDL_FreeSurface(struct_sdl->surface_eating);
    SDL_FreeSurface(struct_sdl->surface_thinking);
    SDL_FreeSurface(struct_sdl->surface_philo);
    SDL_Quit();
    free(struct_sdl->tab_philo);
    free(struct_sdl->tab_etat);
    free(struct_sdl->tab_pos_philo);
    free(struct_sdl->tab_pos_etat);
    free(struct_sdl);
  }
#endif /* !DEBUG */
}
