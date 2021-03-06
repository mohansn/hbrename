#include "../common/libcleanup.h"

extern char *newname;		/* From libcleanup.so */

int min (int a, int b)
{
    return ((a > b) ? b : a);
}

int main(int argc, char **argv)
{
    int opt, quiet = 0, no_action=0;
#ifdef DEBUG
    EF_DISABLE_BANNER = 1;
#endif
    while ((opt = getopt(argc, argv, "qn")) != -1) {
        switch (opt) {
        case 'q':
            quiet = 1;
            break;
        case 'n':
            no_action = 1;
            break;
        case '?':
            fprintf (stderr, "Unexpected option - exiting\n");
            exit(0);
        default:
            quiet = 0;
        }
    }
    assert ((quiet == 0) || (quiet == 1));
    const char *execname = "cleanup";
    DIR *dir = opendir(".");
    if (NULL == dir) {
	perror("Could not open \".\"");
	exit(-1);
    }
    d_printf("opened . \n");
    struct dirent *dirent = NULL;
    newname = malloc(NAMELEN * sizeof(char));
    if (NULL == newname) {
	fprintf(stderr, "Error allocating memory\n");
	closedir(dir);
	exit(-1);
    }
    /* Preserve newname pointer for free()ing later */
    char * newnamebuf = newname;
    char d_name_buf [NAME_MAX];
    while (NULL != (dirent = readdir(dir))) {
        if(!strcmp (dirent->d_name, execname)){
            continue;
        }
	d_printf("file name %s\n", dirent->d_name);
#ifdef _DIRENT_HAVE_D_TYPE
	if (dirent->d_type == DT_REG) {
            strncpy (d_name_buf, dirent->d_name, min (NAMELEN, NAME_MAX));
	    newnamebuf = new_name(d_name_buf);
	    if (strcmp(newnamebuf, dirent->d_name)) {
		int ret = -1;
		struct stat statbuf;
		/* check if file with proposed new name already exists */
		ret = stat(newnamebuf, &statbuf);

		if (-1 == ret){
                    if (!no_action) {
                        ret = rename(dirent->d_name, newnamebuf);
                        /* Set access and last modified time of renamed file
                           to current time */
                        if(-1 == utime(newnamebuf, NULL)) {
                            if(!quiet) {
                                perror(strerror(errno));
                            }
                        }
                    } else {
                        ret = 0;
                    }
		    if (ret) {
			perror(strerror(errno));
		    } else {
                        if (!quiet) {
                            printf ("%s -> %s\n", dirent->d_name, newnamebuf);
                        }
                    }
                } else {
		    /* File with proposed new name exists.
		       Do nothing. */
                    if (!quiet) {
                        fprintf (stderr,
                                 "Renaming %s would overwrite file %s. Hence, leaving it unaltered.\n",
                                 dirent->d_name, newnamebuf);
                    }
		}
	    }
	}
#else
#error "We do not have file type defined. Cannot continue, bailing out..."
#endif
    }
    closedir(dir);
    return 0;
}
