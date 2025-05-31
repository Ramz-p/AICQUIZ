#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 512

// Helper to trim newline
void trim_newline(char *str) {
    char *pos;
    if ((pos=strchr(str, '\n')) != NULL)
        *pos = '\0';
}

// Helper to convert input to uppercase
char to_upper(char c) {
    return (char)toupper((unsigned char)c);
}

int main() {
    int total = 0, correct = 0, wrong = 0;
    char choice;

    do {
        // Generate new question
        system("python generate_question.py > question.txt");

        FILE *file = fopen("question.txt", "r");
        if (!file) {
            printf("Could not open question.txt\n");
            return 1;
        }

        char buffer[MAX_LINE];
        char question[MAX_LINE] = "";
        char options[4][MAX_LINE];
        char correct_answer = '\0';

        // Read JSON manually (simplified for predictable output)
        while (fgets(buffer, sizeof(buffer), file)) {
            if (strstr(buffer, "\"question\"")) {
                sscanf(buffer, " \"question\": \"%[^\"]", question);
            } else if (strstr(buffer, "\"options\"")) {
                for (int i = 0; i < 4; i++) {
                    fgets(buffer, sizeof(buffer), file);
                    sscanf(buffer, " \"%[^\"]", options[i]);
                }
            } else if (strstr(buffer, "\"correct\"")) {
                sscanf(buffer, " \"correct\": \"%c", &correct_answer);
                correct_answer = to_upper(correct_answer);
            }
        }

        fclose(file);

        // Display question
        printf("\nQ: %s\n", question);
        printf("A) %s\n", options[0]);
        printf("B) %s\n", options[1]);
        printf("C) %s\n", options[2]);
        printf("D) %s\n", options[3]);

        // Get user answer
        char answer;
        printf("\nEnter your answer (A, B, C, D): ");
        scanf(" %c", &answer);
        answer = to_upper(answer);

        // Check and update score
        total++;
        if (answer == correct_answer) {
            printf(" Correct!\n");
            correct++;
        } else {
            printf(" Wrong. Correct answer was: %c\n", correct_answer);
            wrong++;
        }

        // Ask if user wants to continue
        printf("\nDo you want to continue? (Y/N): ");
        scanf(" %c", &choice);
        choice = to_upper(choice);

    } while (choice == 'Y');

    // Final stats
    printf("\nQuiz ended.\n");
    printf("Total Questions: %d\n", total);
    printf("Correct Answers: %d\n", correct);
    printf("Wrong Answers:   %d\n", wrong);

    return 0;
}
