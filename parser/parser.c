void	add_pipe(int i)
{
	while (g_shell.cmd_list)
	{
		if (i == 0 && g_shell.cmd_list->next)
		{
			g_shell.cmd_list->pipe_in = default_pipe_in;
			g_shell.cmd_list->pipe_out = pipe_out;
		}
		if (i > 0 && g_shell.cmd_list->next)
		{
			g_shell.cmd_list->pipe_in = pipe_in;
			g_shell.cmd_list->pipe_out = pipe_out;
		}
		if (i > 0 && !g_shell.cmd_list->next)
		{
			g_shell.cmd_list->pipe_in = pipe_in;
			g_shell.cmd_list->pipe_out = default_pipe_out;
		}
		i++;
		g_shell.cmd_list = g_shell.cmd_list->next;
	}
}
void	check_pipe(void)
{
	t_cmd	*temp;

	temp = g_shell.cmd_list;
	add_pipe(0);
	g_shell.cmd_list = temp;
}

void	split_cmd(char *str)
{
	int		i;
	char	ch;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			ch = str[i];
			while (str[++i] && str[i] != ch)
				;
		}
		if (str[i] == '|')
			str = pipe_parse(&i, str, 0, 0);
	}
	str = pipe_parse(&i, str, 0, 0);
	free(str);
}

void	*parser(char *str)
{
	if (str == NULL)
	{
		ft_putendl_fd("\033[0;33mMinishell\033[0;32m ⎇ \033[4;0m exit", 2);
		exit(0);
	}
	if (str && str[0] == '\0')
	{
		free(str);
		return (NULL);
	}
	else if (!preparsing(str) || str[0] == '|')
	{
		free(str);
		error_parser("minishell: syntax error near unexpected token");
	}
	else
	{
		str = check_syntax(str, -1, 0);
		split_cmd(str);
		check_pipe();
	}
	return (NULL);
}
