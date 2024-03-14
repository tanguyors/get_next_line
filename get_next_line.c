/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: torsini <torsini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:14:15 by torsini           #+#    #+#             */
/*   Updated: 2024/03/14 09:12:42 by torsini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Inclure le fichier d'en-tête "get_next_line.h"
#include "get_next_line.h"

// La fonction `_fill_line_buffer` est une fonction statique qui lit le contenu d'un fichier et le stocke dans un tampon, tout en gérant les restes de lignes précédentes. Voici une explication détaillée de ce que fait cette fonction :

//1. Elle prend trois arguments : un descripteur de fichier `fd`, une chaîne de caractères `left_c` qui contient le reste d'une ligne précédente, et un tampon `buffer` dans lequel lire le fichier.

//2. Elle initialise `b_read` à 1 pour entrer dans la boucle while.

//3. Dans la boucle while, elle lit le fichier dans le tampon. Le nombre de caractères lus est stocké dans `b_read`.

//4. Si une erreur de lecture se produit, elle libère la mémoire allouée à `left_c` et retourne NULL.

//5. Si la fin du fichier est atteinte, elle arrête la boucle.

//6. Elle ajoute un caractère de fin de chaîne à la fin du tampon.

//7. Si `left_c` est NULL, elle le définit comme une chaîne vide.

//8. Elle concatène `left_c` et `buffer` et stocke le résultat dans `left_c`. Elle utilise `tmp` pour libérer l'ancienne valeur de `left_c`.

//9. Si un caractère de nouvelle ligne est trouvé dans le tampon, elle arrête la boucle.

//10. Finalement, elle retourne la chaîne de caractères `left_c` qui contient soit le reste de la ligne précédente, soit le contenu lu du fichier.
static char	*_fill_line_buffer(int fd, char *left_c, char *buffer)
{
	// Déclaration des variables
	// "b_read" est le nombre de caractères lus à partir du fichier
	// "tmp" est une variable temporaire utilisée pour stocker l'ancienne valeur de left_c
	ssize_t	b_read;
	char	*tmp;

	// Initialiser b_read à 1 pour entrer dans la boucle while
	b_read = 1;
	while (b_read > 0)
	{
		// Lire le fichier dans le tampon
		// Le nombre de caractères lus est stocké dans b_read
		b_read = read(fd, buffer, BUFFER_SIZE);
		// Si une erreur de lecture se produit, libérer la mémoire allouée à left_c et retourner NULL
		if (b_read == -1)
		{
			free(left_c);
			return (NULL);
		}
		// Si la fin du fichier est atteinte, arrêter la boucle
		else if (b_read == 0)
			break ;
		// Ajouter un caractère de fin de chaîne à la fin du tampon
		buffer[b_read] = 0;
		// Si left_c est NULL, le définir comme une chaîne vide
		if (!left_c)
			left_c = ft_strdup("");
		// Concaténer left_c et buffer et stocker le résultat dans left_c
		// Utiliser tmp pour libérer l'ancienne valeur de left_c
		tmp = left_c;
		left_c = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		// Si un caractère de nouvelle ligne est trouvé dans le tampon, arrêter la boucle
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	// Retourner la chaîne de caractères left_c qui contient soit le reste de la ligne précédente, soit le contenu lu du fichier
	return (left_c);
}

// Définition de la fonction _set_line
static char	*_set_line(char *line_buffer)
{
	// Déclaration des variables
	// "left_c" est la chaîne de caractères qui contient le reste de la ligne après le premier caractère de nouvelle ligne
	// "i" est un compteur utilisé pour parcourir la chaîne de caractères line_buffer
	char	*left_c;
	ssize_t	i;

	i = 0;
	// Trouver l'index du premier caractère de nouvelle ligne ou de fin de chaîne
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	// Si le premier caractère est un caractère de fin de chaîne ou si la chaîne est vide, retourner NULL
	if (line_buffer[i] == 0 || line_buffer[1] == 0)
		return (NULL);
	// Créer une sous-chaîne à partir de l'index du premier caractère de nouvelle ligne
	left_c = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	// Si la sous-chaîne est vide, libérer la mémoire et définir left_c sur NULL
	if (*left_c == 0)
	{
		free(left_c);
		left_c = NULL;
	}
	// Ajouter un caractère de fin de chaîne à la fin de la ligne
	line_buffer[i + 1] = 0;
	// Retourner la chaîne de caractères left_c qui contient le reste de la ligne après le premier caractère de nouvelle ligne
	return (left_c);
}

// Définition de la fonction get_next_line
char	*get_next_line(int fd)
{
	// Déclaration des variables
	// "left_c" est la chaîne de caractères qui contient le reste de la ligne précédente
	// "line" est la ligne lue à partir du fichier
	// "buffer" est le tampon utilisé pour lire le fichier
	static char	*left_c;
	char		*line;
	char		*buffer;

	// Allouer de la mémoire pour le tampon
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	// Vérifier si le descripteur de fichier est invalide, la taille du tampon est inférieure ou égale à 0, ou la lecture échoue
	// Si c'est le cas, libérer la mémoire allouée à left_c et au tampon, définir left_c et le tampon sur NULL, et retourner NULL
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(left_c);
		free(buffer);
		left_c = NULL;
		buffer = NULL;
		return (NULL);
	}
	// Vérifier si l'allocation de mémoire pour le tampon a réussi
	// Si ce n'est pas le cas, retourner NULL
	if (!buffer)
		return (NULL);
	// Remplir le tampon de ligne
	line = _fill_line_buffer(fd, left_c, buffer);
	// Libérer la mémoire allouée au tampon et définir le tampon sur NULL
	free(buffer);
	buffer = NULL;
	// Vérifier si le remplissage du tampon de ligne a réussi
	// Si ce n'est pas le cas, retourner NULL
	if (!line)
		return (NULL);
	// Définir la ligne à partir du tampon de ligne
	left_c = _set_line(line);
	// Retourner la ligne lue à partir du fichier
	return (line);
}

// Définition de la fonction ft_strchr
char	*ft_strchr(char *s, int c)
{
	// Déclaration des variables
	// "i" est un compteur utilisé pour parcourir la chaîne de caractères s
	// "cc" est le caractère à chercher dans la chaîne s
	unsigned int	i;
	char			cc;

	// Convertir l'entier c en caractère
	cc = (char)c;
	i = 0;
	// Boucle qui parcourt la chaîne s
	while (s[i])
	{
		// Si le caractère courant est égal à cc, retourner un pointeur vers ce caractère
		if (s[i] == cc)
			return ((char *)&s[i]);
		i++;
	}
	// Si le caractère de fin de chaîne est égal à cc, retourner un pointeur vers ce caractère
	if (s[i] == cc)
		return ((char *)&s[i]);
	// Si cc n'est pas trouvé dans la chaîne s, retourner NULL
	return (NULL);
}