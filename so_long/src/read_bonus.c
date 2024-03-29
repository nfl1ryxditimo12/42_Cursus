/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonkim <seonkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 15:57:18 by seonkim           #+#    #+#             */
/*   Updated: 2021/06/20 05:31:18 by seonkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

char		*ft_bufcpy(char *dest, char *src, int n)
{
	char *d;

	d = dest;
	while (n--)
		*d++ = *src++;
	return (dest);
}

static char	*get_value(int fd)
{
	char	buf[BUFFER_SIZE];
	char	*content;
	char	*tmp;
	int		len;
	int		size;

	if (!(content = malloc(sizeof(char))))
		print_err(0, MEM_ERR, 0);
	*content = '\0';
	size = 0;
	while ((len = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		if (!(tmp = malloc((size + len + 1) * sizeof(char))))
			print_err(0, MEM_ERR, content);
		tmp = ft_bufcpy(tmp, content, size);
		free(content);
		ft_bufcpy(tmp + size, buf, len);
		content = tmp;
		size += len;
		content[size] = '\0';
	}
	if (len)
		free(content);
	free(tmp);
	return ((len) ? NULL : content);
}

void		read_file(t_game *game, char *file)
{
	int		fd;

	if ((fd = open(file, O_RDONLY)) == -1)
	{
		game->map.map = 0;
		print_err(0, "Cannot open file", 0);
	}
	game->map.map = ft_split(game, get_value(fd), 0);
	close(fd);
	check_map(game);
}
