#pragma once

namespace protocol {

namespace command {

enum { Exit, Echo, EchoBin, GetFile, Version, Ls };

extern const char *names[];

} // namespace command

enum ErrorCode { Success = 0, EndStrList, BadParameter, InvalidPath, IllegalPath };

} // namespace protocol