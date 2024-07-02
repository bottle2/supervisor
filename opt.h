#ifndef OPT_H
#define OPT_H

// Pass entry-point `argc` and `argv` unmodified.
// Either exit on failure, or assign global variables `scheduler`,
// `verbose` and `aging` appropriately.
void opt(int argc, char *argv[]);

#endif
