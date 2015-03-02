/*
** philosophe.h for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Mar  1 12:47:38 2015 chapui_s
** Last update Sun Mar  1 15:18:53 2015 chapui_s
*/

#ifndef PHILOSOPHE_H_
# define PHILOSOPHE_H_

# include <semaphore.h>
# include <pthread.h>
# include <stdio.h>
# include <time.h>
# include <stdarg.h>
# include <unistd.h>
# include <sys/time.h>
# include <SDL/SDL.h>
# include <fcntl.h>
# include <string.h>

typedef enum	e_state
{
  EATING,
  THINKING,
  RESTING
}		t_state;

typedef struct	s_sdl
{
  SDL_Surface	*ecran;
  SDL_Surface	*image_fond;
  SDL_Surface	**tab_philo;
  SDL_Surface	**tab_etat;
  SDL_Surface	*surface_thinking;
  SDL_Surface	*surface_eating;
  SDL_Surface	*surface_resting;
  SDL_Surface	*surface_philo;
  SDL_Rect	*tab_pos_philo;
  SDL_Rect	*tab_pos_etat;
  SDL_Rect	position_fond;
}		t_sdl;

sem_t		*sticks;
sem_t		stdout_lock;
pthread_cond_t	*conds;
pthread_cond_t	cond_disp;
t_state		*states;
sem_t		access_states;
int		run;
int		nb_philos;
int		time_waiting;
int		nb_rices;
int		time_refresh;

# ifndef DEBUG
t_sdl		*init_SDL(void);
void		update_picture(t_sdl *struct_sdl, t_state *states_tmp, int i);
# endif /* !DEBUG */

void		print_msg(char *fmt, ...);
void		update_states(t_state *states_tmp, int i);
void		get_states(t_state *states_tmp);
void		init_le_bordel(pthread_mutex_t *unused,
			       t_state *states_tmp,
			       t_sdl *struct_sdl);
void		destroy_le_bordel(t_sdl *struct_sdl);
void		disp_philo(t_sdl *struct_sdl);
t_state		check_status(int n);
void		mod_status(int n, t_state state);
void		philo_run(int *number);
void		get_config();
int		init_all(int **current,
			 pthread_t **threads,
			 t_sdl **struct_sdl);
int		destroy_all(int *current, pthread_t *threads);

#endif /* !PHILOSOPHE_H_ */
