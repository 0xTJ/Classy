#include "course.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

int start_slot = 48;
int end_slot = -1;

int first[7][48] = {0};
int second[7][48] = {0};
int more_than_two[7][48] = {0};

struct Course courses[16] = {
    {0},
    {
        .code = {
            .subject = "ENPH",
            .number = "323"
        },
        .name = "Cont.-Time Signals & Systems"
    },
    {
        .code = {
            .subject = "ELEC",
            .number = "353"
        },
        .name = "Electronics II"
    },
    {
        .code = {
            .subject = "ELEC",
            .number = "371"
        },
        .name = "Microprocessor Systems"
    },
    {
        .code = {
            .subject = "ENPH",
            .number = "344"
        },
        .name = "Intro. To Quantum Mechanics"
    },
    {
        .code = {
            .subject = "ENPH",
            .number = "353"
        },
        .name = "Eng Physics Lab II"
    },
    {
        .code = {
            .subject = "MTHE",
            .number = "338"
        },
        .name = "Fourier Meths for Boundary Val"
    }
};

struct Class classes[128] = {
    {0},
    {
        .code = {
            .subject = "ENPH",
            .number = "323"
        },
        .start_slot = 17,
        .length_slots = 2,
        .wday = MONDAY,
        .type = LECTURE,
        .location = "BIOSCI RM1102"
    },
    {
        .code = {
            .subject = "ENPH",
            .number = "323"
        },
        .start_slot = 21,
        .length_slots = 2,
        .wday = TUESDAY,
        .type = LECTURE,
        .location = "BIOSCI RM1102"
    },
    {
        .code = {
            .subject = "ENPH",
            .number = "323"
        },
        .start_slot = 27,
        .length_slots = 2,
        .wday = THURSDAY,
        .type = LECTURE,
        .location = "BIOSCI RM1102"
    },
    {
        .code = {
            .subject = "ENPH",
            .number = "323"
        },
        .start_slot = 35,
        .length_slots = 2,
        .wday = WEDNESDAY,
        .type = TUTORIAL,
        .location = "CHERNOFF RM117"
    },
    {
        .code = {
            .subject = "ENPH",
            .number = "323"
        },
        .start_slot = 17,
        .length_slots = 6,
        .wday = WEDNESDAY,
        .type = LAB,
        .location = "BEAMISH-MUNRO RM214"
    },
    {
        .code = {
            .subject = "ELEC",
            .number = "353"
        },
        .start_slot = 27,
        .length_slots = 2,
        .wday = MONDAY,
        .type = LECTURE,
        .location = "DUPUIS RM217"
    },
    {
        .code = {
            .subject = "ELEC",
            .number = "353"
        },
        .start_slot = 25,
        .length_slots = 2,
        .wday = WEDNESDAY,
        .type = LECTURE,
        .location = "DUPUIS RM217"
    },
    {
        .code = {
            .subject = "ELEC",
            .number = "353"
        },
        .start_slot = 23,
        .length_slots = 2,
        .wday = FRIDAY,
        .type = LECTURE,
        .location = "DUPUIS RM217"
    },
    {
        .code = {
            .subject = "ELEC",
            .number = "353"
        },
        .start_slot = 31,
        .length_slots = 2,
        .wday = TUESDAY,
        .type = TUTORIAL,
        .location = "DUPUIS RM217"
    },
    {
        .code = {
            .subject = "ELEC",
            .number = "353"
        },
        .start_slot = 17,
        .length_slots = 6,
        .wday = THURSDAY,
        .type = LAB,
        .location = "BEAMISH-MUNRO RM314"
    },
    {
        .code = {
            .subject = "ELEC",
            .number = "371"
        },
        .start_slot = 23,
        .length_slots = 2,
        .wday = MONDAY,
        .type = LECTURE,
        .location = "ETHERINGTON AUD"
    },
    {
        .code = {
            .subject = "ELEC",
            .number = "371"
        },
        .start_slot = 27,
        .length_slots = 2,
        .wday = TUESDAY,
        .type = LECTURE,
        .location = "ETHERINGTON AUD"
    },
    {
        .code = {
            .subject = "ELEC",
            .number = "371"
        },
        .start_slot = 25,
        .length_slots = 2,
        .wday = THURSDAY,
        .type = LECTURE,
        .location = "ETHERINGTON AUD"
    },
    {
        .code = {
            .subject = "ELEC",
            .number = "371"
        },
        .start_slot = 31,
        .length_slots = 2,
        .wday = WEDNESDAY,
        .type = TUTORIAL,
        .location = "STIRLING RM A"
    },
    {
        .code = {
            .subject = "ELEC",
            .number = "371"
        },
        .start_slot = 29,
        .length_slots = 6,
        .wday = MONDAY,
        .type = LAB,
        .location = "BEAMISH-MUNRO RM212"
    },
    {
        .code = {
            .subject = "ENPH",
            .number = "344"
        },
        .start_slot = 23,
        .length_slots = 2,
        .wday = TUESDAY,
        .type = LECTURE,
        .location = "STIRLING RM A"
    },
    {
        .code = {
            .subject = "ENPH",
            .number = "344"
        },
        .start_slot = 27,
        .length_slots = 2,
        .wday = WEDNESDAY,
        .type = LECTURE,
        .location = "STIRLING RM A"
    },
    {
        .code = {
            .subject = "ENPH",
            .number = "344"
        },
        .start_slot = 25,
        .length_slots = 2,
        .wday = FRIDAY,
        .type = LECTURE,
        .location = "STIRLING RM A"
    },
    {
        .code = {
            .subject = "ENPH",
            .number = "344"
        },
        .start_slot = 21,
        .length_slots = 2,
        .wday = MONDAY,
        .type = TUTORIAL,
        .location = "STIRLING RM C"
    },
    {
        .code = {
            .subject = "ENPH",
            .number = "353"
        },
        .start_slot = 29,
        .length_slots = 2,
        .wday = THURSDAY,
        .type = LECTURE,
        .location = "IWC RM225"
    },
    {
        .code = {
            .subject = "ENPH",
            .number = "353"
        },
        .start_slot = 37,
        .length_slots = 6,
        .wday = THURSDAY,
        .type = LAB,
        .location = "STIRLING"
    },
    {
        .code = {
            .subject = "MTHE",
            .number = "338"
        },
        .start_slot = 25,
        .length_slots = 2,
        .wday = TUESDAY,
        .type = LECTURE,
        .location = "JEFFERY RM127"
    },
    {
        .code = {
            .subject = "MTHE",
            .number = "338"
        },
        .start_slot = 23,
        .length_slots = 2,
        .wday = THURSDAY,
        .type = LECTURE,
        .location = "JEFFERY RM127"
    },
    {
        .code = {
            .subject = "MTHE",
            .number = "338"
        },
        .start_slot = 27,
        .length_slots = 2,
        .wday = FRIDAY,
        .type = LECTURE,
        .location = "JEFFERY RM127"
    },
    {
        .code = {
            .subject = "MTHE",
            .number = "338"
        },
        .start_slot = 25,
        .length_slots = 2,
        .wday = MONDAY,
        .type = TUTORIAL,
        .location = "JEFFERY RM127"
    }
};

