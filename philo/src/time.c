/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:41:54 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/09/12 17:20:06 by ealgar-c         ###   ########.fr       */
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
	if (time <= 0)
		usleep(0);
	else
		usleep(time * 1000);
}
