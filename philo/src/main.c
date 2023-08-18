/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 17:01:08 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/08/18 17:30:58 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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

bool	valid_atoi(char *str)
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
		if (ac == 6)
		{
			if (valid_atoi(av[5]))
				return (true);
		}
		else
			return (true);
	}
}

void	bad_args(void)
{
	printf("Bad arguments, Execute the program as shown below:\n");
	printf("./philo number_of_philosophers time_to_die time_to_eat ");
	printf("time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	exit(1);
}

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
		academy->arr_philos[i].last_meal_ts = 0;
		academy->arr_philos[i].academy = academy;
		academy->arr_philos[i].left_fork = &academy->arr_forks[i];
		if (i == academy->number_of_philos - 1)
			academy->arr_philos[i].right_fork = &academy->arr_forks[0];
		else
			academy->arr_philos[i].right_fork = &academy->arr_forks[i + 1];
		i++;
	}
}

int	main(int ac, char **av)
{
	t_master	academy;

	if (ac == 5 || ac == 6)
	{
		if (!check_args(ac, av))
			bad_args();
		init_academy(&academy, ac, av);
		init_forks(&academy);
		init_philos(&academy);
		init_threads(&academy);
		close_threads(&academy);
	}
	return (0);
}

/* t_master	*init_academy(int ac, char **av)
{
	t_master	*academy;

	academy = malloc(sizeof(t_master));
	if (!academy)
		return (NULL);
	academy->number_of_philos = ft_atoi(av[1]);
	academy->philos = malloc(sizeof(t_philo) * academy->number_of_philos);
	academy->forks = malloc(sizeof(t_fork) * academy->number_of_philos);
	if (!academy->philos)
		return (NULL);
	academy->time_to_die = ft_atoi(av[2]);
	academy->time_to_eat = ft_atoi(av[3]);
	academy->time_to_sleep = ft_atoi(av[4]);
	gettimeofday(&academy->init_ts, NULL);
	academy->nb_of_meals = 0;
	if (ac == 6)
		academy->nb_of_meals = ft_atoi(av[5]);
	academy->actual_group = 1;
	return (academy);
}

void	init_philos(t_master *academy)
{
	int	i;

	i = -1;
	while (i++ < academy->number_of_philos - 1)
	{
		academy->philos[i].index = i + 1;
		gettimeofday(&academy->philos[i].last_meal_ts, NULL);
		academy->philos[i].nb_of_meals = 0;
		if (i == 0)
		{
			academy->philos[i].right_fork = &academy->forks[i].thread;
			academy->philos[i].left_fork = \
				&academy->forks[academy->number_of_philos - 1].thread;
		}
		else if (i == academy->number_of_philos - 1)
		{
			academy->philos[i].left_fork = &academy->forks[i].thread;
			academy->philos[i].right_fork = &academy->forks[0].thread;
		}
		else
		{
			academy->philos[i].left_fork = &academy->forks[i - 1].thread;
			academy->philos[i].right_fork = &academy->forks[i].thread;
		}
	}
}

void	init_forks(t_master *academy)
{
	int	i;

	i = 0;
	while (i < academy->number_of_philos)
	{
		academy->forks[i].index = i + 1;
		i++;
	}
	i = 0;
	while (i++ < academy->number_of_philos)
		pthread_mutex_init(&academy->forks[i].thread, NULL);
}

void	eating(t_master *academy, int philo_index)
{
	pthread_mutex_lock(academy->philos[philo_index - 1].left_fork);
	printf("TIMER %d has taken a fork\n", philo_index);
	pthread_mutex_lock(academy->philos[philo_index - 1].right_fork);
	printf("TIMER %d has taken a fork\n", philo_index);
	printf("TIMER %d is eating\n", philo_index);
	usleep(academy->time_to_eat * 1000);
	pthread_mutex_unlock(academy->philos[philo_index - 1].left_fork);
	pthread_mutex_unlock(academy->philos[philo_index - 1].right_fork);
}

void	*ft_philo(void *academy_cast)
{
	t_master	*academy;
	int			philo_index;

	academy = (t_master *)academy_cast;
	philo_index = academy->temp_nbr;
	while (1)
	{
		if (philo_index % 2 == academy->actual_group)
			eating(academy, philo_index);
		sleeping(academy, philo_index);
		thinking(academy, philo_index); 
	}
	return (NULL);
}

void	init_philothreads(t_master *academy)
{
	int		i;
	void	*academy_cast;

	i = -1;
	while (i++ < academy->number_of_philos - 1)
	{
		academy->temp_nbr = academy->philos[i].index;
		academy_cast = (void *)academy;
		pthread_create(&academy->philos[i].thread, NULL, ft_philo,
			academy_cast);
		usleep(50);
	}
}

void	join_philothreads(t_master *academy)
{
	int	i;

	i = 0;
	while (i++ < academy->number_of_philos)
		pthread_join(academy->philos[i].thread, NULL);
}

void	main_loop(t_master *academy)
{
	while (1)
	{
		usleep(academy->time_to_eat * 1000);
		academy->actual_group = 0;
		usleep(academy->time_to_eat * 1000);
		academy->actual_group = 1;
	}
}
int	main(int ac, char **av)
{
	t_master	*academy;

	if (ac == 5 || ac == 6)
	{
		academy = init_academy(ac, av);
		init_forks(academy);
		int i = 0;
		while (i++ < academy->number_of_philos)
			printf("FORK %d\n", academy->forks[i].index);
		init_philos(academy);
		//i = 0;
		while (i++ < academy->number_of_philos)
			printf("PHILO %d\n", academy->philos[i].index);
		pause();
		init_philothreads(academy);
		main_loop(academy);
		join_philothreads(academy);
	}
} */
