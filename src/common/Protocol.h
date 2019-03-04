#pragma once

namespace protocol {

namespace command {

enum { Exit, Echo, EchoBin, GetFile };

const char *names[] = {"EXIT", "ECHO", "ECHO_BIN", "GET_FILE"};

} // namespace command

} // namespace protocol