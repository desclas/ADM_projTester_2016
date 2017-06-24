/*
** main.c for  in /home/mathias/Bureau/projet_epitech/synthese/ADM_projTester_2016
** 
** Made by Mathias
** Login   <mathias.descoin@epitech.eu@epitech.net>
** 
** Started on  Thu Jun 22 10:43:31 2017 Mathias
** Last update Sat Jun 24 10:22:45 2017 Mathias
*/

#include "proj.h"

void exec_it_begin_sequel(char *name, int *file)
{
  int i;
  
  i = *file - 1;
  write(1, "[", 1);
  while (name[++i] != '/')
    write(1, &name[i], 1);
  write(1, "] ", 2);
  *file = i + 1;
}

void exec_it_begin(char *name, int file)
{
  int i;

  while (name[file] != '\0')
    {
      i = file;
      while (name[++i] != '\0' && name[i] != '/');
      if (name[i] == '/')
	exec_it_begin_sequel(name, &file);
      else
	{
	  putstr(&name[file], ": ");
	  file = i;
	}
    }
}

char *take_path(char *file, char *path)
{
  char *str;
  int i;

  str = calloc(strlen(file) + strlen(file) + 2, sizeof(char));
  strcpy(str, path);
  i = strlen(path);
  while (str[--i] != -1 && str[i] != '/');
  while (str[++i] != '\0')
    str[i] = '\0';
  strcat(str, file);
  return (str);
}

void print_whith_res(t_all *all, char *bin)
{
  int file;
  char *tmp;
  int pipe_fd[2];

  pipe(pipe_fd);
  if (fork() > 0)
    {
      close(pipe_fd[1]);
      wait(&file);
      tmp = get_it_all_fd(pipe_fd[0]);
      (my_cmp(tmp, all->res) == 0 ? printf("OK\n") : printf("KO\n"));
    }
  else
    {
      close(pipe_fd[0]);
      dup2(all->input, 0);
      dup2(pipe_fd[1], 1);
      execvp(bin, all->arg);
      exit(0);
    }
  close(pipe_fd[0]);
  free(tmp);
}

void print_exec_input_and_res(t_all *all, char *bin, char *name, int file)
{
  if (all->input != -1)
    {
      exec_it_begin(name, file);
      if (all->res != NULL)
	print_whith_res(all, bin);
      else
	{
	  if (fork() > 0)
	    wait(&file);
	  else
	    {
	      dup2(all->input, 0);
	      execvp(bin, all->arg);
	      exit(0);
	    }
	}
    }
}

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
