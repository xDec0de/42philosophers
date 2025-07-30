/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:53:18 by daniema3          #+#    #+#             */
/*   Updated: 2025/07/30 19:11:42 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo_info	*init_info(void)
{
	t_philo_info	*info;
	int				errors;

	errors = 0;
	info = malloc(sizeof(t_philo_info));
	if (info == NULL)
	{
		printf(MALLOC_ERR);
		return ;
	}
	info->philo_n = 0;
	info->die_ms = 0;
	info->eat_ms = 0;
	info->sleep_ms = 0;
	info->m_print = mutex_init(&errors);
	if (errors != 0)
		return (NULL);
	return (info);
}

t_philo_info	*get_info()
{
	static	t_philo_info *info = NULL;

	if (info = NULL)
		info = get_info();
	return (info);
}
