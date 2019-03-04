#include "CmdGetFile.hpp"

void CmdGetFile::start(const std::vector<std::string> &args) {
  if (args.empty())
    return;
  _session->writeFile(args[0]);
}
