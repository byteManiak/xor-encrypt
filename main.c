#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void encrypt(char *data, unsigned len)
{
	char *ptr = data, xor_value;
	ptr = realloc(ptr, len+1); // increase string size by 1
	for(int i = 0; i < len; i++)
		if(rand()%2 == 0) // if random event happens, start putting XOR inside the string (put it at random position for "increased security")
		{
			xor_value = rand()%15+17; // the value to XOR the entire string with is between 17 and 31. that's because actual ascii characters start at 32
			for(int j = len; j > i; j--)
				ptr[j] = ptr[j-1]; // move everything to the right one by one to make space for the XOR value in the string
			ptr[i] = xor_value; // put the XOR value in the string
			break;
		}
	printf("Intermediary: %s\n", ptr);
	for(int i = 0; i < len+1; i++)
		if(ptr[i] >= 32)
			ptr[i] ^= xor_value; // encrypt the entire string except for the XOR value

}

void decrypt(char *data, unsigned len)
{
	char *ptr = data, xor_value;
	for(int i = 0; i < len; i++)
		if(ptr[i] < 32) // XOR value is less than 32
		{
			xor_value = ptr[i]; // if found, store in xor_value
			for(int j = i; j < len; j++)
				ptr[j] = ptr[j+1]; // shift everything to left one by one to remove the XOR value from the string
			ptr[len]=0; // null-terminate the string
			break;
		}
	ptr = realloc(ptr, len); // resize the string back to its original size
	for(int i = 0; i < len; i++)
		ptr[i] ^= xor_value; // decrypt the string by XOR-ing every character (for any x and y, x ^ y ^ y = x)
}

int main()
{
	srand(time(NULL)); // get randomizer from system time
	char *data = malloc(12 * sizeof(char));
	
	sprintf(data, "Mello world!");

	printf("Original text: %s\n", data);

	encrypt(data, 12);
	printf("Encrypted: %s\n", data);
	
	decrypt(data, 12);
	printf("Decrypted: %s\n", data);
	return 0;	
}
