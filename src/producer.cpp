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

    if (q->size() < 100)
    {
      counter++;
      q->push(counter);
      consumer_cv->notify_all();

    }
    else
    {
      cout << "--------"<<endl;
      counter = 0;
      this->producer_cv->wait(lk, [this]{ return this->q->size() < 100; });
    }
    lk.unlock();
    //this_thread::sleep_for(chrono::milliseconds(random() % 400 + 100));
  }
}
