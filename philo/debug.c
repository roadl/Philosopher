/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojin <yojin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:11:30 by yojin             #+#    #+#             */
/*   Updated: 2024/08/08 14:25:22 by yojin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philo_state(t_philo *philo)
{
	printf("[%d]-state:%d, time: %ld.%d\n", \
		philo->num, philo->state, philo->time.tv_sec, philo->time.tv_usec);
}

void	f(void)
{
	system("leaks philo");
}
