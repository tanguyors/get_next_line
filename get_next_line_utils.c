/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: torsini <torsini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:12:04 by torsini           #+#    #+#             */
/*   Updated: 2024/03/13 10:48:30 by torsini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Cette fonction crée une copie de la chaîne de caractères s1 et la renvoie.
char	*ft_strdup(char *s1)
{
	char			*dest;
	unsigned int	i;

	// Alloue de la mémoire pour la nouvelle chaîne de caractères
	dest = malloc(ft_strlen(s1) + 1);
	if (!dest)
		return (NULL);
	i = 0;
	// Copie chaque caractère de s1 à dest
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	// Ajoute le caractère de fin de chaîne
	dest[i] = 0;
	return (dest);
}

// Cette fonction renvoie la longueur de la chaîne de caractères s.
size_t	ft_strlen(char *s)
{
	int	i;

	i = 0;
	// Compte le nombre de caractères dans la chaîne jusqu'à ce qu'il atteigne le caractère de fin de chaîne
	while (s[i])
		i++;
	return (i);
}

// Cette fonction crée une sous-chaîne de la chaîne s à partir de l'index de départ et de la longueur spécifiés.
char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	// Vérifie si la chaîne s est NULL. Si c'est le cas, retourne NULL.
	if (!s)
		return (NULL);
	// Vérifie si l'index de départ est plus grand que la longueur de la chaîne s.
	// Si c'est le cas,
		//alloue de la mémoire pour une chaîne de caractères de taille 1 (juste pour le caractère de fin de chaîne '\0') et retourne cette chaîne.
	if (start > ft_strlen(s))
		return (malloc(1));
	// Vérifie si la longueur demandée est plus grande que la longueur de la sous-chaîne à partir de l'index de départ.
	// Si c'est le cas,
		//ajuste la longueur pour qu'elle corresponde à la longueur de la sous-chaîne.
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	// Alloue de la mémoire pour la sous-chaîne. La taille allouée est égale à la longueur demandée plus 1 pour le caractère de fin de chaîne '\0'.
	str = malloc((len + 1) * sizeof(char));
	// Vérifie si l'allocation de mémoire a réussi. Si ce n'est pas le cas,
		//retourne NULL.
	if (!str)
		return (NULL);
	i = 0;
	// Le reste du code qui n'est pas montré ici copierait probablement les caractères de la chaîne s à la sous-chaîne str à partir de l'index de départ et pour la longueur demandée.
// Boucle qui parcourt la chaîne s à partir de l'index de départ et pour la longueur demandée
while (i < len)
{
    // Copie chaque caractère de s à str
    str[i] = s[start + i];
    i++;
}
// Ajoute le caractère de fin de chaîne à la fin de str
str[i] = 0;
// Retourne la sous-chaîne str
return (str);
}

// Cette fonction concatène deux chaînes de caractères s1 et s2
char	*ft_strjoin(char *s1, char *s2)
{
    char	*res;

    // Alloue de la mémoire pour la nouvelle chaîne de caractères. La taille allouée est égale à la somme des longueurs de s1 et s2 plus 1 pour le caractère de fin de chaîne '\0'.
    res = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));

    // Vérifie si l'allocation de mémoire a réussi. Si ce n'est pas le cas, retourne NULL.
    if (!res)
        return (NULL);

    // Remplit la nouvelle chaîne avec les caractères de s1 et s2
    fill_str(res, s1, s2);

    // Retourne la nouvelle chaîne
    return (res);
}

// Cette fonction remplit la chaîne de caractères res avec les caractères de s1 et s2
void	fill_str(char *res, char *s1, char *s2)
{
    unsigned int i;
    unsigned int j;

    i = 0;
    j = 0;

    // Boucle qui parcourt la chaîne s1
    while (s1[j])
        // Copie chaque caractère de s1 à res
        res[i++] = s1[j++];

    j = 0;

    // Boucle qui parcourt la chaîne s2
    while (s2[j])
        // Copie chaque caractère de s2 à res
        res[i++] = s2[j++];

    // Ajoute le caractère de fin de chaîne à la fin de res
    res[i] = '\0';
}