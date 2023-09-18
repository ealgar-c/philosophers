/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 17:01:08 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/09/07 14:12:04 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*void	ft_leaks(void)
{
	system("leaks -q philo");
	atexit(ft_leaks);
}*/

void	clr_routines(t_master *academy)
{
	int	i;

	i = 0;
	while (i < academy->number_of_philos)
	{
		pthread_mutex_destroy(&academy->arr_forks[i]);
		i++;
	}
	pthread_mutex_destroy(&academy->dr_mutexes->eating);
	pthread_mutex_destroy(&academy->dr_mutexes->dead);
	pthread_mutex_destroy(&academy->dr_mutexes->print);
	free(academy->arr_forks);
	free(academy->arr_philos);
	free(academy->arr_threads);
	free(academy->dr_mutexes);
}

int	main(int ac, char **av)
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
