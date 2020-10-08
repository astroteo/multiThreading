#include "producer.h"
using namespace std;

Producer::Producer(queue<int> *q_)
{
  cout<< " created producer " << endl;
  this->q = q_;
}

void
Producer::doJob()
{
  while(true)
  {
    unique_lock<mutex> lk(*mx);

    if (q->size() < 10)
    {
      counter < 100 ? counter++ : counter=1;

      q->push(counter);
      cout << counter << endl;

    }
    else
    {

      consumer_cv->notify_all();
      producer_cv->wait(lk, [this]{ return q->size() < 10; });


    }

    lk.unlock();
    this_thread::sleep_for(chrono::milliseconds(random() % 400 + 100));
  }
}
