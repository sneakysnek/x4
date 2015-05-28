#ifndef _ioengine_h
#define _ioengine_h

typedef int (*IOEngineInitFunc)(int);

int ioengine_init(int max_connects);

struct IOEngine {
  const char*         eng_name;
  IOEngineInitFunc    eng_init;
};

#endif /* _ioengine_h */
