// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/* sampleCodeModule.c */
#include <libc.h>
#include <shell.h>
#include <userSyscalls.h>

<<<<<<< HEAD
int main() {
  char *argv[] = {"Shell"};
  newProcess(startShell, 1, argv, FOREGROUND, NULL);
  return 0;
=======
int main()
{
	// _setStack();
	char *argv[] = {"Shell"};
	newProcess(initialize, 1, argv, FOREGROUND, NULL);
	return 0;
>>>>>>> 4952e0d119666c812b43ed3d08c647ea077f623a
}
