#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* --------------------------------------------- */
/* Basic validation: ensure option name is safe   */
/* --------------------------------------------- */
int validate_option(const char *option) {

    /* Empty option name */
    if (option[0] == '\0') {
        printf("What were you thinking?\n");
        return 0;
    }

    /* First character must be alphabetic */
    if (!isalpha(option[0])) {
        printf("Option '%s' must start with a letter\n", option);
        return 0;
    }

    /* Check each character */
    for (int i = 0; option[i] != '\0'; i++) {
        char c = option[i];

        /* Allowed: letters, digits, underscore */
        if (isalnum(c) || c == '_') {
            continue;
        }

        /* Everything else is invalid */
        printf("Option '%s' contains invalid character '%c'\n",
               option, c);
        return 0;
    }

    return 1;
}

/* --------------------------------------------- */
/* Safe wrapper used by main.c                   */
/* --------------------------------------------- */
void write_validated_option(FILE *out, const char *option, int enable) {

    /* Validate */
    if (!validate_option(option)) {
        printf("Skipping invalid option '%s'\n", option);
        return;
    }

    /* Write output */
    if (enable) {
        fprintf(out, "echo \"Enabling %s\"\n", option);
        fprintf(out, "export %s=1\n", option);
    } else {
        fprintf(out, "echo \"Disabling %s\"\n", option);
        fprintf(out, "export %s=0\n", option);
    }
}
