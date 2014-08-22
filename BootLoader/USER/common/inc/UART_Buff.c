/*************************************************************************

					   Creating a Message Queue

*************************************************************************/
#define MY_MSG_SIZE 10

OS_EVENT *MyQ;
void *MyMsg[MY_MSG_SIZE];

static  void  App_ObjectCreate (void)
{
	MyQ = OSQCreate(&MyMsg[0], MY_MSG_SIZE);
	/*The first argument is the base address of the message storage area*/
	
	/*The second argument is the size of the message storage area       */
}