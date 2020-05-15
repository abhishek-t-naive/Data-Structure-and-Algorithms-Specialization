#include <iostream>
#include <queue>
#include <vector>

//#define IF_DEBUG

struct Request {
    Request(int arrival_time, int process_time):
        arrival_time(arrival_time),
        process_time(process_time)
    {}

    int arrival_time;
    int process_time;
};

struct Response {
    Response(bool dropped, int start_time):
        dropped(dropped),
        start_time(start_time)
    {}

    bool dropped;
    int start_time;
};

class Buffer {
public:
    Buffer(int size):
        size_(size),
        finish_time_()
    {}

		int proc_time;
		int last_fin_time = 0;
    Response Process(const Request &request) {

			proc_time = request.arrival_time;
			#ifdef IF_DEBUG
				std::cout << "Processing time is: "<<proc_time<<"\n";
				std::cout << "last_fin_time is: "<<last_fin_time<<"\n";
				std::cout << "Total size of the queue is: "<<size_<<"\n";
			#endif

			if(finish_time_.empty()){
				finish_time_.push(request.process_time);
				#ifdef IF_DEBUG
					std::cout << "First request is being pushed into the queue!\n";
				#endif
				last_fin_time	+= request.process_time;
				return(Response(0,request.arrival_time));
			}
			else {
				while((proc_time >= finish_time_.front()) && !finish_time_.empty()){			//Popping all the completed requests by now
					#ifdef IF_DEBUG
						std::cout << "Finished request popped from the queue!\n";
					#endif
					finish_time_.pop();			
				}

				if(proc_time < last_fin_time){
					if(finish_time_.size() < size_){
						#ifdef IF_DEBUG
							std::cout << "There is space in the queue!\n";
							std::cout << "Current size of the queue is: "<<finish_time_.size()<<"\n";
						#endif
						int start_time = last_fin_time;
						last_fin_time += request.process_time;
						finish_time_.push(last_fin_time);
						return(Response(0,start_time));
					}
					else{
						#ifdef IF_DEBUG
							std::cout << "Finished request popped from the queue!\n";
						#endif
						return(Response(1,last_fin_time));
					}
				}
				else if (proc_time >= last_fin_time){
					if(finish_time_.size() < size_){
						#ifdef IF_DEBUG
							std::cout << "There is space in the queue!\n";
							std::cout << "Current size of the queue is: "<<finish_time_.size()<<"\n";
						#endif
						int start_time = proc_time;
						last_fin_time	= request.arrival_time + request.process_time;
						finish_time_.push(last_fin_time);		
						return(Response(0,start_time));
					}
					else
						return(Response(1,last_fin_time));
				}	
			}
    }
private:
    int size_;
    std::queue <int> finish_time_;
};

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

std::vector <Response> ProcessRequests(const std::vector <Request> &requests, Buffer *buffer) {
    std::vector <Response> responses;
    for (int i = 0; i < requests.size(); ++i)
        responses.push_back(buffer->Process(requests[i]));
    return responses;
}

void PrintResponses(const std::vector <Response> &responses) {
    for (int i = 0; i < responses.size(); ++i)
        std::cout << (responses[i].dropped ? -1 : responses[i].start_time) << std::endl;
}

int main() {
    int size;
    std::cin >> size;
    std::vector <Request> requests = ReadRequests();

    Buffer buffer(size);
    std::vector <Response> responses = ProcessRequests(requests, &buffer);

    PrintResponses(responses);
    return 0;
}
