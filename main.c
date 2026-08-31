/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerr <chguerr@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 12:57:51 by chguerr           #+#    #+#             */
/*   Updated: 2026/08/31 14:06:27 by chguerr          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
typedef struct s_cmd
{
	char *path;
	char **args;
} t_cmd;

void parssing_cmd(t_cmd *cmd, char *path, char **arg)
{
	(*cmd).path =  path;
	(*cmd).args = arg;
}

int main(void)
{
	t_cmd cmd[3];
	pid_t pid[3];
	int n;
	int fd[2];
	int old_fd;
	int i;

	n = 3;
	old_fd = -1;
	i = 0;
	while(i < 3)
	{
		if(i < n -1)
			pipe(fd);
		pid[i] = fork();
		if(pid[i] == 0)
		{
			if(old_fd != -1)
			{
				dup2(old_fd, STDIN_FILENO);
				close(old_fd);
			}
			if(i < n - 1)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
				close(fd[0]);
			}
			if(i == 0)
				parssing_cmd(&cmd[i], "/usr/bin/ls", (char*[]){"ls",NULL} );
			else if (i == 1)
				parssing_cmd(&cmd[i], "/usr/bin/grep", (char*[]){"grep","a", NULL} );
			else if (i == 2)
				parssing_cmd(&cmd[i], "/usr/bin/cat", (char*[]){"cat",NULL} );
			execve(cmd[i].path, cmd[i].args, NULL);
			perror(cmd[i].path);
			exit(127);
		}
		if(old_fd != -1)
			close(old_fd);
		old_fd = fd[0];
		if(i < n -1)
			close(fd[1]);
		i++;
	}
	wait(NULL);
	wait(NULL);
	wait(NULL);
	return (0);
}