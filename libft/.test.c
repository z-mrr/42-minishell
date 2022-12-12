/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 14:23:50 by jdias-mo          #+#    #+#             */
/*   Updated: 2021/10/26 19:11:07 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <bsd/string.h>

int	main(void)
{
	printf("\n");

	//1. ATOI
	const char nptr1[] = "	    -123a321";
	printf("1.\n");
	printf("ft_atoi: %d\n", ft_atoi(nptr1));
	printf("atoi:    %d\n", atoi(nptr1));
	printf("\n");

	//2. ISALNUM
	int c2 = 69;
	printf("2.\n");
	printf("ft_isalnum: %d\n", ft_isalnum(c2));
	printf("isalnum:    %d\n", isalnum(c2));
	printf("\n");

	//3. ISALPHA
	int c3 = 69;
	printf("3.\n");
	printf("ft_isalpha: %d\n", ft_isalpha(c3));
	printf("isalpha:    %d\n", isalpha(c3));
	printf("\n");

	//4. ISASCII
	int c4 = 69;
	printf("4.\n");
	printf("ft_isascii: %d\n", ft_isascii(c4));
	printf("isascii:    %d\n", isascii(c4));
	printf("\n");

	//5. ISDIGIT
	int c5 = 69;
	printf("5.\n");
	printf("ft_isdigit: %d\n", ft_isdigit(c5));
	printf("isdigit:    %d\n", isdigit(c5));
	printf("\n");

	//6. ISPRINT
	int c6 = 69;
	printf("6.\n");
	printf("ft_isprint: %d\n", ft_isprint(c6));
	printf("isprint:    %d\n", isprint(c6));
	printf("\n");

	//7. STRDUP
	const char s17[] = "Hello World";
	printf("7.\n");
	printf("ft_strdup: %s\n", ft_strdup(s17));
	printf("strdup:    %s\n", strdup(s17));
	printf("\n");

	//8. STRLCAT
	char dst8[10] = "Hello";
	const char src8[] = "World";
	size_t dstsize8 = 10;
	printf("8.\n");
	printf("ft_strlcat: %lu\n", ft_strlcat(dst8, src8, dstsize8));
	printf("strlcat:    %lu\n", strlcat(dst8, src8, dstsize8));
	printf("\n");

	//9. STRLCPY
	char dst9[10] = "Hello";
	const char src9[] = "World";
	size_t dstsize9 = 10;
	printf("9.\n");
	printf("ft_strlcpy: %lu\n", ft_strlcpy(dst9, src9, dstsize9));
	printf("strlcpy:    %lu\n", strlcpy(dst9, src9, dstsize9));
	printf("\n");

	//10. STRLEN
	const char s10[] = "Hello World.";
	printf("10.\n");
	printf("ft_strlen: %lu\n", ft_strlen(s10));
	printf("strlen:    %lu\n", strlen(s10));
	printf("\n");

	//11. STRNCMP
	const char s111[] = "Hello";
	const char s211[] = "World";
	size_t n11 = 20;
	printf("11.\n");
	printf("ft_strncmp: %d\n", ft_strncmp(s111, s211, n11));
	printf("strncmp:    %d\n", strncmp(s111, s211, n11));
	printf("\n");

	//12. TOLOWER
	int c12 = 69;
	printf("12.\n");
	printf("ft_tolower: %d\n", ft_tolower(c12));
	printf("tolower:    %d\n", tolower(c12));
	printf("\n");

	//13. TOUPPER
	int c13 = 124;
	printf("13.\n");
	printf("ft_toupper: %d\n", ft_toupper(c13));
	printf("toupper:    %d\n", toupper(c13));
	printf("\n");

	//14. STRCHR
	const char s14[] = "A tua prima.";
	int c14 = 0;
	printf("14.\n");
	printf("ft_strchr: %s\n", ft_strchr(s14, c14));
	printf("strchr:    %s\n", strchr(s14, c14));
	printf("\n");

	//15. STRRCHR
	const char s15[] = "A tua prima.";
	int c15 = 0;
	printf("15.\n");
	printf("ft_strrchr: %s\n", ft_strrchr(s15, c15));
	printf("strrchr:    %s\n", strrchr(s15, c15));
	printf("\n");

	//16. STRNSTR
	const char haystack16[] = "A tua prima.";
	const char needle16[] = "tua";
	size_t len16 = 8;
	printf("16.\n");
	printf("ft_strnstr: %s\n", ft_strnstr(haystack16, needle16, len16));
	printf("strnstr:    %s\n", strnstr(haystack16, needle16, len16));
	printf("\n");

	//17. MEMSET
	char str17[50] = "A tua prima feia.";
	char str117[50] = "A tua prima feia.";
	printf("17.\n");
	printf("Before ft_memset(): %s\n", str17);
	printf("Before memset():    %s\n", str117);
	ft_memset(str17 + 13, '.', 8*sizeof(char));
	memset(str117 + 13, '.', 8*sizeof(char));
	printf("After ft_memset():  %s\n", str17);
	printf("After memset():     %s\n", str117);
	printf("\n");

	//18. BZERO
	char str18[50] = "A tua prima feia.";
	char str118[50] = "A tua prima feia.";
	printf("18.\n");
	printf("Before ft_bzero(): %s\n", str18);
	printf("Before bzero():    %s\n", str118);
	ft_bzero(str18 + 13, 1);
	bzero(str118 + 13, 1);
	printf("After ft_bzero():  %s\n", str18);
	printf("After bzero():     %s\n", str118);
	printf("\n");

	//19. MEMCPY
	char str19[100] = "Learningisfun";
	char str199[100] = "Learningisfun";
	char *a19, *b19;
	char *a199, *b199;
	a19 = str19;
	b19 = str19;
	a199 = str199;
	b199 = str199;
	printf("19.\n");
	printf("Before ft_memcpy(): %s\n", str19);
	printf("Before memcpy():    %s\n", str199);
	ft_memcpy(a19 + 8, b19, 10);
	memcpy(a199 + 8, b199, 10);
	printf("After ft_memcpy():  %s\n", str19);
	printf("After memcpy():     %s\n", str199);
	printf("\n");

	//20. MEMMOVE
	char str20[100] = "Learningisfun";
	char str200[100] = "Learningisfun";
	char *a20, *b20;
	char *a200, *b200;
	a20 = str20;
	b20 = str20;
	a200 = str200;
	b200 = str200;
	printf("20.\n");
	printf("Before ft_memmove(): %s\n", str20);
	printf("Before memmove():    %s\n", str200);
	ft_memmove(a20 + 8, b20, 10);
	memmove(a200 + 8, b200, 10);
	printf("After ft_memmove():  %s\n", str20);
	printf("After memmove():     %s\n", str200);
	printf("\n");

	//21. MEMCHR
	char str21[50] = "A tua prima feia.";
	char str211[50] = "A tua prima feia.";
	printf("21.\n");
	printf("Before ft_memchr(): %s\n", str21);
	printf("Before memchr():    %s\n", str211);
	printf("ft_memchr: %p\n", ft_memchr(str21, 'a', 8));
	printf("memchr:    %p\n", memchr(str211, 'a', 8));
	printf("After ft_memchr():  %s\n", str21);
	printf("After memchr():     %s\n", str211);
	printf("\n");

	//22. MEMCMP
	char str22[50] = "A tua prima feia.";
	char str222[50] = "A tua primA feia.";
	printf("22.\n");
	printf("ft_memcmp: %d\n", ft_memcmp(str22, str222, 20));
	printf("memchr:    %d\n", memcmp(str22, str222, 20));
	printf("\n");

	//23. CALLOC
	printf("23.\n");
	printf("ft_calloc: %p\n", ft_calloc(4, 4));
	printf("calloc:    %p\n", calloc(4, 4));
	printf("\n");

	//24. FT_SUBSTR
	char str24[50] = "A tua prima feia.";
	int start24 = 6;
	size_t len24 = 5;
	printf("24.\n");
	printf("ft_substr: %s\n", ft_substr(str24, start24, len24));
	printf("\n");

	//25. FT_STRJOIN
	char str25[] = "A tua prima feia.";
	char str255[] = "A tua primA feia.";
	printf("25.\n");
	printf("ft_strjoin: %s\n", ft_strjoin(str25, str255));
	printf("\n");

	//26. FT_STRTRIM
	char str26[] = "222";
	char str266[] = "2222";
	printf("26.\n");
	printf("ft_strtrim: %s\n", ft_strtrim(str26, str266));
	printf("\n");

	//27. FT_SPLIT
	char	str27[] = "     A tua prima feia   .      ";
	char	c27 = ' ';
	int	i27 = 0;
	printf("27.\n");
	while (ft_split(str27, c27)[i27] != 0)
	{
		printf("%s\n", ft_split(str27, c27)[i27]);
		i27++;
	}
	printf("\n");

	//28. ITOA
	int	n28 = -2147483648;
	printf("28.\n");
	printf("ft_itoa: %s\n", ft_itoa(n28));
	printf("\n");

	//29. STRMAPI

	//30. STRITERI

	//31. PUTCHAR_FD
	char	a31 = 'A';
	printf("31.\n");
	ft_putchar_fd(a31, 1);
	printf("\n");
	printf("\n");

	//32. PUTSTR_FD
	char	*a32 = "A tua prima.";
	printf("32.\n");
	ft_putstr_fd(a32, 1);
	printf("\n");
	printf("\n");

	//33. PUTENDL_FD
	printf("33.\n");
	ft_putendl_fd(a32, 1);
	printf("\n");

	//34. PUTNBR_FD
	int	n34 = -2147483648;
	printf("34.\n");
	ft_putnbr_fd(n34, 1);
	printf("\n");
	printf("\n");

	return (0);
}
