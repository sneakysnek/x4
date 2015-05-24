#ifndef _engines_h
#define _engines_h

typedef int (*EngineInitFunc)(int);

int engines_init(int max_connects);

struct Engine {
  const char*       eng_name;
  EngineInitFunc    eng_init;
};

#endif /* _engines_h */
