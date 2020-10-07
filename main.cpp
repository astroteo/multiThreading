
#include <thread>
#include "consumer.h"
#include "producer.h"

using namespace std;


int main(int argc, const char * argv[])
{
  cout << "Start program" << endl;

  //shared objects
  queue<int> *shared_queue = new queue<int>;
  std::mutex mx;
  condition_variable producer_cv,consumer_cv;

  //Instances
  Consumer * consumer = new Consumer(shared_queue);
  consumer->mx = &mx;
  consumer->consumer_cv = &consumer_cv;
  consumer->producer_cv = &producer_cv;

  Producer *producer = new Producer(shared_queue);
  producer->mx = &mx;
  producer->consumer_cv = &consumer_cv;
  producer->producer_cv = &producer_cv;


  //Create threads
  thread producer_thread(&Consumer::doJob,consumer);
  thread consumer_thread(&Producer::doJob,producer);

  //Start threads
  consumer_thread.join();
  producer_thread.join();

  cout << " HERE threads started" << endl;

  return 0;

}
