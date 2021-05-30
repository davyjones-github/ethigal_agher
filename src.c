// gcc -no-pie -o password_reset src.c
// sudo chown root:root password_reset && sudo chmod +s password_reset
// crontab -e
// @reboot socat TCP-LISTEN:6969,reuseaddr,fork EXEC:/home/password_reset

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define WHT "\x1B[37m"
#define RESET "\x1B[0m"

void banner();
void password_recovery();
void resetpwd();
int checkname(char *);
int checkplaceofbirth(char *);
int checkpetname(char *);
// void reportincident();

int main()
{
    banner();
    puts(YEL "This is a test platform to allow password recovery for administrator.");
    puts(YEL "If you answer the questions correctly you will be given the opportunity to log in as root to the system and reset the password.");
    puts(YEL "It is still on development, sorry for the possible bugs (:");
    puts(YEL "I uploaded the source code to this link: https://pastebin.com/PkTUeRJv" RESET);
    password_recovery();
return 0;
}

void password_recovery() {
    ssize_t n_chars_read;
    char buffer[56];

    puts(WHT "\nWhat is your name?" RESET);
    printf(GRN "> " RESET);
    fflush(stdout);

    memset(buffer, 0, sizeof(buffer));
    n_chars_read = read(0, buffer, 0x38);
    buffer[(int)n_chars_read] = '\n';
    printf(YEL "Hello %s" RESET, buffer);
    
    if(!checkname(buffer)) {
        puts(RED "You are not the admin! This incident will be reported" RESET);
        // reportincident();
        exit(EXIT_FAILURE);
    }

    puts(WHT "Where were you born?" RESET);
    printf(GRN "> " RESET);
    fflush(stdout);
    memset(buffer, 0, sizeof(buffer));
    read(0, buffer, 0x50);

    if(!checkplaceofbirth(buffer)) {
        puts(RED "You are not the admin! This incident will be reported" RESET);
        // reportincident();
        exit(EXIT_FAILURE);
    }
    
    puts(WHT "\nWhat is your pet's name?" RESET);
    printf(GRN "> " RESET);
    fflush(stdout);
    memset(buffer, 0, sizeof(buffer));
    fgets(buffer, sizeof(buffer), stdin);

    if(!checkpetname(buffer)) {
        puts(RED "You are not the admin! This incident will be reported" RESET);
        // reportincident();
        exit(EXIT_FAILURE);
    }
    
    // TODO: enter other questions
    // resetpwd();
    
    puts(RED "Goodbye!" RESET);
}

void banner() {
    puts(GRN "\
  _____                                    _                                          \n\
 |  __ \\                                  | |                                         \n\
 | |__) |_ _ ___ _____      _____  _ __ __| |  _ __ ___  ___ _____   _____ _ __ _   _ \n\
 |  ___/ _` / __/ __\\ \\ /\\ / / _ \\| '__/ _` | | '__/ _ \\/ __/ _ \\ \\ / / _ \\ '__| | | |\n\
 | |  | (_| \\__ \\__ \\\\ V  V / (_) | | | (_| | | | |  __/ (_| (_) \\ V /  __/ |  | |_| |\n\
 |_|   \\__,_|___/___/ \\_/\\_/ \\___/|_|  \\__,_| |_|  \\___|\\___\\___/ \\_/ \\___|_|   \\__, |\n\
                                                                                 __/ |\n\
                                                                                |___/ \n" RESET);
}

int checkname(char *name) {
    return !strncmp(name, "buzz", 4) ? 1 : 0; 
}

int checkplaceofbirth(char *place) {
    printf("%s", place);
    return !strncmp(place, "campodimele", 11) ? 1 : 0; 
}

int checkpetname(char *pet) {
    return !strncmp(pet, "terminator", 10) ? 1 : 0; 
}

void resetpwd() {
    setuid(0);
    char *argv[2] = {"/bin/sh", NULL};
    execve(argv[0], argv, NULL);
    return;
}

// void reportincident() {
//     // TODO
// }
