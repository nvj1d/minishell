#include "minishell.h"

void	signal_handler(void)
{
	signal(SIGINT, sig_init);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_init_here(void)
{
	signal(SIGINT, SIG_DFL);
}

void	signal_init(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}

void	sig_init(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
	write(2, "  \n", 3);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_shell.status = 1;
}