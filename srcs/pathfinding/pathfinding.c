/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:00:13 by albaur            #+#    #+#             */
/*   Updated: 2022/11/02 18:34:05 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

int		node_path_size(t_anode *end)
{
	int i;

	i = 0;
	while (end)
	{
		++i;
		end = end->parent;
	}
	return (i);
}

t_vector3	*make_path(t_anode *end)
{
	int			size;
	t_vector3	*path;

	size = node_path_size(end);
	if (!end || size == 0)
		return (NULL);
	path = malloc(sizeof(t_vector3) * (size + 1));
	if (!path)
		return (NULL);
	path[size].x = -999;
	path[size].y = -999;
	while (end)
	{
		path[--size] = end->pos;
		end = end->parent;
	}
	return (path);
}

void insert_node(t_anode **list, t_anode *current)
{
	t_anode *last;
	t_anode *prev;

	last = *list;
	current->next = NULL;
	if (!last || (prev = NULL))
	{
		*list = current;
		return ;
	}
	while (last)
	{
		if (last->dist > current->dist)
		{
			if (prev)
				prev->next = current;
			else
				*list = current;
			current->next = last;
			return ;
		}
		prev = last;
		last = last->next;
	}
	prev->next = current;
}

int	pathfinding_dist(t_vector3 start, t_vector3 end)
{
	end.x -= start.x;
	end.y -= start.y;
	return (end.x * end.x + end.y * end.y);
}

t_anode *create_node(t_anode *parent, t_vector3 end, t_vector3 pos)
{
	t_anode *new;

	new = malloc(sizeof(t_anode));
	if (!new)
		throw_err_ex("Malloc error\n");
	new->parent = parent;
	new->dist = pathfinding_dist(end, pos);
	new->pos = pos;
	new->next = NULL;
	return (new);
}

void	remove_node(t_anode **list, t_anode *current)
{
	t_anode *prev;
	t_anode *tmp;

	prev = NULL;
	tmp = *list;
	while (tmp)
	{
		if (tmp == current)
		{
			if (prev == NULL)
				*list = tmp->next;
			else
				prev->next = tmp->next;
			break ;
		}
		prev = tmp;
		tmp = prev->next;
	}
}

void	push_node(t_anode **list, t_anode *current)
{
	current->next = *list;
	*list = current;
}

t_anode *add_node(t_data *data, t_pathfinding *astar, t_anode *parent, t_vector3 end)
{
	t_anode	*tmp;

	if (astar->map[data->map->size_arr[end.y] * end.y + end.x])
		return (NULL);
	tmp = create_node(parent, astar->end, end);
	if (astar->end.x == end.x && astar->end.y == end.y)
		return (tmp);
	insert_node(&astar->list_open, tmp);
	astar->map[data->map->size_arr[end.y] * end.y + end.x] = 1;
	return (NULL);
}

t_vector3	get_neighbor(int rot, t_vector3 origin)
{
	if (rot == 0)
		origin.x++;
	else if (rot == 1)
		origin.x--;
	else if (rot == 2)
		origin.y++;
	else if (rot == 3)
		origin.y--;
	return (origin);
}

int	check_path(t_data *data, t_vector3 vec)
{
	int	pos;

	if (vec.x < 0 || vec.y < 0 || vec.x > data->map->size_arr[vec.y]
		|| vec.y > data->map->size.y)
		return (1);
	pos = minimap_get(data->map, vec.x, vec.y);
	if (pos == 1)
		return (1);
	return (0);
}

void	add_neighbors(t_data *data, t_pathfinding *astar, t_anode *current)
{
	size_t		i;
	t_vector3	pos;
	t_anode		*next;

	while (current)
	{
		i = 0;
		next = current->next;
		remove_node(&astar->list_open, current);
		push_node(&astar->list_closed, current);
		while (i < 4)
		{
			pos = get_neighbor(i++, current->pos);
			if (!check_path(data, pos))
			{
				astar->goal = add_node(data, astar, current, pos);
				if (astar->goal)
					return ;
			}
		}
		current = next;
	}
}

t_vector3	*pathfinding(t_data *data, t_vector3 start, t_vector3 end)
{
	t_pathfinding	astar;
	t_vector3		*path;
	int				tries;

	tries = 500;
	astar.map = ft_strdup(data->map->map_str);
	if (check_path(data, start) || check_path(data, end) || !astar.map)
		return (NULL);
	astar.start = start;
	astar.end = end;
	astar.list_open = create_node(NULL, end, start);
	astar.list_closed = NULL;
	astar.goal = NULL;
	while (tries--)
	{
		if (!astar.list_open)
			break;
		add_neighbors(data, &astar, astar.list_open);
	}
	path = make_path(astar.goal);
	return (path);
}