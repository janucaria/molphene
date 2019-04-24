#include <sstream>

#include "application.hpp"

// NOLINTNEXTLINE(bugprone-exception-escape)
auto main(int argc, char* argv[]) -> int
{
  auto app = molphene::application{};

  app.setup();

  if(argc > 1) {
    std::ifstream pdbfile(argv[1]);
    if(pdbfile.is_open()) {
      std::cout << "openfile success!" << std::endl;
      struct close_guard {
        void operator()(std::ifstream* ptr) const
        {
          ptr->close();
        }
      };
      const auto close = std::unique_ptr<std::ifstream, close_guard>{&pdbfile};

      const auto strjson =
       std::string{std::istreambuf_iterator<char>{pdbfile}, {}};

      app.open_pdb_data(strjson);
    } else {
      std::cout << "openfile failure!" << std::endl;
    }
  }

  app.run();

  return 0;
}
