/*
 * Copyright 2017 Google Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef LEARNING_GENOMICS_DEEPVARIANT_VENDOR_STATUSOR_CLIF_CONVERTERS_H_
#define LEARNING_GENOMICS_DEEPVARIANT_VENDOR_STATUSOR_CLIF_CONVERTERS_H_

#include "clif/python/postconv.h"
#include "clif/python/types.h"
#include "deepvariant/util/vendor/statusor.h"

namespace clif {

// Note: comment below is an instruction to CLIF.
// CLIF use `nucleus::StatusOr` as StatusOr
// CLIF use `::tensorflow::Status` as Status

void ErrorFromStatus(const tensorflow::Status& status);

PyObject* Clif_PyObjFrom(const tensorflow::Status& c, py::PostConv);

template <typename T>
PyObject* Clif_PyObjFrom(const nucleus::StatusOr<T>& c, py::PostConv pc) {
  if (!c.ok()) {
    ErrorFromStatus(c.status());
    return nullptr;
  }
  return Clif_PyObjFrom(c.ValueOrDie(), pc.Get(0));
}

template <typename T>
PyObject* Clif_PyObjFrom(nucleus::StatusOr<T>&& c,
                         py::PostConv pc) {  // NOLINT:c++11
  if (!c.ok()) {
    ErrorFromStatus(c.status());
    return nullptr;
  }
  return Clif_PyObjFrom(c.ConsumeValueOrDie(), pc.Get(0));
}

}  // namespace clif

#endif  // LEARNING_GENOMICS_DEEPVARIANT_VENDOR_STATUSOR_CLIF_CONVERTERS_H_
