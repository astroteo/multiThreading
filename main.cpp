
#include <thread>
#include "consumer.h"
#include "producer.h"

using namespace std;


int main(int argc, const char * argv[])
{
  cout << "Start program" << endl;

  //shared objects
  queue<int> *shared_queue = new queue<int>;
  mutex mx;
  condition_variable producer_cv,consumer_cv;

  //Instances
  Consumer consumer(shared_queue);
  consumer.mx = &mx;
  consumer.consumer_cv = &consumer_cv;
  consumer.producer_cv = &producer_cv;

  Producer producer(shared_queue);
  producer.mx = &mx;
  producer.consumer_cv = &consumer_cv;
  producer.producer_cv = &producer_cv;

  //Create threads
  thread producer_thread(&Consumer::doJob,producer);
  thread consumer_thread(&Producer::doJob,consumer);

  //Start threads
  consumer_thread.join();
  producer_thread.join();

  cout << " HERE threads started" << endl;

  return 0;

}
