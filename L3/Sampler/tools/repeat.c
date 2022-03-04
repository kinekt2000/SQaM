#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>


#define OUT_FNAME "sampler.out"

void
usage(const char *argv0)
{
    printf("usage: %s N_RUNS N_SKIP PROGRAM ARGS ...\n", argv0);
}

int
main(int argc, char **argv)
{
    if (argc < 4) {
        usage(argv[0]);
        return 2;
    }

    int fd = open(OUT_FNAME, O_WRONLY | O_CREAT | O_TRUNC, 0664);
    if (fd < 0) {
        perror("open");
        return 1;
    }
    if (fd != 3) {
        if (0 > dup2(fd, 3)) {
            perror("dup2");
            return 1;
        }
        close(fd);
        fd = 3;
    }

    /* argv[3] (-o|-O) (/dev/null|3) -- argv[4] argv[5] ... argv[argc-1] NULL */
    char **child_argv = malloc((argc + 1) * sizeof(*child_argv));

    int n_runs, n_skip;
    if (1 != sscanf(argv[1], "%d", &n_runs)
        || 1 != sscanf(argv[2], "%d", &n_skip)) {
        usage(argv[0]);
        return 2;
    }

    for (int i = 0; i < n_runs; ++i) {
        int pid = fork();
        if (pid < 0) {
            perror("fork");
            return 1;
        } else if (0 == pid) {
            child_argv[0] = argv[3];
            if (i >= n_skip) {
                child_argv[1] = "-O";
                child_argv[2] = "3";
            } else {
                child_argv[1] = "-o";
                child_argv[2] = "/dev/null";
            }
            child_argv[3] = "--";
            memcpy(&child_argv[4], &argv[4], (argc - 4) * sizeof(*child_argv));
            child_argv[argc] = NULL;

            if (0 > execvp(child_argv[0], &child_argv[0])) {
                perror("exec");
                return 1;
            }
        } else {
            int ws;
            if (0 > waitpid(pid, &ws, 0)) {
                perror("waitpid");
                return 1;
            }

            if (WIFEXITED(ws)) {
                int es = WEXITSTATUS(ws);
                if (es != 0) {
                    fprintf(stderr, "child exited with status %d\n", es);
                    break;
                }
            } else if (WIFSIGNALED(ws)) {
                fprintf(stderr, "child terminated by signal %d\n", WTERMSIG(ws));
                break;
            } else {
                fprintf(stderr, "child terminated for unknown reason\n");
                break;
            }

            if (i >= n_skip) {
                char c = '\n';
                write(fd, &c, 1);
            }
        }
    }

    free(child_argv);

    close(fd);

    return 0;
}
