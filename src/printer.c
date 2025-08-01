/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:53:04 by daniema3          #+#    #+#             */
/*   Updated: 2025/08/01 23:17:48 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	p_print(const char *str)
{
	t_philo_info	*info;
	unsigned int	len;

	len = p_strlen(str);
	if (len == 0)
		return ;
	info = get_info();
	pthread_mutex_lock(info->m_print);
	write(STDOUT_FILENO, str, len);
	pthread_mutex_unlock(info->m_print);
}

static int	write_unum_to_buffer(char *buf, unsigned int nb)
{
	char	tmp[10];
	int		i;
	int		j;

	i = 0;
	if (nb == 0)
	{
		buf[0] = '0';
		return (1);
	}
	while (nb > 0)
	{
		tmp[i] = '0' + (nb % 10);
		nb /= 10;
		i++;
	}
	j = 0;
	while (i-- > 0)
	{
		buf[j] = tmp[i];
		j++;
	}
	return (j);
}

void	p_printf(const char *str, ...)
{
	va_list			args;
	t_philo_info	*info;
	char			buf[PRINT_BUF_SIZE];
	size_t			i;
	size_t			out;

	info = get_info();
	va_start(args, str);
	pthread_mutex_lock(info->m_print);
	i = 0;
	out = 0;
	while (str[i] && out < PRINT_BUF_SIZE - 1)
	{
		if (str[i] == '%' && str[i + 1] == 'u')
		{
			out += write_unum_to_buffer(&buf[out], va_arg(args, unsigned int));
			i += 2;
		}
		else
			buf[out++] = str[i++];
	}
	write(STDOUT_FILENO, buf, out);
	pthread_mutex_unlock(info->m_print);
	va_end(args);
}
