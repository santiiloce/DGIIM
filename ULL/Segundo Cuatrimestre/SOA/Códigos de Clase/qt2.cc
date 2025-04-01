#define WORKLOAD 10000000000
#define PARALLEL 2
#define PADDING 16
#include <thread>
void thread_func(int* ptr)
{
for (unsigned long i = 0; i < WORKLOAD / PARALLEL; ++i)
{
(*ptr)++;
}
}
int main()
{
int arr[PARALLEL * PADDING];
std::thread threads[PARALLEL];
for (unsigned i = 0; i < PARALLEL; ++i)
{
threads[i] = std::thread(thread_func, &(arr[i * PADDING]));
}
for (auto& th : threads)
{
th.join();
}
return 0;
}