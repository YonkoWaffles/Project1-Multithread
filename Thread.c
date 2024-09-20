
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<pthread.h>
#include<unistd.h>

//declaring variables
FILE *file;
FILE *file2;
FILE *file3;

//thread 1 method writes to file
void* Thread1(void* v1){
	printf("T1 File Writing starting...\n");
	file = fopen("/home/DomainofD/Desktop/T1 assignment.txt", "w");
	fprintf(file,"Title: Monthly Sales Report\n"
        "=============================\n"
        "Prepared by: John Doe\n"
        "Date: September 2024\n\n"
        "1. Executive Summary\n"
        "This report summarizes the sales performance for the month of August 2024.\n\n"
        "2. Sales Performance\n"
        "   - Total Sales: $150,000\n"
        "   - Number of Transactions: 1,200\n"
        "   - Average Transaction Value: $125\n\n"
        "3. Key Highlights\n"
        "   - Increased sales in the Electronics department.\n"
        "   - Successful launch of the new product line.\n\n"
        "4. Challenges\n"
        "   - Supply chain delays affected inventory levels.\n"
        "   - Increased competition in the market.\n\n"
        "5. Conclusion\n"
        "Overall, the sales team performed well this month, but there are areas for improvement.\n"
        "We will focus on addressing the challenges in the coming months.");
        
	fclose(file);
	printf("T1 Ended.\n");
	
	
return NULL;
}

//thread 2 method reads from file
void* Thread2(void* v1){
	printf("T2 File Reading starting...\n");
	file2 = fopen("/home/DomainofD/Desktop/T2 assignment.txt", "r");
	char readSTR[1000000];
	
	while(fgets(readSTR,1000000,file2)){
	printf("%s", readSTR);
	}
	
	fclose(file2);
	printf("T2 Ended.\n");
	
	
return NULL;
}

//Thread 3 writes to a file
void* Thread3(void* v1){
	printf("T3 File Writing starting...\n");
	file3 = fopen("/home/DomainofD/Desktop/T3 assignment.txt", "w");
	fprintf(file3, "Title: Chemistry Lab Report on Acid-Base Reactions\n"
        "Prepared by: Dr. Sarah Johnson\n"
        "Date: September 2024\n\n"
        "1. Objectives\n"
        "   - To investigate the reaction between hydrochloric acid and sodium hydroxide.\n"
        "   - To determine the pH changes during the reaction.\n\n"
        "2. Methodology\n"
        "   - A titration setup was prepared using a burette and a conical flask.\n"
        "   - 0.1 M hydrochloric acid was gradually added to 0.1 M sodium hydroxide while stirring.\n"
        "   - pH measurements were taken at regular intervals.\n\n"
        "3. Results\n"
        "   - The neutralization point was reached at 25 mL of hydrochloric acid added.\n"
        "   - The final pH at the equivalence point was approximately 7.0.\n\n"
        "4. Discussion\n"
        "   The experiment demonstrated a typical acid-base neutralization reaction, with the expected pH change.\n"
        "   The results were consistent with theoretical predictions, confirming the effectiveness of titration for determining concentrations.\n\n"
        "5. Conclusion\n"
        "   The experiment successfully achieved its objectives. Further investigations could include varying concentrations and additional acid-base pairs.");
	
	fclose(file3);
	printf("T3 Ended.\n");
	
	
return NULL;
}


int main(void){
	pthread_t thread_id[3];
	int result;
	int result2;
	int result3;
	
	//Creating threads and throwing alert if they are null 
	printf("From Main -> Creating T1.\n");
	result = pthread_create(&thread_id[0], NULL, Thread1, NULL);
	assert(!result);
	printf("From Main -> Creating T2.\n");
	result2 = pthread_create(&thread_id[1], NULL, Thread2, NULL);
	assert(!result2);
	printf("From Main -> Creating T3.\n");
	result3 = pthread_create(&thread_id[2], NULL, Thread3, NULL);
	assert(!result3);
   
	printf("From Main -> all thread are created");
  
  	//Ending threads 
	pthread_join(thread_id[0], NULL);
	printf("From Main -> T1 has ended.\n");
	pthread_join(thread_id[1], NULL);
	printf("From Main -> T2 has ended.\n");
	pthread_join(thread_id[2], NULL);
	printf("From Main -> T3 has ended.\n");

	//Ending program
	printf("From Main -> Main tired.............Main ended\n");
}
