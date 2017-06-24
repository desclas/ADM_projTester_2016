/*
** get.c for  in /home/mathias/Bureau/projet_epitech/synthese/ADM_projTester_2016
** 
** Made by Mathias
** Login   <mathias.descoin@epitech.eu@epitech.net>
** 
** Started on  Sat Jun 24 10:12:07 2017 Mathias
** Last update Sat Jun 24 10:13:21 2017 Mathias
*/

#include "proj.h"

void print_first(char *name)
{
  int i;
  DIR *fd;

  if ((fd = opendir(name)) == NULL)
    exit(84);
  else
    closedir(fd);
  i = strlen(name) - 1;
  while (--i > 0 && name[i] != '/');
  if (i < 0)
    i = 0;
  if (name[strlen(name) - 1] == '/')
    printf("%s\n", &name[i]);
  else
    printf("%s/\n", &name[i]);
}

char **split(char *str, char sp)
{
  char **res;
  int i;
  char *tmp;

  res = malloc(sizeof(char *));
  res[0] = NULL;
  i = 0;
  tmp = calloc(1, sizeof(char));
  while (str[i] != '\0')
    {
      if (str[i] == sp)
	{
	  while (str[++i] == sp);
	  i -= 1;
	  res = append_chartab(res, tmp);
	  tmp = calloc(1, sizeof(char));
	}
      else
	tmp = append_char(tmp, str[i]);
      i += 1;
    }
  return (append_chartab(res, tmp));
}

void free_tab(char **tab, char *str, int ex, int find)
{
  int i;

  i = 0;
  if (str != NULL)
    free(str);
  if (tab != NULL)
    {
      while (tab[i] != NULL)
	{
	  free(tab[i]);
	  i += 1;
	}
      free(tab);
    }
  if (find == 1)
    dprintf(2, "binary not found\n");
  if (ex >= 0)
    exit(ex);
}

void check_bin(char *name, int ch)
{
  char *tmp;
  char **sv;
  int i;

  if (access(name, F_OK | X_OK) != 0)
    {
      if ((tmp = getenv("PATH")) == NULL)
	exit(84);
      sv = split(tmp, ':');
      i = 0;
      while (sv[i] != NULL)
	{
	  ch = 0;
	  tmp = cat_copy(sv[i], name);
	  if (access(tmp, F_OK | X_OK) == 0)
	    break;
	  free(tmp);
	  ch = 1;
	  i += 1;
	}
      if (ch != 0)
	free_tab(sv, NULL, 84, 1);
      free_tab(sv, tmp, -1, 0);
    }
}

char *get_all_file(char *name)
{
  int fd;
  char *str;
  char c;

  if ((fd = open(name, O_RDONLY)) == -1)
    return (NULL);
  str = calloc(1, sizeof(char));
  c = '\0';
  while (read(fd, &c, 1) > 0)
    str = append_char(str, c);
  close(fd);
  return (str);
}
