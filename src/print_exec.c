/*
** print_exec.c for  in /home/mathias/Bureau/projet_epitech/synthese/ADM_projTester_2016
** 
** Made by Mathias
** Login   <mathias.descoin@epitech.eu@epitech.net>
** 
** Started on  Sat Jun 24 10:53:57 2017 Mathias
** Last update Sat Jun 24 15:30:04 2017 Mathias
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

  str = calloc(strlen(path) + strlen(file) + 2, sizeof(char));
  strcpy(str, path);
  i = strlen(path);
  while (--i != -1 && str[i] != '/');
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
      dup2((all->input == -1 ? 0 : all->input), 0);
      dup2(pipe_fd[1], 1);
      (access(bin, F_OK | X_OK) == 0 ?
       execv(bin, all->arg) : execvp(bin, all->arg));
      exit(0);
    }
  close(pipe_fd[0]);
  free(tmp);
}

void print_exec_input_and_res(t_all *all, char *bin, char *name, int file)
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
	  dup2((all->input == -1 ? 0 : all->input), 0);
	  (access(bin, F_OK | X_OK) == 0 ?
	   execv(bin, all->arg) : execvp(bin, all->arg));
	  exit(0);
	}
    }
}
