#include "random.h"
#include <stdio.h>
#include <time.h>

#define MIN_DAY    1    /* min birth day */
#define MAX_DAY    31   /* max birth day */

#define MIN_MONTH    0    /* min birth month */
#define MAX_MONTH    11    /* max birth month */

#define MIN_YEAR    0    /* min birth year */
#define MAX_YEAR    121    /* max birth year */

#define MIN_CONVICTION_AGE    18

#define MAX_DATE_BUF_SIZE    12    /* max length of birth date + termination character */

#define DIG_CODE_LEN    10

/* using random API to generate simple fake ID-cards */
int main(void) {
    /* let the ID-card contain information: name, surname, date of birth, convicted/not convicted, code, digital code */

    char* names[] = {"Richard", "Anna", "Bob", "Elizabeth", "Harold", "Margaret"};
    size_t names_size = sizeof(names) / sizeof(names[0]);

    char* surnames[] = {"Davis", "Smith", "Rodriguez", "Anderson", "Lee", "Scott"};
    size_t surnames_size = sizeof(surnames) / sizeof(surnames[0]);

    /* randomize name and surname */

    char* name = names[rand_int_range(0, (int64_t)names_size)];
    char* surname = surnames[rand_int_range(0, (int64_t)surnames_size)];

    /* randomize birth data */

    struct tm birth_date = {
            0, 0, 0,
            .tm_mday = (int)rand_int_range(MIN_DAY, MAX_DAY),
            .tm_mon = (int)rand_int_range(MIN_MONTH, MAX_MONTH),
            .tm_year = (int)rand_int_range(MIN_YEAR, MAX_YEAR),
            0, 0, 0
    };

    char date_string[MAX_DATE_BUF_SIZE];
    strftime(date_string, MAX_DATE_BUF_SIZE, "%b %d %Y", &birth_date);

    time_t cur_time = time(NULL);
    struct tm cur_time_data = *localtime(&cur_time);
    uint8_t age = (uint8_t)(cur_time_data.tm_year - birth_date.tm_year);

    /* randomize conviction info */

    uint8_t convicted = rand_bool();

    /* randomize codes */

    char code[DIG_CODE_LEN + 1] = {0};

    for (int i = 0; i < DIG_CODE_LEN; ++i) {
        if (rand_bool()) {
            code[i] = (char)rand_int_range(48, 57);    /* numerical characters */
        } else {
            code[i] = (char)rand_int_range(65, 90);    /* capital alphabet characters */
        }
    }

    uint16_t digital_code = rand16();

    /* display data */

    printf("Name: %s\n", name);
    printf("Surname: %s\n", surname);
    printf("Date of birth: %s\n", date_string);
    printf("Age: %u\n", age);
    putchar('\n');
    printf("Was%s convicted\n", convicted && age >= MIN_CONVICTION_AGE ? "" : " not");
    putchar('\n');
    printf("Code: %s\n", code);
    printf("Digital code: %hu\n", digital_code);

    return 0;
}