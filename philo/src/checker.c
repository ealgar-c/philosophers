/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:41:31 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/09/21 15:20:32 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (true);
	return (false);
}

static bool	valid_atoi(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	check_args(int ac, char **av)
{
	if (valid_atoi(av[1]) && valid_atoi(av[2]) && valid_atoi(av[3])
		&& valid_atoi(av[4]))
	{
		if (ft_atoi(av[1]) == 0)
			return (false);
		if (ac == 6)
		{
			if (valid_atoi(av[5]))
				return (true);
		}
		else
			return (true);
	}
	return (false);
}

void	bad_args(void)
{
	printf("Bad arguments, Execute the program as shown below:\n");
	printf("./philo number_of_philosophers time_to_die time_to_eat ");
	printf("time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
}
