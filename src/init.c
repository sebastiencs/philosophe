/*
** init.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Mar  1 14:35:49 2015 chapui_s
** Last update Sun Mar  1 14:43:12 2015 chapui_s
*/

#include "philosophe.h"

static int	alloc_var(int **current, pthread_t **threads)
{
  if ((sticks = (sem_t*)malloc(sizeof(sem_t) * nb_philos)) == (sem_t*)0
      || (conds = (pthread_cond_t*)malloc(sizeof(*conds) * nb_philos))
      == (pthread_cond_t*)0
      || (states = (t_state*)malloc(sizeof(*states) * nb_philos))
      == (t_state*)0
      || (*current = (int*)malloc(sizeof(*current) * nb_philos)) == (int*)0
      || (*threads = (pthread_t*)malloc(sizeof(*threads) * nb_philos))
      == (pthread_t*)0)
  {
    fprintf(stderr, "ERROR: malloc()\n");
    return (-1);
  }
  return (0);
}

static int	init_sem()
{
  int		i;

  i = 0;
  while (i < nb_philos)
  {
    if ((sem_init(&(sticks[i]), 0, 1))
	|| (pthread_cond_init(&(conds[i]), (const pthread_condattr_t*)0)))
    {
      fprintf(stderr, "ERROR: sem_init/pthread_cond_init()\n");
      return (-1);
    }
    states[i] = RESTING;
    i += 1;
  }
  if (sem_init(&(stdout_lock), 0, 1)
      || sem_init(&(access_states), 0, 1))
  {
    printf("ERROR: sem_init()\n");
    return (-1);
  }
  return (0);
}

int		init_all(int **current,
			 pthread_t **threads,
			 t_sdl **struct_sdl)
{
#if defined(DEBUG) || defined(NO_SDL)
  (void)struct_sdl;
#endif /* !DEBUG || !NO_SDL */
  if (alloc_var(current, threads) == -1)
    return (-1);
  if (init_sem() == -1)
    return (-1);
#ifndef DEBUG
# ifndef NO_SDL
  if ((*struct_sdl = init_SDL()) == (t_sdl*)0)
    fprintf(stderr, "Warning: Can't initialize SDL\n");
# endif /* !NO_SDL */
#endif /* !DEBUG */
  return (0);
}
