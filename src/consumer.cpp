#include "consumer.h"
using namespace std;
Consumer::Consumer(queue<int> *q_)
{
  q = q_;

  sum = 0;
  cout<< " created consumer" << endl;
}

void
Consumer::doJob()
{
  this_thread::sleep_for(chrono::milliseconds(50));
  cout << "consumer thread started"<<endl;
  
  while(*work_flag)
  {
    unique_lock<std::mutex> lk(*mx);
    if(!q->empty())
    {
      this->sum += q->front();
      q->pop();
    }
    else
    {
      producer_cv->notify_all();

      cout << "==>buffer sum = " << this->sum << endl;
      cout << "---------------------------------------"<<endl;

      this->sum = 0;
      consumer_cv->wait(lk, [this]{ return !q->empty(); });
      this_thread::sleep_for(chrono::milliseconds(random() % 400 + 100));
      lk.unlock();
    }
      }
  terminate();
}
