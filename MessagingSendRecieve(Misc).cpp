
struct Message {
	float x1, x2, y1, y2;
};

class MessageSender {
public:
	MessageSender() {

	}
	~MessageSender() {
	//Vectors Auto Delete Themselves
	}

	void sendMessge(float x1,float x2,float y1, float y2) {//Sending the message to everybody
		Message newMessage;//instance of struct

		newMessage.x1 = x1;//Message assembled
		newMessage.x2 = x2;
		newMessage.y1 = y1;
		newMessage.y2 = y2;

		for (unsigned int i = 0; i < mListeners.size(); i++) {
			mListeners[i]-> recieveMessage(newMessage);//For all listeners execute recieve message for the assembled message
		}
	}

	void recieveListener(MessageListener* listener) {
		mListeners.push_back(listener);//adding listener to the "adress book" stack
	}
private:
	vector<MessageListener*> mListeners;//stack of listeners
};

class MessageListener {
public:
	MessageListener() {

	}
	~MessageListener() {

	}

	void listenToSender(MessageSender* sender){// adding listener to the senders adress book
		sender->recieveListener(this);//this is pointer to this instance of object
	}
	
	vector<float> GetMessage(){//Retruns floats from messages
		vector<float> messageVector;
		
		for (unsigned int i = 0; i < mMessages.size(); i++) {//pushing the coordinates serially from the stack
			messageVector.push_back(mMessages[i].x1);
			messageVector.push_back(mMessages[i].x2);
			messageVector.push_back(mMessages[i].y1);
			messageVector.push_back(mMessages[i].y2);
		}

		mMessages.clear();//Clear the message stack

		return messageVector;
	}

	void recieveMessage(Message newMessage) {
		mMessages.push_back(newMessage);//Pushed unread messages to the stack
	}

private:
	vector<Message> mMessages//Stack of recieved messages
};


/*-------------------------------------------------------------------------*/
int main() {



	return 0;
}