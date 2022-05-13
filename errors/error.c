#include "../minishell.h"

void	print_error(char *arg, char *err_name)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(err_name, STDERR_FILENO);
}

void	exit_with_error(char *str)
{
	ft_putendl_fd(str, STDERR_FILENO);
	clear_all(&g_shell);
	exit(1);
}