/*
** run_thread.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Mar  1 13:14:29 2015 chapui_s
** Last update Sun Mar  1 13:15:49 2015 chapui_s
*/

#include "philosophe.h"

static void		to_thinking(int n)
{
#ifdef DEBUG
  print_msg("%d is thinking\n", n);
#endif /* !DEBUG */
  mod_status(n, THINKING);
}

static void		get_sticks(int n)
{
  int			one;
  int			first;
  int			second;

  one = 0;
  first = (!(n % 2)) ? ((n + 1) % nb_philos) : (n);
  second = (!(n % 2)) ? (n) : ((n + 1) % nb_philos);
  while (check_status(first) == THINKING)
    usleep(1000);
  while (sem_trywait(&(sticks[first])))
    pthread_cond_signal(&(conds[first]));
  while (sem_trywait(&(sticks[second])))
  {
    if (!one && (one = 1))
      to_thinking(n);
    pthread_cond_signal(&(conds[second]));
  }
}

static void		release_sticks(int n)
{
  sem_post(&(sticks[n]));
  sem_post(&(sticks[(n + 1) % nb_philos]));
}

static void		wait_eating(int n)
{
  pthread_mutex_t	unused;
  struct timespec	time_to_wait;
  struct timeval	now;

  pthread_mutex_init(&unused, (const pthread_mutexattr_t*)0);
  pthread_mutex_lock(&unused);
  if (!gettimeofday(&now, (struct timezone*)0))
  {
    time_to_wait.tv_sec = now.tv_sec + time_waiting;
    time_to_wait.tv_nsec = now.tv_usec * 1000;
    pthread_cond_timedwait(&(conds[n]), &unused, &time_to_wait);
  }
  else
    pthread_cond_wait(&(conds[n]), &unused);
  pthread_mutex_unlock(&unused);
  pthread_mutex_destroy(&unused);
}

void			philo_run(int *number)
{
  int			rice;
  int			n;

  rice = nb_rices;
  n = *number;
  while (rice)
  {
    get_sticks(n);
    mod_status(n, EATING);
#ifdef DEBUG
    print_msg("%d is eating, %d rice left\n", n, rice);
#endif /* !DEBUG */
    wait_eating(n);
    rice -= 1;
    mod_status(n, RESTING);
#ifdef DEBUG
    print_msg("%d is resting\n", n);
#endif /* !DEBUG */
    release_sticks(n);
    if (rice)
      sleep(1);
  }
}
