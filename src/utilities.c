/*
** utilities.c for  in /home/mathias/Bureau/projet_epitech/synthese/ADM_projTester_2016
** 
** Made by Mathias
** Login   <mathias.descoin@epitech.eu@epitech.net>
** 
** Started on  Sat Jun 24 10:09:04 2017 Mathias
** Last update Sat Jun 24 10:10:29 2017 Mathias
*/

#include "proj.h"

char *append_char(char *str, char c)
{
  int i;

  i = strlen(str);
  str = realloc(str, sizeof(char) * (i + 2));
  str[i] = c;
  str[i + 1] = '\0';
  return (str);
}

char **append_chartab(char **tab, char *str)
{
  int i;

  i = -1;
  while (tab[++i] != NULL);
  tab = realloc(tab, sizeof(char *) * (i + 2));
  tab[i] = str;
  tab[i + 1] = NULL;
  return (tab);
}

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
