/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:54:31 by danimart          #+#    #+#             */
/*   Updated: 2023/10/02 19:13:29 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philosophers.h"

void	p_eat(t_philo *philo);
void	p_sleep(t_philo *philo);

void	print_philo_msg(char *message, t_philo *philo)
{
	pthread_mutex_lock(philo->prog_info->m_print);
	printf(message, get_current_ms(philo->prog_info), philo->id);
	pthread_mutex_unlock(philo->prog_info->m_print);
}

void	p_eat(t_philo *philo)
{
	philo->state = THINKING;
	pthread_mutex_lock(philo->prog_info->m_print);
	print_philo_msg(PHILO_THINKING, philo);
	pthread_mutex_unlock(philo->prog_info->m_print);
	// Eating logic here...
	p_sleep(philo);
}

void	p_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->prog_info->m_print);
	print_philo_msg(PHILO_SLEEPING, philo);
	pthread_mutex_unlock(philo->prog_info->m_print);
	philo->state = SLEEPING;
	usleep(philo->prog_info->sleep_time * 1000);
	// Attempt to eat again... We just kill the philosopher now to end the program.
	philo->state = DEAD;
	//p_eat(philo);
}

void	*philo_routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	p_eat(philo);
	if (philo->state == DEAD)
		return (philo_ptr);
	usleep(100);
	return (philo_routine(philo_ptr));
}
