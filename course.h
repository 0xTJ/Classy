#ifndef _COURSE_H
#define _COURSE_H

#include <time.h>

enum ClassType { LECTURE, TUTORIAL, LAB, STUDIO, OTHER };
enum Weekday { SUNDAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY };
const char const * const classtypes[] = { "lecture", "tutorial", "laboratory", "studio", "other" };
const char const * const weekdays[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

union CourseCode {
    struct {
        char subject[8];
        char number[8];
    };
    unsigned long ident;
};
    
struct Course {
    union CourseCode code;
    char name[64];
};

struct Class {
    union CourseCode code;
    struct tm start_time;
    enum ClassType type;
};

#endif // ifndef _COURSE_H
