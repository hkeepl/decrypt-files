#include <fstream>
#include <sstream>

int main(int argc, char *argv[]) {
  if (argc < 3) {
    exit(-1);
  }
  std::string file = argv[1];
  std::string decrypt_file = argv[2];

  std::ifstream ifs(file, std::ios::binary);
  std::stringstream buffer;
  if (ifs.is_open()) {
    buffer << ifs.rdbuf();
    ifs.close();
  }

  std::ofstream ofs(decrypt_file, std::ios::binary);
  if (ofs.is_open()) {
    ofs << buffer.str();
    ofs.close();
  }

  return 0;
}
