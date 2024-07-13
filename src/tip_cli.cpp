#include "tip_cli.h"

int help() {
  cout << BOLD << "Usage: tip [COMMAND]" << RESET << endl;
  cout << endl;
  cout << BOLD << "Commands:" << RESET << endl;
  cout << setw(25) << left << GREEN + "  help" + RESET
       << YELLOW + "  # Show how to use" + RESET << endl;
  cout << setw(25) << left << GREEN + "  init-backend" + RESET
       << YELLOW +
              "  # Init a backend with TS, Prisma, PostgreSQL, Docker, and "
              "Fastify" +
              RESET
       << endl;
  cout << endl;
  cout << BOLD << "Options:" << RESET << endl;
  cout << setw(25) << left << CYAN + "  -h, --help" + RESET
       << YELLOW + "  # Show this help message" + RESET << endl;

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

  // run commands

  vector<CommandDefinition> commands = {
      CommandDefinition{"🔥Running npm init", "npm", {"init", "-y"}},
      CommandDefinition{
          "🔥Installing dev dependencies",
          "npm",
          {"install", "-D", "typescript", "@types/node", "tsx", "prisma"}},

      CommandDefinition{
          "🔥Installing dependencies",
          "npm",
          {"install", "@prisma/client", "dotenv", "fastify", "zod"}},
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

  // create important files
  vector<string> filenames = {"docker-compose.yml", ".gitignore"};
  vector<string> contents = {
      R"(version: '3.9'

services:
  db:
    container_name: db
    image: bitnami/postgresql:latest
    hostname: localhost
    environment:
      POSTGRES_USER: postgres_user
      POSTGRES_PASSWORD: postgres_password
      POSTGRES_DB: postgres_db
    ports:
      - '5432:5432'
)",
      R"(node_modules/
.env
)",
  };

  for (size_t i = 0; i < filenames.size(); ++i) {
    ofstream file(filenames[i]);
    if (file.is_open()) {
      cout << "File created: " << filenames[i] << endl;
      file << contents[i] << endl;
      file.close();
    } else {
      cerr << "Error creating file: " << filenames[i] << endl;
    }
  }

  return 0;
}

int ts_react_frontend_boilerplate() {
  cout << "🔥 initializing the frontend with ts and react (vite)" << endl;

  // run commands

  vector<CommandDefinition> commands = {
      CommandDefinition{
          "🔥Running npm create vite ",
          "npm",
          {"create ", "vite@latest", ".", "--", "--template", "react-ts"}},
      CommandDefinition{"🔥Running npm install", "npm", {"install"}},

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

  // create dirs

  string root_dir = "src";
  vector<string> inner_src = {
      "api", "components", "hooks", "types", "utils", "tests", "views     "
  };

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

  return 0;
}
