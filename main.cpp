#include "src/tip_cli.h"

int main(int argc, char *argv[]) {
  string arg;

  if (argc > 1)
    arg = argv[1];

  if (argc == 1 || arg == "--help" || arg == "-h") {
    help();
  } else {
    if (arg == "init-backend") {
      ts_backend_boilerplate();
    } else if (arg == "init-frontend") {
      ts_react_frontend_boilerplate();
    } else if (arg == "osfetch") {
      osfetch();
    }
  }

  return 0;
}
