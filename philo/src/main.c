/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 17:01:08 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/09/06 15:06:37 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"



/* void	ft_leaks(void)
{
	system("leaks -q philo");
	atexit(ft_leaks);
} */

int	main(int ac, char **av) // hay que comprobar los leaks de momoria aunque no deberia de haber.
{
	t_master	academy;

	if (ac == 5 || ac == 6)
	{
		if (!check_args(ac, av))
		{
			bad_args();
			return (0);
		}
		init_academy(&academy, ac, av);
		init_forks(&academy);
		init_philos(&academy);
		init_mutexes(&academy);
		crt_routines(&academy);
		clr_routines(&academy);
	}
	else
		bad_args();
	return (0);
}
