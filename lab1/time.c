#include <stdio.h>
#include <time.h>

char* get_time(char* s) {
    struct tm *local;
    time_t t;
    // time_t time(time_t * timer);如果参数为空（NULL），函数将只通过返回值返回现在的日历时间
    t = time(NULL);
    // localtime()函数是将日历时间转化为本地时间
    local = localtime(&t);
    sprintf(s, "Local time is: %02d:%02d:%02d\n", local->tm_hour, local->tm_min, local->tm_sec);
    return s;
}

int main(void)
{
    char time[40];
    printf("%s", get_time(time));
    return 0;
}

