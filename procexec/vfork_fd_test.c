/**********************************************************************\
*                Copyright (C) Michael Kerrisk, 2010.                  *
*                                                                      *
* This program is free software. You may use, modify, and redistribute *
* it under the terms of the GNU Affero General Public License as       *
* published by the Free Software Foundation, either version 3 or (at   *
* your option) any later version. This program is distributed without  *
* any warranty. See the file COPYING for details.                      *
\**********************************************************************/

#include "tlpi_hdr.h"

int
main(int argc, char *argv[])
{
    switch (vfork()) {
    case -1: errExit("vfork");

    case 0: if (close(STDOUT_FILENO) == -1)
                errMsg("close - child");
            _exit(EXIT_SUCCESS);

    default: break;
    }

    /* Now parent closes STDOUT_FILENO twice: only the second close
       should fail, indicating that the close(STDOUT_FILENO) by the
       child did not affect the parent. */

    if (close(STDOUT_FILENO) == -1)
        errMsg("close");
    if (close(STDOUT_FILENO) == -1)
        errMsg("close");

    exit(EXIT_SUCCESS);
}
