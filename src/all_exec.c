/*
** all_exec.c for  in /home/mathias/Bureau/projet_epitech/synthese/ADM_projTester_2016
** 
** Made by Mathias
** Login   <mathias.descoin@epitech.eu@epitech.net>
** 
** Started on  Sat Jun 24 10:55:57 2017 Mathias
** Last update Sat Jun 24 10:57:07 2017 Mathias
*/

#include "proj.h"

t_all *fill_it(char *str, char *bin, char *name)
{
  t_all *all;
  char **tmp;
  char *tp;

  all = malloc(sizeof(t_all));
  tmp = split(str, '\n');
  tp = NULL;
  all->arg = print_exec_begin(split(&tmp[0][5], ' '), bin);
  all->input = 0;
  if (tmp[1] != NULL && my_cmp(tmp[1], "INPUT:") == 0)
    tp = take_path(&tmp[1][6], name);
  all->res = NULL;
  if (tmp[1] != NULL && my_cmp(tmp[1], "INPUT:") == 0)
    all->input = open(tp, O_RDONLY);
  if (tmp[1] != NULL && my_cmp(tmp[1], "RES:") == 0)
    all->res = &str[strlen(tmp[0]) + 5];
  else if (tmp[1] != NULL && tmp[2] != NULL && my_cmp(tmp[2], "RES:") == 0)
    all->res = &str[strlen(tmp[0]) + strlen(tmp[1]) + 6];
  free_tab(tmp, tp, -1, 0);
  return (all);
}

void free_struct(t_all *all)
{
  free_tab(all->arg, NULL, -1, 0);
  if (all->input != -1)
    close(all->input);
  free(all);
}

void exec_it_sequel(char *name, char *bin, char *file, char *str)
{
  t_all *all;

  all = fill_it(str, bin, name);
  if (all->input != -1 || all->res != NULL)
    print_exec_input_and_res(all, bin, name, (file[strlen(file) - 1] == '/' ?
					     strlen(file) : strlen(file) + 1));
  else
    {
      exec_it_begin(name, (file[strlen(file) - 1] == '/' ?
			   strlen(file) : strlen(file) + 1));
      print_exec(all->arg, bin);
    }
  free_struct(all);
}

void exec_it(char *name, char *bin, char *file)
{
  char *str;

  if ((str = get_all_file(name)) != NULL)
    {
      if (my_cmp(str, "ARGS:") == 0)
	exec_it_sequel(name, bin, file, str);
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
	      else if (namelist[k]->d_type == DT_REG &&
		       my_cmp(&namelist[k]->d_name[strlen(namelist[k]->d_name)
						  - 4], ".tdf") == 0)
		exec_it(cat_copy(name, namelist[k]->d_name), bin, file);
	    }
	  free(namelist[k]);
	}
      free(namelist);
    }
  free(name);  
}
