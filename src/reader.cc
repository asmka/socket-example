#include "streamutil.h"
#include "unixsock.h"
#include <boost/program_options.hpp>
#include <cstdlib>
#include <exception>
#include <iostream>

namespace po = boost::program_options;

int main(int argc, char *argv[]) {
  std::string sockpath{};

  // Command options
  po::options_description opt_desc("options");
  opt_desc.add_options()("help,h", "show this help message");

  po::positional_options_description pos_desc;
  pos_desc.add("socket", 1);

  // Verify
  {
    po::variables_map vm;
    auto parsed = po::parse_command_line(argc, argv, opt_desc);
    try {
      po::store(parsed, vm);
      po::notify(vm);
    } catch (po::error &err) {
      std::cerr << err.what() << std::endl;
      std::exit(EXIT_FAILURE);
    }

    // -h --help option
    if (vm.count("help")) {
      std::cout << opt_desc << std::endl;
      exit(EXIT_SUCCESS);
    }

    // Extract <sockpath> argument
    auto non_opts =
        po::collect_unrecognized(parsed.options, po::include_positional);
    if (non_opts.size() != 1) {
      std::cout << "Usage: reader [options] <sockpath>" << std::endl;
      exit(EXIT_FAILURE);
    }
    sockpath = *(non_opts.begin());
  }

  // Main process
  try {
    int sockfd = CreateUnixStreamSocket();
    BindUnixSocket(sockfd, sockpath);
    ListenSocket(sockfd);
  } catch (std::exception &exc) {
    std::cout << exc.what() << std::endl;
    std::exit(EXIT_FAILURE);
  }

  return 0;
}
