#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

pthread_mutex_t first_mutex;
pthread_mutex_t second_mutex;
pthread_t tid[2];
int counter = 0;
FILE *file;


int max_resources[2][2] = {
    {1, 0}, // Max resources for Thread 1
    {0, 1}  // Max resources for Thread 2
};

int allocation[2][2] = {
    {0, 0}, // Currently allocated resources for Thread 1
    {0, 0}  // Currently allocated resources for Thread 2
};

int need[2][2] = {
    {1, 0}, // Remaining resources needed for Thread 1
    {0, 1}  // Remaining resources needed for Thread 2
};

bool is_safe() {
    int work[2] = {1, 1}; // Available resources
    bool finish[2] = {false, false};
    
    while (true) {
        bool found = false;
        for (int i = 0; i < 2; i++) {
            if (!finish[i]) {
                // Check if resources can be allocated
                if (need[i][0] <= work[0] && need[i][1] <= work[1]) {
                    // Simulate allocation
                    work[0] += allocation[i][0];
                    work[1] += allocation[i][1];
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) break; // No further allocations possible
    }
    
    for (int i = 0; i < 2; i++) {
        if (!finish[i]) return false; // If any thread is not finished, not safe
    }
    
    return true; // All threads can finish
}

void* ThreadTest1(void* v1) {
    printf("T1 trying to acquire first mutex\n");

    pthread_mutex_lock(&first_mutex);

    // Simulate resource allocation
    if (is_safe()) {
        allocation[0][0] = 1; // T1 is using the first resource
        printf("T1 writing to file => mutex 1 locked\n");

        file = fopen("/home/DomainofD/Desktop/TDsync.txt", "w");
        fprintf(file, "Title: A Night at the Theater\n\n"
            "Characters:\n"
            "   - Alice\n"
            "   - Bob\n\n"
            "Scene 1: A cozy living room.\n\n"
            "  (The lights dim, and Alice sits on the couch, reading a book.)\n\n"
            "Alice: (sighs) It's such a quiet evening. I wish something exciting would happen.\n\n"
            "  (Bob enters from stage left, holding a hat.)\n\n"
            "Bob: Did someone say 'exciting'? Look what I found!\n\n"
            "  (He dramatically reveals a magician's hat.)\n\n"
            "Alice: (curiously) A magician's hat? What do you plan to do with that?\n\n"
            "Bob: I'm going to perform magic! Watch and be amazed!\n\n"
            "  (Bob waves his hands over the hat.)\n\n"
            "Bob: Abracadabra! Something magical, appear!\n\n"
            "  (Suddenly, a stuffed rabbit pops out of the hat.)\n\n"
            "Alice: (claps) Wow! That’s incredible!\n\n"
            "Bob: (grinning) See? Magic is real!\n\n"
            "  (They both laugh as the lights fade.)\n\n");

        fclose(file);
        printf("T1 finished writing and releasing first mutex\n");
        allocation[0][0] = 0; // Release the resource
    }

    pthread_mutex_unlock(&first_mutex);
    return NULL;
}

void* ThreadTest2(void* v1) {
    printf("T2 trying to acquire second mutex\n");

    pthread_mutex_lock(&second_mutex);

    // Simulate resource allocation
    if (is_safe()) {
        allocation[1][1] = 1; // T2 is using the second resource
        printf("T2 writing to file => mutex 2 locked\n");

        file = fopen("/home/DomainofD/Desktop/TDsync2.txt", "w");
        fprintf(file, "Scene 4: A few hours later, the living room is transformed with flowers.\n\n"
            "  (Diana enters, looking amazed.)\n\n"
            "Diana: Wow! What happened here? It’s like a garden!\n\n"
            "Alice: Bob turned the living room into a magical place with his tricks!\n\n"
            "Diana: (smiling) That’s incredible! Bob, you have a real talent.\n\n"
            "Bob: (humbly) Thank you, Diana! But it’s all about having fun together.\n\n"
            "Charlie: (playfully) And proving to skeptics that magic exists!\n\n"
            "Diana: (laughs) Alright, show me a trick!\n\n"
            "Bob: (grinning) How about the old ‘disappearing coin’ trick?\n\n"
            "  (Bob takes a coin from his pocket and shows it to everyone.)\n\n"
            "Bob: Watch closely! One... two... three!\n\n"
            "  (He makes a dramatic gesture, and then opens his hand to show it empty.)\n\n"
            "Alice: (gasping) No way! Where did it go?\n\n"
            "Bob: (smirking) Ah, but that’s the magic! Now, let’s see if we can bring it back!\n\n"
            "  (Bob reaches behind Diana’s ear and pulls out the coin.)\n\n"
            "Diana: (astonished) How did you do that?\n\n"
            "Bob: (winking) A magician never reveals their secrets!\n\n"
            "Charlie: (grinning) I’m starting to believe in magic after all.\n\n"
            "Alice: (clapping) Let’s have a magic night! More tricks!\n\n"
            "Bob: (enthusiastically) Absolutely! Let’s keep the magic alive!\n\n");

        fclose(file);
        printf("T2 finished writing and releasing second mutex\n");
        allocation[1][1] = 0; // Release the resource
    }

    pthread_mutex_unlock(&second_mutex);
    return NULL;
}

int main(void) {
    pthread_mutex_init(&first_mutex, NULL);
    pthread_mutex_init(&second_mutex, NULL);

    pthread_create(&tid[0], NULL, &ThreadTest1, NULL);
    printf("T1 created\n");
    pthread_create(&tid[1], NULL, &ThreadTest2, NULL);
    printf("T2 created\n");

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    printf("Threads joined\n");

    pthread_mutex_destroy(&first_mutex);
    pthread_mutex_destroy(&second_mutex);
    
    return 0;
}

