/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: torsini <torsini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:12:04 by torsini           #+#    #+#             */
/*   Updated: 2024/03/14 09:12:42 by torsini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Inclure le fichier d'en-tête "get_next_line.h"
#include "get_next_line.h"

// Définition de la fonction ft_strdup
char	*ft_strdup(char *s1)
{
	// Déclaration des variables
	// "dest" est la nouvelle chaîne de caractères qui sera créée
	// "i" est un compteur utilisé pour parcourir la chaîne de caractères s1
	char			*dest;
	unsigned int	i;

	// Allouer de la mémoire pour la nouvelle chaîne de caractères
	// La taille allouée est égale à la longueur de s1 plus 1 pour le caractère de fin de chaîne '\0'
	dest = malloc(ft_strlen(s1) + 1);
	// Vérifier si l'allocation de mémoire a réussi
	// Si ce n'est pas le cas, retourner NULL
	if (!dest)
		return (NULL);
	i = 0;
	// Boucle qui copie chaque caractère de s1 à dest
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	// Ajouter le caractère de fin de chaîne à la fin de dest
	dest[i] = 0;
	// Retourner la nouvelle chaîne de caractères
	return (dest);
}

// Définition de la fonction ft_strlen
size_t	ft_strlen(char *s)
{
	int	i;

	i = 0;
	// Boucle qui compte le nombre de caractères dans la chaîne s
	while (s[i])
		i++;
	// Retourner le nombre de caractères dans la chaîne s
	return (i);
}

// Définition de la fonction ft_substr
char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	// Vérifier si la chaîne s est NULL
	// Si c'est le cas, retourner NULL
	if (!s)
		return (NULL);
	// Vérifier si l'index de départ est plus grand que la longueur de la chaîne s
	// Si c'est le cas, allouer de la mémoire pour une chaîne de caractères de taille 1 (juste pour le caractère de fin de chaîne '\0') et retourner cette chaîne
	if (start > ft_strlen(s))
		return (malloc(1));
	// Vérifier si la longueur demandée est plus grande que la longueur de la sous-chaîne à partir de l'index de départ
	// Si c'est le cas, ajuster la longueur pour qu'elle corresponde à la longueur de la sous-chaîne
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	// Allouer de la mémoire pour la sous-chaîne
	// La taille allouée est égale à la longueur demandée plus 1 pour le caractère de fin de chaîne '\0'
	str = malloc((len + 1) * sizeof(char));
	// Vérifier si l'allocation de mémoire a réussi
	// Si ce n'est pas le cas, retourner NULL
	if (!str)
		return (NULL);
	i = 0;
	// Boucle qui copie chaque caractère de la chaîne s à la sous-chaîne str à partir de l'index de départ et pour la longueur demandée
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	// Ajouter le caractère de fin de chaîne à la fin de str
	str[i] = 0;
	// Retourner la sous-chaîne
	return (str);
}