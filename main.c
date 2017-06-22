/*
** main.c for  in /home/mathias/Bureau/projet_epitech/synthese/ADM_projTester_2016
** 
** Made by Mathias
** Login   <mathias.descoin@epitech.eu@epitech.net>
** 
** Started on  Thu Jun 22 10:43:31 2017 Mathias
** Last update Thu Jun 22 11:56:31 2017 Mathias
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

void print_lvl(int lvl, char *name, int dir)
{
  while (lvl != 0)
    {
      printf("-----");
      lvl -= 1;
    }
  if (dir == 1)
    printf("%s/\n", name);
  else
    printf("%s\n", name);
}

char *cat_copy(char *str, char *cp)
{
  char *res;

  res = calloc(strlen(str) + strlen(cp) + 2, sizeof(char));
  strcat(res, str);
  if (str[strlen(str) - 1] != '/')
    strcat(res, "/");
  strcat(res, cp);
  return (res);
}

void disp_all_file(char *name, int lvl)
{
  struct dirent **namelist;
  int n;
  int k;

  k = -1;
  n = scandir(name, &namelist, NULL, alphasort);
  if (n >= 0)
    {
      while (++k != n)
	{
	  if (namelist[k]->d_name[0] != '.')
	    {
	      if (namelist[k]->d_type == DT_DIR)
		{
		  print_lvl(lvl, namelist[k]->d_name, 1);
		  disp_all_file(cat_copy(name, namelist[k]->d_name), lvl + 1);
		}
	      else
		print_lvl(lvl, namelist[k]->d_name, 0);
	    }
	  free(namelist[k]);
	}
      free(namelist);
    }
  free(name);
}

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

int main(int av, char **ac)
{
  char *str;

  str = calloc(strlen(ac[1]) + 1, sizeof(char));
  strcpy(str, ac[1]);
  if (av == 2)
    {
      print_first(str);
      disp_all_file(str, 1);
    }
  return (0);
}
