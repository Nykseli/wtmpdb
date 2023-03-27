/* SPDX-License-Identifier: BSD-2-Clause

  Copyright (c) 2023, Thorsten Kukuk <kukuk@suse.com>

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice,
     this list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.
*/

/* Test case:
   Create login entry, add logout time via logwtmpdb()
*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wtmpdb.h"

int
main(void)
{
  const char *db_path = "tst-logwtmpdb.db";
  char *error = NULL;
  int64_t id;

  if (logwtmpdb (db_path, "pts/99", "user", NULL, "test", &error) < 0)
    {
      if (error)
        {
          fprintf (stderr, "%s\n", error);
          free (error);
        }
      else
        fprintf (stderr, "logwtmpdb (login) failed\n");
      return 1;
    }

  if (logwtmpdb (db_path, "pts/99", NULL, NULL, NULL, &error) != 0)
    {
      if (error)
        {
          fprintf (stderr, "%s\n", error);
          free (error);
        }
      else
        fprintf (stderr, "logwtmpdb (logout) failed\n");
      return 1;
    }

  return 0;
}
