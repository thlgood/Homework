#include <string>
#include <vector>
#include <pthread.h>

std::vector<std::string>all_paths;

std::string id;

pthread_mutex_t paths_mutex;

int pthread_count;
