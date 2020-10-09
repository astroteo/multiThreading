#include "producer.h"

using namespace std;

//Constructor
Producer::Producer(queue<int> *q_)
{
  cout<< " created producer " << endl;
  q = q_;

}

// Threaed function
void
Producer::doJob()
{

  //sleep 10ms => since with consumer
  this_thread::sleep_for(chrono::milliseconds(150));
  cout << "producer thread started"<<endl;

  while(*work_flag)
  {
    unique_lock<mutex> lk(*mx);

    if (q->size() < BUFFER_SIZE && *work_flag)
    {
      counter < 100 ? counter++ : counter = 1;

      q->push(counter);
      cout << counter << endl;

    }
    else
    {
      consumer_cv->notify_all();
      producer_cv->wait(lk, [this]{ return q->size() < BUFFER_SIZE; });
      lk.unlock();
    }

    this_thread::sleep_for(chrono::milliseconds(random() % 400 + 100));


  }
  terminate();

}
