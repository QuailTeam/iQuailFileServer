#pragma once

namespace protocol {

namespace command {

enum { Exit, Echo, EchoBin, GetFile, Version };

extern const char *names[];

} // namespace command

enum ErrorCode { Success = 0, BadParameter, InvalidPath, IllegalPath };

} // namespace protocol