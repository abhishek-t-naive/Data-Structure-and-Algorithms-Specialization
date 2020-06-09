#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>
#include <utility>

using std::vector;
using std::priority_queue;
using std::queue;
using std::greater;
using std::pair;
using std::make_pair;
using std::cin;
using std::cout;

//#define PRINT_DEBUG
typedef pair<long long, int> jobs_data;

class JobQueue {
 private:
	
	struct Job_q{
		int 			job_id;	
		long long end_time;
	};
	
  int num_workers_;
  vector<long long> jobs_;

	/*NOTE: We are utilising two Priority Queues (PQ) for this problem. workers_ is used for
		storing the threads available at a given point of time. Whereas, running_jobs_ stores 
		the threads which are running along with their designated end time. This way, whenever
		a job finishes, the corresponding worker thread is made available by pushing it to
		the workers_ queue.*/
	/*TODO: Implement the same with a custom Priority Queue*/	
	priority_queue <jobs_data, vector<jobs_data>, greater<jobs_data> > running_jobs_;
	priority_queue <int, vector<int>, greater<int> > workers_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    long long m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(long long i = 0; i < m; ++i){
      cin >> jobs_[i];
		#ifdef PRINT_DEBUG
			cout << "Loading Done!\n";
		#endif
		}
		for(int j = 0; j < num_workers_; ++j)
			workers_.push(j);
  }


  void AssignJobs() {
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
		
		jobs_data job_id_time;
		int i = 0;
		long long curr_time = 0;
		
		#ifdef PRINT_DEBUG
			cout << "Workers pq filled with " << workers_.size() << " elements!\n";
		#endif
		
		while(i < jobs_.size()){
			while(!workers_.empty() && (i<jobs_.size())){
				assigned_workers_[i]	= workers_.top();
				start_times_[i]				=	curr_time; 
				job_id_time						=	make_pair((curr_time + jobs_[i]),workers_.top());
				running_jobs_.push(job_id_time);
				#ifdef PRINT_DEBUG
					cout <<"Worker assigned to the job "<<i<<" is "<<assigned_workers_.back() << " and start time is " << start_times_.back()<<"\n";
				#endif
				workers_.pop();
				i++;
			}
			
			curr_time = running_jobs_.top().first;
			#ifdef PRINT_DEBUG
				cout << "Out of the workers loop!"<<"\n";
				cout << "curr_time now is " << curr_time << "\n";
			#endif
		
			/*NOTE: The condition in while loop determines whether there are more than one jobs
				finishing at the same time.*/	
			while((!running_jobs_.empty())&& (curr_time == running_jobs_.top().first)){
				workers_.push(running_jobs_.top().second);
				curr_time = running_jobs_.top().first;
				running_jobs_.pop();
			}
		}
  }

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
