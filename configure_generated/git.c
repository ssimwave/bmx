#include "git.h"

bool bmx_git_IsPopulated() {
    return true;
}
bool bmx_git_AnyUncommittedChanges() {
    return false;
}
const char* bmx_git_AuthorName() {
    return "Tareq A. Siraj";
}
const char* bmx_git_AuthorEmail() {
    return "tsiraj@imax.com";
}
const char* bmx_git_CommitSHA1() {
    return "346bab6eab30d4d13fa761b330666bc7fed6d130";
}
const char* bmx_git_CommitDate() {
    return "2024-03-01 17:02:20 -0500";
}
const char* bmx_git_CommitSubject() {
    return "Add configure script generated files";
}
const char* bmx_git_CommitBody() {
    return "";
}
const char* bmx_git_Describe() {
    return "v1.2-2-g346bab6e";
}
const char* bmx_git_Branch() {
    return "ssimwave_v1.2_migrate_patches";
}
const char* bmx_git_DescribeTag() {
    return "v1.2-2-g346bab6e";
}
