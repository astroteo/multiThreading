#include "consumer.h"
using namespace std;
Consumer::Consumer(queue<int> *q_)
{
  this->q = q_;
  this->sum = 0;
  cout<< " created consumer" << endl;
}

void
Consumer::doJob()
{
  cout << "consumer thread started"<<endl;

  while(true)
  {
      //cout << "queue size = " << q->size()<<endl;
      unique_lock<std::mutex> lk(*mx);

      if(!q->empty())
      {

        for (int i = q->size()-1; i==0; i--)
        {
          this->sum += q->front();
          q->pop();
          producer_cv->notify_all();

        }

        cout << "buffer sum = " << this->sum << endl;
        cout << "buffer length = " << q->size() << endl;
      }
      else
      {
        this->sum = 0;
        consumer_cv->wait(lk, [this]{ return !q->empty(); });
      }

      lk.unlock();
      //this_thread::sleep_for(chrono::milliseconds(random() % 400 + 100));
  }
}
