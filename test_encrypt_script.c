#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char __attribute__((annotate("sensitive"))) *key ;
char *ciphertext;
unsigned int i;

void greeter (char *str) {
	printf("%s\n",str); 
	printf(", welcome!\n"); 
}

void initkey (int sz) {
	key = (char *) (malloc (sz));
	// init the key randomly; code omitted
	for (i=0; i<sz; i++) key[i]= 1;
}

void encrypt (char *plaintext, int sz) {
	ciphertext = (char *) (malloc (sz));
	for (i=0; i<sz; i++)
		ciphertext[i]=plaintext[i] ^ key[i];
}

int main (){
	char username[20], text[1024];
	printf("Enter username: ");
	scanf("%19s",username);
	greeter(username);
	printf("Enter plaintext: ");
	scanf("%1023s",text);

	initkey(strlen(text));
	encrypt(text, strlen(text));
	printf("Cipher text: ");
	for (i=0; i<strlen(text); i++)
		printf("%x ",ciphertext[i]);
    return 0;
}
