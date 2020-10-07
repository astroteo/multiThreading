#include <iostream>
#include <cstring>
#include <cstdlib>
#include <stdlib.h>
#include <queue>

using namespace std;

class Producer
{
  public:
    Producer(queue<int> *q_);
    void doJob();


  public:
    int counter =0;
    queue<int> *q;
    mutex *mx = nullptr;
    condition_variable *producer_cv= nullptr;
    condition_variable *consumer_cv= nullptr;

  };
