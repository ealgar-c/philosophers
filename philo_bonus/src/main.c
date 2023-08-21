/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 17:01:08 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/08/21 17:55:14 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sn;
	int	num;

	i = 0;
	sn = 1;
	num = 0;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\t' || str[i] == '\v')
		i++;
	if (str[i] == '-')
		sn *= -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (str[i] - 48) + (num * 10);
		i++;
	}
	num *= sn;
	return (num);
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
		init_semaphores(&academy);
		init_philos(&academy);
		crt_routines(&academy);
		clr_routines(&academy);
	}
	else
		bad_args();
	return (0);
}
