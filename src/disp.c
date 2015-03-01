/*
** disp.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Mar  1 13:08:03 2015 chapui_s
** Last update Sun Mar  1 13:08:19 2015 chapui_s
*/

#include "philosophe.h"

void			print_msg(char *fmt, ...)
{
  va_list		list;

  va_start(list, fmt);
  sem_wait(&stdout_lock);
  vprintf(fmt, list);
  sem_post(&stdout_lock);
  va_end(list);
}

void			update_states(t_state *states_tmp, int i)
{
  if (states_tmp[i] == THINKING)
    print_msg("%d is thinking\n", i);
  else if (states_tmp[i] == EATING)
    print_msg("%d is eating\n", i);
  else
    print_msg("%d is resting\n", i);
}

void			get_states(t_state *states_tmp)
{
  int			i;

  i = 0;
  sem_wait(&(access_states));
  i = 0;
  while (i < nb_philos)
  {
    states_tmp[i] = states[i];
    i += 1;
  }
  sem_post(&(access_states));
}

void			disp_philo(t_sdl *struct_sdl)
{
  pthread_mutex_t	unused;
  t_state		states_tmp[nb_philos];
  int			i;

  pthread_mutex_init(&unused, (const pthread_mutexattr_t*)0);
  pthread_mutex_lock(&unused);
  while (run)
  {
    init_le_bordel(&unused, states_tmp, struct_sdl);
    i = 0;
    while (i < nb_philos)
    {
#ifndef DEBUG
      update_picture(struct_sdl, states_tmp, i);
#endif /* !DEBUG */
      update_states(states_tmp, i);
      i += 1;
    }
#ifndef DEBUG
    if (struct_sdl)
      SDL_Flip(struct_sdl->ecran);
#endif /* !DEBUG */
  }
  destroy_le_bordel(struct_sdl);
  pthread_mutex_destroy(&unused);
}
