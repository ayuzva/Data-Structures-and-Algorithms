#include <iostream>
#include <queue>
#include <vector>

struct Request {
	Request(int arrival_time, int process_time) :
		arrival_time(arrival_time),
		process_time(process_time)
	{}

	int arrival_time;
	int process_time;
};

struct Response {
	Response(bool dropped, int start_time) :
		dropped(dropped),
		start_time(start_time)
	{}

	bool dropped;
	int start_time;
};

class Buffer {
public:
	Buffer(int size) :
		size_(size),
		maxsize_(size),
		finish_time_(){}
	
	Response Process(const Request& request) {//We get arrival and process time in a Request object
		//Pulling out ALL completed packets when new ones arive
		while ((finish_time_.empty() != true) && (request.arrival_time >= finish_time_.front())) {
			finish_time_.pop();
			size_++;
		}

		if (size_ > 0 && size_ < maxsize_) {//Buffer not full
			Response PacketResult(false, std::max(request.arrival_time, finish_time_.back()));
			finish_time_.push(std::max(request.arrival_time,finish_time_.back()) + request.process_time);
			size_--;
			return PacketResult;
		}else if (size_ == maxsize_) {//Buffer empty
			Response PacketResult(false, request.arrival_time);
			finish_time_.push(request.arrival_time + request.process_time);
			size_--;
			return PacketResult;
		}else {//Buffer full
			Response PacketResult(true, 0);//Buffer full, drop the packet
			return PacketResult;
		}
	}
private:
	int size_;//Current size of buffer
	int maxsize_;
	std::queue <int> finish_time_;
};
//Reads Requests from IO into a vecotor of Requests
std::vector <Request> ReadRequests() {
	std::vector <Request> requests;
	int count;
	std::cin >> count;
	for (int i = 0; i < count; ++i) {
		int arrival_time, process_time;
		std::cin >> arrival_time >> process_time;
		requests.push_back(Request(arrival_time, process_time));
	}
	return requests;
}
//Store Response objects in a vector
std::vector <Response> ProcessRequests(const std::vector <Request>& requests, Buffer* buffer) {
	std::vector <Response> responses;
	for (int i = 0; i < requests.size(); ++i)
		responses.push_back(buffer->Process(requests[i]));//Executes "process a request" subroutine 
	return responses;
}
//Readsout Response objects from a vector
void PrintResponses(const std::vector <Response>& responses) {
	for (int i = 0; i < responses.size(); ++i)
		std::cout << (responses[i].dropped ? -1 : responses[i].start_time) << std::endl;
}

int main() {
	int size;
	std::cin >> size; //Buffer size
	std::vector <Request> requests = ReadRequests();

	Buffer buffer(size);
	std::vector <Response> responses = ProcessRequests(requests, &buffer);

	PrintResponses(responses);
	return 0;
}
