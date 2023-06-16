// error.h
// Author: Michal Krulich
// Declarations of functions which give additional debugging info or end the program.

/*
 * Prints out an error message to stderr in printf format with line feed.
 */
void warning(const char *fmt, ...);

/*
 * Prints out an error message to stderr in printf format with line feed and ends the program.
 */
void error_exit(const char *fmt, ...);
