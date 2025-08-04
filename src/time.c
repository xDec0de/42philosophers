/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 21:46:08 by daniema3          #+#    #+#             */
/*   Updated: 2025/08/04 18:04:01 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (LONG_MAX);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	get_current_ms(t_philo_info *info)
{
	size_t	current_time;

	current_time = get_current_time();
	if (current_time == LONG_MAX)
		return (-1);
	return (current_time - info->start_date);
}

void	p_sleep(size_t ms)
{
	size_t	start;
	size_t	now;

	start = get_current_time();
	if (ms > 10)
		usleep((ms - 10) * 1000);
	now = get_current_time();
	while ((now - start) < (ms - 3))
	{
		usleep(500);
		now = get_current_time();
	}
	while ((now - start) < ms)
		now = get_current_time();
}
