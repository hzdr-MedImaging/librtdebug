# conda-forge recipe

[recipe.yaml](recipe.yaml) is the recipe of the conda-forge package
`librtdebug`, in the format of [rattler-build](https://rattler.build). It is
the source of the recipe submitted to
[conda-forge/staged-recipes](https://github.com/conda-forge/staged-recipes)
and later held by the feedstock `conda-forge/librtdebug-feedstock`. The
recipes of the packages of libmedio, which uses librtdebug, are in
[libmedio/conda-forge](https://github.com/hzdr-MedImaging/libmedio/tree/main/conda-forge).

- The package holds the shared library and the headers (conda-forge ships no
  static libraries).
- Windows is skipped.

## Test the recipe locally

With rattler-build and the variant configuration of conda-forge
(`conda install -c conda-forge rattler-build conda-forge-pinning`):

```bash
conda.recipe/build-local.sh
```

The script builds the recipe with this checkout as source instead of the
release archive (into `build-conda/`).

## Release

1. Create a GitHub release with the tag of the version (`PKG_VERSION` of
   `CMakeLists.txt`, without `v`, e.g. `3.0.0`).
2. For the first submission to conda-forge, set the checksum of the archive
   in the recipe:
   ```bash
   curl -sL https://github.com/hzdr-MedImaging/librtdebug/archive/refs/tags/<version>.tar.gz | sha256sum
   ```
   Afterwards, the bot of conda-forge opens a pull request with the new
   version and checksum in the feedstock for every release.
