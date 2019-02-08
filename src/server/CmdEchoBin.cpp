#include "CmdEchoBin.hpp"

void CmdEchoBin::start(const std::vector<std::string> & /*args*/) {
  _session->readBinary(getAsCallback(&CmdEchoBin::readInputAsBin));
}

void CmdEchoBin::readInputAsBin(std::shared_ptr<std::vector<char>> input) {
  _session->writeBinary(input);
}
