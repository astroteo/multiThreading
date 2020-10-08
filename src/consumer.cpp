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
        this->sum += q->back();
        q->pop();


        //cout << "buffer sum = " << this->sum << endl;
        //cout << "buffer length = " << q->size() << endl;
      }
      else
      {
        producer_cv->notify_all();
        cout << "==>buffer sum = " << this->sum << endl;
        cout << "==>buffer length = " << q->size() << endl;
        cout << "---------------------------------------"<<endl;

        this->sum = 0;
        consumer_cv->wait(lk, [this]{ return !q->empty(); });
      }

      lk.unlock();
      this_thread::sleep_for(chrono::milliseconds(random() % 400 + 100));
  }
}
