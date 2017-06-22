/*
** main.c for  in /home/mathias/Bureau/projet_epitech/synthese/ADM_projTester_2016
** 
** Made by Mathias
** Login   <mathias.descoin@epitech.eu@epitech.net>
** 
** Started on  Thu Jun 22 10:43:31 2017 Mathias
** Last update Thu Jun 22 17:12:41 2017 Mathias
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

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

void print_exec(char *name, char **arg, char *bin, int file)
{
  int i;
  char **tmp;

  tmp = print_exec_begin(arg, bin);
  while (name[file] != '\0')
    {
      i = file;
      while (name[++i] != '\0' && name[i] != '/');
      if (name[i] == '/')
	{
	  i = file - 1;
	  write(1, "[", 1);
	  while (name[++i] != '/')
	    write(1, &name[i], 1);
	  write(1, "] ", 2);
	  file = i + 1;
	}
      else
	{
	  putstr(&name[file], ": ");
	  file = i;
	}
    }
  if (fork() == 0)
    {
      if (execvp(bin, tmp) < 1)
	printf("llllllllllllllllllllllllllllllllllllllllllll\n");
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

void exec_it(char *name, char *bin, char *file)
{
  char **tmp;
  char *str;
  char **arg;

  if ((str = get_all_file(name)) != NULL)
    {
      if (my_cmp(str, "ARGS:") == 0)
	{
	  tmp = split(str, '\n');
	  arg = split(&tmp[0][5], ' ');
	  print_exec(name, arg, bin, (file[strlen(file) - 1] == '/' ?
				       strlen(file) : strlen(file) + 1));
	  free_tab(arg, NULL, -1, 0);
	  free_tab(tmp, NULL, -1, 0);
	}
      free(str);
    }
  free(name);
}

void all_exec(char *name, char *bin, char *file)
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
		all_exec(cat_copy(name, namelist[k]->d_name), bin, file);
	      else if (namelist[k]->d_type == DT_REG)
		exec_it(cat_copy(name, namelist[k]->d_name), bin, file);
	    }
	  free(namelist[k]);
	}
      free(namelist);
    }
  free(name);  
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
	{
	  if (access(str, F_OK | R_OK) != 0)
	    free_tab(NULL, str, 84, 0);
	  check_bin(ac[2], 3);
	  if (av == 3)
	    all_exec(str, ac[2], ac[1]);
	  /* else if (av == 4) */
	  /*   ; */
	}
      return (0);
    }
  return (84);
}
