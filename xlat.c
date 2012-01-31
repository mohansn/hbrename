#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAMELEN 80
int main(int argc, char ** argv)
{
        char newname[NAMELEN]="", * argvptr=argv[1], * newnameptr = newname;
	if ( argc != 2 )
	{
	        printf ("Usage : %s <filename>\n", argv[0]);
		return -1;
	}
	/* Skip leading hyphens */
	while ( *argvptr && *argvptr == '-')
	{
		argvptr ++;
	}
	/* At this point, if argvptr points to '.', we have only hyphens in the filename,
	 * followed by the extension. We do not want to modify such a name. Let us return it as it is
	 */
	if (*argvptr == '.')
	{
		printf("%s", argv[1]);
		return -1;
	}
	strncpy(newname, argv[1], NAMELEN - 1);

	while(*argvptr && *argvptr != '-')
	{
		*newnameptr++ = *argvptr++;
	}
	while(*argvptr && *argvptr != '.')
		argvptr++;

	/*
	 * Remove trailing '_' from resulting names
	 */
	if (*(newnameptr - 1) == '_')
	{
		newnameptr--;
		while (*newnameptr == '_' && newnameptr != newname)
			newnameptr --;
		newnameptr ++;
	}

	while(*argvptr)
	{
		*newnameptr++ = *argvptr++;
	}
	*newnameptr = 0;
	printf("%s", newname);
	return 0;
}
