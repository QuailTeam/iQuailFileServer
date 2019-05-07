#pragma once

namespace protocol {

namespace command {

enum { Exit, Echo, EchoBin, GetFile };

extern const char *names[];

} // namespace command

enum ErrorCode { Success = 0, InvalidPath, IllegalPath };

} // namespace protocol