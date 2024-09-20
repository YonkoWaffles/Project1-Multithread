
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>

//Declaring of variables to be used
pthread_t tid[3];
pthread_mutex_t lock;
int counter = 0;

FILE *file;

//one method for thread function to demostrate synchronization 
void* ThreadTest1(void* v1){

  pthread_mutex_lock(&lock); //locks the thread up on access
  
  //based on the current thread a particularaction takes to show sync
  switch (counter){
  	case 0: //case 0 writing to file
  	
	printf("Thread Job %d: Started.\n", counter );
	printf("T1 File Writing starting...\n");
	file = fopen("/home/DomainofD/Desktop/Tsync.txt", "w");
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
	printf("Thread Job %d: Ended.\n", counter);
  	break;
	case 1: //case one appending to previously written file
	
	printf("Thread Job %d: Started.\n", counter );
	printf("T2 File Appending starting...\n");
	file = fopen("/home/DomainofD/Desktop/Tsync.txt", "a");
	fprintf(file, "Bob: Let’s find out! More magic awaits!\n\n"
        "  (Bob puts the rabbit back into the hat.)\n\n"
        "  (Suddenly, Charlie enters, looking puzzled.)\n\n"
        "Charlie: What’s all this commotion? Are you two plotting something?\n\n"
        "Bob: (smirking) Just a little magic, Charlie! Want to see?\n\n"
        "Charlie: (crosses arms) I don’t believe in magic. Show me something real.\n\n"
        "Alice: (cheerfully) Come on, Charlie! Just watch!\n\n"
        "Bob: (confidently) Okay, how about a disappearing act?\n\n"
        "  (Bob covers the hat with a cloth and waves his hands.)\n\n"
        "Bob: Now you see it... now you don’t!\n\n"
        "  (He pulls the cloth away, revealing an empty hat.)\n\n"
        "Charlie: (eyes widening) Wait, where did it go?\n\n"
        "Alice: (giggling) Magic, remember?\n\n"
        "Bob: (with a flourish) It’s all part of the show!\n\n"
        "  (The lights dim again as Bob reaches into the hat.)\n\n"
        "Bob: And now... for the grand finale!\n\n"
        "Scene 3: The living room, moments later.\n\n"
        "  (Bob pulls out an unexpected object—a bouquet of flowers.)\n\n"
        "Bob: Ta-da! A bouquet for our lovely audience!\n\n"
        "Alice: (delighted) Oh, they’re beautiful!\n\n"
        "Charlie: (softening) Okay, I’ll admit, that was pretty cool.\n\n"
        "Bob: (bowing) Thank you, thank you! But the night isn’t over yet!\n\n"
        "Alice: What do you have planned now?\n\n"
        "Bob: (grinning) Let’s make this living room a magical place!\n\n"
        "  (Bob starts arranging the flowers around the room.)\n\n"
        "Charlie: (laughing) Alright, Mr. Magician, let’s see what you can do!\n\n"
        "  (The curtain falls as they prepare for more magic.)\n");
	
	fclose(file);
	printf("Thread Job %d: Ended.\n", counter);
	
	break;
	case 2: //reading from the previously written and appended file
	printf("Thread Job %d: Started.\n", counter );
	printf("T3 File Reading starting...\n");
	file = fopen("/home/DomainofD/Desktop/Tsync.txt", "r");
	char readSTR[1000000];
	
	while(fgets(readSTR,1000000,file)){
	printf("%s", readSTR);
	}
	fclose(file);
	printf("Thread Job %d: Ended.\n", counter);
	break;
  	
  	counter += 1;
  }
  
  pthread_mutex_unlock(&lock);// Unlocking the thread after each process is done
  
  counter += 1; //increase counter to ensure current function is done
  return NULL;
}

int main(void){

  int result;
  int Oresult;
  int i = 0;
  int j = 0;
  
  //ensure mutex exists
  if(pthread_mutex_init(&lock, NULL)!=0){
  	printf("\n mutex init has failed\n");
  	return 1;
  }
  
  //creates the threads incrementally and send them to he thread method
  while (i< 3){
    
    printf("From Main -> Creating thread %d.\n", i);
    result = pthread_create(&tid[i], NULL, &ThreadTest1, NULL);
    if (result != 0){
    	printf("\nThread can't be created :[%s]", strerror(result));
    }
    i++;
  }
  printf("From Main -> all thread are created\n");
  
  //ends threads
  while (j < 3){
   pthread_join(tid[j], NULL);
   j++;
  }
  
  //destroys mutex
  pthread_mutex_destroy(&lock);
  printf("From Main -> Main tired.............Main ended\n");
  
  return 0;
}
