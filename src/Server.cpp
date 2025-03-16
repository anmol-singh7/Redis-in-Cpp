#include <iostream>
#include "Server.h"

using namespace std;


int main(int argc, char **argv) {
  try {
      std::cout << std::unitbuf;
      std::cerr << std::unitbuf;
      cout<<"Server starting...\n";
    
      cout << "You have entered " << argc  << " arguments:" << endl;

      int i = 0;
      while (i < argc) {
          cout << "Argument " << i + 1 << ": " << argv[i]
               << endl;
          i++;
      }

      Server server;
      server.setPort(6379);
      server.init();
      server.startEventLoop();
  } catch (const exception &e) {
      cout<<"Fatal error: " + string(e.what()) + "\n";
      return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

