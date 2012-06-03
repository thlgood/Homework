#include <string>
#include <vector>
#include <pthread.h>
using namespace std;

vector<std::string>all_paths;
string id;
pthread_mutex_t paths_mutex;
int pthread_count;
