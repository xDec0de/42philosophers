/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:54:31 by danimart          #+#    #+#             */
/*   Updated: 2023/10/04 19:13:11 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philosophers.h"

void	p_eat(t_philo *philo);
void	p_sleep(t_philo *philo);

t_philo	*set_philo_state(t_philo *philo, int state)
{
	char	*state_str;

	if (state == DEAD)
		state_str = PHILO_DIED;
	else if (state == THINKING)
		state_str = PHILO_THINKING;
	else if (state == SLEEPING)
		state_str = PHILO_SLEEPING;
	pthread_mutex_lock(philo->m_state);
	philo->state = state;
	pthread_mutex_lock(philo->prog_info->m_print);
	printf(state_str, get_current_ms(philo->prog_info), philo->id);
	pthread_mutex_unlock(philo->prog_info->m_print);
	pthread_mutex_unlock(philo->m_state);
	return (philo);
}

t_philo	*get_left_philo(t_philo *philo)
{
	int	id;
	int	max;

	id = philo->id;
	max = philo->prog_info->amount;
	if (id == 0)
		return (philo->prog_info->philo_lst[max - 1]);
	return (philo->prog_info->philo_lst[id - 1]);
}

void	p_eat(t_philo *philo)
{
	set_philo_state(philo, THINKING);
	// Eating logic here...
	p_sleep(philo);
}

void	p_sleep(t_philo *philo)
{
	set_philo_state(philo, SLEEPING);
	usleep(philo->prog_info->sleep_time * 1000);
	// Attempt to eat again... We just kill the philosopher now to end the program.
	philo->state = DEAD;
	//p_eat(philo);
}

void	*philo_routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	printf("Left philo of %i is %i\n", philo->id, get_left_philo(philo)->id);
	p_eat(philo);
	if (philo->state == DEAD)
		return (philo_ptr);
	usleep(100);
	return (philo_routine(philo_ptr));
}
