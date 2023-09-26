/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:41:54 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/09/21 15:18:11 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	get_actual_time(void)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

long	process_timer(t_philo *philo)
{
	return (get_actual_time() - philo->academy->init_time);
}

void	ft_usleep(int time)
{
	long	end;

	end = get_actual_time() + time;
	while (get_actual_time() < end)
		usleep(10);
}

/* void	ft_usleep(int time)
{
	if (time <= 0)
		usleep(0);
	else
		usleep(time * 1000);
} */
