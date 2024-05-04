#include <stdio.h>
#include <pthread.h>
#include <stdint.h>


/* Thread-Funktion */
void *example_fct(void *args){
  /* Die Übergabe wird zurück auf einen int-Pointer gecastet*/
  
  char* str = *(char**)args;

  return (void *)strlen(str);
}

int main(){
  /* Lege ein Thread-Handle, einen Übergabe- und einen Rü ckgabeparameter an */
  pthread_t thread;
  uintptr_t threadParam = 42;
  uintptr_t threadRetParam = -1;
  char* name = "Fabi";

  /* Starte einen Thread mit der auszuführenden Funktion example_fct. Zudem wir ein Parameter übrgeben.
     Konfigurations-Parameter werden nicht gesetzt, daher NULL. */
  pthread_create(&thread, NULL, &example_fct, &name);

  /* Warte auf Beendigung des Threads */
  pthread_join(thread, (void **)(&threadRetParam));

  /* Inhalt des Rückgabeparameters ausgeben */
  printf("Rueckgabe von Thread: %llu\n", threadRetParam);

  return 0;
}
