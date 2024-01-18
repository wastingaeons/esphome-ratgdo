#pragma once
#include <cstdint>
#include <functional>
#include "macros.h"
#include "observable.h"

#define ESP_LOG1 ESP_LOGD
#define ESP_LOG2 ESP_LOGD


namespace esphome {
namespace ratgdo {

namespace protocol {

struct SetRollingCodeCounter { uint32_t counter; };
struct GetRollingCodeCounter {};
struct SetClientID { uint64_t client_id; };
struct QueryStatus{};
struct QueryOpenings{};


// a poor man's sum-type, because C++
SUM_TYPE(Args,
    (SetRollingCodeCounter, set_rolling_code_counter),
    (GetRollingCodeCounter, get_rolling_code_counter),
    (SetClientID, set_client_id),
    (QueryStatus, query_status),
    (QueryOpenings, query_openings),
)


struct RollingCodeCounter { observable<uint32_t>* value; };

SUM_TYPE(Result,
    (RollingCodeCounter, rolling_code_counter),
)

} // namespace protocol
} // namespace ratgdo
} // namespace esphome
