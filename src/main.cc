#include <boost/program_options.hpp>
#include <cstdlib>
#include <exception>
#include <iostream>

namespace po = boost::program_options;

int main(int argc, char *argv[]) {
  {
    // Command options
    po::options_description description("option");
    description.add_options()("help,h", "show this help message");

    po::variables_map vm;
    try {
      store(parse_command_line(argc, argv, description), vm);
    } catch (po::error &err) {
      std::cerr << err.what() << std::endl;
      std::exit(EXIT_FAILURE);
    }

    po::notify(vm);

    if (vm.count("help")) {
      std::cout << description << std::endl;
      exit(EXIT_SUCCESS);
    }

    // try {
    //   int sfd = createUnixStreamSocket();
    //   bind(sfd,

    // } catch (std::exception exc) {
    //   std::cout << exc.what() << std::endl;
    //   std::exit(EXIT_FAILURE);
    // }

    return 0;
  }
}
