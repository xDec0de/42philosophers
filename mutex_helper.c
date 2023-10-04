/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 20:33:26 by danimart          #+#    #+#             */
/*   Updated: 2023/10/04 19:26:13 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philosophers.h"

pthread_mutex_t	*mutex_init(int *errors)
{
	pthread_mutex_t	mutex;
	pthread_mutex_t	*mutex_ptr;
	int				result;

	result = pthread_mutex_init(&mutex, NULL);
	mutex_ptr = &mutex;
	if (result == 0)
		return (mutex_ptr);
	printf(MUTEX_ERR);
	if (errors != NULL)
		*errors += 1;
	return (NULL);
}

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
