#include <stdio.h>
#include <ctype.h>

//struct
typedef struct user_s{
	
	int userCounter;
	char *userName;
	char *encodedPassword;
	char *decodedPassword;
	int userToken;
}user_s;

//functions
void recordUser(struct user_s *);
int length(struct user_s *);
void encodePassword(struct user_s *);
void decodePassword(struct user_s *);
void writeToFile(struct user_s *);

//get user information (name, password, token), check them and write to the file
void recordUser(struct user_s *u)
{
	//a termination block for those who want to enter less than 10 records
	int exit=1;
	printf("\n*** To terminate, please enter '0', to continue please enter '1': ");
	scanf("%d", &exit);
	if(!exit)
	{
		u->userCounter=10;
		return;
	}
	//regular record user function starts here
	int controller=0, alpha=0;
	u->userCounter++;
	//get name
	printf("\nEnter the user name: ");
	scanf("%s", u->userName);
	//get password and check it
	while(controller<8 || !alpha)
	{
		alpha=1;
		char tempC, *temp;
		printf("\nEnter the password (at least 8 alphabet characters): ");
		scanf("%s", u->decodedPassword);
		temp=u->decodedPassword;
		while(*temp!='\0')
		{
			tempC = *temp;
			alpha=isalpha(tempC);
			*temp++;
		}
		controller=length(u);
		if(!alpha) printf("\nPassword characters must be alphabet, please enter again.");
		else if(controller<8) printf("\nPassword must contain at least 8 characters, please enter again.");
	}
	controller=0;
	//get token and check it
	while(controller<1 || controller>9)
	{
		printf("\nEnter the token (from 1 to 9): ");
		scanf("%d", &(u->userToken));
		controller=u->userToken;
		if(controller<1 || controller>9) printf("\nToken must be in the range 1-9, please enter again.");
	}
	//write the record of given user to the file
	writeToFile(u);
}

//calculate the length of given char pointer, in this program it will be the password length which must >8
int length(struct user_s *u)
{
	int pLength=0;
	char *temp = u->decodedPassword;
	while(*temp!='\0')
	{
		pLength++;
		*temp++;
	}
	return pLength;
}

//encode the given password 
void encodePassword(struct user_s *u)
{
	char cTemp, *temp;
	int iAsciiCode;
	int iToken=u->userToken;
	temp=u->decodedPassword;
	u->encodedPassword=temp;
	while(*temp!='\0')
	{
		cTemp = *temp;
		cTemp = toupper(cTemp);
		iAsciiCode = (int)cTemp;
		cTemp = iAsciiCode + iToken;
		*temp = cTemp;
		*temp++;
	}
}

void decodePassword(struct user_s *u)
{
	char cTemp, *temp;
	int iAsciiCode;
	int iToken=u->userToken;
	temp=u->encodedPassword;
	u->decodedPassword=temp;
	while(*temp!='\0')
	{
		cTemp = *temp;
		cTemp = tolower(cTemp);
		iAsciiCode = (int)cTemp;
		cTemp = iAsciiCode - iToken;
		*temp = cTemp;
		*temp++;
	}
}

//write the record of user to the file
void writeToFile(struct user_s *u)
{
	FILE *p;
	p=fopen("text.txt","a");
	if(u->userCounter==1) fprintf(p, "User Name\tDecoded Password\tEncoded Password\tToken\r\n");
	fprintf(p, "%s\t\t", u->userName);
	//calling both encode and decode to show decode function is also working
	encodePassword(u);
	decodePassword(u);
	fprintf(p, "%s\t\t", u->decodedPassword);
	encodePassword(u);
	fprintf(p, "%s\t\t%d\r\n", u->encodedPassword, u->userToken);
	
	fclose(p);
}

//main function
int main()
{
	//clear the file at the begining of program
	FILE *p;
	p=fopen("text.txt", "w");
	fclose(p);
	struct user_s aUser;
	aUser.userCounter=0;
	struct user_s *pUser = &aUser;
	pUser->userName=(malloc(sizeof(char)*64)); 
	pUser->decodedPassword=(malloc(sizeof(char)*64)); 
	pUser->encodedPassword=(malloc(sizeof(char)*64));
	while(pUser->userCounter<10)
	{
		recordUser(pUser);
	}
	return 0;
}
