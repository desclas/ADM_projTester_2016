/*
** test.c for  in /home/mathias/Bureau/projet_epitech/synthèse/ADM_projTester_2016
** 
** Made by Mathias
** Login   <mathias.descoin@epitech.eu@epitech.net>
** 
** Started on  Wed Jun 21 10:13:54 2017 Mathias
** Last update Wed Jun 21 18:05:16 2017 Mathias
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

char *free_tab(char **tab, int ex)
{
  int i;

  if (tab != NULL)
    {
      i = 0;
      while (tab[i] != NULL)
	{
	  free(tab[i]);
	  i += 1;
	}
      free(tab);
    }
  if (ex >= 0)
    exit(ex);
  else
    return (NULL);
}

char *cat_copy(char *str, char *cp)
{
  char *tmp;

  tmp = calloc(strlen(str) + 2 + strlen(cp), sizeof(char));
  tmp = strcpy(tmp, str);
  if (tmp[strlen(tmp) - 1] != '/')
    strcat(tmp, "/");
  strcat(tmp, cp);
  return (tmp);
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

void inistr(char *str, int max)
{
  int i;

  i = 0;
  while (i != max)
    {
      str[i] = '\0';
      i += 1;
    }
}

char **all_files(char **name, char *path)
{
  struct dirent **namelist;
  int n;
  char *tmp;
  int k;
  
  if ((k = scandir(path, &namelist, NULL, alphasort)) >= 0 && (n = 0) == 0)
    {
      while (n < k)
	{
	  if (namelist[n]->d_name[0] != '.')
	    {
	      tmp = cat_copy(path, namelist[n]->d_name);
	      name = append_chartab(name, tmp);
	      if (namelist[n]->d_type == DT_DIR &&
		  (tmp = cat_copy(path, namelist[n]->d_name)) != NULL)
		name = all_files(name, tmp);
	    }
	  free(namelist[n]);
	  n += 1;
	}
      free(namelist);
    }
  free(path);
  return (name);
}

int the_lvl(char *str, int sv)
{
  int i;
  int count;

  i = 0;
  count = 0;
  while (str[i + sv] != '\0')
    {
      if (str[i + sv] == '/')
	count += 1;
      i += 1;
    }
  return (count);
}

void print_lvl_name(int lvl, char *str, int sl)
{
  int i;

  while (lvl != 0)
    {
      printf("-----");
      lvl -= 1;
    }
  i = strlen(str);
  while (str[--i] != '/');
  if (sl == 1)
    printf("%s/\n", &str[i + 1]);
  else
    printf("%s\n", &str[i + 1]);
}

int my_cmp_inv(char *str, char *cmp)
{
  int i;

  i = 0;
  while (str[i] != '\0' && cmp[i] != '\0')
    {
      if (str[i] != cmp[i])
	return (1);
      i += 1;
    }
  if (str[i] == '\0')
    return (0);
  return (1);
}

void my_print(char **name)
{
  int i;
  int lvl;
  int sv;

  i = -1;
  while (name[0][++i] == '.' || name[0][i] == '/');
  printf("%s/\n", &name[0][i]);
  sv = i;
  i = 0;
  while (name[i] != NULL)
    {
      lvl = the_lvl(name[i], sv);
      if (name[i + 1] != NULL && my_cmp_inv(name[i], name[i + 1]) == 0)
	print_lvl_name(lvl, name[i], 1);
      else
	print_lvl_name(lvl, name[i], 0);
      i += 1;
    }
}

int main(int av, char **ac)
{
  char **names;
  char *path;

  if (av > 1)
    {
      if ((names = malloc(sizeof(char *))) == NULL ||
	  (path = calloc(strlen(ac[1]) + 1, sizeof(char))) == NULL)
	return (84);
      path = strcpy(path, ac[1]);
      names[0] = NULL;
      if ((names = all_files(names, path)) == NULL)
	return (84);
      my_print(names);
      free_tab(names, 0);
    }
  return (84);
}
