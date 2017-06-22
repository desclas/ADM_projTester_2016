/*
** requirement.c for  in /home/mathias/Bureau/projet_epitech/synthèse/ADM_projTester_2016
** 
** Made by Mathias
** Login   <mathias.descoin@epitech.eu@epitech.net>
** 
** Started on  Wed Jun 21 09:05:29 2017 Mathias
** Last update Thu Jun 22 09:17:08 2017 Mathias
*/

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void my_ps_synthesis()
{
  int pid;

  if ((pid = fork()) == 0)
    execl("/bin/sh", "sh", "-c", "ps", (char *) 0);
  else if (pid > 0)
    wait(&pid);
}
