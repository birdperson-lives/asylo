/*
 *
 * Copyright 2018 Asylo authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef ASYLO_PLATFORM_PRIMITIVES_TEST_TEST_BACKEND_H_
#define ASYLO_PLATFORM_PRIMITIVES_TEST_TEST_BACKEND_H_

#include <memory>

#include "asylo/platform/primitives/untrusted_primitives.h"
#include "asylo/test/util/status_matchers.h"

namespace asylo {
namespace primitives {
namespace test {

// An abstract factory class loading a test enclave.
class TestBackend {
 public:
  // Factory method to access TestBackend, with different implementation for
  // each sub-class.
  static TestBackend *Get();

  TestBackend() = default;
  virtual ~TestBackend() = default;

  // Loads an instance of an enclave, aborting on failure.
  std::shared_ptr<EnclaveClient> LoadTestEnclaveOrDie(
      std::unique_ptr<EnclaveClient::ExitCallProvider> exit_call_provider) {
    auto result = LoadTestEnclave(std::move(exit_call_provider));
    EXPECT_THAT(result.status(), IsOk());
    return result.ValueOrDie();
  }

  // Allows to ignore memory leak checking on abort tests. Off by default.
  virtual bool LeaksMemoryOnAbort() { return false; }

 private:
  // Loads an instance of an enclave, aborting on failure.
  virtual StatusOr<std::shared_ptr<EnclaveClient>> LoadTestEnclave(
      std::unique_ptr<EnclaveClient::ExitCallProvider> exit_call_provider) = 0;
};

}  // namespace test
}  // namespace primitives
}  // namespace asylo

#endif  // ASYLO_PLATFORM_PRIMITIVES_TEST_TEST_BACKEND_H_
