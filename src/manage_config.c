/*
** manage_config.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Mar  1 13:01:44 2015 chapui_s
** Last update Sun Mar  1 13:06:03 2015 chapui_s
*/

#include "philosophe.h"

static void	interpret_line(char *line)
{
  if (line && line[0] != '#' && line[0] != '\n')
  {
    if (!strncmp(line, "rices:", 6))
    {
      nb_rices = atoi(line + 6);
      nb_rices = (nb_rices >= 1) ? (nb_rices) : (10);
    }
    else if (!strncmp(line, "philos:", 7))
    {
      nb_philos = atoi(line + 7);
      nb_philos = (nb_philos >= 7) ? (nb_philos) : (7);
    }
    else if (!strncmp(line, "wait:", 5))
    {
      time_waiting = atoi(line + 5);
      time_waiting = (time_waiting >= 1) ? (time_waiting) : (3);
    }
    else if (!strncmp(line, "refresh:", 8))
    {
      time_refresh = atoi(line + 8);
      time_refresh = (time_refresh >= 1) ? (time_refresh) : (3);
    }
    else
      printf("Warning: invalid caracteristic in config file\n");
  }
}

void		get_config()
{
  FILE		*file;
  ssize_t	read;
  size_t	len;
  char		*line;

  nb_rices = 10;
  nb_philos = 7;
  time_waiting = 3;
  time_refresh = 3;
  if (!(file = fopen("config", "r")))
  {
    printf("Can't find config file, use default values\n");
  }
  else
  {
    printf("Reading file config...\n\n");
    line = (char*)0;
    while ((read = getline(&line, &len, file)) != -1)
      interpret_line(line);
    printf("nb_rices: %d\nnb_philos: %d\ntime_waiting: %d\nrefresh: %d\n\n",
	   nb_rices, nb_philos, time_waiting, time_refresh);
    free(line);
  }
}
