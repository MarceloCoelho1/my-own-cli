#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct CommandDefinition {
  string description;
  string command;
  vector<string> args;
};

int help() {
  cout << "How to use tip cli: " << endl;
  cout << "$ tip help                   #Show How to use" << endl;
  cout << "$ tip init-backend                   #init a backend with ts, prisma, postgres, docker and fastify" << endl;


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
    string full_path = root_dir + "/" + dir;
    if (!filesystem::exists(full_path)) {
      filesystem::create_directory(full_path);
      cout << "Directory created: " << full_path << endl;
    } else {
      cout << "Directory already exists: " << full_path << endl;
    }
  }

  // create importants files
  vector<string> filenames = {"docker-compose.yml", ".gitignore",
                              "package.json"};
  std::vector<std::string> contents = {
      R"(version: '3.9'

services:
  db:
    container_name: db
    image: bitnami/postgresql:latest
    hostname: localhost
    environment:
      POSTGRES_USER: ${POSTGRES_USER}
      POSTGRES_PASSWORD: ${POSTGRES_PASSWD}
      POSTGRES_DB: ${POSTGRES_DB}
    ports:
      - '5432:5432'
)",
      R"(node_modules/
.env
)",
      R"({
  "name": "project name",
  "version": "1.0.0",
  "main": "index.js",
  "scripts": {
    "test": "echo \"Error: no test specified\" && exit 1",
    "build": "tsc -p tsconfig.json",
    "dev": "tsx watch src/server.ts"
  },
  "keywords": [],
  "author": "",
  "license": "ISC",
  "description": "",
  "devDependencies": {
    "@types/node": "^20.14.8",
    "prisma": "^5.16.0",
    "tsx": "^4.15.7",
    "typescript": "^5.5.2"
  },
  "dependencies": {
    "@fastify/cors": "^9.0.1",
    "@prisma/client": "^5.16.0",
    "dotenv": "^16.4.5",
    "fastify": "^4.28.0",
    "zod": "^3.23.8"
  }
})"};

  for (size_t i = 0; i < filenames.size(); ++i) {
    ofstream file(filenames[i]);
    if (file.is_open()) {
      cout << "File created: " << filenames[i] << endl;
      file << contents[i] << endl;
      file.close();
    } else {
      cerr << "error to create file: " << filenames[i] << endl;
    }
  }

  // run commands

  vector<CommandDefinition> commands = {
      CommandDefinition{"🔥Install npm dependencies", "npm", {"install"}},
      CommandDefinition{"🔥Create tsc config", "npx", {"tsc", "--init"}},
      CommandDefinition{"🔥Run npx prisma", "npx", {"prisma", "init"}},
  };

  for (const auto &cmd : commands) {
    string full_command = cmd.command;
    for (const auto &arg : cmd.args) {
      full_command += " " + arg;
    }

    cout << "Executing: " << cmd.description << endl;

    int result = system(full_command.c_str());
    if (result != 0) {
      cerr << "Command failed with exit code " << result << endl;
      break;
    }
  }

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
    } else if (arg == "ls") {
    }
  }

  return 0;
}