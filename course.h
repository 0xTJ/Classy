#ifndef _COURSE_H
#define _COURSE_H

#include <time.h>

enum ClassType { LECTURE, TUTORIAL, LAB, STUDIO, OTHER };
enum Weekday { SUNDAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY };
const char * const classtypes[] = { "lecture", "tutorial", "laboratory", "studio", "other" };
const char * const weekdays[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

struct CourseCode {
    char subject[8];
    char number[8];
};

struct Course {
    struct CourseCode code;
    char name[32];
};

struct Class {
    struct CourseCode code;
    int start_slot;
    int length_slots;
    enum Weekday wday;
    enum ClassType type;
};

#endif // ifndef _COURSE_H