void loadTimetables(void) {
    for (int i = 1; i < sizeof(classes) / sizeof(classes[0]); ++i) {
        for (int j = 0; j < classes[i].length_slots; ++j) {
            if (first[classes[i].wday][classes[i].start_slot + j] == 0)
                first[classes[i].wday][classes[i].start_slot + j] = i;
            else if (second[classes[i].wday][classes[i].start_slot + j] == 0)
                second[classes[i].wday][classes[i].start_slot + j] = i;
            else
                ++more_than_two[classes[i].wday][classes[i].start_slot + j];

            if (classes[i].start_slot < start_slot)
                start_slot = classes[i].start_slot;
            if (classes[i].start_slot + classes[i].length_slots > end_slot)
                end_slot = classes[i].start_slot + classes[i].length_slots;
        }
    }
};

char *findCourseName(struct Class *class) {
    for (int i = 0; i < sizeof(courses) / sizeof(courses[0]); ++i) {
        if (!strcmp(class->code.subject, courses[i].code.subject) && !strcmp(class->code.number, courses[i].code.number))
            return courses[i].name;
    }
    return NULL;
}

int main (int argc, char **argv) {
    loadTimetables();

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    int class_col_width = (w.ws_col - 7 - 5) / 5;
    int class_col_width_half0 = (class_col_width - 1) / 2;
    int class_col_width_half1 = class_col_width - 1 - class_col_width_half0;
    int time_col_width = w.ws_col - 5 * class_col_width - 7;

    putchar('|');
    for (int i = 0; i < time_col_width; ++i)
        putchar('-');
    putchar('|');
    for (int i = MONDAY; i <= FRIDAY; ++i) {
        for (int j = 0; j < class_col_width; ++j) {
            putchar('-');
        }
        putchar('|');
    }
    putchar('\n');

    putchar('|');
    for (int i = 0; i < time_col_width; ++i)
        putchar(' ');
    putchar('|');
    for (int i = MONDAY; i <= FRIDAY; ++i) {
        printf("%-*.*s", class_col_width, class_col_width, weekdays[i]);
        putchar('|');
    }
    putchar('\n');

    for (int slot = start_slot; slot < end_slot; slot += 2) {
        putchar('|');
        for (int i = 0; i < time_col_width; ++i)
            putchar('-');

        for (int wday = MONDAY; wday <= FRIDAY; ++wday) {
            putchar('|');
            if (!second[wday][slot]) {
                if (!second[wday][slot - 1]) {
                    if (first[wday][slot] == first[wday][slot - 1] && slot != start_slot) {
                        for (int i = 0; i < class_col_width; ++i)
                            putchar(' ');
                    } else {
                        for (int i = 0; i < class_col_width; ++i)
                            putchar('-');
                    }
                } else {
                    if (first[wday][slot] == first[wday][slot - 1] && slot != start_slot) {
                        for (int i = 0; i < class_col_width_half0; ++i)
                            putchar(' ');
                    } else {
                        for (int i = 0; i < class_col_width_half0; ++i)
                            putchar('-');
                    }
                    putchar('|');
                    if (first[wday][slot] == second[wday][slot - 1] && slot != start_slot) {
                        for (int i = 0; i < class_col_width_half1; ++i)
                            putchar(' ');
                    } else {
                        for (int i = 0; i < class_col_width_half1; ++i)
                            putchar('-');
                    }
                }
            } else if (!more_than_two[wday][slot]) {
                if (first[wday][slot] == first[wday][slot - 1] && slot != start_slot) {
                    for (int i = 0; i < class_col_width_half0; ++i)
                        putchar(' ');
                } else {
                    for (int i = 0; i < class_col_width_half0; ++i)
                        putchar('-');
                }
                putchar('|');
                if ((second[wday][slot] == second[wday][slot - 1] || !second[wday][slot - 1] && second[wday][slot] == first[wday][slot - 1]) && slot != start_slot) {
                    for (int i = 0; i < class_col_width_half1; ++i)
                        putchar(' ');
                } else {
                    for (int i = 0; i < class_col_width_half1; ++i)
                        putchar('-');
                }
            } else {
                printf("ERROR: More than 3 courses at a time");
                return -1;
            }
        }
        putchar('|');
        putchar('\n');

        putchar('|');
        printf("%*.2d:%2.2d", time_col_width - 3, slot / 2, slot % 2 * 30);
        for (int wday = MONDAY; wday <= FRIDAY; ++wday) {
            putchar('|');
            if (!second[wday][slot]) {
                if (first[wday][slot] == first[wday][slot - 1] || first[wday][slot] == second[wday][slot - 1])
                    printf("%*s", class_col_width, "");
                else
                    printf("%4.4s %3.3s %-*.*s", classes[first[wday][slot]].code.subject, classes[first[wday][slot]].code.number, class_col_width - 9, class_col_width - 9, classtypes[classes[first[wday][slot]].type]);
            } else if (!more_than_two[wday][slot]) {
                if (first[wday][slot] == first[wday][slot - 1]) {
                    printf("%*s", class_col_width_half0, "");
                } else {
                    printf("%4.4s %-*.3s", classes[first[wday][slot]].code.subject, class_col_width_half0 - 5, classes[first[wday][slot]].code.number);
                }
                putchar('|');
                if (second[wday][slot] == second[wday][slot - 1] || !second[wday][slot - 1] && second[wday][slot] == first[wday][slot - 1]) {
                    printf("%*s", class_col_width_half1, "");
                } else {
                    printf("%4.4s %-*.3s", classes[second[wday][slot]].code.subject, class_col_width_half1 - 5, classes[second[wday][slot]].code.number);

                }
            } else {
                printf("ERROR: More than 3 courses at a time");
                return -1;
            }
        }
        putchar('|');
        putchar('\n');

        putchar('|');
        printf("%*s", time_col_width, "");
        for (int wday = MONDAY; wday <= FRIDAY; ++wday) {
            putchar('|');
            if (!second[wday][slot]) {
                if (first[wday][slot] == first[wday][slot - 1] || first[wday][slot] == second[wday][slot - 1])
                    printf("%*s", class_col_width, "");
                else
                    printf("%*.*s", class_col_width, class_col_width, findCourseName(&classes[first[wday][slot]]));
            } else if (!more_than_two[wday][slot]) {
                if (first[wday][slot] == first[wday][slot - 1]) {
                    printf("%*s", class_col_width_half0, "");
                } else {
                    printf("%*.*s", class_col_width_half0, class_col_width_half0, findCourseName(&classes[first[wday][slot]]));
                }
                putchar('|');
                if (second[wday][slot] == second[wday][slot - 1] || !second[wday][slot - 1] && second[wday][slot] == first[wday][slot - 1]) {
                    printf("%*s", class_col_width_half1, "");
                } else {
                    printf("%*.*s", class_col_width_half1, class_col_width_half1, findCourseName(&classes[second[wday][slot]]));
                }
            } else {
                printf("ERROR: More than 3 courses at a time");
                return -1;
            }
        }
        putchar('|');
        putchar('\n');

        putchar('|');
        printf("%*s", time_col_width, "");
        for (int wday = MONDAY; wday <= FRIDAY; ++wday) {
            putchar('|');
            if (!second[wday][slot]) {
                if (first[wday][slot] == first[wday][slot - 1] || first[wday][slot] == second[wday][slot - 1])
                    printf("%*s", class_col_width, "");
                else
                    printf("%*.*s", class_col_width, class_col_width, classes[first[wday][slot]].location);
            } else if (!more_than_two[wday][slot]) {
                if (first[wday][slot] == first[wday][slot - 1]) {
                    printf("%*s", class_col_width_half0, "");
                } else {
                    printf("%*.*s", class_col_width_half0, class_col_width_half0, classes[first[wday][slot]].location);
                }
                putchar('|');
                if (second[wday][slot] == second[wday][slot - 1] || !second[wday][slot - 1] && second[wday][slot] == first[wday][slot - 1]) {
                    printf("%*s", class_col_width_half1, "");
                } else {
                    printf("%*.*s", class_col_width_half1, class_col_width_half1, classes[first[wday][slot]].location);
                }
            } else {
                printf("ERROR: More than 3 courses at a time");
                return -1;
            }
        }
        putchar('|');
        putchar('\n');
    }

    putchar('|');
    for (int i = 0; i < time_col_width; ++i)
        putchar('-');
    putchar('|');
    for (int i = MONDAY; i <= FRIDAY; ++i) {
        for (int j = 0; j < class_col_width; ++j) {
            putchar('-');
        }
        putchar('|');
    }
    putchar('\n');
}
