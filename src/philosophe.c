/*
** philosophe.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Mar  1 14:44:03 2015 chapui_s
** Last update Sun Mar  1 14:44:05 2015 chapui_s
*/

#include "philosophe.h"

int		create_thread_disp(pthread_t *thread_disp,
				   t_sdl *struct_sdl)
{
#ifndef DEBUG
  if (pthread_create(thread_disp,
		     (const pthread_attr_t*)0,
		     (void *(*)(void*))&disp_philo,
		     (void*)struct_sdl))
  {
    fprintf(stderr, "ERROR: pthread_create()\n");
    return (-1);
  }
#else /* !DEBUG */
  (void)thread_disp;
  (void)struct_sdl;
#endif /* !DEBUG */
  return (0);
}

int		manage_thread_philo(pthread_t **threads,
				    int *current)
{
  int		i;

  i = 0;
  while (i++ < nb_philos)
  {
    current[i - 1] = i - 1;
    if (pthread_create(&((*threads)[i - 1]),
  		       (const pthread_attr_t*)0,
  		       (void *(*)(void*))&philo_run,
  		       &(current[i - 1])))
    {
      fprintf(stderr, "ERROR: pthread_create()\n");
      return (-1);
    }
  }
  i = 0;
  while (i < nb_philos)
    if (pthread_join((*threads)[i++], (void**)0))
    {
      fprintf(stderr, "ERROR: pthread_join()\n");
      return (-1);
    }
  return (0);
}

int		join_thread_disp(pthread_t *thread_disp)
{
#ifndef DEBUG
  if (pthread_join(*thread_disp, (void**)0))
  {
    fprintf(stderr, "ERROR: pthread_join()\n");
    return (-1);
  }
#else /* !DEBUG */
  (void)thread_disp;
#endif /* !DEBUG */
  return (0);
}

int		main()
{
  int		*current;
  pthread_t	*threads;
  pthread_t	thread_disp;
  t_sdl		*struct_sdl;

  struct_sdl = (t_sdl*)0;
  get_config();
  if (init_all(&current, &threads, &struct_sdl) == -1)
    return (-1);
  run = 1;
  if (create_thread_disp(&thread_disp, struct_sdl) == -1)
    return (-1);
  if (manage_thread_philo(&threads, current) == -1)
    return (-1);
  run = 0;
  if (join_thread_disp(&thread_disp) == -1)
    return (-1);
  if ((destroy_all(current, threads)) == -1)
    return (-1);
  return (0);
}
