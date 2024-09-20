#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<pthread.h>
#include<unistd.h>

//decalring variables to be used
pthread_mutex_t first_mutex; 
pthread_mutex_t second_mutex;
pthread_t tid[2];
int counter = 0;
FILE *file;

void* ThreadTest1(void* v1){
	printf("T1 writing to file => mutex 1 locked\n");
	pthread_mutex_lock(&first_mutex);//locks first mutex
	printf("Process is writing\n"); //Continues thread 1 process
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
        "  (They both laugh as the lights fade.)\n\n"
        "Scene 2: The living room, later that evening.\n\n"
        "Alice: (excitedly) What else can you do with that hat?\n\n"
        "Bob: Let’s find out! More magic awaits!\n\n"
        "  (The curtain falls as they prepare for the next trick.)\n");
	
	fclose(file);
	printf("T1 trying to access mutex 2\n");//tries to access second mutex, but its locked
	pthread_mutex_lock(&second_mutex);
	printf("T1 second mutex acquired\n");//never reaches the unlocking of the first mutex due to deadlock
	pthread_mutex_unlock(&first_mutex);
return NULL;
}
void* ThreadTest2(void* v1){
	printf("T2 writing to file => mutex 2 locked\n");
	pthread_mutex_lock(&second_mutex); //lock second mutex
	printf("Process is writing\n"); //Continues thread 2 process
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
        "Bob: (enthusiastically) Absolutely! Let’s keep the magic alive!\n\n"
        "  (The friends gather around as the lights fade.)\n\n"
        "Scene 5: The living room, a few moments later.\n\n"
        "  (The group is laughing and chatting, enjoying the magical atmosphere.)\n\n"
        "Diana: So, what’s next on the magic agenda?\n\n"
        "Bob: (thoughtfully) How about we create our own magic potion?\n\n"
        "Alice: (excited) That sounds fun! What do we need?\n\n"
        "Bob: (pretending to think) A dash of laughter, a sprinkle of joy, and a pinch of friendship!\n\n"
        "Charlie: (smirking) And maybe some soda for bubbles?\n\n"
        "  (They all laugh as they begin gathering items for their ‘potion’.)\n\n"
        "Diana: (playfully) This is going to be the best magic night ever!\n\n"
        "  (The curtain falls as they start mixing their ingredients, the atmosphere filled with laughter and joy.)\n");
	fclose(file);

	printf("T2 trying to access mutex 1\n");
	pthread_mutex_lock(&first_mutex); //tries to access first mutex, but its locked
	printf("T2 first mutex acquired\n");
	pthread_mutex_unlock(&second_mutex); // never reaches the unlocking of the second mutex due to deadlock
return NULL;
}

int main(void){
pthread_mutex_init(&first_mutex, NULL); //Creation of mutexes
pthread_mutex_init(&second_mutex, NULL);

pthread_create(&tid[0], NULL, &ThreadTest1, NULL); //Creation of threads
printf("T1 created\n");
pthread_create(&tid[1], NULL, &ThreadTest2, NULL);
printf("T2 created\n");

//End threads but we will never reach  here because of deadlock
pthread_join(tid[0], NULL);
pthread_join(tid[1], NULL);
printf("Thread joined\n");

return 0;
}


