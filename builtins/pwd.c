
void	pwd(void)
{
	char	*pwd;
	char	buf[4096];

	pwd = getcwd(buf, sizeof(buf));
	if (pwd)
	{
		ft_putendl_fd(buf, STDOUT_FILENO);
		g_shell.status = 0;
	}
	else
	{
		perror("minishell: pwd: ");
		g_shell.status = 127;
	}
}