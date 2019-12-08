/*****************************************************************************
 *                                                                           *
 *   cocoformat.c                                                            *
 *   (C) 2005 Aaron Sebold                                                   *
 *   Version 2                                                               *
 *                                                                           *
 *****************************************************************************
 *                                                                           *
 *   This program is free software; you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation; either version 2 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the            *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with this program; if not, write to the Free Software             *
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA *
 *                                                                           *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define VOID    0xFF
#define BYTES   256
#define SECTORS 18
#define TRACKS  35
#define NONAME  "empty.dsk"
#define ERR_CLI 1
#define ERR_FIL 2

void format_err(int error_code);

int main(int argc, char *argv[])
{
    /* This program will create a blank single-sided 35 track virtual disk */
    int x, total_bytes;
    FILE *dskini;

    /* First off check the command line options */
    if(argc > 2) {
        format_err(ERR_CLI);                    /* Hand out error message */
    }

    /* Do a little math */
    total_bytes = (BYTES * SECTORS) * TRACKS;   /* Total bytes on disk */

    /* Create the new disk image */
    if(argc == 1) {
        dskini = fopen(NONAME, "w");            /* Use "default" filename */
    } else {
        dskini = fopen(argv[1], "w");           /* Use defined filename */
    }

    /* Couldn't create the file */
    if(!dskini) {
        format_err(ERR_FIL);
    }

    for (x = 0; x < total_bytes; x++) {
        fputc(VOID, dskini);                    /* Write 0xFF to every byte */
    }

    fclose(dskini);                             /* Close the file */

    return EXIT_SUCCESS;


void format_err(int error_code)
{
    /* Give the standard error */
    fprintf(stderr, "FORMAT: cocoformat [Optional: \"filename\"]\n");
    fprintf(stderr, "  cocoformat creates a blank single-sided 35 track virtual disk\n");
    fprintf(stderr, "  for use with RSDOS in Color Computer emulators.\n\n");

    /* Give error details */
    switch(error_code)
    {
        case 1:
            fprintf(stderr, "There were too many arguments or bad arguments in the command line!\n");
            break;
        case 2:
            fprintf(stderr, "Could not create file!\n");
            break;
        default:
            break;
    }

    exit(EXIT_FAILURE);
}
