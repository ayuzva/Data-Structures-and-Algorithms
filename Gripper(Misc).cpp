/*#ifndef GRIPPER_H
#define GRIPPER_H
/**
*Assumptions: Gripper has positional feedback
*
*Functions:
*Gripper() - Constructor. Can go through startup procedure if required. e.g. fully open initially, as a diagnostic
*~Gripper() - Destructor. Can implement shutdown procedure if necessary. e.g.
*Open() - Opens the gripper, if the amount is not provided opens fully.
*Close() - Closes the gripper, if the amount is not provided closes fully.
*Update() - Updates the current position of the gripper from the sensor feedback.
*
*isOpen() - Checking if Gripper is open. Returns boolean.
*isClosed() - Checking if Gripper is closed. Returns boolean.
*
*Parameters:
*Position - Current position from feedback, can be used for interrupting closing procedure.
*

class Gripper {
public:
	Gripper();
	~Gripper();

	void Open(int delta = 100);
	void Close(int delta = 100);
	
	bool isOpen();
	bool isClosed();

private:
	int Position;

	void UpdatePosition();
};
#endif

#include <iostream>
using std::cout;
using std::endl;

void printan(int g = 69) {
	cout << g << endl;
}
int main() {
	printan(5);
	return 0;
}
int main() {
	Gripper a;
	a.isOpen = 1;

}*/