#include "CircularBuffer.h"

//Initializes the struct commBuffer_t to zero, Type = Rx or Tx
void initBuffer(commBuffer_t* comm, uint8_t type) {

	comm->type = type;
	comm->MessageCount = 0;
	comm->head = 0;
	comm->tail = 0;
	comm->bufferSize = 0;
	memset(comm->buffer, '~', MAXCOMMBUFFER+1);

}
//Test if a complete message is in buffer delimiter is \n
uint8_t haveMessage(commBuffer_t* comm){
	if(comm->MessageCount){
		//comm->MessageCount--;
		return 1;
	}
	else {
		return 0;
	}
}

//Put character in buffer and update head
void putChar(commBuffer_t* comm, char ch){
	comm->buffer[comm->head] = ch;
	comm->head++;
	if(ch == '\n'){
		comm->MessageCount++;
	}
	if(comm->head > MAXCOMMBUFFER){
		comm->head = 0;
	}

}
//Get character from buffer and update tail;
char getChar(commBuffer_t* comm){
	char ch = comm->buffer[comm->tail];
	comm->tail++;
	if(comm->tail > MAXCOMMBUFFER){
		comm->tail = 0;
	}
	return ch;
}
//put C string into buffer
void putMessage(commBuffer_t* comm, char* str, uint8_t length){
	for(int i=0;i<length;i++){
		putChar(comm,str[i]);
	}

}
//get C string from buffer
void getMessage(commBuffer_t* comm, char* str){
	uint32_t i = 0;
	str[i] = getChar(comm);
	while(str[i] != '\n'){
		i++;
		str[i] = getChar(comm);
	}
	str[i] = '\n';
	str[i+1] = '\0';
	comm->MessageCount--;
}
//get Size of Buffer
int getBufferSize(commBuffer_t* comm){
	int maxSize = (comm->head - comm->tail + MAXCOMMBUFFER+1)%(MAXCOMMBUFFER+1);
	return maxSize;
}
