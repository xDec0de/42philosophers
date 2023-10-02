/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:54:31 by danimart          #+#    #+#             */
/*   Updated: 2023/10/02 18:27:37 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philosophers.h"

void	print_philo_msg(char *message, t_philo *philo)
{
	pthread_mutex_lock(philo->prog_info->m_print);
	printf(message, get_current_ms(philo->prog_info), philo->id);
	pthread_mutex_unlock(philo->prog_info->m_print);
}

void	start_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->prog_info->m_print);
	print_philo_msg(PHILO_SLEEPING, philo);
	philo->state = SLEEPING;
	usleep(philo->prog_info->sleep_time * 1000);
	philo->state = F_SLEEPING;
	pthread_mutex_unlock(philo->prog_info->m_print);
}

void	*philo_routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	start_sleep(philo);
	if (get_current_ms(philo->prog_info) - philo->last_interacion >= 10) // This kills the philosopher at 10ms since program execution
		philo->state = DEAD;
	if (philo->state == DEAD)
		return (philo_ptr);
	usleep(100);
	return (philo_routine(philo_ptr));
}
