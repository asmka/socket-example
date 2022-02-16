#include "./socket/streamutil.h"
#include "./socket/unixsock.h"
#include <boost/program_options.hpp>
#include <cstdlib>
#include <exception>
#include <iostream>

namespace po = boost::program_options;

int main(int argc, char *argv[]) {
  std::string sockpath{};
  std::string senddata{};

  // Parse arguments
  {
    // Command options
    po::options_description opt_desc("options");
    opt_desc.add_options()("help,h", "Show this help message");

    po::positional_options_description pos_desc;
    pos_desc.add("sockpath", 1);
    pos_desc.add("senddata", 1);

    // Verify
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

    // Extract <sockpath> <senddata> argument
    auto non_opts =
        po::collect_unrecognized(parsed.options, po::include_positional);
    if (non_opts.size() != 2) {
      const std::string cmd{argv[0]};
      std::cout << "Usage: " << cmd << " [options] <sockpath> <senddata>"
                << std::endl;
      exit(EXIT_FAILURE);
    }
    sockpath = non_opts[0];
    senddata = non_opts[1];
  }

  // Main processing
  try {
    int sockfd = CreateUnixStreamSocket();
    ConnectSocket(sockfd, sockpath);
    write(sockfd, senddata.c_str(), senddata.size());
    close(sockfd);
  } catch (std::exception &exc) {
    std::cout << exc.what() << std::endl;
    std::exit(EXIT_FAILURE);
  }

  return 0;
}
