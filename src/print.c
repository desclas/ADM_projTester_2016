/*
** print.c for  in /home/mathias/Bureau/projet_epitech/synthese/ADM_projTester_2016
** 
** Made by Mathias
** Login   <mathias.descoin@epitech.eu@epitech.net>
** 
** Started on  Sat Jun 24 10:14:49 2017 Mathias
** Last update Sat Jun 24 14:27:13 2017 Mathias
*/

#include "proj.h"

char *get_it_all_fd(int fd)
{
  char *str;
  char c;

  str = calloc(1, sizeof(char));
  c = '\0';
  while (read(fd, &c, 1) > 0)
    str = append_char(str, c);
  close(fd);
  return (str);
}

char **print_exec_begin(char **arg, char *bin)
{
  char **tmp;
  char *str;
  int i;

  tmp = malloc(sizeof(char *) * 2);
  str = calloc(strlen(bin) + 2, sizeof(char));
  strcpy(str, bin);
  tmp[0] = str;
  tmp[1] = NULL;
  i = -1;
  while (arg[++i] != NULL)
    tmp = append_chartab(tmp, arg[i]);
  return (tmp);
}

void putstr(char *str, char *plus)
{
  write(1, str, strlen(str) - 4);
  write(1, plus, strlen(plus));
}

void print_exec(char **arg, char *bin)
{
  int i;

  if (fork() == 0)
    {
      (access(bin, F_OK | X_OK) == 0 ? execv(bin, arg) : execvp(bin, arg));
      exit(0);
    }
  else
    wait(&i);
}

int my_cmp(char *str, char *cmp)
{
  int i;

  i = 0;
  while (str[i] != '\0' && cmp[i] != '\0')
    {
      if (str[i] != cmp[i])
	return (1);
      i += 1;
    }
  if (cmp[i] == '\0')
    return (0);
  return (1);
}
