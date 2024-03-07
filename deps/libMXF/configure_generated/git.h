#pragma once
// git.h
// https://raw.githubusercontent.com/andrew-hardin/cmake-git-version-tracking/master/git.h
//
// Released under the MIT License.
// https://raw.githubusercontent.com/andrew-hardin/cmake-git-version-tracking/master/LICENSE

#include <stdbool.h>

#ifdef __cplusplus
#define GIT_VERSION_TRACKING_EXTERN_C_BEGIN extern "C" {
#define GIT_VERSION_TRACKING_EXTERN_C_END }
#else
#define GIT_VERSION_TRACKING_EXTERN_C_BEGIN
#define GIT_VERSION_TRACKING_EXTERN_C_END
#endif

// Don't mangle the C function names if included in a CXX file.
GIT_VERSION_TRACKING_EXTERN_C_BEGIN

/// Is the metadata populated? 
//
/// We may not have metadata if there wasn't a .git directory
/// (e.g. downloaded source code without revision history).
bool libmxf_git_IsPopulated();

/// Were there any uncommitted changes that won't be reflected
/// in the CommitID?
bool libmxf_git_AnyUncommittedChanges();

/// The commit author's name.
const char* libmxf_git_AuthorName();

/// The commit author's email.
const char* libmxf_git_AuthorEmail();

/// The commit SHA1.
const char* libmxf_git_CommitSHA1();

/// The ISO8601 commit date.
const char* libmxf_git_CommitDate();

/// The commit subject.
const char* libmxf_git_CommitSubject();

/// The commit body.
const char* libmxf_git_CommitBody();

/// The commit describe.
const char* libmxf_git_Describe();

/// The symbolic reference tied to HEAD.
const char* libmxf_git_Branch();

/// The commit describe relative to matching tag.
const char* libmxf_git_DescribeTag();

GIT_VERSION_TRACKING_EXTERN_C_END
#undef GIT_VERSION_TRACKING_EXTERN_C_BEGIN
#undef GIT_VERSION_TRACKING_EXTERN_C_END

#ifdef __cplusplus

/// This is a utility extension for C++ projects.
/// It provides a "git" namespace that wraps the
/// C methods in more(?) ergonomic types.
///
/// This is header-only in an effort to keep the
/// underlying static library C99 compliant.


// We really want to use std::string_view if it appears
// that the compiler will support it. If that fails,
// revert back to std::string.
#define GIT_VERSION_TRACKING_CPP_17_STANDARD 201703L
#if __cplusplus >= GIT_VERSION_TRACKING_CPP_17_STANDARD
#define GIT_VERSION_USE_STRING_VIEW 1
#else
#define GIT_VERSION_USE_STRING_VIEW 0
#endif


#if GIT_VERSION_USE_STRING_VIEW
#include <cstring>
#include <string_view>
#else
#include <string>
#endif

namespace libmxf_git {

#if GIT_VERSION_USE_STRING_VIEW
using StringOrView = std::string_view;
#else
typedef std::string StringOrView;
#endif

namespace internal {

/// Short-hand method for initializing a std::string or std::string_view given a C-style const char*.
const StringOrView InitString(const char* from_c_interface) {
  #if GIT_VERSION_USE_STRING_VIEW
    return StringOrView { from_c_interface, std::strlen(from_c_interface) };
  #else
    return std::string(from_c_interface);
  #endif
}

}  // namespace internal

inline bool IsPopulated() {
  return libmxf_git_IsPopulated();
}
inline bool AnyUncommittedChanges() {
  return  libmxf_git_AnyUncommittedChanges();
}
inline const StringOrView& AuthorName() {
  static const StringOrView kValue = internal::InitString(libmxf_git_AuthorName());
  return kValue;
}
inline const StringOrView AuthorEmail() {
  static const StringOrView kValue = internal::InitString(libmxf_git_AuthorEmail());
  return kValue;
}
inline const StringOrView CommitSHA1() {
  static const StringOrView kValue = internal::InitString(libmxf_git_CommitSHA1());
  return kValue;
}
inline const StringOrView CommitDate() {
  static const StringOrView kValue = internal::InitString(libmxf_git_CommitDate());
  return kValue;
}
inline const StringOrView CommitSubject() {
  static const StringOrView kValue = internal::InitString(libmxf_git_CommitSubject());
  return kValue;
}
inline const StringOrView CommitBody() {
  static const StringOrView kValue = internal::InitString(libmxf_git_CommitBody());
  return kValue;
}
inline const StringOrView Describe() {
  static const StringOrView kValue = internal::InitString(libmxf_git_Describe());
  return kValue;
}
inline const StringOrView Branch() {
  static const StringOrView kValue = internal::InitString(libmxf_git_Branch());
  return kValue;
}
inline const StringOrView DescribeTag() {
  static const StringOrView kValue = internal::InitString(libmxf_git_DescribeTag());
  return kValue;
}

}  // namespace libmxf_git


// Cleanup our defines to avoid polluting.
#undef GIT_VERSION_USE_STRING_VIEW
#undef GIT_VERSION_TRACKING_CPP_17_STANDARD

#endif  // __cplusplus