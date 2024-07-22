#include "tip_cli.h"

int help() {
  cout << BOLD << "Usage: tip [COMMAND]" << RESET << endl;
  cout << endl;
  cout << BOLD << "Commands:" << RESET << endl;
  cout << setw(25) << left << GREEN + "  help" + RESET
       << YELLOW + "  # Show how to use" + RESET << endl;
  cout << setw(25) << left << GREEN + "  init-backend" + RESET
       << YELLOW + "  # Init a backend with TS, Prisma, PostgreSQL, Docker, and Fastify" + RESET << endl;
  cout << setw(25) << left << GREEN + "  init-frontend" + RESET
       << YELLOW + "  # Init a frontend with react, vite and ts" + RESET << endl;
  cout << setw(25) << left << GREEN + "  osfetch" + RESET
       << YELLOW + "  # Show system information" + RESET << endl;
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
  vector<Directory> inner_src = {
      {"core", {}},
      {"core/entities", {"user.ts"}},
      {"core/errors", {}},
      {"core/repositories", {"IUserRepository.ts"}},
      {"core/services", {}},
      {"core/types", {}},
      {"core/usecases", {"userUsecases.ts"}},

      {"data", {}},
      {"data/datasources", {"prismaClient.ts"}},
      {"data/repositories", {"prismaUserRepository.ts"}},

      {"env", {"index.ts"}},

      {"http", {}},
      {"http/controller", {"userControler.ts"}},
      {"http/dtos", {}},
      {"http/routes", {"userRoutes.ts"}},
      {"http/schemas", {}},

      {"infra/services", {"jwtService.ts", "BcryptService.ts"}}};

  filesystem::create_directory(root_dir);

  for (const auto &dir : inner_src) {
    string full_path = root_dir + "/" + dir.directory;
    if (!filesystem::exists(full_path)) {
      filesystem::create_directories(full_path);
      cout << "Directory created: " << full_path << endl;
    } else {
      cout << "Directory already exists: " << full_path << endl;
    }

    for (const auto &fileToCreate : dir.files) {
      string file_path = full_path + "/" + fileToCreate;
      ofstream file(file_path);
      if (file.is_open()) {
        cout << "File created: " << file_path << endl;
        file.close();
      } else {
        cerr << "Failed to create file: " << file_path << endl;
      }
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

  // create files
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

string trim(const string &str) {
  size_t first = str.find_first_not_of(" \t\n");
  if (first == string::npos)
    return "";
  size_t last = str.find_last_not_of(" \t\n");
  return str.substr(first, last - first + 1);
}

void print_info(const string &label, const string &value) {
  cout << label << ": " << value << endl;
}

string exec(const char *cmd) {
  char buffer[128];
  string result = "";
  FILE *pipe = popen(cmd, "r");
  if (!pipe)
    throw runtime_error("popen() failed!");
  try {
    while (fgets(buffer, sizeof buffer, pipe) != NULL) {
      result += buffer;
    }
  } catch (...) {
    pclose(pipe);
    throw;
  }
  pclose(pipe);
  return result;
}

int osfetch() {

  string user = trim(exec("whoami"));
  string os = trim(exec("echo $(uname -n) $(uname -s)"));
  string kernel = trim(exec("uname -r"));
  string uptime = trim(exec("uptime -p"));
  string shell = trim(exec("basename $SHELL"));
  string cpu =
      trim(exec("lscpu | grep 'Model name' | sed 's/Model name: //g'"));
  string gpu = trim(exec("lspci | grep 'VGA' | sed 's/.*: //g'"));
  string memory =
      trim(exec("free -h | grep Mem | awk '{print $3 \"/\" $2}'"));
  string distro =
      trim(exec("lsb_release -d | sed 's/Description:\\s*//g'"));
  string model =
      trim(exec("cat /sys/devices/virtual/dmi/id/product_name"));
  string resolution =
      trim(exec("xdpyinfo | grep dimensions | awk '{print $2}'"));
  string de = trim(exec("echo $XDG_CURRENT_DESKTOP"));
  string wm_theme =
      "N/A"; // Obtaining the WM theme might require specific commands per WM
  string theme = trim(exec(
      "gsettings get org.gnome.desktop.interface gtk-theme | sed \"s/'//g\""));
  string icons = trim(exec(
      "gsettings get org.gnome.desktop.interface icon-theme | sed \"s/'//g\""));
  string term = trim(exec("echo $TERM"));
  string term_font =
      "N/A"; // This might require specific commands per terminal

  
  print_info("user", user);
  print_info("OS", os);
  print_info("Host", model);
  print_info("Kernel", kernel);
  print_info("Uptime", uptime);
  print_info("Shell", shell);
  print_info("Resolution", resolution);
  print_info("DE", de);
  print_info("WM Theme", wm_theme);
  print_info("Theme", theme);
  print_info("Icons", icons);
  print_info("Terminal", term);
  print_info("Terminal Font", term_font);
  print_info("CPU", cpu);
  print_info("GPU", gpu);
  print_info("Memory", memory);

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
  vector<string> inner_src = {"api",   "components", "hooks", "types",
                              "utils", "tests",      "views"};

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
