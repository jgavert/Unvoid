#include "filewatch.hpp"
#ifdef _WIN32
#else
FileWatch::FileWatch():fd(inotify_init())
{
  FD_ZERO( &watch_set );
  FD_SET( fd, &watch_set );
  req.tv_sec = (time_t)(0);
  req.tv_nsec = 1;
}


FileWatch::~FileWatch()
{
  close(fd);
}

int FileWatch::add(const std::string file)
{
  int wd = inotify_add_watch( fd, file.c_str(), IN_MODIFY );
  //std::cout << wd << ": \"" << file << std::endl;
  return wd;
}

// returns true if there was new data
bool FileWatch::update()
{
  process();
  return data.size() > 0;
}

std::set<int> FileWatch::getChanged()
{
  return data;
}

void FileWatch::process()
{
  data.clear(); // reset the deque
  i=0;
  if (pselect( fd+1, &watch_set, nullptr, nullptr, &req, nullptr ) > 0) {
    len = read (fd, buf, BUF_LEN);
    if (len < 0) {
      std::cout << "FileWatch: Read error\n";
      goto woot;
    }
    while (i < len) {
      struct inotify_event *event;
      event = (struct inotify_event *) &buf[i];
      if (event->mask == IN_MODIFY) {
        data.insert(event->wd);
        //std::cout << data << ": IN_MODIFY event\n";
      }
      i += EVENT_SIZE + event->len;
    }
  }
  woot:
  FD_ZERO( &watch_set );
  FD_SET( fd, &watch_set );
}

#endif
