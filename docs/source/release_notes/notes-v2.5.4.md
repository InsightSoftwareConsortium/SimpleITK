# SimpleITK Release v2.5.4


To upgrade to this Python binary package run:
```pip install --upgrade --pre simpleitk --find-links https://github.com/SimpleITK/SimpleITK/releases/tag/v2.5.4```



**What's Changed**
* Update FindR to detect R.dll on Windows by @Artur-man and @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2546
* Update ITK Superbuild version to 5.4.6 by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2570


**Bug Fixes**

* Fixed `FindR.cmake` to correctly detect `R.dll` on Windows when building the R package with a MinGW/Rtools toolchain.
* Fixed macOS package builds by replacing the deprecated `macos-13` CI runner with `macos-15-intel`.

**Bug Fixes from ITK 5.4.6**

* Updated GDCM to 2026-03-10 upstream snapshot.


**Security Fixes**

* Addresses a memory leak vulnerability (CVE-2026-3650, GHSA-42p8-rv8p-8h4j) in the GDCM library when parsing malformed DICOM files with non-standard VR types in file meta information. A maliciously crafted file can trigger a denial-of-service condition via heap exhaustion. The fix is contained in ITK 5.4.6.



**Full Changelog**: https://github.com/SimpleITK/SimpleITK/compare/v2.5.3...v2.5.4
