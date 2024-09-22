/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojin <yojin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:11:30 by yojin             #+#    #+#             */
/*   Updated: 2024/08/15 18:14:49 by yojin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_philo_state(t_philo *philo)
{
	printf("[%d]-state:%d, time: %ld.%d\n", \
		philo->num, philo->state, philo->time.tv_sec, philo->time.tv_usec);
}

void	f(void)
{
	system("leaks philo");
}
