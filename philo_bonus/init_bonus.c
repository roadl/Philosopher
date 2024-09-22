/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojin <yojin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:03:12 by yojin             #+#    #+#             */
/*   Updated: 2024/08/15 19:35:44 by yojin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\v')
		return (1);
	if (c == '\n' || c == '\r' || c == '\f')
		return (1);
	return (0);
}

int	philo_atoi(const char *str)
{
	int	result;

	result = 0;
	while (*str && ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			return (-1);
		str++;
	}
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (-1);
		result *= 10;
		result += (*str) - '0';
		str++;
	}
	return (result);
}

void	init_philo(t_philo *philo, t_arg *arg, int i)
{
	philo->time = arg->start_time;
	philo->eat_time = arg->start_time;
	philo->num = i;
	philo->arg = arg;
	philo->state = THINK;
	philo->eat_count = 0;
	philo->holding_fork = 0;
	philo->fork = &arg->forks;
}

int	init_arg(int argc, char **argv, t_arg *arg)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (philo_atoi(argv[i]) == -1)
			return (0);
	}
	arg->philo_num = philo_atoi(argv[1]);
	arg->die_time = philo_atoi(argv[2]);
	arg->eat_time = philo_atoi(argv[3]);
	arg->sleep_time = philo_atoi(argv[4]);
	i = 0;
	gettimeofday(&arg->start_time, NULL);
	if (argc == 6)
		arg->max_eat = philo_atoi(argv[5]);
	else
		arg->max_eat = -1;
	return (1);
}
