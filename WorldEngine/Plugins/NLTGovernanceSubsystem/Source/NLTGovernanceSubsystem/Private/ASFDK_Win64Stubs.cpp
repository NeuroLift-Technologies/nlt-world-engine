// ASFDK Win64 stub implementations for Unreal plugin builds
// Provides inline stubs for ASFDK methods so the NLTGovernanceSubsystem
// can link on Win64 without requiring the full ASFDK-C++ CMake build.
// TODO: Replace with proper Win64 ASFDK library build when available.

#if defined(_WIN32)

#pragma warning(disable: 4668)

#include <string>
#include <memory>
#include <optional>
#include <vector>
#include <chrono>

#include "asfdk/ASFDK.h"

// Pillar headers (for return types)
#include "toi/TOITypes.h"
#include "otoi/OTOITypes.h"
#include "rrt/RRTTypes.h"
#include "sleepwalker/SleepwalkerTypes.h"

namespace asfdk {

ASFDK::ASFDK() = default;
ASFDK::~ASFDK() = default;

toi::TOIDocument ASFDK::parseTOI(const nlohmann::json& /*json*/) {
    return toi::TOIDocument{};
}

tl::expected<toi::TOIDocument, toi::TOIError> ASFDK::safeParseTOI(const nlohmann::json& /*json*/) {
    toi::TOIError err{};
    err.code = toi::TOIError::Code::UnknownError;
    return tl::unexpected(err);
}

bool ASFDK::validateTOI(const toi::TOIDocument& /*doc*/) {
    return false;
}

toi::TOIDocument ASFDK::resolveTOI(std::vector<toi::TOIDocument> docs) {
    return docs.empty() ? toi::TOIDocument{} : docs[0];
}

std::string ASFDK::canonicalize(const std::string& json) {
    return json;
}

otoi::OtoiCharter ASFDK::parseCharter(const nlohmann::json& /*json*/) {
    return otoi::OtoiCharter{};
}

tl::expected<otoi::OtoiCharter, otoi::OtoiError> ASFDK::safeParseCharter(const nlohmann::json& /*json*/) {
    otoi::OtoiError err;
    err.code = otoi::OtoiErrorCode::Parse;
    err.message = "ASFDK stub";
    return tl::unexpected(err);
}

otoi::EffectivePolicy ASFDK::honor(const otoi::OtoiCharter& /*charter*/, const otoi::HonorOptions& /*options*/) {
    return otoi::EffectivePolicy{};
}

nlohmann::json ASFDK::propagate(const otoi::EffectivePolicy& /*policy*/, const std::string& /*agentId*/) {
    return nlohmann::json{};
}

rrt::CrisisAssessment ASFDK::assessMessage(const std::string& /*message*/) {
    return rrt::CrisisAssessment{};
}

sleepwalker::InteractionAssessment ASFDK::assessInteraction(
    const std::string& /*userInput*/,
    const std::vector<std::string>& /*sessionHistory*/,
    const std::optional<std::string>& /*userId*/
) {
    return sleepwalker::InteractionAssessment{};
}

void ASFDK::maintainContinuity(const std::string& /*userId*/, nlohmann::json /*sessionData*/) {
    // Stub
}

Envelope ASFDK::process(const std::string& /*input*/, const std::string& channel) {
    Envelope e;
    e.trusted = false;
    e.channel = channel;
    e.consentLevel = "none";
    e.payload = nlohmann::json{{"error", "Win64 ASFDK stub"}};
    e.flagged = true;
    e.flagReason = "ASFDK not built for Win64";
    return e;
}

AssessmentResult ASFDK::assess(const std::string& /*input*/) {
    return AssessmentResult{};
}

FoundationStatus ASFDK::getStatus() {
    return FoundationStatus{};
}

} // namespace asfdk

namespace sleepwalker {
    SleepwalkerProtocol::SleepwalkerProtocol() 
        : m_stateDetector(),
          m_consentManager(nlohmann::json::object()),
          m_continuityManager() {}
    SleepwalkerProtocol::SleepwalkerProtocol(const Options& options) 
        : m_stateDetector(),
          m_consentManager(options.userToi),
          m_continuityManager(options.storagePath) {}

    // Win64 link-time member stubs (no-op; real implementations come from the
    // full ASFDK-C++ CMake build on Linux / when libasfdk is built for Win64).
    StateDetector::StateDetector() = default;
    ConsentManager::ConsentManager(const nlohmann::json& /*userToi*/) {}
    ContinuityManager::ContinuityManager(const std::string& /*storagePath*/) {}
} // namespace sleepwalker

namespace rrt {
    // Required by asfdk::ASFDK::~ASFDK() which holds unique_ptr<RRTAdvocate>.
    RRTAdvocate::~RRTAdvocate() = default;
} // namespace rrt

#endif // defined(_WIN32)