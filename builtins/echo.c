void	echo_work(char **args, int len)
{
	int	j;

	j = 1;
	if (!ft_strcmp(args[1], "-n"))
		j++;
	while (args[j])
	{
		ft_putstr_fd(args[j], STDOUT_FILENO);
		if (j++ < len - 1)
			write(STDOUT_FILENO, " ", STDOUT_FILENO);
	}
}

void	echo(void)
{
	int		len;
	char	**args;

	len = 0;
	args = g_shell.cmd_list->args;
	while (args[len])
		len++;
	if (len == 1)
	{
		write(STDOUT_FILENO, "\n", 1);
		return ;
	}
	if (len >= 2)
		echo_work(args, len);
	if (ft_strcmp(args[1], "-n"))
		write(STDOUT_FILENO, "\n", 1);
}