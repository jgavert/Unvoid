#pragma once
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <set>
#include <string>
#include <iostream>
/* size of the event structure, not counting name */
#define EVENT_SIZE  (sizeof (struct inotify_event))

/* reasonable guess as to size of 1024 events */
#define BUF_LEN        (1024 * (EVENT_SIZE + 32))

class FileWatch
{
public:
  FileWatch();
  ~FileWatch();
  int add(const std::string file);
  bool update();
  std::set<int> getChanged();
private:
  void process();

  //std::map<std::string, int> wds; // Watch descriptors
  std::set<int> data;
  fd_set watch_set;
  struct timespec req;
  int fd;
  char buf[BUF_LEN];
  int len, i = 0;
};

