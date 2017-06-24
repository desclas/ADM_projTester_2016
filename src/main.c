/*
** main.c for  in /home/mathias/Bureau/projet_epitech/synthese/ADM_projTester_2016
** 
** Made by Mathias
** Login   <mathias.descoin@epitech.eu@epitech.net>
** 
** Started on  Thu Jun 22 10:43:31 2017 Mathias
** Last update Sat Jun 24 10:57:11 2017 Mathias
*/

#include "proj.h"

void main_sequel(int av, char **ac, char *str)
{
  int fd;

  if (access(str, F_OK | R_OK) != 0)
    free_tab(NULL, str, 84, 0);
  check_bin(ac[2], 3);
  if (av == 3)
    all_exec(str, ac[2], ac[1]);
  else if (av == 4)
    {
      if ((fd = open(ac[3], O_CREAT | O_RDWR | O_APPEND,
		     S_IRWXU | S_IRWXG | S_IRWXO)) == -1)
	free_tab(NULL, str, 84, 0);
      dup2(fd, 1);
      all_exec(str, ac[2], ac[1]);
      close(fd);
    }
}

int main(int av, char **ac)
{
  char *str;

  if (av > 1)
    {
      str = calloc(strlen(ac[1]) + 1, sizeof(char));
      strcpy(str, ac[1]);
      if (av == 2)
	{
	  if (access(str, F_OK | R_OK) != 0)
	    free_tab(NULL, str, 84, 0);
	  print_first(str);
	  disp_all_file(str, 1);
	}
      else if (av == 3 || av == 4)
	main_sequel(av, ac, str);
      else
	free_tab(NULL, str, 84, 0);
      return (0);
    }
  return (84);
}
