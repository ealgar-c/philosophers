/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:42:16 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/08/25 12:49:09 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_academy(t_master *academy, int ac, char **av)
{
	academy->number_of_philos = ft_atoi(av[1]);
	academy->time_to_die = ft_atoi(av[2]);
	academy->time_to_eat = ft_atoi(av[3]);
	academy->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		academy->nb_of_meals = ft_atoi(av[5]);
	else
		academy->nb_of_meals = -1;
	academy->arr_threads = malloc(sizeof(pthread_t)
			* academy->number_of_philos);
	academy->arr_philos = malloc(sizeof(t_philo) * academy->number_of_philos);
	academy->arr_forks = malloc(sizeof(pthread_mutex_t)
			* academy->number_of_philos);
}

void	init_forks(t_master *academy)
{
	int	i;

	i = 0;
	while (i < academy->number_of_philos)
	{
		pthread_mutex_init(&academy->arr_forks[i], NULL);
		i++;
	}
}

void	init_philos(t_master *academy)
{
	int	i;

	i = 0;
	while (i < academy->number_of_philos)
	{
		academy->arr_philos[i].index = i + 1;
		academy->arr_philos[i].nb_of_meals = 0;
		academy->arr_philos[i].last_meal = get_actual_time();
		academy->arr_philos[i].academy = academy;
		academy->arr_philos[i].left_fork = &academy->arr_forks[i];
		if (i == academy->number_of_philos - 1)
			academy->arr_philos[i].right_fork = &academy->arr_forks[0];
		else
			academy->arr_philos[i].right_fork = &academy->arr_forks[i + 1];
		i++;
	}
}
