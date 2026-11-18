#!/bin/sh
#
# librtdebug - C++ thread-safe runtime debugging library
#              https://github.com/hzdr-MedImaging/librtdebug
#
# Copyright (C) 2003-2026 hzdr.de and contributors
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# Builds the conda-forge recipe (recipe.yaml) with rattler-build from this checkout
# instead of the release archive, to test it before it is submitted to conda-forge or
# a new version is released.
#
# usage: conda.recipe/build-local.sh [output directory]
#        (default output directory: build-conda in the checkout)
#
# The variants of conda-forge (compilers, C library, ...) are taken from the package
# conda-forge-pinning (conda install -c conda-forge conda-forge-pinning) in the
# active environment, or from the file given in CONDA_FORGE_PINNING.
#

set -e

here=$(cd "$(dirname "$0")" && pwd)
top=$(cd "${here}/.." && pwd)
output=${1:-${top}/build-conda}

pinning=${CONDA_FORGE_PINNING:-${CONDA_PREFIX:-}/conda_build_config.yaml}
if [ ! -f "${pinning}" ]; then
  echo "ERROR: no variant configuration of conda-forge found (${pinning})," >&2
  echo "       install conda-forge-pinning or set CONDA_FORGE_PINNING" >&2
  exit 1
fi

tmp=$(mktemp -d)
trap 'rm -rf "${tmp}"' EXIT

# the recipe with this checkout as source
mkdir -p "${tmp}/librtdebug"
sed -e "s|^  url: .*|  path: ${top}|" \
    -e "/^  sha256: /d" \
    -e "/^  # curl -sL /d" \
    "${here}/recipe.yaml" > "${tmp}/librtdebug/recipe.yaml"

# the channel (conda-forge) is set by the variant configuration (channel_sources)
rattler-build build --recipe-dir "${tmp}" -m "${pinning}" --output-dir "${output}"
