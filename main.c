#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

void sigintHandler(int sig_num);

#ifdef _WIN32
#include <Windows.h>
void sleep_ms(int ms)
{
    Sleep(ms);
}
void clearscr()
{
    system("cls");
}

#else
#include <unistd.h>
#include <signal.h>
void sigintHandler(int sig_num) //return the cursor upon CTRL+C
{
    system("tput cnorm");
    exit(0);
}
void sleep_ms(int ms)
{
    usleep(ms * 1000);
}
void clearscr()
{
    printf("\e[1;1H\e[2J");
}
#endif

#define update_MS 250

#define GREEN "\033[0;32m"
#define RED  "\033[0;31m"
#define BLUE "\033[0;34m"
#define PURPLE "\033[0;35m"
#define CYAN "\033[0;36m"
#define BLACK "\033[0;30m"
#define WHITE "\033[0;37m"
#define RESET "\033[0;0m"

const char* numbers[][5] = {
    {"  ██████  ", " ██  ████ ", " ██ ██ ██ ", " ████  ██ ", "  ██████  "}, //0
    {"  ██ ", " ███ ", "  ██ ", "  ██ ", "  ██ "}, //1
    {" ██████  ", "      ██ ", "  █████  ", " ██      ", " ███████ "}, //2
    {" ██████  ", "      ██ ", "  █████  ", "      ██ ", " ██████  "}, //3
    {" ██   ██ ", " ██   ██ ", " ███████ ", "      ██ ", "      ██ "}, //4
    {" ███████ ", " ██      ", " ███████ ", "      ██ ", " ███████ "}, //5
    {"  ██████  ", " ██       ", " ███████  ", " ██    ██ ", "  ██████  "}, //6
    {" ███████ ", "      ██ ", "     ██  ", "    ██   ", "    ██   "}, //7
    {"  █████  ", " ██   ██ ", "  █████  ", " ██   ██ ", "  █████  "}, //8
    {"  █████  ", " ██   ██ ", "  ██████ ", "      ██ ", "  █████  "}, //9
    {"   ", " █ ", "   ", " █ ", "   "} // :
};

void updateclock(char* cur_time);
int ctoi(char n);

int main(int argc, char** argv)
{
    clearscr();
    #ifndef _WIN32
    system("tput civis"); //hide cursor
    signal(SIGINT, sigintHandler);
    #endif
    time_t now;
    struct tm *tm;
    int hours, minutes, seconds;
    char stime[30] = "";
    char prevtime[30] = "";
    while (1) {
        now = time(NULL);
        tm = localtime(&now);
        int hours = tm->tm_hour, minutes = tm->tm_min, seconds = tm->tm_sec;
        sprintf(stime, "%d:%d:%d", hours, minutes, seconds);
        if (strcmp(stime, prevtime)) {
            updateclock(stime);
            strcpy(prevtime, stime);
            sleep_ms(update_MS);
            clearscr();
        }
        else {
            sleep_ms(update_MS);
        }
    }    
}

void updateclock(char* cur_time)
{
    printf("\n\n\n\n");
    char output_line[500];
    strcpy(output_line, "");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < strlen(cur_time); j++) {
            if (cur_time[j] != ':') {
                strcat(output_line, numbers[ctoi(cur_time[j])][i]);
            }
            else {
                strcat(output_line, numbers[10][i]);
            }
        }
        printf(CYAN "            %s%s\n", output_line, RESET);
        strcpy(output_line, "");
    }
}

int ctoi(char n)
{
    return ((int)n) - 48;
}
