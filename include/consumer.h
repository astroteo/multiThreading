#include <iostream>
#include <cstring>
#include <cstdlib>
#include <stdlib.h>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>

using namespace std;

class Consumer
{
  public:
    Consumer(queue<int> *q_);
    void doJob();

  public:
    queue<int> *q = nullptr;
    mutex *mx = nullptr;
    condition_variable *producer_cv= nullptr;
    condition_variable *consumer_cv= nullptr;
    bool *work_flag = nullptr;
    int sum;

  };
