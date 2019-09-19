#pragma once

namespace protocol {

namespace command {

enum { Exit, GetFile, Version, Ls, NbrFiles };

extern const char *names[];

} // namespace command

enum ErrorCode { Success = 0, EndStrList, BadParameter, InvalidPath, IllegalPath };

} // namespace protocol