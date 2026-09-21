#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

/* Helper: write enable/disable lines to configure script */
void write_option(FILE *out, const char *option, int enable) {
    if (enable) {
        fprintf(out, "echo \"Enabling %s\"\n", option);
        fprintf(out, "export %s=1\n", option);
    } else {
        fprintf(out, "echo \"Disabling %s\"\n", option);
        fprintf(out, "export %s=0\n", option);
    }
}

int main(int argc, char *argv[]) {

    if (argc < 3) {
        printf("Usage:\n");
        printf("  %s build CONFECTIONERYCONFIG\n", argv[0]);
        printf("  %s build PRESETS presetname\n", argv[0]);
        return 1;
    }

    /* Mode detection */
    int using_presets = 0;
    char *config_file = NULL;
    char *presets_file = NULL;
    char *preset_name = NULL;

    if (argc == 3) {
        /* Normal config mode */
        config_file = argv[2];
    } else if (argc == 4) {
        /* Preset mode */
        using_presets = 1;
        presets_file = argv[2];
        preset_name = argv[3];
    }

    /* Create configure script */
    FILE *out = fopen("configure", "w");
    if (!out) {
        printf("Fatality: could not create configure script!\n");
        return 1;
    }

    fprintf(out, "#!/bin/sh\n");
    fprintf(out, "echo \"Running configure script\"\n");

    char line[256];
    char option[128];

    /* ------------------------------- */
    /* Normal config mode              */
    /* ------------------------------- */
    if (!using_presets) {
        FILE *config = fopen(config_file, "r");
        if (!config) {
            printf("Fatality: could not open %s!\n", config_file);
            fclose(out);
            return 1;
        }

        while (fgets(line, sizeof(line), config)) {
            if (strstr(line, "is on")) {
                sscanf(line, "$%127s", option);
                write_option(out, option, 1);
            }
            if (strstr(line, "is off")) {
                sscanf(line, "$%127s", option);
                write_option(out, option, 0);
            }
        }

        fclose(config);
    }

    /* ------------------------------- */
    /* Preset mode                     */
    /* ------------------------------- */
    if (using_presets) {
        FILE *p = fopen(presets_file, "r");
        if (!p) {
            printf("Fatality: could not open %s! Try making your own configuration.\n", presets_file);
            fclose(out);
            return 1;
        }

        int in_correct_preset = 0;

        while (fgets(line, sizeof(line), p)) {

            /* Detect preset header */
            if (strstr(line, "[preset")) {
                /* Example: [preset speedy] */
                if (strstr(line, preset_name)) {
                    in_correct_preset = 1;
                } else {
                    in_correct_preset = 0;
                }
            }

            /* Only parse inside the chosen preset */
            if (in_correct_preset) {
                if (strstr(line, "is on")) {
                    sscanf(line, "$%127s", option);
                    write_option(out, option, 1);
                }
                if (strstr(line, "is off")) {
                    sscanf(line, "$%127s", option);
                    write_option(out, option, 0);
                }
            }
        }

        fclose(p);
    }

    /* Finalize configure script */
    fclose(out);
    chmod("configure", 0755);

    printf("Success!\n");

    return 0;
}
