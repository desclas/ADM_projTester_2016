/*
** proj.h for  in /home/mathias/Bureau/projet_epitech/synthese/ADM_projTester_2016
** 
** Made by Mathias
** Login   <mathias.descoin@epitech.eu@epitech.net>
** 
** Started on  Sat Jun 24 10:07:13 2017 Mathias
** Last update Sat Jun 24 10:16:12 2017 Mathias
*/

#ifndef PROJ_H_
# define PROJ_H_

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <dirent.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>

typedef struct s_all
{
  char **arg;
  int input;
  char *res;
}		t_all;

char *append_char(char *str, char c);
char **append_chartab(char **tab, char *str);
void print_lvl(int lvl, char *name, int dir);
char *cat_copy(char *str, char *cp);
void disp_all_file(char *name, int lvl);
void print_first(char *name);
char **split(char *str, char sp);
void free_tab(char **tab, char *str, int ex, int find);
void check_bin(char *name, int ch);
char *get_all_file(char *name);
char *get_it_all_fd(int fd);
char **print_exec_begin(char **arg, char *bin);
void putstr(char *str, char *plus);
void print_exec(char **arg, char *bin);
int my_cmp(char *str, char *cmp);

#endif /* !PROJ_H_ */
