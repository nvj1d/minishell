/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajid <mnajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 19:17:28 by mnajid            #+#    #+#             */
/*   Updated: 2022/05/09 19:23:06 by mnajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	main(int ac, char **av, char **env)
{
	char	*cmd;

	(void)av;
	if (ac != 1)
	{
		//print not a valid argument!
		//return some value here!
	}
	//print the head 'MINISHELL'
	// env is a global var
	ft_init(env);
}