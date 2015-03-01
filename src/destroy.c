/*
** destroy.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Mar  1 14:38:47 2015 chapui_s
** Last update Sun Mar  1 14:39:05 2015 chapui_s
*/

#include "philosophe.h"

static int	destroy_sem_co()
{
  int		i;

  i = 0;
  while (i < nb_philos)
  {
    if (sem_destroy(&(sticks[i])))
    {
      fprintf(stderr, "ERROR: sem_destroy()\n");
      return (-1);
    }
    if (pthread_cond_destroy(&(conds[i])))
    {
      fprintf(stderr, "ERROR: pthread_cond_destroy()\n");
      return (-1);
    }
    i += 1;
  }
  if (sem_destroy(&(stdout_lock))
      || sem_destroy(&(access_states)))
  {
    fprintf(stderr, "ERROR: sem_destroy()\n");
    return (-1);
  }
  return (0);
}

int		destroy_all(int *current, pthread_t *threads)
{
  if (destroy_sem_co() == -1)
    return (-1);
  free(sticks);
  free(conds);
  free(states);
  free(current);
  free(threads);
  return (0);
}
