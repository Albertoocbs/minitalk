/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoutumur <aoutumur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:31:57 by aoutumur          #+#    #+#             */
/*   Updated: 2025/02/27 11:40:00 by aoutumur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
- bit = 7;//start with the most significant bit
- //loop from the MSB to the LSB to be able to send the bits in correct order
- if ((c >> bit) & 1) extract only the last bit, eg. at position 7(0), 6(1)...
- usleep() delay to ensure signal is sent avoiding overwhelming the server
*/
static void	ft_send_bits(int pid, char c)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		if ((c >> bit) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(500);
		bit--;
	}
}

/*
- ft_atoi convert string argv[1] (server pid) to integer
- check if number of arguments is correct & loop trhoug 2nd arg & call function
- ft_send_bits() sends bits to the server (server pid argv[1 ]+ string argv[2])
- send null carac as termiantion signal
*/
int	main(int argc, char **argv)
{
	int	server_pid;
	int	i;

	i = 0;
	if (argc == 3)
	{
		server_pid = ft_atoi(argv[1]);
		while (argv[2][i])
		{
			ft_send_bits(server_pid, argv[2][i]);
			i++;
			usleep(1000);
		}
		ft_send_bits(server_pid, '\0');
		usleep(5000);
	}
	else
	{
		ft_printf("Error: wrong format.\n");
		ft_printf("Usage: %s <server_pid> <message>\n", argv[0]);
		return (1);
	}
	return (0);
}
