#include "../minishell.h"

void	set_fd_out(t_cmd *cmd_list, int i)
{
	if (cmd_list->redir_out)
	{
		dup2(g_shell.fd_write, STDOUT_FILENO);
		close(g_shell.fd_write);
	}
	if (cmd_list->pipe_out == pipe_out)
	{
		if (!cmd_list->redir_out)
		{
			dup2(g_shell.fds[i][1], STDOUT_FILENO);
			close (g_shell.fds[i][1]);
		}
	}
	if (!cmd_list->next && !g_shell.cmd_list->redir_out)
	{
		dup2(g_shell.stdout, STDOUT_FILENO);
	}
}

void	set_fd(t_cmd *cmd_list, int i)
{	
	if (cmd_list->redir_in)
	{
		dup2(g_shell.fd_read, STDIN_FILENO);
		close(g_shell.fd_read);
	}
	else if (cmd_list->pipe_in == pipe_in)
	{
		if (i > 0)
		{
			dup2(g_shell.fds[i - 1][0], STDIN_FILENO);
			close(g_shell.fds[i - 1][0]);
		}
	}
	set_fd_out(cmd_list, i);
}

int	try_builtin(char **args, int j)
{
	int	i;

	i = 0;
	g_shell.status = 0;
	while (g_shell.builtin_names[i] && \
		ft_strcmp(g_shell.builtin_names[i], args[0]))
		i++;
	if (g_shell.builtin_names[i])
	{
		set_fd(g_shell.cmd_list, j);
		(*g_shell.builtin_funcs[i])();
		dup2(g_shell.stdin, STDIN_FILENO);
		dup2(g_shell.stdout, STDOUT_FILENO);
		return (1);
	}
	return (0);
}

void	exe(t_cmd *cmd_list, int i, int j)
{
	char	*str;

	g_shell.pids[i] = fork();
	signal_init();
	if (g_shell.pids[i] == -1)
	{
		print_error("-", "fork() error");
		return ;
	}
	else if (g_shell.pids[i] == 0)
	{
		signal_init_here();
		set_fd(cmd_list, j);
		close_fds(g_shell.fds);
		execve(cmd_list->args[0], cmd_list->args, g_shell.env);
		str = ft_strjoin("minishell: ", cmd_list->args[0]);
		perror(str);
		free (str);
		exit (126);
	}
}

int	execution(void)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (get_pids_fds(g_shell.cmd_list) == 0)
		return (0);
	while (g_shell.cmd_list)
	{
		if (open_redirs(g_shell.cmd_list) && g_shell.cmd_list->args[0] \
			&& !try_builtin (g_shell.cmd_list->args, j))
		{
			if (parse_cmds(g_shell.cmd_list))
			{
				exe(g_shell.cmd_list, i, j);
				i++;
			}
		}
		j++;
		g_shell.cmd_list = g_shell.cmd_list->next;
	}
	cmd_end_works(g_shell.fds, g_shell.pids, i);
	return (0);
}