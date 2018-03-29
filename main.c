#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void encrypt(char *data, unsigned len)
{
	char *ptr = data, xor_value;
	ptr = realloc(ptr, len+1);
	for(int i = 0; i < len; i++)
		if(rand()%2 == 0)
		{
			xor_value = rand()%15+17;
			for(int j = len; j > i; j--)
				ptr[j] = ptr[j-1];
			ptr[i] = xor_value;
			break;
		}
	printf("Intermediary: %s\n", ptr);
	for(int i = 0; i < len+1; i++)
		if(ptr[i] >= 32)
			ptr[i] ^= xor_value;

}

void decrypt(char *data, unsigned len)
{
	char *ptr = data, xor_value;
	for(int i = 0; i < len; i++)
		if(ptr[i] < 32)
		{
			xor_value = ptr[i];
			for(int j = i; j < len; j++)
				ptr[j] = ptr[j+1];
			ptr[len]=0;
			break;
		}
	ptr = realloc(ptr, len);
	for(int i = 0; i < len; i++)
		ptr[i] ^= xor_value;
}

int main()
{
	srand(time(NULL));
	char *data = malloc(12);
	sprintf(data, "Mello world!");
	printf("Original text: %s\n", data);
	encrypt(data, 12);
	printf("Encrypted: %s\n", data);
	decrypt(data, 12);
	printf("Decrypted: %s\n", data);
	return 0;	
}
