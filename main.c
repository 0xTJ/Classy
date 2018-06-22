#include "course.h"
#include <assert.h>
#include <stdio.h>

#define print_course(x) printf("%s %s: %s", x.code.subject, x.code.number, x.name)
#define print_class(x) printf("%s %s %s at %d:%d on %s", x.code.subject, x.code.number, classtypes[x.type], x.start_time.tm_hour, x.start_time.tm_min, weekdays[x.start_time.tm_wday])

struct Course courses[16] = {
    {
        .code = {
            .subject = "ENPH",
            .number = "353"
        },
        .name = "Engineering Physics Laboratory II"
    }
};

struct Class classes[128] = {
    {
        .code = {
            .subject = "ENPH",
            .number = "353"
        },
        .start_time = {
            .tm_min = 30,
            .tm_hour = 8,
            .tm_wday = MONDAY
        },
        .type = LECTURE
    }
};

int main (int argc, char **argv) {
    assert(sizeof(char) == 1);
    assert(sizeof(long int) == 4);

    print_class(classes[0]);
}
