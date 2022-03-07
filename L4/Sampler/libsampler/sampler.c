#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>

#include <time.h>

#include "sampler.h"

struct sampler_point {
    const char *file;
    int line;
    const char *func;
};

static char
json_control_char(char c)
{
    switch (c) {
    case '\b': return 'b';
    case '\n': return 'n';
    case '\r': return 'r';
    case '\t': return 't';
    case '\f': return 'f';
    default: return -1;
    }
}

static void
json_print_char(FILE *f, char c)
{
    if (c == '"' || c == '\\') {
        fputc('\\', f);
        fputc(c, f);
        return;
    }

    if (c >= 0x20) {            /* should be ok for UTF-8 */
        fputc(c, f);
        return;
    }

    char cc = json_control_char(c);
    if (cc >= 0) {
        fputc('\\', f);
        fputc(cc, f);
        return;
    }
    fprintf(f, "\\u%04x", c);
}

static void
json_print_string(FILE *f, const char *s)
{
    fputc('"', f);
    for (const char *i = s; *i; i++) {
        json_print_char(f, *i);
    }
    fputc('"', f);
}

static void
json_print_point(FILE *f, const struct sampler_point *pt)
{
    fputs("{\"file\":", f);
    json_print_string(f, pt->file);
    fprintf(f, ",\"line\":%d,\"func\":", pt->line);
    json_print_string(f, pt->func);
    fputs("}", f);
}

static void
json_print_edge(FILE *f,
                const struct sampler_point *prev,
                const struct sampler_point *curr,
                uint64_t dt, uint64_t ref_start, uint64_t ref_end)
{
    fputs("{\"prev\":", f);
    json_print_point(f, prev);
    fputs(",\"curr\":", f);
    json_print_point(f, curr);
    fprintf(f, ",\"dt\":%" PRIu64, dt);
    fprintf(f, ",\"ref_start\":%" PRIu64, ref_start);
    fprintf(f, ",\"ref_end\":%" PRIu64 "}\n", ref_end);
}

static uint64_t
ns_delta(const struct timespec *t1,
         const struct timespec *t2)
{
    return (t2->tv_sec - t1->tv_sec) * 1000000000
        + (t2->tv_nsec - t1->tv_nsec);
}

static struct sampler_point sampler_last;
static FILE *sampler_outfile;
struct sampler_times sampler_times;

void
sampler_do_checkpoint(const char *file, int line, const char *func)
{
    struct sampler_point curr = {
        .file = file,
        .line = line,
        .func = func,
    };

    if (sampler_last.file != NULL) {
        uint64_t dt
            = ns_delta(&sampler_times.tss2, &sampler_times.tse1);
        uint64_t ref_start
            = ns_delta(&sampler_times.tss1, &sampler_times.tss2);
        uint64_t ref_end
            = ns_delta(&sampler_times.tse1, &sampler_times.tse2);

        json_print_edge(sampler_outfile,
                        &sampler_last, &curr,
                        dt, ref_start, ref_end);
    }

    sampler_last = curr;
}

void
sampler_checkpoint(const char *file, int line, const char *func)
{
    clock_gettime(CLOCK, &sampler_times.tse1);
    clock_gettime(CLOCK, &sampler_times.tse2);

    sampler_do_checkpoint(file, line, func);

    clock_gettime(CLOCK, &sampler_times.tss1);
    clock_gettime(CLOCK, &sampler_times.tss2);
}

void
sampler_init(int *pargc, char **argv)
{
    const char *filename = NULL;
    int filedes = -1;

    int i;
    for (i = 1; i < *pargc; i++) {
        const char *s = argv[i];
        if (!strcmp(s, "-o")) {
            filename = argv[++i];
            filedes = -1;
        } else if (!strcmp(s, "-O")) {
            filename = NULL;
            if (sscanf(argv[++i], "%d", &filedes) != 1) {
                fprintf(stderr,
                        "%s: -O: argument must be a number\n",
                        argv[0]);
                exit(2);
            }
        } else if (!strcmp(s, "--")) {
            ++i;
            break;
        } else {
            break;
        }
    }

    if (i > 1) {
        for (int j = i; j < *pargc; j++) {
            argv[j - i + 1] = argv[j];
        }
        argv[*pargc - i + 1] = NULL;
    }
    *pargc -= i - 1;

    if (filename != NULL) {
        sampler_outfile = fopen(filename, "w");
    } else if (filedes >= 0) {
        sampler_outfile = fdopen(filedes, "w");
    } else {
        sampler_outfile = stdout;
    }
}
