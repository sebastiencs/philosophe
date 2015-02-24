/*
** philosophe.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Mon Feb 23 23:18:06 2015 chapui_s
** Last update Tue Feb 24 01:53:54 2015 chapui_s
*/

#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <stdarg.h>

typedef enum	e_state
{
  EATING,
  THINKING,
  RESTING
}		t_state;

sem_t		sticks[7];
sem_t		stdout_lock;
pthread_cond_t	conds[7];
t_state		states[7];
sem_t		access_states;
sem_t		disp;

void		print_msg(char *fmt, ...)
{
  va_list	list;

  va_start(list, fmt);
  sem_wait(&stdout_lock);
  vprintf(fmt, list);
  sem_post(&stdout_lock);
  va_end(list);
}

void		disp_philosophes()
{
  t_state	states_tmp[7];
  int		i;

  i = 0;
  sem_wait(&(access_states));
  while (i < 7)
  {
    states_tmp[i] = states[i];
    i += 1;
  }
  sem_post(&(access_states));
  sem_wait(&(disp));
  i = 0;
  print_msg("%s\n", "--------");
  while (i < 7)
  {
    if (states_tmp[i] == THINKING)
      print_msg("%d is thinking\n", i);
    else if (states_tmp[i] == EATING)
      print_msg("%d is eating\n", i);
    else
      print_msg("%d is resting\n", i);
    i += 1;
  }
  sem_post(&(disp));
}

t_state		check_status(int n)
{
  t_state	tmp;

  sem_wait(&(access_states));
  tmp = states[n];
  sem_post(&(access_states));
  return (tmp);
}

void		mod_status(int n, t_state state)
{
#ifndef DEBUG
  static int	nb = 0;
#endif /* !DEBUG */

  sem_wait(&(access_states));
  states[n] = state;
#ifndef DEBUG
  nb += 1;
#endif /* !DEBUG */
  sem_post(&(access_states));
#ifndef DEBUG
  if (!((nb - 1) % 5))
    disp_philosophes();
#endif /* !DEBUG */
}

void		get_sticks(int n)
{
  int		one;
  int		first;
  int		second;

  one = 0;
  first = (!(n % 2)) ? ((n + 1) % 7) : (n);
  second = (!(n % 2)) ? (n) : ((n + 1) % 7);
  while (check_status(first) == THINKING)
    usleep(1000);
  while (sem_trywait(&(sticks[first])))
    pthread_cond_signal(&(conds[first]));
  while (check_status(second) == THINKING)
    usleep(1000);
  while (sem_trywait(&(sticks[second])))
  {
    if (!one && (one = 1))
    {
#ifdef DEBUG
      print_msg("%d is thinking\n", n);
#endif /* !DEBUG */
      mod_status(n, THINKING);
    }
    pthread_cond_signal(&(conds[second]));
  }
}

void		release_sticks(int n)
{
  sem_post(&(sticks[n]));
  sem_post(&(sticks[(n + 1) % 7]));
}

void			wait_eating(int n)
{
  pthread_mutex_t	unused;
  struct timespec	time_to_wait;
  struct timeval	now;

  pthread_mutex_init(&unused, (const pthread_mutexattr_t*)0);
  pthread_mutex_lock(&unused);
  gettimeofday(&now, (struct timezone*)0);
  time_to_wait.tv_sec = now.tv_sec + 3;
  time_to_wait.tv_nsec = now.tv_usec * 1000;
  pthread_cond_timedwait(&(conds[n]), &unused, &time_to_wait);
  pthread_mutex_unlock(&unused);
  pthread_mutex_destroy(&unused);
}

void		philo_run(int *number)
{
  int		rice;
  int		n;

  rice = 10;
  n = *number;
  while (rice)
  {
    get_sticks(n);
    mod_status(n, EATING);
#ifdef DEBUG
    print_msg("%d is eating, %d rice left\n", n, rice);
#endif /* !DEBUG */
    wait_eating(n);
    rice -= 2;
    mod_status(n, RESTING);
#ifdef DEBUG
    print_msg("%d is resting\n", n);
#endif /* !DEBUG */
    release_sticks(n);
    sleep(1);
  }
}

int		main()
{
  int		i;
  int		current[7];
  pthread_t	threads[7];

  i = 0;
  while (i < 7)
  {
    if (sem_init(&(sticks[i]), 0, 1))
    {
      printf("ERROR: sem_init()\n");
      return (-1);
    }
    if (pthread_cond_init(&(conds[i]), (const pthread_condattr_t*)0))
    {
      printf("ERROR: pthread_cond_init()\n");
      return (-1);
    }
    states[i] = RESTING;
    i += 1;
  }
  if (sem_init(&(stdout_lock), 0, 1)
      || sem_init(&(access_states), 0, 1)
      || sem_init(&(disp), 0, 1))
  {
    printf("ERROR: sem_init()\n");
    return (-1);
  }
  i = 0;
  while (i < 7)
  {
    current[i] = i;
    if (pthread_create(&(threads[i]),
		       (const pthread_attr_t*)0,
		       (void *(*)(void*))&philo_run,
		       &(current[i])))
    {
      printf("ERROR: pthread_create()\n");
      return (-1);
    }
    i += 1;
  }
  i = 0;
  while (i < 7)
  {
    if (pthread_join(threads[i], (void**)0))
    {
      printf("ERROR: pthread_join()\n");
      return (-1);
    }
    i += 1;
  }
  i = 0;
  while (i < 7)
  {
    if (sem_destroy(&(sticks[i])))
    {
      printf("ERROR: sem_destroy()\n");
      return (-1);
    }
    if (pthread_cond_destroy(&(conds[i])))
    {
      printf("ERROR: pthread_cond_destroy()\n");
      return (-1);
    }
    i += 1;
  }
  if (sem_destroy(&(stdout_lock))
      || sem_destroy(&(access_states))
      || sem_destroy(&(disp)))
  {
    printf("ERROR: sem_destroy()\n");
    return (-1);
  }
}
