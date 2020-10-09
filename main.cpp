

#include "consumer.h"
#include "producer.h"
#include <string>


using namespace std;

// function commanding program (producer/consumer threads)
void
commander(bool *work_flag,
         queue<int> *shared_queue)
{

  this_thread::sleep_for(chrono::milliseconds(300));
  cout << "commander thread started" << endl;
  while(true)
  {
    string k_in;
    cout <<" press a key to stop: "<<endl;

    getline(std::cin, k_in);

    if(!k_in.empty())
    {
      cout << "pressed keyboard"<< endl;
      *work_flag = false;

      int end_sum = 0;
      cout << "values currently in buffer: " << endl;

      for(int i=0; i<shared_queue->size(); i++)
      {
        cout << shared_queue->front() << endl;
        end_sum += shared_queue->front();
        shared_queue->pop();
      }

      cout << "exit sum = " << end_sum << endl;
      break;
    }
  }

}


int main(int argc, const char * argv[])
{
  cout << "===> Start program <===" << endl;

  /*shared objects*/
  //1. buffer
  queue<int> *shared_queue = new queue<int>;

  //2. mutex and notifications
  std::mutex mx;
  condition_variable producer_cv,consumer_cv;

  //3. activation flag
  bool *work_flag = new bool;
  *work_flag = true;

  /*Instances*/
  Consumer *consumer = new Consumer(shared_queue);
  consumer->mx = &mx;
  consumer->consumer_cv = &consumer_cv;
  consumer->producer_cv = &producer_cv;
  consumer->work_flag = work_flag;

  Producer *producer = new Producer(shared_queue);
  producer->mx = &mx;
  producer->consumer_cv = &consumer_cv;
  producer->producer_cv = &producer_cv;
  producer->work_flag = work_flag;


  /*Create threads*/
  thread producer_thread(&Consumer::doJob,consumer);
  thread consumer_thread(&Producer::doJob,producer);
  thread commander_thread(commander,work_flag,shared_queue);

  /*Start threads*/
  producer_thread.detach();
  consumer_thread.detach();
  commander_thread.join();

  /*End of program*/
  cout << " ===>  end of program <===" << endl;
  return 0;

}
