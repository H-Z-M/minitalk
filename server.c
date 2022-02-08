/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudatsu <sudatsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 19:00:16 by sudatsu           #+#    #+#             */
/*   Updated: 2022/01/09 23:32:04 by sudatsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

sig_atomic_t	g_flag;

static void	receive_msg(t_minitalk *sv, pid_t client_pid, uint8_t c)
{
	if (g_flag < 0)
		sv->c |= (1 << sv->bit_count);
	sv->bit_count++;
	if (sv->bit_count == 8)
	{
		write(1, &sv->c, 1);
		sv->bit_count = 0;
		sv->c = 0;
	}
	send_sig(c, client_pid);
}

int	main(void)
{
	t_minitalk	sv;

	ft_putnbr_fd(getpid(), 1);
	ft_putendl_fd("", 1);
	set_signal();
	sv.c = 0;
	sv.bit_count = 0;
	while (1)
	{
		g_flag = 0;
		pause();
		if (g_flag > 0)
			receive_msg(&sv, g_flag, 0);
		else if (g_flag < 0)
			receive_msg(&sv, -g_flag, 1);
	}
}
