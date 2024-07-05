#include <filesystem>
#include <iostream>
#include <vector>
using namespace std;

int help() {
  cout << "How to use dev cli: " << endl;
  cout << "$ dev help                   #Show How to use" << endl;

  return 0;
}

int ts_backend_boilerplate() {
  cout << "🔥 initializing backend with ts" << endl;

  // create dirs

  string root_dir = "src";
  vector<string> inner_src = {"core",
                              "core/entities",
                              "core/errors",
                              "core/repositories",
                              "core/services",
                              "core/types",
                              "core/usecases",

                              "data",
                              "data/datasources",
                              "data/repositories",

                              "env",

                              "http",
                              "http/controller",
                              "http/dtos",
                              "http/routes",
                              "http/schemasValidation",

                              "infra"};

  filesystem::create_directory(root_dir);

  for (const auto &dir : inner_src) {
    std::string full_path = root_dir + "/" + dir;
    if (!filesystem::exists(full_path)) {
      filesystem::create_directory(full_path);
      std::cout << "Directory created: " << full_path << std::endl;
    } else {
      std::cout << "Directory already exists: " << full_path << std::endl;
    }
  }

  // create importants files


  // run commands

  return 0;
}

int main(int argc, char *argv[]) {

  string arg;

  if (argc > 1)
    arg = argv[1];

  if (argc == 1 || arg == "--help") {
    help();
  } else {

    if (arg == "init-backend") {
      ts_backend_boilerplate();
    }
  }

  return 0;
}