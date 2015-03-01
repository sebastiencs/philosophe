/*
** access_status.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Mar  1 13:11:32 2015 chapui_s
** Last update Sun Mar  1 13:11:37 2015 chapui_s
*/

#include "philosophe.h"

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
  sem_wait(&(access_states));
  states[n] = state;
  sem_post(&(access_states));
#ifndef DEBUG
  pthread_cond_signal(&cond_disp);
#endif /* !DEBUG */
}
